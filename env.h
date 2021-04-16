//
//  env.hpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/28/21.
//

#ifndef env_hpp
#define env_hpp

#include <stdio.h>
#include "pointer.h"
#include "val.h"
#include<iostream>
#include <string>
#include<sstream>

class Env;
class Expr;
class Val;
class Cont;
class Step;

CLASS (Env) {
    
public:
    //
    virtual PTR(Val) lookup(std::string find_name) = 0;
    static PTR(Env) empty;
};

class EmptyEnv : public Env {
    //constructor:
public:
    EmptyEnv();
    
      PTR(Val) lookup(std::string find_name) {
        
        throw std::runtime_error("free variable: "                             + find_name);
    }
};

class ExtendedEnv : public Env {
public:

    std::string name;
    PTR(Val) val;
    PTR(Env) rest;
    
    //constructor
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    
    PTR(Val) lookup(std::string find_name) {
//        std::cout << "name: " << std::endl;
//        std::cout << name << std::endl;
//        std::cout << "val:" << std::endl;
//        std::cout << val << std::endl;
        
        if (find_name == name)
            return val;
        else
            return rest->lookup(find_name);
    }
};

#endif /* env_hpp */
