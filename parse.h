//
//  parse.hpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 2/16/21.
//

#ifndef parse_hpp
#define parse_hpp

#include <stdio.h>
#include <iostream>
#include "pointer.h"

// ADD all the parse homework here:
//consume
//skip_whitespace
//parse_num (add other types later) - added
//parse_add (add other types later)
//parse_mult (add other types later)
//parse_variable(add other types later)
//parse_let (add other types later)
//parse_exp need to be before the parse_addend so addend can see it:

// leave it normal
class Expr; // this say that the class exist:

class Env;

// refactor PTR(Expr)
PTR(Expr) parse_comparg(std::istream &in);


PTR(Expr)parse_str(std::string s); //Expr *parse_str(std::string s)

static void consume(std::istream &in, int expect);

#endif /* parse_hpp */
