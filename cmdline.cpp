//
//  cmdline.cpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 1/19/21.

#define CATCH_CONFIG_RUNNER // need to be before the catch.h place it at the top: 
#include <iostream>
#include <string>
#include <stdio.h>
#include "cmdline.h"
#include "catch.h"
#include "expr.h"
#include <sstream>
#include <iomanip>
#include "parse.h"
#include "val.h"
#include "pointer.h"
#include "env.h"
#include "step.h"
#include "cont.h"


void use_arguments(int argc, char **argv){
    
    // we do not care about the coverage red marks here in cmdline.cpp we are are only care for the test coverage in the expr.cpp and other .cpp files
    
    //std::string argv
    //std::cout << argv[0] << std::endl; // file path
    //std::cout << argv[1] << std::endl; // argument passed = --help
    //std::cout << argv[2] << std::endl; // --testing
    //std::cout << argc << std::endl; // number of arguments = 2
    
    bool textExist = false;
    for(int i = 1; i < argc; i++){ // Start the loop at one because it needs
        //        std::cout << argv[i] << std::endl; // loop and print all the arguments  this is printing
        
        //If the next argument is "--help", then use_arguments should print to std::cout some help text that describes what arguments are allowed. The exact text is up to you. After printing the help text, it should exit immediately with exit(0). No further command-line argument should be inspected.
        if(argv[i] == std::string("--help")) {
            std::cout << "    You can use the following commands within this MSDScript program --help, --test, --print, --interp and --step: for a example to run the program and check if all test pass run the following command on the terminal: ./msdscript --test if want to interp run: ./msdcript --interp   " << std::endl;
            exit(0); // exit all the code
        }
        // If the argument is "--test", then use_arguments should print "Tests passed" on its own line and continue, but only if a "--test" argument has not been seen already. If "--test" has been seen before, use_arguments should print an error to std::cerr and exit with exit(1).
        
        //  Change your command-line handler from the first assignment so that passing "--test" causes all tests to be run. If "--test" is not provided, then your tests should not run. When running tests, if Catch::Session().run returns a non-0 value, then exit immediately with exit(1).
        else if(argv[i] == std::string("--test")) {
            if (Catch::Session().run(1, argv) != 0){
                exit(1);
            }
            
            if(textExist == false){ // if not seen before mark as true
                textExist = true;
            }
            else if(textExist == true){ // if  the text exist
                std::cerr<< "test argument has been seen already " << std::endl;
                exit(1); // exit
            }
            exit(0);
        }
        
        // INTERP:
        
        //--interp : accept a single expression on standard input, parse it, interp it, and print the result to standard output, exiting with a 0 status:
        else if(argv[i] == std::string("--interp")) {
            //            std::cout<< "INTERP CALL 2" << std::endl;
            
            
            //expr is what need to be passed from the which_day.cpp: 
           // std::string expr = "_let mtg = (" + content + ") _in mtg(" + argv[1] + ")\n";
//            std::stringstream s(expr);
            //PTR(Expr)
            PTR(Expr) y = parse_comparg(std::cin);
//            PTR(Expr) y = parse_comparg(s);
            //
            PTR(Val) v = y->interp(Env::empty);
            //            y = v->to_string();
            std::cout<< v->to_string() << std::endl;
            
            exit(0);
        }
        
        //--STEP:
        
        else if(argv[i] == std::string("--step")) {
            //            std::cout<< "step CALL 2" << std::endl;
            
            //PTR(Expr)
            PTR(Expr) y = parse_comparg(std::cin);
            //
            PTR(Val) v;
            v =   Step::interp_by_steps(y);
            
            //            y = v->to_string();
            std::cout<< v->to_string() << std::endl;
            
            exit(0);
        }
        
        // --PRINT:
        else if(argv[i] == std::string("--print")) {
            //            std::cout<< "PRINT SOMETHING" << std::endl;
            PTR(Expr) y = parse_comparg(std::cin);
            
            y->print(std::cout);
            
            exit(0);
        }
        
        //find out how to enable this pretty print:
        //        else if(argv[i] == std::string("--pretty_print")) {
        //            std::cout<< "PRINT SOMETHING" << std::endl;
        //            PTR(Expr) y = parse_comparg(std::cin);
        //
        //            y->pretty_print_at(std::cout,print_group_none);
        //
        //            exit(0);
        //        }
        
        // create a helper method for parse_interp here and call it in the else if -- interp
        //If the argument is any other string, use_arguments should print an error message to std::cerr and exit with exit(1).
        
        else {
            //        else (argv[i] != std::string("--test") || argv[i] != std::string("--help")) {
            std::cerr<< "Arguments is not either --help or --test or --interp " << std::endl;
            //        exit(0); // exit // by not having the exit(0) exit(1) the loop will continue running and find out if there is an argument like --help or --test
        }
    }
}


//  if (Catch::Session().run(1, argv) == 0); // == 0; this // only use this when using the --test
//        std::cout<< "Tests passed " << std::endl;


// MAKEFILE FOR THIS PROJECT:

//INCS = cmdline.h expr.h parse.h val.h pointer.h env.h step.h cont.h
//INCSTEST = exec.h
//SRCS = main.cpp cmdline.cpp test.cpp expr.cpp parse.cpp val.cpp env.cpp step.cpp cont.cpp
//SRCSTEST = test_msdscript.cpp exec.cpp
//msdscript: $(SRCS) $(INCS) ; c++ --std=c++14 -O2 -fsanitize=undefined -fno-sanitize-recover=undefined -o msdscript $(SRCS)
//test_msdscript: $(SRCSTEST) $(INCSTEST) ; c++ --std=c++14 -O2 -o test_msdscript $(SRCSTEST)
//.PHONY: test
//test: msdscript
//    ./msdscript --test


// instruction to make a MakeFile:
//it should be in the same folder

//vi Makefile in the same folder
//
//vi would open a file
//
//then type i
//
//this would take you to insert mode
//add the .cpp and .h files see sample below:

//INCS = cmdline.h expr.h parse.h val.h pointer.h env.h step.h cont.h
//INCSTEST = exec.h
//SRCS = main.cpp cmdline.cpp test.cpp expr.cpp parse.cpp val.cpp env.cpp step.cpp cont.cpp
//SRCSTEST = test_msdscript.cpp exec.cpp
//msdscript: $(SRCS) $(INCS) ; c++ --std=c++14 -O2 -fsanitize=undefined -fno-sanitize-recover=undefined -o msdscript $(SRCS)
//test_msdscript: $(SRCSTEST) $(INCSTEST) ; c++ --std=c++14 -O2 -o test_msdscript $(SRCSTEST)
//.PHONY: test
//test: msdscript
//    ./msdscript --test

//then hit escape then type :wq
//this would save the above code in Makefile,
//to compile in the terminal run: "make"


