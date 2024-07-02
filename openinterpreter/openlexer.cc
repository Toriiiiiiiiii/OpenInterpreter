#include "openlexer.h"
#include <cassert>
#include <string>

Lexer::Lexer(std::string source) {
    this->source = source;
    this->tokens = {};
    this->line = this->col = 1;

    this->performAnalysis();
}

Lexer::~Lexer() {
    this->line = this->col = 0;
    this->source = "";
    this->tokens = {};
}

char Lexer::getCurrent() {
    if(isEmpty()) return '\0';

    return source[0];
}

char Lexer::getCurrentAndConsume() {
    if(isEmpty()) return '\0';

    char result = source[0];

    source = source.substr(1);
    col++;

    if(result == '\n') {
        col = 1;
        line++;
    }

    return result;
}

bool Lexer::isEmpty() {
    return (source.length() == 0)? true : false;
}

bool Lexer::charInString(std::string s, char c) {
    return (s.find(c) != std::string::npos)? true : false;
}

Token Lexer::buildNumber() {
    int tokenStartLine = line;
    int tokenStartCol = col;

    unsigned int numDots = 0;
    std::string value = "";

    while( charInString(numberBody, getCurrent()) ) {
        if(getCurrent() == '.') numDots++;

        value += getCurrentAndConsume();
    }

    if( numDots > 1 ) {
        fprintf(stderr, "[%d, %d] Lexer: Invalid float literal '%s'.\n", tokenStartLine, tokenStartCol, value.c_str());
        return NULLTOKEN;
    }

    if(numDots == 1) 
        return Token{tokenStartLine, tokenStartCol, TokenType::FloatLiteral, value};

    return Token{tokenStartLine, tokenStartCol, TokenType::IntegerLiteral, value};
}

Token Lexer::buildString() {
    int tokenStartLine = line;
    int tokenStartCol = col;
    char terminator = getCurrentAndConsume();

    std::string value = "";

    while( !isEmpty() && getCurrent() != terminator ) {
        value += getCurrentAndConsume();
    }

    if( isEmpty() ) {
        fprintf(stderr, "[%d, %d] Lexer: Unterminated String Literal.\n", tokenStartLine, tokenStartCol);
        return NULLTOKEN;
    }

    return Token{tokenStartLine, tokenStartCol, TokenType::StringLiteral, value};
}

Token Lexer::buildKeyword() {
    int tokenStartLine = line;
    int tokenStartCol = col;

    std::string value = "";

    while( charInString(wordBody, getCurrent()) ) {
        value += getCurrentAndConsume();
    }

    return Token{tokenStartLine, tokenStartCol, TokenType::Keyword, value};
}

Token Lexer::buildOperator() {
    int tokenStartLine = line;
    int tokenStartCol = col;

    std::string value = "";

    // Detect negative numbers
    if(source.size() >= 2 && source[0] == '-' && charInString(numberStart, source[1])) {
        getCurrentAndConsume();
        Token t = buildNumber();

        // Decrement column - the buildNumber() function will not encounter the "-" sign.
        t.col--;
        t.value = '-' + t.value;
        return t;
    }

    while( charInString(operators, getCurrent()) ) {
        value += getCurrentAndConsume();
    }

    return Token{tokenStartLine, tokenStartCol, TokenType::BinaryOperator, value};
}

bool Lexer::performAnalysis() {
    while(!isEmpty()) {
        char currentChar = getCurrent();

        if( charInString(whitespace, currentChar) ) {
            getCurrentAndConsume();
            continue;
        }

        if(charInString(numberStart, currentChar)) {
            Token t = buildNumber();

            if(t.type == TokenType::Error) return false;
            tokens.push_back(t);
        } else if(charInString(stringTerminators, currentChar)) {
            Token t = buildString();

            if(t.type == TokenType::Error) return false;
            tokens.push_back(t);
        } else if(charInString(wordStart, currentChar)) {
            tokens.push_back( buildKeyword() );
        } else if(charInString(operators, currentChar)) {
            tokens.push_back(buildOperator());
        } else {
            printf("[%d, %d] Lexer: Unrecognised character '%c'.\n", line, col, currentChar);
            return false;
        }
    }

    return true;
}