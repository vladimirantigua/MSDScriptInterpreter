//
//  main.cpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 1/19/21.
//
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <string>
#include "cmdline.h"


int main(int argc, char **argv) { // **argv  * first star mean string and second star ** mean array of string I can add a third star *** which mean array of string arrays but this is not done usually in main. String is an array of characters and array of string is a 2D array of characters ** two stars the number of star is the dimenssion of the array 1D or 2D or 3D array depending on the star * **  ***
// Catch::Session().run(1, argv);

    use_arguments(argc, argv);
    
    printf(" Test Completed :) !");
    
    // in main create a object representation for the constructor: with two numbers 42 + 2. =>
    // new add(new Num(42), new Num(2)); means: 42+2

    // return 0 means success and non 0 means failure in Unix
  return 0;
}

// we do not care about the coverage red marks here in main.cpp we are are only care for the test coverage in the expr.cpp and other .cpp files
