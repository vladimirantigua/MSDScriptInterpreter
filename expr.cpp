
//  expr.cpp
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 1/24/21.


#include "expr.h"
#include<iostream>
#include <string>
#include "catch.h"
#include <stdio.h>
#include <stdexcept>
#include<sstream>
#include "val.h"
#include "env.h"
#include "parse.h"


// to switch between MSDSCRIPT and TestGenerator program:
//   click product then
//      click Scheme
//          then select either MSDSCRIPT or TestGenerator
//              then run it


// Implementing Constructor:
NumExpr::NumExpr(int val) {
    this->rep = val;
}

// implementing Equals:
bool NumExpr::equals(PTR(Expr) e){
    //PTR(NumExpr) c = CAST(FunVal)(other);
    //dynamic_cast<T>(arg)CAST(T)(arg)
    PTR(NumExpr) c = CAST (NumExpr) (e); // dynamic_cast<Num*> it convert one pointer into another pointer
    if(c == NULL){ // if the cast is not a successful it will create a nullpointer and if the cast is successfull it convert my Expr pointer to a Num pointer.
        //create a test case that will pass non Number expression
        //NOTE: DON'T Change or modify  the field of an object - except in the constructor.
        return false; // add test that will make this like of code to run
    }
    else {
        return  (this->rep == c->rep);// integers can use the == to compare while comparing two objects need to use the equal
    }
}

PTR(Val) NumExpr::interp(PTR(Env) env){
    //    constructor:
    PTR(NumVal) numVal = NEW (NumVal)(this->rep); // object name = new object name
    return (PTR(Val)) numVal;
}

//converting Number Expressions:
void NumExpr::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(NumVal)(rep);
    Step::cont = Step::cont; /* no-op */
}

bool NumExpr::has_variable() {
    return false;
}

// Print for Num
void NumExpr::print(std::ostream &stream){
    stream << this->rep;
}

void NumExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    stream << this->rep;
}

// BoolExpr: implementation:

// Implementing Constructor:
BoolExpr::BoolExpr(bool val) {
    this->rep = val;
}

// implementing Equals:
bool BoolExpr::equals(PTR(Expr) e){
    //PTR(NumExpr) c = CAST(FunVal)(other);
    
    PTR(BoolExpr) c = CAST (BoolExpr)(e); // dynamic_cast<Num*> it convert one pointer into another pointer
    if(c == NULL){ // if the cast is not a successful it will create a nullpointer and if the cast is successfull it convert my Expr pointer to a BoolExpr  pointer.
        //create a test case that will pass non Number expression
        return false; // add test that will make this like of code to run
    }
    else {
        return  (this->rep == c->rep);// integers can use the == to compare while comparing two objects need to use the equal
    }
}

PTR(Val) BoolExpr::interp(PTR(Env) env){
    //    constructor:
    PTR(BoolVal) numVal = NEW (BoolVal)(this->rep); // object name = new object name
    return numVal;
}

//converting BoolExpr Expressions:
void BoolExpr::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(rep);
    Step::cont = Step::cont; /* no-op */
}

bool BoolExpr::has_variable() {
    return false;
}

// Print for Num
void BoolExpr::print(std::ostream &stream){
    //    stream << this->rep;
    if (rep) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

// Pretty_Print for Num
//void Num::pretty_print(std::ostream &stream){
//    stream << this->val;
//}

void BoolExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    //    stream << this->rep;
    if (rep) {
        stream << "_true";
    } else {
        stream << "_false";
    }
}

//EqExpr:

//implementing Constructor:
EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this-> lhs = lhs;
    this-> rhs = rhs;
}

// implementing Equals:
bool EqExpr::equals(PTR(Expr) e) {
    //PTR(NumExpr) c = CAST(FunVal)(other);
    
    PTR(EqExpr) c = CAST (EqExpr)(e);
    if(c == NULL){
        return false;
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs));
    }
};

PTR(Val) EqExpr::interp(PTR(Env) env) { // it will keep going until find a number or a variable expression pointer
    //returns either true or false -> want to return BoolVal("_true") or BoolVal("_false")
    if (lhs->interp(env)->equals(rhs->interp(env))) {
        return NEW (BoolVal)(true);
    }
    else {
        return NEW (BoolVal)(false);
    }
}

