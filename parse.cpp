//
//  parse.cpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 2/16/21.
//

#include "parse.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include "cmdline.h"
#include "expr.h"
#include "val.h"
#include <sstream>
#include <iomanip>
#include "catch.h"
#include "env.h"


// to switch between MSDSCRIPT and TestGenerator program:
//   click product then
//      click Scheme
//          then select either MSDSCRIPT or TestGenerator
//              then run it

//consume
//skip_whitespace
//parse_num (add other types later) - added
//parse_add (add other types later)
//parse_mult (add other types later)
//parse_variable(add other types later)
//parse_let (add other types later)

// consume
//static void consume(std::istream &in, int expect);

//skit white spaces:
static void skip_whitespace(std::istream &in);

//num
static  PTR(Expr)parse_num(std::istream &in);

//parse_multicand  need to be before parse_add end so addend can see it:
static  PTR(Expr)parse_multicand(std::istream &in);

static  PTR(Expr)parse_inner(std::istream &in);

//parse_var  need to be before parse_multicand end so addend can see it
static  PTR(Expr)parse_var(std::istream &in); // Variable type

// parse_let:
static PTR(Expr) parse_let(std::istream &in);

// parse_fun:
static  PTR(Expr)parse_fun(std::istream &in);

// parse_keyword:
static std::string parse_keyword(std::istream &in);

// Testing wrapper:
//static  PTR(Expr)parse_str(std::string s); //Expr *parse_str(std::string s)

//parse_alphabetic - start with letter to help parse_expression that start with a letter
static std::string parse_alphabetic(std::istream &in, std::string prefix);

static  PTR(Expr)parse_expr(std::istream &in);


static PTR(Expr) parse_if(std::istream &in);

// COSUME:
static void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c != expect)
        throw std::runtime_error("consume mismatch");
}

// Skit white spaces

static void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);// calling consume in skip_whitespace this is why consume need to be declared above skip_whitespace
    }
}

//parse_num:
PTR(Expr) parse_num(std::istream &in) { //#include "expr.h"
    int n = 0;
    bool negative = false;
    if (in.peek() == '-') {
        negative = true;
        consume(in, '-'); // we use single quote because characters can be converted into ints -- int expect here is expecting an int not a string according to the parameter that is passed in consume consume(std::istream &in, int expect);
    }
    while (1) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            //cast to unsigned before adding and multiplying, since unsigned overflow is defined:
            n = (unsigned)n*10 + (c - '0');// grammar for add
            //check if there is an overflow:
            if(n < 0){
                throw std::runtime_error("Integer Overflow...! ");
            }
        } else
            break;
    }
    if (negative)
        n = -n;
    return NEW (NumExpr)(n);
}

// Add: parse_addend
PTR(Expr) parse_addend(std::istream &in) {
    PTR(Expr) e;
    e = parse_multicand(in);
    //check multiple symbols:
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        PTR(Expr) rhs = parse_addend(in);
        return NEW (MultExpr)(e, rhs);
        
    } else
        return e;
}

// Mult: parse_multicand new Multicand:
//〈multicand〉=〈inner〉|〈multicand〉(〈expr〉)
PTR(Expr) parse_multicand(std::istream &in) {
    PTR(Expr) expr = parse_inner(in); // parse t
    while (in.peek() == '(') { // check if left parenthesis
        consume(in, '(');
        PTR(Expr) actual_arg = parse_expr(in);
        consume(in, ')');
        expr = NEW (CallExpr)(expr, actual_arg);
    }
    return expr;
}

//was multicand now is parse_inner:
PTR(Expr) parse_inner(std::istream &in) {
    PTR(Expr) e;
    //〈multicand〉 = 〈number〉  // grammar
    skip_whitespace(in); // skit white spaces
    int c = in.peek(); // double check that c == '('
    if ((c == '-') || isdigit(c))
        e = parse_num(in);
    //( 〈expr〉 )   // grammar
    else if (c == '(') {
        consume(in, '(');
        e = parse_comparg(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')')
            throw std::runtime_error("missing close parenthesis");
    }
    //grammar for variable:
    //〈variable〉
    //| _let 〈variable〉 = 〈expr〉 _in 〈expr〉
    else if (isalpha(c)) { // decide if a variable or not
        e = parse_var(in);// to be able to return e
    }
    //adding let to multican
    else if (c == '_') { // if underscore found mean there is a _let
        std::string keyWords = parse_keyword(in);
        if (keyWords == "_let") {
            return parse_let(in);
        }
        else  if (keyWords == "_true") {
            return NEW (BoolExpr)(true);
        }
        else  if (keyWords == "_false") {
            return NEW (BoolExpr)(false);
        }
        else  if (keyWords == "_if") {
            return parse_if(in);
        }
        else  if (keyWords == "_fun") {
            return parse_fun(in);
        } //make a method similar to parse_if and call it parse_fun
        
        else {
            throw std::runtime_error("invalid keyword is not a _if or _let or _true or _false or _fun");
        }
    }
    else {
        consume(in, c);
        throw std::runtime_error("invalid input");
    }
    //_fun
    return e;
}

// parse_var
PTR(Expr) parse_var(std::istream &in){
    std::string name;
    while (1) {
        char c = in.peek(); // peek looks it but does not consume it
        if (isalpha(c)) { // check if c is alpha
            consume(in, c); // consume c
            name = name+c;// grammar for variable
        }
        else {
            break; // if not a variable break after finishing parsing the characters that below to the variable
        }
    }
    return NEW (VarExpr)(name); // Create an instance of the Variable class and pass the name
}

