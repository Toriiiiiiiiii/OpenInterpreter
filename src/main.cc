#include <cstdio>
#include <pthread.h>
#include <vector>

#include "arguments.h"
#include "../openinterpreter/openinterpreter.h"

void printUsage(char **argv) {
    printf("Usage : %s <filename> [-h]\n", argv[0]);
}

int main(int argc, char **argv) {
    std::vector<ArgumentTemplate> usage;
    std::vector<Argument> args;
    ArgumentParser *argParser;

    int interpreterResult;
    int returnCode = 0;

    usage = {
        ArgumentTemplate{ARG_REQUIRED | ARG_POSITIONAL, "", "filename"},
        ArgumentTemplate{ARG_OPTIONAL | ARG_IMPLIED, "-h", "help"}
    };

    argParser = new ArgumentParser(argc, argv, usage);

    if(!argParser->parseArguments(args)) {
        printUsage(argv);

        returnCode = 1;
        goto cleanup;
    }

    if(argParser->argumentExists(args, "help")) {
        printUsage(argv);
        goto cleanup;
    }

    interpreterResult = runInterpreter( argParser->getArgByName(args, "filename").value );
    printf("Interpreter finished with code %d.\n", interpreterResult);
    returnCode = interpreterResult;

cleanup:
    delete argParser;
    return returnCode;
}