//Coverting equal
void EqExpr::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::cont = NEW(RightThenEqCont)(rhs, Step::env, Step::cont);
}

bool EqExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

//Print for EqExpr:
void EqExpr::print(std::ostream &stream){
    
    stream << "(";
    this->lhs->print(stream);// recursive method
    stream << "==";
    this->rhs->print(stream);
    stream << ")";
}

// pretty_print_at Mult
//Pretty_Print_at for Add:
void EqExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    
    // add a parenthesis
    if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
        stream << "(";
    }
    lhs->pretty_print_at(stream, print_group_add);
    stream << " == ";
    rhs->pretty_print_at(stream, print_group_none);
    if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
        stream << ")";
    }
}

//VARIABLE:
// Implementing Constructor:
VarExpr::VarExpr(std::string val) {
    this->val = val;
}

// implementing Equals: for Variable
bool VarExpr::equals(PTR(Expr) e){
    //PTR(NumExpr) c = CAST(FunVal)(other);
    
    PTR(VarExpr)  c = CAST (VarExpr)(e);
    if(c == NULL){
        return false;// add test that will make this like of code to run
    }
    else {
        return  (this->val == c->val);// integers can use the == to compare while comparing two objects need to use the equal
    }
}

// interp for Variable
PTR(Val) VarExpr::interp(PTR(Env) env){
    return env->lookup(val);
}

//converting VarExpr Expressions:
void VarExpr::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = Step::env->lookup(val);
    Step::cont = Step::cont; /* no-op */
}

bool VarExpr::has_variable() {
    return true;// return true because variable has a string
}

//Print for Variable
void VarExpr::print(std::ostream &stream){
    stream << this->val;
}

void VarExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    stream << this->val;
}

// implementing the constructor:
AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this-> lhs = lhs;
    this-> rhs = rhs;
}

// implementing Eqquals:
//(LHS)30+2 == 42+2(RHS) this ==LHS(30+2); c=e = RHS(42+2)
//30 == 42 = F
//(RHS)42==
bool AddExpr::equals(PTR(Expr) e) {
    //PTR(NumExpr) c = CAST(FunVal)(other);
    
    PTR(AddExpr) c = CAST (AddExpr)(e);
    if(c == NULL){
        return false; // add test that will make this like of code to run same as the mult add equals another type
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs));
    }
}

// Val Interp:
PTR(Val) AddExpr::interp(PTR(Env) env) { // it will keep going until find a number or a
    //    std::cout << "add interp: " << std::endl;
    
    //    std::cout << "lhs: " << std::endl;
    //    std::stringstream empty_string_string("");
    //    lhs->print(empty_string_string);
    //
    //    std::cout << empty_string_string.str() << std::endl;
    //
    //    std::cout << "rhs" << std::endl;
    //    std::stringstream empty_string_string2("");
    //    rhs->print(empty_string_string2);
    //
    //    std::cout << empty_string_string2.str() << std::endl;
    
    //variable expression pointer
    return lhs->interp(env)->add_to(rhs->interp(env));
}

// covering for add step_interp:
void AddExpr::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env; /* no-op, so could omit */
    Step::cont = NEW(RightThenAddCont)(rhs, Step::env, Step::cont);
}

bool AddExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

//Print for Add:
void AddExpr::print(std::ostream &stream){
    
    stream << "(";
    this->lhs->print(stream);// recursive method
    stream << "+";
    this->rhs->print(stream);
    stream << ")";
}

//Pretty_Print for Add:
void AddExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){ // the prettyValue is used to determine if I need parenthesis or not
    
    // if come from an add or a mult add the open bracket
    if(prettyValue == print_group_add || prettyValue == print_group_add_or_mult){
        stream << "(";
    }
    lhs->pretty_print_at(stream, print_group_add);
    stream << " + ";
    rhs->pretty_print_at(stream, print_group_none);
    if(prettyValue == print_group_add || prettyValue == print_group_add_or_mult){
        stream << ")";
    } //  stream << "Add";
}

