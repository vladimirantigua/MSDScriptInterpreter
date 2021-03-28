//
//  textHelp.cpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 1/19/21.

#define CATCH_CONFIG_RUNNER // need to be before the catch.h place it at the top: 
#include <iostream>
#include <string>
#include <stdio.h>
#include "Header.h"
#include "catch.h"
#include "expr.h"
#include <sstream>
#include <iomanip>
#include "parse.h"
#include "val.h"
#include "pointer.h"


void use_arguments(int argc, char **argv){
    
// we do not care about the coverage red marks here in texthelp.cpp we are are only care for the test coverage in the expr.cpp
    
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
            std::cout << "this is the --help message ... " << std::endl;
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
           
            //PTR(Expr)
            PTR(Expr) y = parse_comparg(std::cin);
            //
        PTR(Val) v = y->interp();
            y = v->to_expr();
            std::cout<< y->to_string() << std::endl;
            
            exit(0);
        }

        // --print:
        else if(argv[i] == std::string("--print")) {
//            std::cout<< "PRINT SOMETHING" << std::endl;
            PTR(Expr) y = parse_comparg(std::cin);
            
            y->print(std::cout);
            
            exit(0);
        }
        
        //ask the instructor how to enable this pretty print: 
//        else if(argv[i] == std::string("--pretty_print")) {
////            std::cout<< "PRINT SOMETHING" << std::endl;
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


// ADD THE TEST HERE






// add a else that will continue checking if --test or help is in the second argument can still show it and bypass the first argument or sencond until it find an argument that is the one like --test or --help
//    else {
//
//    }

//  if (Catch::Session().run(1, argv) == 0); // == 0; this // only use this when using the --test
//        std::cout<< "Tests passed " << std::endl;
        // comment line 34
        // call it here to run THE TEST CATCH:
//        new Add(newNum(42),new Num(2));
        

// TO MAKEFILE FOR THIS homework:
//INCS = Header.h
//SRCS = main.cpp textHelp.cpp
//msdscript: $(SRCS) $(INCS) ; c++ --std=c++14 -O2 -o msdscript $(SRCS)


// instruction to make a MakeFile:
//it should be in the same folder

//vi Makefile in the same folder
//
//vi would open a file
//
//then type i
//
//this would take you to insert mode
//
//INCS = Header.h
//SRCS = main.cpp textHelp.cpp
//msdscript: $(SRCS) $(INCS)
//  c++ --std=c++14 -02 -o msdscript $(SRCS)
//
//copy paste above content
//
//then hit escape then type :wq
//
//this would save the above code in Makefile, then just do make
//
//
//so I will do all of that inside the same place my Header.h and main.cppand textHelp.cpp folder right
//yes, correct


//git push -u origin main

//think the make file was created
//10:17
//how can I test it to see it is right?
//
//Sushmitha  10:18 PM
//run make
//
//
//
//
//
//10:18
//then do ./msdscript
//
//Vladimir a  10:18 PM
//so type in the terminal
//10:18
//run make
//10:18
//the type
//10:18
//./msdscript
//
//Sushmitha  10:18 PM
//yes..
//
//Vladimir a  10:19 PM
//when type run make I get
//10:19
//command not found
//10:20
//(base) mj@Vladimirs-MBP MSDscript Command Line % vi Makefile
//(base) mj@Vladimirs-MBP MSDscript Command Line % ls
//Header.h    Makefile    main.cpp    textHelp.cpp
//(base) mj@Vladimirs-MBP MSDscript Command Line % run make
//zsh: command not found: run
//
//Sushmitha  10:20 PM
//just make
//
//Vladimir a  10:20 PM
//just type make then enter?
//
//Sushmitha  10:20 PM
//Sushmithas-MBP:HW1 sushmitha$ make
//c++ --std=c++14 -O2 -o msdscript main.o cmdline.o
//Sushmithas-MBP:HW1 sushmitha$
//10:21
//is make succeeds you will get the above output
//
//Vladimir a  10:22 PM
//(base) mj@Vladimirs-MBP MSDscript Command Line % make
//make: Nothing to be done for `msdscript'.
//(base) mj@Vladimirs-MBP MSDscript Command Line % ./msdscript
//zsh: no such file or directory: ./msdscript
//(base) mj@Vladimirs-MBP MSDscript Command Line %
//10:22
//typed make
//
//Sushmitha  10:22 PM
//rm msdscript
//10:22
//make
//10:23
//do above things in that order
//10:23
//push your code to git and i will have a look in sometime?
//
//Vladimir a  10:24 PM
//(base) mj@Vladimirs-MBP MSDscript Command Line % rm msdscript
//rm: msdscript: No such file or directory
//(base) mj@Vladimirs-MBP MSDscript Command Line % make
//make: Nothing to be done for `msdscript'
//10:25
//can you still meet tonight?
//New
//
//Sushmitha  10:26 PM
//Tonight is really hard.. If you can push the code, I will try to run it on my system and get back to you by tomorrow morning.
//
//Vladimir a  10:28 PM
//Yes I will push it and send you the link via slack
//
//Sushmitha  10:28 PM
//perfect
//
//Vladimir a  10:28 PM
//thank you for all your help good night
//
//Sushmitha  10:28 PM
//no problem. good night
//
//Vladimir a  10:28 PM
//let me know if you are able to open my code and see it
//10:29
//I just one to make sure my commit works give me a second

//Commit:
//
//(base) mj@Vladimirs-MacBook-Pro MSDscript Command Line % git status
//On branch main
//Your branch is up to date with 'origin/main'.
//
//Changes not staged for commit:
//  (use "git add <file>..." to update what will be committed)
//  (use "git restore <file>..." to discard changes in working directory)
//    modified:   ../MSDscript Command Line.xcodeproj/xcshareddata/xcschemes/MSDscript Command Line.xcscheme
//    modified:   main.cpp
//    modified:   textHelp.cpp
//    modified:   ../../cmake-build-debug/CMakeFiles/clion-log.txt
//    modified:   ../../cmake-build-debug/Testing/Temporary/LastTest.log
//
//no changes added to commit (use "git add" and/or "git commit -a")
//(base) mj@Vladimirs-MacBook-Pro MSDscript Command Line % git add -A
//(base) mj@Vladimirs-MacBook-Pro MSDscript Command Line % git commit -m "Homework: MSDscript Command Line"
//[main a0f5d68] Homework: MSDscript Command Line
// 5 files changed, 117 insertions(+), 32 deletions(-)
// rewrite cmake-build-debug/CMakeFiles/clion-log.txt (100%)
//(base) mj@Vladimirs-MacBook-Pro MSDscript Command Line % git push -u main


//name: CI
//
//on: [push]
//
//jobs:
//build:
//
//    runs-on: macos-latest
//    steps:
//    - uses: actions/checkout@v1
//    - name: Build and run tests
//        run: make test


