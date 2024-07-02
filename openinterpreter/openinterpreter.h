#pragma once
#include <string>

#include "openlexer.h"

// Call this function to handle all of the interpreting. Useful if you want to quickly set up an environment, without worrying about what goes on inside.
// - source : The path to the source file -- Expected to be an OI Assembly file.
int runInterpreter(std::string source);