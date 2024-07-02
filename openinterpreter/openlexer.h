#pragma once
#include <string>
#include <vector>

enum class TokenType {
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    Keyword,
    BinaryOperator,
    Error,
};

typedef struct {
    int line, col;

    TokenType type;
    std::string value;
} Token;

#define NULLTOKEN Token{-1, -1, TokenType::Error, ""}

class Lexer {
    private:
        std::string source;
        unsigned int line, col;

        char getCurrent();
        char getCurrentAndConsume();

        bool isEmpty();
        bool charInString(std::string s, char c);

        Token buildNumber();
        Token buildString();
        Token buildKeyword();
        Token buildOperator();

        std::string numberStart       = "0123456789";
        std::string numberBody        = numberStart + ".";
        std::string wordStart         = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string wordBody          = wordStart + numberStart;
        std::string operators         = "+-*/%=<>";
        std::string whitespace        = "\n\t ";
        std::string stringTerminators = "\"'";

        bool performAnalysis();

    public:
        std::vector<Token> tokens;

        Lexer(std::string source);
        ~Lexer();
};