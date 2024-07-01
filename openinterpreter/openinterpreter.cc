#include "openinterpreter.h"

#include <string>
#include <cstdio>

#include <iostream>
#include <fstream>

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
    return 0;
}