//
//  val.cpp
//  MSDscript
//
//  Created by Vladimir Antigua on 2/23/21.
//

#include "val.h"
#include "expr.h"
  
// Implement Equals: public is like extends in Java

bool NumVal::equals(PTR(Val) other){
    PTR(NumVal) c = CAST(NumVal) (other); // dynamic_cast<Num*> it convert one pointer into another pointer
    if(c == nullptr){ // if the cast is not a successful it will create a nullpointer and if the cast is successfull it convert my Expr pointer to a Num pointer.
        //create a test case that will pass non Number expression
        return false; // add test that will make this like of code to run
    }
    else {
        return  (this->val == c->val);// integers can use the == to compare while comparing two objects need to use the equal
    }
}



    // Implement Equals: public is like extends in Java
                   //T *PTR(T)
bool BoolVal::equals(PTR(Val) other) {
    //dynamic_cast<T>(arg) CAST(T)(arg)
    PTR(BoolVal) c = CAST(BoolVal) (other); // dynamic_cast<Num*> it convert one pointer into another pointer
    if(c == nullptr){ // if the cast is not a successful it will create a nullpointer and if the cast is successfull it convert my Expr pointer to a Num pointer.
        //create a test case that will pass non Number expression
        return false; // add test that will make this like of code to run
    }
    else {
        return  this->val == c->val;
    }
}
   
 
PTR(Expr) BoolVal::to_expr() {
    
//    newT(arg, ...)NEW(T)(arg, ...)
    PTR(BoolExpr) boolExpr = NEW( BoolExpr) (this->val);
    
   
    return boolExpr;
}

PTR(Val) BoolVal::add_to(PTR(Val) other ) {
    
    throw std::runtime_error("This is a Bool value unable to add or multipy...");
    
//    BoolVal *c = dynamic_cast<BoolVal*>(other);
//    if(other == NULL) throw std::runtime_error("add of non-number");
//    return NEW (BoolVal)(val + c->val);
}


PTR(Val) BoolVal::mult_to(PTR(Val) other) {
    // Throw an error because we cannot perform multiply or add
   throw std::runtime_error("This is a Bool value unable to add or multipy...");
    
    
//    BoolVal *c = dynamic_cast<BoolVal*>(other);
//    if(other == NULL) throw std::runtime_error("mult of non-number");
//    return NEW (BoolVal)(val * c->val);

}

PTR(Val) BoolVal::call(PTR(Val) actual_arg) {
    // since we cannot call a number or a bool we need to throw an error:
     throw std::runtime_error("unable to call a bool");
    
}

// help to change a value expression into an int or number
PTR(Expr) NumVal::to_expr() {
    // create  a number: this is helping us to convert number value into a expression. and will going to use it in our ADD MULT and _let methods:
    //NEW (NumExpr) (this->val)
    return NEW (NumExpr) (this->val); // object name = new object name
    
}

PTR(Val) NumVal::add_to(PTR(Val) other ) {
    PTR(NumVal) c = CAST(NumVal) (other);
    if(other == NULL) throw std::runtime_error("add of non-number");
    //NEW (NumExpr) (this->val)
    return NEW (NumVal) (val + c->val);
}


PTR(Val) NumVal::mult_to(PTR(Val) other) {
    PTR(NumVal) c = CAST(NumVal) (other);
    if(other == NULL) throw std::runtime_error("mult of non-number");
    return NEW (NumVal) (val * c->val); // val * c->val this is multiplication not a pointer

}

PTR(Val) NumVal::call(PTR(Val) actual_arg) {
    // since we cannot call a number or a bool we need to throw an error:
     throw std::runtime_error("unable to call a number");
    
}

FunVal::FunVal(std::string formal_arg, PTR(Expr) body) {
    this->formal_arg = formal_arg;
    this->body = body;
}
//
PTR(Val) FunVal::call(PTR(Val) actual_arg) {
    //f(2) , Val* actual_arg is 2
    //want to return the result of subst 2 into the function f
    //called on a FunVal, all FunVals have a string formal_arg and a Expr* body
    //_let f = _fun (x = formal_arg) Expr* body = x*x  // this is a function
    // when calling a function I pass a actual argument = _in  f(2)
    // this is the result of let which format it like this = (_fun (x) x*x)(2)
    //2*2 = replace the formal argument x which with actual arguament which 2
    // then evaluate with interp() which will give a 4: 
    return this->body->subst(formal_arg, actual_arg->to_expr())->interp();
}

bool FunVal::equals(PTR(Val) other) {
    PTR(FunVal) c = CAST(FunVal)(other); // dynamic_cast<Num*> it convert one pointer into another pointer
    if(c == nullptr){ // if the cast is not a successful it will create a nullpointer and if the cast is successfull it convert my Expr pointer to a Num pointer.
        //create a test case that will pass non Number expression
        return false; // add test that will make this like of code to run
    }
    else {
        return  this->val == c->val;
    }
}
//Expr* to_expr():
PTR(Expr) FunVal::to_expr() {
    
    PTR(FunExpr) funExpr = NEW (FunExpr) (this->formal_arg, this->body);
    
   
    return funExpr;
}

//Val* add_to(Val *other);
PTR(Val) FunVal::add_to(PTR(Val) other){
    throw std::runtime_error("unable to add two functions");
}

//Val* mult_to(Val *other);
PTR(Val) FunVal::mult_to(PTR(Val) other){
    throw std::runtime_error("unable to multiply two functions");
}