//implementing Constructor:
MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs){
    this-> lhs = lhs;
    this-> rhs = rhs;
}

// implementing Equals:
bool MultExpr::equals(PTR(Expr) e) {
    PTR(MultExpr) c = CAST(MultExpr)(e);
    if(c == NULL){
        return false;
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs));
    }
};

PTR(Val) MultExpr::interp(PTR(Env) env) { // it will keep going until find a number or a variable expression pointer
    return lhs->interp(env)->mult_to(rhs->interp(env));
}

//Coverting mult;
void MultExpr::step_interp() {
    
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::cont = NEW(RightThenMultCont)(rhs, Step::env, Step::cont);
}

bool MultExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
}

//Print for Mult:
void MultExpr::print(std::ostream &stream){
    
    stream << "(";
    this->lhs->print(stream);// recursive method
    stream << "*";
    this->rhs->print(stream);
    stream << ")";
}

//Pretty_Print for Mult:
void Expr::pretty_print(std::ostream &stream){// it takes an output stream and take the address of the pointer &stream
    //pretty_print_at(stream, print_group_add_or_mult);
    
    //calling pretty print:
    pretty_print_at(stream, print_group_none);
}

// pretty_print_at Mult
//Pretty_Print_at for Add:
void MultExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    
    // add a parenthesis
    if(prettyValue == print_group_add_or_mult){
        stream << "(";
    }
    lhs->pretty_print_at(stream, print_group_add_or_mult);
    stream << " * ";
    rhs->pretty_print_at(stream, print_group_add);
    if(prettyValue == print_group_add_or_mult){
        stream << ")";
    }
}

// Implemeting to_string:
std::string Expr::to_string(){
    std::string basket = ""; // create an empty to store the stringstream out
    std::stringstream out(""); // create an new stringstream out that is empty
    this->print(out); // here is only print() append to the stringstream out calling print on this-> current object current expression
    basket = out.str(); // get the expression out to extract an output string
    
    return basket;
}

// Implemeting to_string_pretty:
std::string Expr::to_string_pretty(){
    std::string basket = ""; // create an empty to store the stringstream out
    std::stringstream out(""); // create an new stringstream out that is empty
    this->pretty_print(out); // calling pretty_print() append to the stringstream out calling print on this-> current object current expression
    basket = out.str(); // get the expression out to extract an output string
    
    return basket;
}

//_LET:

//_Let class the constructor has a lhs, rhs, and body: _let(Expr *lhs, Expr *rhs, Expr *body); So you are just creating another class for _let like you did for Add or Mult or Var.

// implementing the _LET Constructor:
LetExpr::LetExpr(PTR(VarExpr) lhs, PTR(Expr) rhs, PTR(Expr) body){
    this-> lhs = lhs;
    this-> rhs = rhs;
    this-> body= body;
}

// implementing Eqquals:
//(LHS)30+2 == 42+2(RHS) this ==LHS(30+2); c=e = RHS(42+2)
//30 == 42 = F
//(RHS)42==
bool LetExpr::equals(PTR(Expr) e) {
    PTR(LetExpr) c = CAST(LetExpr)(e);
    if(c == NULL){
        return false; // add test that will make this like of code to run same as the mult add equals another type
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs) && this->body->equals(c-> body));
    }
}

//_Let interp:

//ENVIRONMENT: 
PTR(Val) LetExpr::interp(PTR(Env) env) {
    PTR(Val) rhs_val = rhs->interp(env);
    // covert the lhs which is type var to a string to match the constructor for ExtendedEnv:
    PTR(Env) new_env = NEW(ExtendedEnv)(lhs->to_string(), rhs_val, env);
    return body->interp(new_env);
}

// Converting _let step_interp:
void LetExpr::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = Step::env;
    Step::cont = NEW(LetBodyCont)(lhs->val, body, Step::env, Step::cont);
}

bool LetExpr::has_variable() {
    // only rhs and body for has_variable() because the left hand side is already a variable
    return (this->rhs->has_variable() || this->body->has_variable());
}

//Print for _Let:
void LetExpr::print(std::ostream &stream){
    
    stream << "(_let ";
    this->lhs->print(stream);// recursive method
    stream << "=";
    this->rhs->print(stream);
    stream << " _in ";
    this->body->print(stream);
    stream << ")";
}

