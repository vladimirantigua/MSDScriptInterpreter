//
//  env.cpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/28/21.
//

#include "env.h"

PTR(Env) Env::empty = NEW(EmptyEnv)();

EmptyEnv::EmptyEnv() {
//    this->name = name;
//    this->val = val;
//    this->rest = Env::empty;
    
}

ExtendedEnv::ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest){
    this->name = name;
    this->val = val;
    this->rest = rest;
}
