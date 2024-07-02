#include "openinterpreter.h"

#include <string>
#include <cstdio>

#include <iostream>
#include <fstream>

void printToken(Token t) {
    printf("TOKEN{%d, %d, %d, %s}\n", t.line, t.col, (int)t.type, t.value.c_str());
}

std::string readFileContents(std::string path, bool& success) {
    success = true;
    std::ifstream file(path);

    if(!file.is_open()) { 
        success = false;
        return std::string(); 
    }

    std::string result;
    std::string line;
    while(std::getline(file, line)) {
        result += line + "\n";
    }

    return result;
}

int runInterpreter(std::string source) {
    bool fileReadSuccess;
    std::string contents = readFileContents(source, fileReadSuccess);

    std::cout << contents << std::endl;

    Lexer *lex = new Lexer(contents);

    for(Token t : lex->tokens) {
        printToken(t);
    }

    delete lex;
    return 0;
}