//Pretty_Print for _let:
void LetExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){ // the prettyValue is used to determine if I need parenthesis or not
    
    //==== _LET ==//
    // if come from an add or a mult add the open bracket
    if(prettyValue == print_group_add || prettyValue == print_group_add_or_mult || prettyValue == print_group_let){
        stream << "(_let " ;
        stream << lhs->val;
        //lhs->pretty_print_at(stream, print_group_add);
        stream << " = ";
        rhs->pretty_print_at(stream, print_group_none);
        stream << "     _in ";
        body->pretty_print_at(stream, print_group_let);
        stream << ")";
    }
}

//IfExpr:

//implementing Constructor:
IfExpr::IfExpr(PTR(Expr) _if, PTR(Expr) _then, PTR(Expr) _else){
    
    this-> _if = _if;
    this-> _then = _then;
    this-> _else = _else;
}

// implementing Equals:
bool IfExpr::equals(PTR(Expr) e) {
    //PTR(NumExpr) c = CAST(FunVal)(other);
    //    PTR(IfExpr) c = dynamic_cast<IfExpr*>(e);
    
    PTR(IfExpr) c = CAST (IfExpr)(e);
    if(c == nullptr){
        return false; // add test that will make this like of code to run
        // mult equals and some other type expression
    }
    else {
        return (this->_if->equals(c->_if) && this->_then->equals(c->_then) && this->_else->equals(c->_else));
    }
};

PTR(Val) IfExpr::interp(PTR(Env) env) { // it will keep going until find a number or a variable expression pointer
    //returns either true or false -> want to return BoolVal("_true") or BoolVal("_false")
    //if->interp() returns a BoolVal
    //1) BoolVal is true
    //2) BoolVal is false
    //3) interp does not return a BoolVal, but a NumVal
    //    |_false|_if〈expr〉_then〈expr〉_else〈expr〉:
    //if ( 1+2)
    // return 3
    //else
    //  return (4+1)->interp
    
    if (_if->interp(env)->equals(NEW (BoolVal)(true))) {
        //        return NEW (BoolVal)("_true");
        return _then->interp(env);
    }
    else {
        return _else->interp(env);
    }
}

//Coverting _if
void IfExpr::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = _if;
    Step::env = Step::env;
    Step::cont = NEW(IfBranchCont)(_then, _else, Step::env, Step::cont);
}

bool IfExpr::has_variable() {
    return (this->_if->has_variable() || this->_then->has_variable() || this->_else->has_variable());
}

//Print for IfExpr:
void IfExpr::print(std::ostream &stream){
    // _if <if>
    // <then>
    // <else>
    
    // <expr> <expr>
    // (_if <expr> _then <expr> _else <expr>)
    
    stream << "(";
    stream << "_if ";
    this->_if->print(stream);// recursive method
    stream << " _then ";
    this->_then->print(stream);
    stream << " _else ";
    this->_else->print(stream);
    stream << ")";
}

//IfExpr pretty_print:
void IfExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    
    //add a parenthesis
    if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
        stream << "(";
    }
    stream << "_if ";
    _if->pretty_print_at(stream, print_group_add);
    stream << " _then ";
    _then->pretty_print_at(stream, print_group_none);
    stream << " _else ";
    _else->pretty_print_at(stream, print_group_none); // find out which print group is this here
    if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
        stream << ")";
    }
}

//FUNEXPR:

//constructor:
FunExpr::FunExpr(std::string formal_arg,  PTR(Expr) body){
    
    this->formal_arg = formal_arg;
    this->body = body;
}

//bool equals(Expr *other);

bool FunExpr::equals(PTR(Expr) e) {
    //PTR(NumExpr) c = CAST(FunVal)(other);
    
    PTR(FunExpr) c = CAST (FunExpr)(e);
    if(c == NULL){
        return false; // add test that will make this like of code to run same as the mult add equals another type
    }
    else {// when comparing a string use the . dot when ->
        //        if (str1.compare(str2) != 0)                //call equals on a expression for body
        return (this->formal_arg.compare(c->formal_arg) == 0 && this->body->equals(c->body));
    }
}

