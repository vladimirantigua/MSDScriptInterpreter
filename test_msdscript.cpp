//
//  test_msdscript.cpp
//  Test_Generation_Homework
//
//  Created by Vladimir Antigua on 2/22/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "exec.h"

// To compile and run:

// make test_msdscript
//  ./test_msdscript MSDscriptCommandLine/msdscript

// to run the group msd script:

//./test_msdscript test_MDSCRIPT_group/msdscript1

// to add the executables in github:

// git add -f .

// To create random varible class:
std::string random_var_string() {
    // will help create random:
    srand(clock());
    if ((rand() % 10) < 3) { // represent x 30%
        return "x";
        
    }
    else if ((rand() % 10) < 3) { // represent y 30%
        return "y";
        
    }
    else {
        char c;
        int i;
        int num = ((rand() % 10) + 1); // +1 so variable never zero the length of the variable will be from 1 - 10
        int r;
        std::string s = "";
        srand(clock());    // initialize the random number generator
        for (i = 0; i < num; i++)
        {    r = rand() % 26;   // generate a random number
            c = 'a' + r;            // Convert to a character from a-z
            s += c; // apprennd to the string
        }
        return s; // return s
    }
    
}
std::string random_expr_string() {
    // NUM will be from 0 - 2:
    if ((rand() % 10) < 3) {// ADDING WEIGHT TO NUMBER AND VARIABLES TO VOID HAVING INFITE EXPRESSION
        //    〈expr〉 = 〈number〉 //already have this grammar num
        return std::to_string(rand()); // CREATES A RANDOM NUMBER 30% and Variable 30% AT total with Num and Variable 60%
    }
    // VARIABLE will be from 3 - 5:
    //    | 〈variable〉 // still need variable
   else if ((rand() % 10) < 6) { // mean 30%
       return random_var_string(); //random_var_string() this is how to create a variable
   }
    
    // ADD EXPRESSION will be from 6
   else if ((rand() % 10) < 7) { // mean 60%
       //    | 〈expr〉 + 〈expr〉// already have this grammar add two expressions
       return random_expr_string() + " + " + random_expr_string(); //CREATES A RANDOM ADD EXPRESSION AT 40%
   }
    // Mult EXPRESSION will be from 7
   else if ((rand() % 10) < 8)  { //mean 70%
       //    | 〈expr〉*〈expr〉// already have this grammar add two expressions
       return random_expr_string() + " * " + random_expr_string(); //CREATES A RANDOM ADD EXPRESSION AT 40%
   }
    //    | _let 〈variable〉 = 〈expr〉 _in 〈expr〉// still needs _let
   else if((rand() % 10) < 9) {  // 8
       return " _let " + random_var_string() + " = " + random_expr_string() + " _in " + random_expr_string();
     
   }

    
   //| _let 〈variable〉 = 〈expr〉 _in 〈expr〉// still needs _let
   else { //9
       //    | ( 〈expr〉 ) // still need parenthesis to add the parenthesis: to add Parenthesis in the expression
       return " ( " + random_expr_string() + " ) ";
       

   }
    //grammar:
//    〈expr〉 = 〈number〉 //already have this grammar num
//    | ( 〈expr〉 ) // still need parenthesis
//    | 〈expr〉 + 〈expr〉// already have this grammar add two expressions
//    | 〈expr〉 * 〈expr〉 // still need multiply
//    | 〈variable〉 // still need variable
//    | _let 〈variable〉 = 〈expr〉 _in 〈expr〉// still needs _let




}

    
    
//Comment and uncomment depending on the test I want to use from the two main methods below:



// Main # 1
//int main(int argc, char **argv) {
//    
//    //If your parser or interpreter can raise an exception, then probably main should be something like Try Catch:
//    //so that any exception is caught, its message is printed, and the exit code is 1.
//
//    try {
//        //./msdcript --interp "2+3"
//        const char * const interp_argv[] = { argv[1], "--interp" }; /// this to allow to pass argument on the terminal
////        const char * const interp_argv[] = { "msdscript", "--interp" };
//        
//        const char * const print_argv[] = {argv[1], "--print" }; // this to allow to pass argument on the terminal
//
////        const char * const print_argv[] = { "msdscript", "--print" };
//        for (int i = 0; i < 100; i++) {
//         
//            std::string in = random_expr_string();
//            
////
////            if (argc == 3) {
////                const char * const interp_argv2[] = { argv[2], "--interp" }; /// this to allow to pass argument on the terminal
////        //        const char * const interp_argv[] = { "msdscript", "--interp" };
////
////                const char * const print_argv2[] = {argv[2], "--print" }; // this to allow to pass argument on the terminal
////                ExecResult interp_result2 = exec_program(2, interp_argv2, in);
////                ExecResult print_result2 = exec_program(2, print_argv2, in);
////            }
////
//            
////            std::string in = "1+2";
//            std::cout << "Trying " << in << "\n";
//            ExecResult interp_result = exec_program(2, interp_argv, in);
//            std::cout << "Result:" << interp_result.out << in << "\n";
//            ExecResult print_result = exec_program(2, print_argv, in);
//            std::cout << "Print:" << print_result.out << in << "\n";
//
//            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);
//            std::cout << "Print2:" << interp_again_result.out << in << "\n";
//
//            if (interp_again_result.out != interp_result.out)
//                throw std::runtime_error("different result for printed");
//
//        }
//        return 0;
//    }
//    catch (std::runtime_error exn) {
//        std::cerr << exn.what() << "\n";
//        return 1;
//    }
//}
//


//// Main # 2      -- Uncomment when testing  INTERP FROM 2 DIFFERNT MSDSCRIPT FROM 0 TO 7 BELOW:


//msdscript0
//msdscript1
//msdscript2
//msdscript3
//msdscript4
//msdscript5
//msdscript6
//msdscript7

// MAIN # 2:
//int main(int argc, char **argv) {
//const char * const interp1_argv[] = { argv[1], "--interp" }; // this to allow to pass argument on the terminal
//
//    const char * const interp1_argv[] = { "msdscript", "--interp" };
//    const char * const interp2_argv[] = { "msdscript2", "--interp" };
//const char * const interp1_argv[] = { argv[2], "--interp" }; // this to allow to pass argument on the terminal
//
//    for (int i = 0; i < 100; i++) {
//        std::string in = random_expr_string();
//        std::cout << "Trying:  " << in << "\n";
//        ExecResult interp1_result = exec_program(2, interp1_argv, in);
//        ExecResult interp2_result = exec_program(2, interp2_argv, in);
//        if (interp1_result.out != interp2_result.out)
//            throw std::runtime_error("different results");
//    }
//    return 0;
//}