//〈expr〉 = 〈addend〉
//| 〈addend〉 + 〈expr〉
//〈addend〉 = 〈multicand〉
//| 〈multicand〉 * 〈addend〉
//〈multicand〉 = 〈number〉
//| ( 〈expr〉 )
//| 〈variable〉
//| _let 〈variable〉 = 〈expr〉 _in 〈expr〉

// parse_let
PTR(Expr)  parse_let(std::istream &in){
    //parse right handside:
    skip_whitespace(in);
    //in.peek();
    //    Expr *e = parse_multicand(in); // who should be consuming the _let // variable
    skip_whitespace(in);
    
    PTR(Expr) v = parse_var(in); // expression object but it is expecting a variable
    
    //Expr *v = parse_var(in); // expression object but it is expecting a variable
    
    //_let y = 2 _in 1+y
    skip_whitespace(in); // check white space between variable and equal sign
    
    consume(in, '='); // consume equal here
    
    skip_whitespace(in);
    PTR(Expr) rhs = parse_comparg(in);
    //        PTR(Expr) rhs = parse_expr(in);
    std::string in_string = parse_keyword(in); // we get the in keyword
    
    if (in_string != "_in"){
        
        std::cout << "Check in_string value: .. " + in_string << std::endl;
        
        throw std::runtime_error("it should have an _in");
    }
    skip_whitespace(in);
    PTR(Expr) body = parse_comparg(in); // getting the body
    //std::dynamic_pointer_cast   <T>    (e)
    return NEW (LetExpr)(CAST(VarExpr) (v), rhs, body); // casting a Variable* to _let t = 3 _in t + 2 = 5;
    //_let〈variable〉=〈expr〉_in〈expr〉
    
}

PTR(Expr)  parse_fun(std::istream &in){
    //_fun (〈variable〉)〈expr〉
    
    //parse right handside:
    skip_whitespace(in);
    //_fun (x) x*x
    consume(in, '('); // add right (
    skip_whitespace(in);
    //std::string formal_arg:
    PTR(Expr) formal_arg = parse_var(in); // 〈variable〉 expression object but it is expecting a variable
    skip_whitespace(in);
    consume(in, ')'); // add left )
    skip_whitespace(in);
    PTR(Expr) body = parse_comparg(in); //〈expr〉
    
    return NEW (FunExpr)(formal_arg->to_string(), body);
}

PTR(Expr) parse_if(std::istream &in){
    //parse right handside:
    skip_whitespace(in);
    
    PTR(Expr)  if_part = parse_expr(in);
    
    std::string thenString = parse_keyword(in);
    if (thenString != "_then"){
        
        throw std::runtime_error("it should have a _then");
    }
    
    PTR(Expr) then_part = parse_expr(in);
    std::string elseString = parse_keyword(in);
    if (elseString != "_else"){
        
        throw std::runtime_error("it should have a _else");
    }
    PTR(Expr) else_part = parse_expr(in);
    
    return NEW (IfExpr)(if_part, then_part, else_part);
}
//parse_keyword:
std::string parse_keyword(std::istream &in){
    // read in the input stream and return
    in.get(); //consume first
    //define
    return parse_alphabetic(in, "_");
    
}

//parse_alphabet:
//parse_alphabetic - start with letter to help parse_expression that start with a letter

static std::string parse_alphabetic(std::istream &in, std::string prefix) {
    std::string name = prefix; // this is to get underscore character
    while (1) {
        char c = in.peek();
        if (!isalpha(c))
            break;
        name += in.get();
    }
    return name;
}

// Expression Helper Method goes below everything related to Parse because it will be calling all the methods above:

//parse_expr:
PTR(Expr) parse_expr(std::istream &in) {
    //    〈expr〉=〈comparg〉
    //            |〈comparg〉==〈expr
    PTR(Expr) e;
    e = parse_comparg(in);
    
    skip_whitespace(in);
    int c = in.peek();
    if (c == '=') {
        consume(in, '='); //
        consume(in, '='); //
        PTR(Expr) rhs = parse_expr(in);
        // we want to see what is inside the expression to see if we are parsing correctly:
        std::stringstream testing_parse_expr("");
        e->print(testing_parse_expr);
//        std::cout << " Testing PARSE_EXPR...... :)" + testing_parse_expr.str() << std::endl;
        return NEW (EqExpr)(e, rhs);
    } else
        return e;
}

// Refactor parse_expr to  parse_comparg :
PTR(Expr) parse_comparg(std::istream &in) { ///
    PTR(Expr) e;
    e = parse_addend(in);
    
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        PTR(Expr) rhs = parse_comparg(in);
        return NEW (AddExpr) (e, rhs);
    } else
        return e;
}

//parse_expr〈expr〉=〈comparg〉|〈comparg〉==〈expr〉

//Expr *parse_expr(std::istream &in) { ///
//    Expr *e;
//    e = parse_addend(in);
//
//    skip_whitespace(in);
//    int c = in.peek();
//    if (c == '==') {
//        consume(in, '+');
//        Expr *rhs = parse_expr(in);
//        return NEW (AddExpr)r(e, rhs);
//    } else
//        return e;
//}

// parse_str  Expr *parse_str(std::string s)
PTR(Expr) parse_str(std::string s) {// wrapper for testing.
    // transfer the string into a input the std::istream &in:
    std::istringstream in(s); // read the stream as a std::istringstream in(s);
    
    return parse_expr(in);
}