// ENVIRONEMNT:
PTR(Val) FunExpr::interp(PTR(Env) env) {
    return NEW(FunVal)(formal_arg, body, env);
}

//converting FunExpr:
void FunExpr::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(FunVal)(formal_arg, body, Step::env ); // this is correct way to pass the environment = Step::env
    Step::cont = Step::cont; /* no-op */
}

bool FunExpr::has_variable() {
    
    throw std::runtime_error("method not implemented invalid call");
}

void FunExpr::print(std::ostream &stream) {
    
    //    For print, always put a _fun expression in parentheses, include exactly one space around the outside of the parentheses for the argument, and include no space inside the parentheses. Never print a pair of parentheses around a function call (because it turns out that's not necessary), and include no space on the outside or inside edges of the parentheses around the argument in a function call.
    // (_fun (x) x*x)(2)
    //formal_arg, body)
    stream << "(_fun (";
    stream << formal_arg; // strings does not have to be recursive only call recursive if it is an expression.
    stream << ") "; // closing the formal_arg
    this->body->print(stream);
    stream << ") ";
}

void FunExpr::pretty_print(std::ostream &stream)  {
    
    
    //calling pretty print:
    pretty_print_at(stream, print_group_none);
}

void FunExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    //_fun expressions need parentheses in the same contexts where _let would need parentheses. Add a newline after the argument parentheses for _fun and indent the body two spaces more than the column where _fun starts
    
    // add a parenthesis
    if(prettyValue == print_group_add_or_mult){
        stream << "(";
    }
    stream << "_fun (";
    //formal_arg, body)
    stream << formal_arg;
    stream << ")\n";
    
    stream << "  ";
    body->pretty_print_at(stream, print_group_add);
    if(prettyValue == print_group_add_or_mult){
        stream << ")";
    }
}

//CALLEXPR:

//constructor:
CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg) {
    
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(PTR(Expr) e) {
    PTR(CallExpr) c = CAST(CallExpr)(e);
    if(c == NULL){
        return false; // add test that will make this like of code to run same as the mult add equals another type
    }
    else {// when comparing a string use the . dot when ->
        //if (str1.compare(str2) != 0)
        //call equals on a expression for body
        return (this->to_be_called->equals(c->to_be_called) && this->actual_arg->equals(c->actual_arg));
    }
    
}

//Call Expression class:
PTR(Val) CallExpr::interp(PTR(Env) env) {
    
    //    std::cout << "to_be_called: " << std::endl;
    //
    //    std::stringstream empty_string_string("");
    //    to_be_called->print(empty_string_string);
    //
    //    std::cout << empty_string_string.str() << std::endl;
    //std::cout <<  to_be_called->interp(env)->to_string() << std::endl;
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}

// convertiring function Call:
void CallExpr::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = to_be_called;
    Step::cont = NEW(ArgThenCallCont)(actual_arg, Step::env, Step::cont);
}

bool CallExpr::has_variable() {
    
    throw std::runtime_error("method not implemented invalid call");
}

void CallExpr::print(std::ostream &stream) {
    //    For print, always put a _fun expression in parentheses, include exactly one space around the outside of the parentheses for the argument, and include no space inside the parentheses. Never print a pair of parentheses around a function call (because it turns out that's not necessary), and include no space on the outside or inside edges of the parentheses around the argument in a function call.
    //(_fun x x*x)(2) this is to be call
    //to be called = (_fun x x*x) (actarg) = (2)
    //f(2)
    
    this->to_be_called->print(stream); //f
    // recursive only call recursive if it is an expression.
    stream << "(";
    this->actual_arg->print(stream); //(2)
    stream << ")"; // closing the actual_arg
}

void CallExpr::pretty_print(std::ostream &stream)  {
    //calling pretty print:
    pretty_print_at(stream, print_group_none);
}

void CallExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    //function call never needs extra parentheses.
    
    this->to_be_called->print(stream); //f
    // recursive only call recursive if it is an expression.
    stream << "(";
    this->actual_arg->print(stream); //(2)
    stream << ")"; // closing the actual_arg
}
