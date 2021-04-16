//
//  val.hpp
//  MSDscript
//
//  Created by Vladimir Antigua on 2/23/21.
//

#ifndef val_hpp
#define val_hpp

#include <stdio.h>
#include <string>
#include "pointer.h"
#include<sstream>
#include "expr.h"
#include "env.h"
#include "step.h"
#include "val.h"
#include "cont.h"


class Expr; //In "val.h", similarly use class Expr; to allow Val::to_expr's return type to be Expr*

class Env;


CLASS (Val){  // change anytime where is said Value for Val since I labeled the class Value and changed to Val
public:
    virtual bool equals(PTR(Val) other) = 0;
//    virtual PTR(Expr) to_expr() = 0;
    virtual PTR(Val) add_to(PTR(Val) other) = 0;
    virtual PTR(Val) mult_to(PTR(Val) other) = 0;
    std::string val;
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
    virtual std::string to_string() = 0;
    virtual bool is_true() = 0;
    
    virtual void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest) = 0;
};


//subclass:
//class T { .... };  CLASS (T) { .... };
class NumVal : public Val { // subclass Num extends parent class Expr
public:
    int val;
    
    //constructor
    NumVal(int val) {
        this->val = val;
    }

    // Implement Equals: public is like extends in Java
    bool equals(PTR(Val) other);
//   PTR(Expr) to_expr();
   PTR(Val) add_to(PTR(Val) other);
   PTR(Val) mult_to(PTR(Val) other);
   PTR(Val) call(PTR(Val) actual_arg);
   std::string to_string(); // add the to_string
   bool is_true(); // IS_TRUE
   void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

//subclass:
class BoolVal : public Val { // subclass Num extends parent class Expr
public:
    // it should be stored as a string because it has an undercore:
    //_true or _false
    //std::string val;
    bool val;
    
    //constructor
//    BoolVal(std::string val) {
//        this->val = val;
//    }
    BoolVal(bool val){
        this->val = val;
    }

    // Implement Equals: public is like extends in Java
    
    bool equals(PTR(Val) other);
//   PTR(Expr) to_expr();
   PTR(Val) add_to(PTR(Val) other);
   PTR(Val) mult_to(PTR(Val) other);
   PTR(Val) call(PTR(Val) actual_arg);
   std::string to_string(); // add the to_string
   bool is_true(); // IS_TRUE
   void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

class FunVal : public Val {
public:
    
    std::string formal_arg;
    PTR(Expr) body;
    PTR(Env) env; // add it to the constructor
    
    //contructor:
    FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env); //PTR(Env) env; // add it to the constructor
    
     bool equals(PTR(Val) other);
//    PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) other);
    PTR(Val) mult_to(PTR(Val) other);
    PTR(Val) call(PTR(Val) actual_arg);
    std::string to_string(); // add the to_string
    bool is_true(); // IS_TRUE
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

//class NumExpr : public Val {
//    int rep;
//    NumExpr(int rep) {
//        this->rep = rep;
//    }
//};

#endif /* val_hpp */

