
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

//#include"textHelp.cpp"

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
        return false; // add test that will make this like of code to run
    }
    else {
        return  (this->rep == c->rep);// integers can use the == to compare while comparing two objects need to use the equal
    }
    
}

//PTR(Expr) NumVal::to_expr(){
//    return NEW (NumExpr) (this->val);
//}

PTR(Val) NumExpr::interp(){
    //    constructor:
   PTR(NumVal) numVal = NEW (NumVal)(this->rep); // object name = new object name
    return (PTR(Val)) numVal;
}

bool NumExpr::has_variable() {
    return false;
}
//Subst for Num
PTR(Expr) NumExpr::subst(std::string sub, PTR(Expr) expr){
    //this replace with ===>   THIS  NOTE: when not followed by ->
    return THIS; //WAS: return this;
}

// Print for Num
void NumExpr::print(std::ostream &stream){
    stream << this->rep;
}

//// Pretty_Print for Num
//void Num::pretty_print(std::ostream &stream){
//    stream << this->val;
//}

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

//Expr* NumVal::to_expr(){
//    return NEW (NumExpr) (this->val);
//}

PTR(Val) BoolExpr::interp(){
    //    constructor:
    PTR(BoolVal) numVal = NEW (BoolVal)(this->rep); // object name = new object name
    return numVal;
}

bool BoolExpr::has_variable() {
    return false;
}
//Subst for Num
PTR(Expr) BoolExpr::subst(std::string sub, PTR(Expr) expr){
    return THIS;
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

//// Pretty_Print for Num
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
        return false; // add test that will make this like of code to run
        // mult equals and some other type expression
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs));
    }
};


PTR(Val) EqExpr::interp() { // it will keep going until find a number or a variable expression pointer
    //returns either true or false -> want to return BoolVal("_true") or BoolVal("_false")
    if (lhs->interp()->equals(rhs->interp())) {
        return NEW (BoolVal)(true);
    }
    else {
        return NEW (BoolVal)(false);
    }
}

//        //this->lhs->interp() = this is a val pointer change to expression pointer
//        //this->lhs->interp()->to_expr() + this->rhs->interp()->to_expr());
//        // we are calling the entire expression inside the parethesis inside the constructor to convert it into a Val*
//        return NEW (NumVal)(this->lhs->interp()->to_expr() * this->rhs->interp()->to_expr()); // for Interp we only care about returning the value of the expression from left side and right side.
//        //The value of an addition expression is the sum of the subexpression values
//
//    }



bool EqExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable()); // add test that will make this like of code to run here for the right side
    
    
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals:
}

PTR(Expr) EqExpr::subst(std::string sub, PTR(Expr) expr){
    // I can use either use two options Mult subst below:
    
    //    return new Mult(lhs->subst(sub, expr), rhs->subst(sub, expr)); // Do the substitution and compare to the Add expression of the lhs-left hand side and rhs-right hand side.
    
    // I can use either use two options Mult subst below:
    //    another way to do the multiply subst is:
    
    PTR(Expr) new_lhs = lhs->subst(sub, expr);
    PTR(Expr) new_rhs = rhs->subst(sub, expr);
    return NEW (EqExpr)(new_lhs, new_rhs);
    
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals
    
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




//IfExpr:

//implementing Constructor:
IfExpr::IfExpr(PTR(Expr) _if, PTR(Expr) _then, PTR(Expr) _else){
//   BoolExpr *c = dynamic_cast<BoolExpr*>(_if);
    
//    if(c == NULL){
//        throw std::runtime_error("The first parameter need to be a BoolExpr");
//    }
//    else {
//
//    }
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


PTR(Val) IfExpr::interp() { // it will keep going until find a number or a variable expression pointer
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

    if (_if->interp()->equals(NEW (BoolVal)(true))) {
//        return NEW (BoolVal)("_true");
        return _then->interp();
    }
   else {
        return _else->interp();
    }
   
}


bool IfExpr::has_variable() {
    return (this->_if->has_variable() || this->_then->has_variable() || this->_else->has_variable()); // add test that will make this like of code to run here for the right side
    
}

PTR(Expr) IfExpr::subst(std::string sub, PTR(Expr) expr){
    // I can use either use two options Mult subst below:
    
    //    return new Mult(lhs->subst(sub, expr), rhs->subst(sub, expr)); // Do the substitution and compare to the Add expression of the lhs-left hand side and rhs-right hand side.
    
    // I can use either use two options Mult subst below:
    //    another way to do the multiply subst is:
    
    PTR(Expr) new_if = _if->subst(sub, expr);
    PTR(Expr) new_then = _then->subst(sub, expr);
    PTR(Expr) new_else = _else->subst(sub, expr);
    return NEW (IfExpr)(new_if, new_then, new_else);
    
}

//Print for IfExpr:
void IfExpr::print(std::ostream &stream){
    // _if <if>
//            <then>
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
PTR(Val) VarExpr::interp(){
    throw std::runtime_error("Runtime error unable to mutiply a non integer type ....");
    //    return 0;
}



bool VarExpr::has_variable() {
    return true;// return true because variable has a string
}

//Subst for Variable
PTR(Expr) VarExpr::subst(std::string sub, PTR(Expr) expr){
    if (this->val == sub) {
        return expr;
    }
    return THIS; // add test that will make this like of code to run
}

//Print for Variable
void VarExpr::print(std::ostream &stream){
    stream << this->val;
}

//// Pretty_Print for Variable
//void Variable::pretty_print(std::ostream &stream){
//    stream << this->val;
//}

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
PTR(Val) AddExpr::interp() { // it will keep going until find a number or a variable expression pointer
    return lhs->interp()->add_to(rhs->interp());
    
}

bool AddExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable());
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals:
    
}

PTR(Expr) AddExpr::subst(std::string sub, PTR(Expr) expr){
    
    return NEW (AddExpr)(lhs->subst(sub, expr), rhs->subst(sub, expr)); // Do the substitution and compare to the Add expression of the lhs-left hand side and rhs-right hand side.
    
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
        return false; // add test that will make this like of code to run
        // mult equals and some other type expression
    }
    else {
        return (this->lhs->equals(c-> lhs) && this->rhs->equals(c-> rhs));
        
    }
};


PTR(Val) MultExpr::interp() { // it will keep going until find a number or a variable expression pointer
    return lhs->interp()->mult_to(rhs->interp());
    
}
//        //this->lhs->interp() = this is a val pointer change to expression pointer
//        //this->lhs->interp()->to_expr() + this->rhs->interp()->to_expr());
//        // we are calling the entire expression inside the parethesis inside the constructor to convert it into a Val*
//        return NEW (NumVal)(this->lhs->interp()->to_expr() * this->rhs->interp()->to_expr()); // for Interp we only care about returning the value of the expression from left side and right side.
//        //The value of an addition expression is the sum of the subexpression values
//
//    }



bool MultExpr::has_variable() {
    return (this->lhs->has_variable() || this->rhs->has_variable()); // add test that will make this like of code to run here for the right side
    
    
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals:
}

PTR(Expr) MultExpr::subst(std::string sub, PTR(Expr) expr){
    // I can use either use two options Mult subst below:
    
    //    return new Mult(lhs->subst(sub, expr), rhs->subst(sub, expr)); // Do the substitution and compare to the Add expression of the lhs-left hand side and rhs-right hand side.
    
    // I can use either use two options Mult subst below:
    //    another way to do the multiply subst is:
    PTR(Expr)new_lhs = lhs->subst(sub, expr);
    PTR(Expr)new_rhs = rhs->subst(sub, expr);
    return NEW (MultExpr)(new_lhs, new_rhs);
    
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals
    
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

//// Implemeting to_string:
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


//       _LET:

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

// like in the video and add return on the ....

PTR(Val) LetExpr::interp() {
    
    //    throw std::runtime_error("There is no value for this expression");
    
    PTR(Val) rhs = this->rhs->interp();  // *rhs_val where to put this
    
    return body->subst(this->lhs->val, rhs->to_expr())->interp();
    
}

//Val* _let::interp() {
//    //When interpreting a _let expression I need to interpret the right hand side first before substituing the right hand side of a expression in the body:
//    return body->subst(lhs->val, rhs)->interp();
//    return rhs->subst(body->to_string(), lhs)->interp();

//    return (this->lhs->interp() + this->rhs->interp()); // for Interp we only care about returning the value of the expression from left side and right side.
//        The value of an addition expression is the sum of the subexpression values




bool LetExpr::has_variable() {
    // only rhs and body for has_variable() because the left hand side is already a variable
    return (this->rhs->has_variable() || this->body->has_variable());
    // DON'T Change or modify  the field of an object - except in the constructor: - DO NOT USE DYNAMIC CASTING like the example below other than the equals:
    
}

// _Let Subst
PTR(Expr) LetExpr::subst(std::string sub, PTR(Expr) expr){
    
    // The left hand side is always a variable and we do not want it to have it replaced:
    // Do the substitution and compare to
    if (this->lhs->val == sub) {
        return NEW (LetExpr)(this->lhs, this->rhs->subst(sub, expr), this->body); // we want the body but not the subst part the else will include the subst in the body
    } else {
        return NEW (LetExpr)(this->lhs, this->rhs->subst(sub, expr), this->body->subst(sub, expr));
    }
    
    //the //Add expression of the lhs-left hand side and rhs-right hand side.
    // To fix the subst implementation add a if statement
    // add if statement lhs equals variable subst
    
    // if there is a variable inside the body x+y+3
}

////Print for _Let:
void LetExpr::print(std::ostream &stream){
    
    stream << "(_let ";
    this->lhs->print(stream);// recursive method
    stream << "=";
    this->rhs->print(stream);
    stream << " _in ";
    this->body->print(stream);
    stream << ")";
}

//ask instructor for help fixing this pretty_print_at
////Pretty_Print for _let:
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

PTR(Val) FunExpr::interp() {
    
   return NEW (FunVal)(formal_arg, body);
    
    
}

bool FunExpr::has_variable() {
    
    throw std::runtime_error("method not implemented invalid call");
}


//Expr* subst(std::string, Expr* expr); body for subst

PTR(Expr) FunExpr::subst(std::string sub, PTR(Expr) expr){
    // this is comparing two strings
    if(sub.compare( formal_arg) == 0){
        /// if return true then return same expression because we do not want to substite formal argument:
        return NEW (FunExpr)(this->formal_arg, this->body);
        
    }
 return NEW (FunExpr)(this->formal_arg, this->body->subst(sub, expr));
    
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
//        if (str1.compare(str2) != 0)                //call equals on a expression for body
        return (this->to_be_called->equals(c->to_be_called) && this->actual_arg->equals(c->actual_arg));
    }
    
}



//Call Expression class:
PTR(Val) CallExpr::interp() {
    
    return to_be_called->interp()->call(actual_arg->interp());
    //
    
}

bool CallExpr::has_variable() {
    
    throw std::runtime_error("method not implemented invalid call");
}


PTR(Expr) CallExpr::subst(std::string sub, PTR(Expr) expr){
    
    PTR(Expr) new_to_be_called = to_be_called->subst(sub, expr);
    PTR(Expr) new_actual_arg = actual_arg->subst(sub, expr);
    return NEW (CallExpr)(new_to_be_called, new_actual_arg);
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








// TEST: Write the function Test here and call it in the textHelp.cpp:

TEST_CASE("equals"){
    PTR(Expr) num40 =  NEW (NumExpr)(5); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num41 = NEW (NumExpr)(2);
    CHECK(num41->equals(num40 ) == false);
    
    PTR(Expr) num42 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num43 = NEW (NumExpr)(2);
    CHECK(num43->equals(num42 ) == false);
    
    // true
    PTR(Expr) num44 =  NEW (NumExpr)(23); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num45 = NEW (NumExpr)(23);
    CHECK(num45->equals(num44 ) == true);
    
    PTR(Expr) variable40 =  NEW (VarExpr)("this is variable"); // creating new Variable  object to assign memory for that object Making a pointer to the Expr class
    PTR(VarExpr) variable41 = NEW (VarExpr)("variable2");
    CHECK(variable41->equals(variable40 ) == false);
    
    PTR(Expr) variable42 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(VarExpr) variable43 = NEW (VarExpr)("variable3");
    CHECK(variable43->equals(variable42) == false);
    
    // true
    PTR(Expr) variable44 =  NEW (VarExpr)("variable3"); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(VarExpr) variable45 = NEW (VarExpr)("variable3");
    CHECK(variable45->equals(variable44 ) == true);
    
    
    // this is false if the expression is not an add
    PTR(Expr) num50 =  NEW (NumExpr)(5); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(AddExpr) num51 = NEW (AddExpr)(NEW (NumExpr)(7), NEW (NumExpr)(3));
    CHECK(num51->equals(num50 ) == false);
    
    // true
    PTR(Expr) num46 =  NEW (AddExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(AddExpr) num47 = NEW (AddExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4));
    CHECK(num47->equals(num46 ) == true);
    
    //false
    PTR(Expr) num48 =  NEW (AddExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(AddExpr) num49 = NEW (AddExpr)(NEW (NumExpr)(5), NEW (NumExpr)(6));
    CHECK(num49->equals(num48 ) == false);
    
      
    
    
    // this is false if the expression is not an add
    PTR(Expr) num52 =  NEW (NumExpr)(5); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(MultExpr) num53 = NEW (MultExpr)(NEW (NumExpr)(7), NEW (NumExpr)(3));
    CHECK(num53->equals(num52 ) == false);
    
    // true
    PTR(Expr) num54 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(MultExpr) num55 = NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4));
    CHECK(num55->equals(num54 ) == true);
    
    //false
    PTR(Expr) num56 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(MultExpr) num57 = NEW (MultExpr)(NEW (NumExpr)(5), NEW (NumExpr)(6));
    CHECK(num57->equals(num56 ) == false);
    
    
    CHECK( (NEW (AddExpr)(NEW (NumExpr)(3),NEW (NumExpr)(2)))->equals(NEW (AddExpr)(NEW (NumExpr)(5),NEW (NumExpr)(2)))== false); //true this mean it should return true
    
    CHECK( (NEW (AddExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))->equals(NEW (AddExpr) (NEW (NumExpr)(42),NEW (NumExpr)(2)))== true); //true this mean it should return true
    CHECK( (NEW (AddExpr)(NEW (NumExpr)(30),NEW (NumExpr)(15)))->equals(NEW (AddExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))== false); // == false this mean it should return false
    CHECK( (NEW (AddExpr)(NEW (NumExpr)(2),NEW (NumExpr)(42)))->equals(NEW (AddExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))== false);
    
    //(LHS)42+2 == 42+2(RHS)
    
    //multiply;
    CHECK( (NEW (MultExpr)(NEW (NumExpr)(7),NEW (NumExpr)(2)))->equals(NEW (MultExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))== false);
    CHECK( (NEW (MultExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))->equals(NEW (MultExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))== true);
    CHECK( (NEW (MultExpr)(NEW (NumExpr)(8),NEW (NumExpr)(2)))->equals(NEW (MultExpr)(NEW (NumExpr)(42),NEW (NumExpr)(2)))== false);
    
    // testing Num:
    CHECK((NEW (NumExpr)(7))->equals(NEW (NumExpr)(7))==true);
    CHECK((NEW (NumExpr)(5))->equals(NEW (NumExpr)(3))==false);
    CHECK((NEW (NumExpr)(8))->equals(NEW (NumExpr)(9))==false);
    
    // Variable: a variable expression can be represented by string:
    //    That's a new subclass of the Expr class, just like Num or Add, except instead of int val you'll do std:string val:
    
    //Variable;
    CHECK( (NEW (VarExpr)("words"))->equals(NEW (VarExpr)("words"))== true);
    CHECK( (NEW (VarExpr)("song"))->equals(NEW (VarExpr)("words"))== false);
    CHECK( (NEW (VarExpr)("new"))->equals(NEW (VarExpr)("old"))== false);
    
}

//TEST_CASE("BoolExp"){
//    BoolExpr* num40 =  NEW (BoolExpr)("5"); // creating new Num object to assign memory for that object Making a pointer to the Expr class
//    BoolExpr* num41 = NEW (BoolExpr)(2);
//    CHECK(num41->equals(num40 ) == false);
//
//    BoolExpr* num42 =  NEW (BoolExpr)(NEW (BoolExpr)(8), NEW (BoolExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
//    BoolExpr* num43 = NEW (BoolExpr)(2);
//    CHECK(num43->equals(num42 ) == false);
//
//}

TEST_CASE("interp test"){
    //    CHECK( (5 == 6) == false);
    
    //do all the interp like 518 and 519:
    
    PTR(NumExpr) Num2 = NEW (NumExpr)(333); // create new variable called num2 which is pointer to a Num object class it will have all the properties of the Num class
    CHECK((  (Num2->interp() )->equals(NEW (NumVal)(333)) == true));// num2 has a attribute call val set to 333 which the interp retrieve 333 value
    
    PTR(Expr) num1 = NEW (NumExpr)(1);
    CHECK(((NEW (LetExpr)(NEW (VarExpr)("x"), num1, num1))->interp()->equals(NEW (NumVal)(1))) == true);
    
    //          CHECK((NEW (LetExpr) ("x",
    //                             NEW (AddExpr)r(NEW (NumExpr)(2), NEW (NumExpr)(3)),
    //                             NEW (MultExpr)(NEW (VarExpr)("x"), NEW (VarExpr)("x"))))
    //          ->interp()
    //          ->equals(NEW (NumVal)(25)));
    //
    PTR(AddExpr) add5 = NEW (AddExpr)(NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    PTR(AddExpr) add6 = NEW (AddExpr) (NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    //        CHECK ( (add5 -> equals(add6)) == true);
    
    PTR(AddExpr) add7 = NEW (AddExpr)(NEW (NumExpr)(9), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    PTR(AddExpr) add8 = NEW (AddExpr)(NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    //    CHECK ( (add7 -> equals(add8)) == false);
    
    PTR(MultExpr) mult5 = NEW (MultExpr)(NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    PTR(MultExpr) mult6 = NEW (MultExpr)(NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    //    CHECK ( (mult5 -> equals(mult6)) == true);
    
    PTR(MultExpr) mult7 = NEW (MultExpr)(NEW (NumExpr)(9), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    PTR(MultExpr) mult8 = NEW (MultExpr)(NEW (NumExpr)(15), NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    //    CHECK ( (mult7 -> equals(mult8)) == false);
    
    //    CHECK ( (new Num(5)) -> equals (new Num(7)) == false);
    
    CHECK ( (NEW (NumExpr)(5))->has_variable()== false); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(AddExpr) add4 = NEW (AddExpr)(NEW (NumExpr)(5), NEW (NumExpr)(3));
    CHECK ( (add4->has_variable())== false); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(AddExpr) add9 = NEW (AddExpr)(NEW (VarExpr)("Var1"), NEW (NumExpr)(3));
    CHECK ( (add9->has_variable())== true); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(AddExpr) mult4 = NEW (AddExpr)(NEW (NumExpr)(20), NEW (NumExpr)(5));
    CHECK ( (mult4->has_variable())== false); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(MultExpr) mult9 = NEW (MultExpr)(NEW (VarExpr)("Var2"), NEW (NumExpr)(5));
    CHECK ( (mult9->has_variable())== true); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(MultExpr) mult10 =   NEW (MultExpr)(NEW (NumExpr)(5), NEW (VarExpr)("Var2"));
    CHECK ( (mult10->has_variable())== true); // Num(5) is an integer which return false because variable are strings has_variable()
    
    PTR(AddExpr) add2 = NEW (AddExpr)(NEW (NumExpr)(1), NEW (NumExpr)(2)); // create an instance with the lhs and rhs
    
    
    PTR(Expr) num2 = NEW (NumExpr)(2);
    PTR(Expr) num3 = NEW (NumExpr)(3);
    CHECK((((NEW (AddExpr)(num1, num2))->interp())->equals(num3->interp())) == true); // 3 == 3 // interp will be adding 1+2=3
    
    PTR(AddExpr) add3 = NEW (AddExpr)(NEW (VarExpr)("this is a variable"), NEW (NumExpr)(2)); // trying to string create an instance with the lhs and rhs
    CHECK_THROWS_WITH( add3->interp(), "Runtime error unable to mutiply a non integer type ...." ); // checks that add3->interp()
    
    CHECK( (NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(7))) // created an add expression lhs is x and rhs is 7
          ->subst("x", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 7
          ->equals(NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(7))) == true ); // equals check the return of substr y  lhs y and rhs is 7
    
    CHECK( (NEW (AddExpr)(NEW (AddExpr)(NEW (VarExpr)("x"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) // created an add expression lhs is x and rhs is 4
          ->subst("x", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 4
          ->equals(NEW (AddExpr)(NEW (AddExpr)(NEW (VarExpr)("y"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) == true ); // equals check the return of substr y  lhs y and rhs is 4
    
    CHECK( (NEW (AddExpr)(NEW (AddExpr)(NEW (VarExpr)("x"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) // created an add expression lhs is x and rhs is 4
          ->subst("p", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 4
          ->equals(NEW (AddExpr)(NEW (AddExpr)(NEW (VarExpr)("y"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) == false ); // equals check the return of substr y  lhs y and rhs is 4
    PTR(MultExpr) mult2 = NEW (MultExpr)(NEW (NumExpr)(7), NEW (NumExpr)(6)); // create an instance with the lhs and rhs
    CHECK((mult2->interp()->equals(NEW (NumVal) (42)) == true)); // interp will be adding 7*6=42
    
    PTR(Expr) mult3 = NEW (MultExpr)(NEW (VarExpr)("trying adding String to Multiply class"), NEW (NumExpr)(10)); // trying to string create an instance with the lhs and rhs
    CHECK_THROWS_WITH( mult3->interp(), "Runtime error unable to mutiply a non integer type ...." ); // checks that add3->interp()
    
    CHECK( (NEW (MultExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(4))) // created an add expression lhs is x and rhs is 4
          ->subst("x", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 4
          ->equals(NEW (MultExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(4))) == true ); // equals check the return of substr y  lhs y and rhs is 4
    
    CHECK( (NEW (MultExpr)(NEW (AddExpr)(NEW (VarExpr)("x"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) // created an add expression lhs is x and rhs is 4
          ->subst("x", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 4
          ->equals(NEW (MultExpr)(NEW (AddExpr)(NEW (VarExpr)("y"),NEW (NumExpr)(5)), NEW (NumExpr)(4))) == true ); // equals check the return of substr y  lhs y and rhs is
}

TEST_CASE("to_string"){
    
    PTR(Expr) num1 =  NEW (NumExpr)(5); // Making a pointer to the Expr clas
    PTR(Expr) num2 = NEW (NumExpr)(2);
    CHECK(num1->to_string() == "5");
    CHECK(num2->to_string() == "2");
    
    // Add
    //1 + 2 —> “(1+2)"
    //E1 = add(n1, n2)
    //e1 ->to_string == “(1+2)”
    //    Expr* num1  new Add(new Num(1), new Add(new Num(2), new Num(3)))
    PTR(Expr) add10 =  NEW (AddExpr)(num1, num2);  //5+2
    CHECK(add10->to_string() == "(5+2)");
    
    //(5+2)*(5+2)
    //    Expr* add15 =  new Add(num1, num2);
    PTR(Expr) mult =  NEW (MultExpr)(add10, add10); //(5+2) *( 5+2)
    CHECK(mult->to_string() == "((5+2)*(5+2))");
    
    //    Expr* add =  new Add(add10, add10); //(5+2) *( 5+2)
    //    CHECK(add->to_string() == "5+2 + 5+2");
    //
    //((5+2)*5)
    PTR(Expr) add16 =  NEW (AddExpr)(num1, num2);  //5+2
    PTR(Expr) mult2 =  NEW (MultExpr)(add16, num1); // *5)
    CHECK(mult2->to_string() == "((5+2)*5)");
    
    // Mult: (5*2)
    PTR(Expr) add11 =  NEW (MultExpr)(num1, num2);
    CHECK(add11->to_string() == "(5*2)");
    
    // Variable:
    PTR(Expr) var1 = NEW (VarExpr)("festival");
    CHECK(var1->to_string() == "festival");
    
    PTR(Expr) add12 =  NEW (AddExpr)(num1, var1);
    CHECK(add12->to_string() == "(5+festival)");
    
    PTR(Expr) mult13 =  NEW (MultExpr)(num1, var1);
    CHECK(mult13->to_string() == "(5*festival)");
    
    //(5 + (5 + festival)) + ( festival+ (5+festival ))
//    PTR(Expr) add18 =  NEW (AddExpr)(NEW (NumExpr)(5), NEW (AddExpr)(NEW (NumExpr)(5), NEW (VarExpr)("festival"))), NEW (AddExpr)(NEW (VarExpr)("festival"), NEW (AddExpr)(NEW (NumExpr)(5), NEW (VarExpr)("festival"))));
//    CHECK(add18->to_string() == "((5+(5+festival))+(festival+(5+festival)))" );
    
    //LET to string:
    PTR(Expr) test_let = NEW (LetExpr)(NEW (VarExpr)("y"),NEW (NumExpr)(8),NEW (AddExpr)(NEW (NumExpr)(6), NEW (VarExpr)("y")));
    CHECK((test_let->to_string() == "(_let y=8 _in (6+y))"));
    
    //    CHECK(((new _let((new Variable("x")), new Add(num1 , num2), new Add(new Variable("x") , num2)))->to_string()) == "(_let x=(1+2) _in (x+2))");
    //        CHECK((((new _let((new Variable("x")), new Add(num1 , num2), new Add(new Variable("x") , num2)))->to_string()) == "(_let x=(1+2) _in x+2)") == false);
    
    
}

TEST_CASE("pretty_print_mult"){
    
    //1 * (2 + 3)
    PTR(AddExpr) add21 = NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3));
    PTR(MultExpr) mult22 = NEW (MultExpr)(NEW (NumExpr)(1), add21); // create an instance with the lhs and rhs
    CHECK(mult22->to_string_pretty() == "1 * (2 + 3)");
    
    PTR(MultExpr) mult24 = NEW (MultExpr)(NEW (NumExpr)(2), NEW (NumExpr)(2));
    //    Add* add22 = new Add(new Num(2), new Num(3));
    MultExpr mult25 = MultExpr(mult24, mult24); // create an instance with the lhs and rhs
    CHECK(mult25.to_string_pretty() == "(2 * 2) * 2 * 2"); // (2 * 2) * 2 * 2
    
    //2 * 3 * 4
    PTR(MultExpr) mult26 = NEW (MultExpr)(NEW (NumExpr)(2), NEW (MultExpr)(NEW (NumExpr)(3), NEW (NumExpr)(4)));
    CHECK(mult26->to_string_pretty() == "2 * 3 * 4" );
    //std::stringstream out("");//
    
    //1 + 2 * 3
    PTR(AddExpr) add25 = NEW (AddExpr)(NEW (NumExpr)(1), NEW (MultExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)));
    CHECK(add25->to_string_pretty() == "1 + 2 * 3");
    
    //1 + 2 + 3
    PTR(AddExpr) add40 = NEW (AddExpr)(NEW (NumExpr)(1), NEW (AddExpr)(NEW (NumExpr)(2), NEW (NumExpr)(3)));
    CHECK(add40->to_string_pretty() == "1 + 2 + 3");
    
    //(1 + 2) * 3) + 5"
    PTR(AddExpr) add60 = NEW (AddExpr)(NEW (NumExpr)(1), NEW (NumExpr)(2));
    PTR(MultExpr) mult61 = NEW (MultExpr)(add60, NEW (NumExpr)(3)); // create an instance with the lhs and rhs
    PTR(AddExpr) add61 = NEW (AddExpr)(mult61, NEW (NumExpr)(5));
    CHECK(add61->to_string_pretty() == "(1 + 2) * 3 + 5");
    
    PTR(MultExpr) mult33 = NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(8));
    MultExpr mult34 = MultExpr(mult33, mult33); // create an instance with the lhs and rhs
    CHECK(mult34.to_string_pretty() == "(8 * 8) * 8 * 8"); // (8 * 8) * 8 * 8
    
    //    "4 + testing"
    PTR(AddExpr) add26 =  NEW (AddExpr)(NEW (NumExpr)(4), NEW (VarExpr)("testing"));
    CHECK(add26->to_string_pretty() == "4 + testing");
    
    //50 + testing_Multiply")
    PTR(MultExpr) mult27 =  NEW (MultExpr)(NEW (NumExpr)(50), NEW (VarExpr)("testing_Multiply"));
    CHECK(mult27->to_string_pretty() == "50 * testing_Multiply");
    
    //std::stringstream out("");//
    
    PTR(NumExpr)num30 = NEW (NumExpr)(30);
    std::stringstream empty_string_string(""); // empty but gets set to 5
    num30->pretty_print(empty_string_string);
    CHECK( (empty_string_string.str() == "30") );
    
}


TEST_CASE( "more subst" ) {
    // _let x = 1
    // _in  x + 2  -> subst("x", y+3)
    // =
    // _let x = 1
    // _in  x + 2
    PTR(Expr) let1 = (NEW (LetExpr)(NEW (VarExpr)("x"),
                              NEW (NumExpr)(1),
                              NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(2))));
    CHECK( let1->subst("x", NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(3)))
          ->equals(let1));
    
    // _let x = x
    // _in  x + 2  -> subst("x", y+3)
    // =
    // _let x = y+3
    // _in  x + 2
    PTR(Expr) let2 = (NEW (LetExpr)(NEW (VarExpr)("x"),
                              NEW (VarExpr)("x"),
                              NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(2))));
    CHECK( let2->subst("x", NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(3)))
          ->equals(NEW (LetExpr)(NEW (VarExpr)("x"),
                               NEW (AddExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(3)),
                               NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(2)))));
    
    // _let x = 8
    // _in  x + 2 + y -> subst("y", 9)
    // =
    // _let x = 8
    // _in  x + 2 + 9
    
    PTR(Expr) let3 = (NEW (LetExpr)(NEW (VarExpr)("x"),
                              NEW (NumExpr)(8),
                              NEW (AddExpr)(NEW (VarExpr)("x"), NEW (AddExpr)( NEW (NumExpr)(2), NEW (VarExpr)("y")))));
    CHECK( let3->subst("y", NEW (NumExpr)(9))
          ->equals((NEW (LetExpr)(NEW (VarExpr)("x"),
                                NEW (NumExpr)(8),
                                NEW (AddExpr)(NEW (VarExpr)("x"), NEW (AddExpr)( NEW (NumExpr)(2), NEW (NumExpr)(9)))))));
    PTR(LetExpr)let4 = (NEW (LetExpr)(NEW (VarExpr)("z"), //lhs
                              NEW (VarExpr)("z"),
                              NEW (AddExpr)(NEW (VarExpr)("z"), NEW (NumExpr)(32))));
    CHECK( let4->subst("z", NEW (NumExpr)(0)) // all the z will get replaced with zeros
          ->equals(NEW (LetExpr)(NEW (VarExpr)("z"),
                               NEW (NumExpr)(0), // z gets replaced here
                               NEW (AddExpr)(NEW (VarExpr)("z"), NEW (NumExpr)(32)))));
}


//LET  equals:
TEST_CASE("let_equals") {
    
    PTR(LetExpr) let42 =  NEW (LetExpr)(NEW (VarExpr)("8"), NEW (VarExpr)("4"),NEW (VarExpr)("7") ); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num62 = NEW (NumExpr)(2);
    CHECK(let42->equals(num62) == false);
    
}
//You'll need to update your existing Expr::interp tests to use number-value objects instead of integers. Remember to change == for comparing integers to ->equals for comparing value objects.

//_Let interp:
TEST_CASE("let_interp") {
    
    PTR(LetExpr) let2 = NEW (LetExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(5),NEW (AddExpr)(NEW (NumExpr)(2), NEW (VarExpr)("x"))); // create an instance with the lhs and rhs
    CHECK((let2->interp()->equals(NEW  (NumVal)(7)) == true)); // interp will be adding 7*6=42
    
    
}

//Let has_variable:
TEST_CASE("let_has_variable") {
    PTR(LetExpr) let3 = NEW (LetExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(5),NEW (AddExpr)(NEW (NumExpr)(2), NEW (VarExpr)("x")));
    CHECK(let3->has_variable()== true);
}

TEST_CASE("add_print") {
    PTR(AddExpr) add25 = NEW (AddExpr)(NEW (VarExpr)("a"), NEW (VarExpr)("b"));
    std::stringstream empty_string_string(""); // empty but gets set to 5
    add25->print(empty_string_string);
    CHECK( (empty_string_string.str() == "(a+b)") );
    
}

// to change between main file in the msdscript and test_msdscript click on product then scheme then click on either MSDSCRIPT or TEST_GENERATOR



TEST_CASE("Bool_Exp"){
    
    PTR(BoolExpr) num40 =  NEW (BoolExpr)(true); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    CHECK(num40->equals(num40 ) == true);
    
    //false == false -> true
    PTR(BoolExpr) num41 =  NEW (BoolExpr)(false);
    CHECK(num41->equals(num41 ) == true);
    
    num41 = NEW (BoolExpr)(false);
    CHECK(num41->equals(num40 ) == false);
    
    PTR(NumExpr) num42 =  NEW (NumExpr)(2);
    CHECK(num40->equals(num42 ) == false);
    
    // Interp:
    PTR(BoolExpr) bool1 = NEW (BoolExpr)(true);
    CHECK(bool1->interp()->equals(NEW (BoolVal)(bool1->rep)) == true);
    
    // has variable:
    
    PTR(BoolExpr) trueBool = NEW (BoolExpr)(true);
    CHECK(trueBool->has_variable() == false);
    
    
    // subst:
    PTR(BoolExpr) trueBool2 = NEW (BoolExpr)(true);
    
    CHECK( (trueBool2) // created an add expression lhs is x and rhs is 7
          ->subst("x", NEW (VarExpr)("y"))// then substr take the previous expression replace x with y  lhs y and rhs is 7
          ->equals(trueBool2) == true ); // equals check the return of substr y  lhs y and rhs is 7
    //print:
//    void BoolExpr::print(std::ostream &stream){
//        stream << this->rep;
//    }
    PTR(BoolExpr) trueBool3 = NEW (BoolExpr)(true);
    CHECK(trueBool3->to_string() == "_true");
    
    PTR(BoolExpr) trueBool4 = NEW (BoolExpr)(false);
    CHECK(trueBool4->to_string() == "_false");
    
    //pretty print;
    //    void BoolExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
    //        stream << this->rep;
    //    }
    PTR(BoolExpr) trueBool5 = NEW (BoolExpr)(true);
    CHECK(trueBool5->to_string_pretty() == "_true");
    
    PTR(BoolExpr) trueBool6 = NEW (BoolExpr)(false);
    CHECK(trueBool6->to_string_pretty() == "_false");


    
}

TEST_CASE("equal_expression") {
    //equals:
    PTR(EqExpr) equals1 = NEW (EqExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(9));
    PTR(EqExpr) equals2 = NEW (EqExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(9));
    PTR(EqExpr) equals3 = NEW (EqExpr)(NEW (VarExpr)("b"), NEW (NumExpr)(9));
    CHECK( equals1->equals(equals2) == true);
    CHECK( equals1->equals(equals3) == false);
    CHECK( equals2->equals(NEW (VarExpr)("7")) == false);
    
    //    EqExpr::EqExpr(Expr *lhs, Expr *rhs){
    //        this-> lhs = lhs;
    //        this-> rhs = rhs;
    //    }
    // 1 == 1
    // x == y
    PTR(EqExpr) equalexpr = NEW (EqExpr)(NEW (NumExpr) (1), NEW (NumExpr) (1) );
    CHECK(equalexpr->interp()->equals(NEW (BoolVal)(true)) == true);
    
    PTR(EqExpr) equalexpr2 = NEW (EqExpr)(NEW (NumExpr) (1), NEW (NumExpr) (3) );
    CHECK(equalexpr2->interp()->equals(NEW (BoolVal)(false)) == true);
    
    PTR(Expr) muilt2 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num2 = NEW (NumExpr)(2);
    CHECK(num2->equals(muilt2 ) == false);
    
    // has_variable  y == 6
    CHECK( ((NEW (EqExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(6)))
            ->has_variable()) == true );
    
    // has_variable 8 == 6
    CHECK( ((NEW (EqExpr)(NEW (NumExpr)(8), NEW (NumExpr)(6)))
            ->has_variable()) == false );
    
    //subst:
    // subst x in j == 8 -> equals x == 6
    std::string j = (NEW (EqExpr)(NEW (VarExpr)("j"), NEW (NumExpr)(8)))->subst("j", NEW (VarExpr)("a"))->to_string();
    CHECK( (j == "(a==8)") );
    
  
    
    // pretty_print:
    PTR(EqExpr) e1 = NEW (EqExpr)(NEW (VarExpr)("a"), NEW (NumExpr)(1));
    PTR(AddExpr) a1 = NEW (AddExpr)(e1, NEW (NumExpr)(2));
    PTR(MultExpr) m1 = NEW (MultExpr)(NEW (NumExpr)(1), a1);
    CHECK( m1->to_string_pretty() == "1 * ((a == 1) + 2)" );
     
}


TEST_CASE("if_expr") {
    
    //    IfExpr::IfExpr(Expr *_if, Expr *_then, Expr *_else){
    //
    //        this-> _if = _if;
    //        this-> _then = _then;
    //        this-> _else = _else;
    
    // look the equals as sample
    
    //if:
    // if (true)
            //then 1
      // else
    PTR(IfExpr) if_expr = NEW (IfExpr)(NEW (BoolExpr)(true),NEW (NumExpr)(1), NEW (NumExpr)(2) );
    CHECK(if_expr->interp()->equals(NEW (NumVal)(1)));
    
    PTR(IfExpr) if_expr2 = NEW (IfExpr)(NEW (BoolExpr)(false),NEW (NumExpr)(1), NEW (NumExpr)(2));
    CHECK(if_expr2->interp()->equals(NEW (NumVal)(2)) );
    
//    equals:
   
    // true

    PTR(Expr) if_expr11 =  NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(4), NEW (NumExpr)(5)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(IfExpr) if_expr22 = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(4), NEW (NumExpr)(5));
    CHECK(if_expr22->equals(if_expr11 ) == true);
    
    //false
    PTR(Expr) if_expr14 =  NEW (IfExpr)(NEW (BoolExpr)(false), NEW (NumExpr)(4), NEW (NumExpr)(5)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(IfExpr) if_expr23 = NEW (IfExpr)(NEW (BoolExpr)(false), NEW (NumExpr)(1), NEW (NumExpr)(5));
    CHECK(if_expr23->equals(if_expr14 ) == false);
    
    
//    CHECK_THROWS_AS(NEW (IfExpr)(NEW (NumExpr)(1), NEW (NumExpr)(2), NEW (NumExpr)(3)), std::exception);
    
    PTR(Expr) if_expr17 =  NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(4), NEW (NumExpr)(5)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) numExpr27 = NEW  (NumExpr)(6);
    CHECK(if_expr17->equals(numExpr27 ) == false);
    
    CHECK ( (if_expr17)->has_variable()== false); // Num(5) is an integer which return false because variable are strings has_variable()

    
    PTR(Expr) if_expr19 =  NEW (IfExpr)(NEW (BoolExpr)(false), NEW (NumExpr)(4), NEW (NumExpr)(5)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(IfExpr) if_expr29 = NEW (IfExpr)(NEW (BoolExpr)(false), NEW (NumExpr)(1), NEW (NumExpr)(5));
    CHECK(if_expr29->equals(if_expr19 ) == false);
    
    
    //subst:
    // subst x in j == 8 -> equals x == 6
    PTR(IfExpr) r = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(8), NEW (NumExpr)(6));
    CHECK( (r->subst("r", NEW (VarExpr)("a"))->equals(r)));
    
    //IfExpr pretty_print:
//    std::stringstream =
    PTR(IfExpr) e1 = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(1), NEW (NumExpr)(4));
   
    CHECK( e1->to_string() == "(_if _true _then 1 _else 4)");
    
    //IfExpr pretty_print:
    PTR(IfExpr) e2 = NEW (IfExpr)(NEW (BoolExpr)(true), NEW (NumExpr)(1), NEW (NumExpr)(4));
   
    CHECK( e2->to_string_pretty() == "_if _true _then 1 _else 4");
    

    
}

TEST_CASE("fun_expr") {
    
//    _let f = _fun (x) x
//    _in  f(2)
    //equals
    PTR(FunExpr) fun1 =  NEW (FunExpr)("x", NEW (VarExpr)("x"));
    PTR(FunExpr) fun2 =  NEW (FunExpr)("y", NEW (VarExpr)("y"));// creating new Num object to assign memory for that object Making a pointer to the Expr class
    //NumExpr* num = NEW (NumExpr)(2);
    CHECK(fun1->equals(fun2) == false);
    //equals
    PTR(FunExpr) fun3 =  NEW (FunExpr)("x", NEW (VarExpr)("x"));// creating new Num object to assign memory for that object Making a pointer to the Expr class
    //NumExpr* num = NEW (NumExpr)(2);
    CHECK(fun1->equals(fun3) == true);
    ////equals NULL
    PTR(FunExpr) fun4 = NULL;
    CHECK(fun1->equals(fun4) == false);
    //Has_Variable
    CHECK_THROWS_WITH( fun1->has_variable(), "method not implemented invalid call" );
    //Subst
    CHECK(fun1->subst("x", fun1)->equals(NEW (FunExpr)("x", NEW (VarExpr)("x"))));
    

//    FunExpr::interp:
    PTR(Expr) n1 = NEW (NumExpr)(1);
    PTR(Expr) f1 = NEW (FunExpr)("y", n1);

    CHECK(f1->interp()->equals(n1->interp()) == false);
    
//subst ask Matthew: is this a function expression or call expression?
    
//    CHECK(fun1->subst("y", fun1)->equals(NEW (FunExpr)("x", NEW (VarExpr)("x")->subst("y", NEW (VarExpr)("x")))));
    
    //print:
    std::stringstream empty_string_string(""); // empty but gets set to fun1
    fun1->print(empty_string_string);
    //_fun (x) x
    //std::cout << empty_string_string.str() << std::endl;
    CHECK( (empty_string_string.str() == "(_fun (x) x) ") );
    
    
}


TEST_CASE("call_expr") {
    
//    (_fun (x) x)(10)
    
    //equals
    PTR(CallExpr) call1 =  NEW (CallExpr)(NEW (FunExpr)("x", NEW (VarExpr)("x")), NEW (NumExpr)(10));
    PTR(CallExpr) call2 =  NEW (CallExpr)(NEW (FunExpr)("x", NEW (VarExpr)("x")), NEW (NumExpr)(10));
    PTR(CallExpr) call3 = NULL;
    PTR(CallExpr) call4 =  NEW (CallExpr)(NEW (FunExpr)("x", NEW (VarExpr)("x")), NEW (NumExpr)(11));
    CHECK(call1->equals(call3) == false);
    CHECK(call1->equals(call2) == true);
    CHECK(call1->equals(call4) == false);

    //Has_Variable
    CHECK_THROWS_WITH( call1->has_variable(), "method not implemented invalid call" );
    
    //print:
    std::stringstream empty_string_string(""); // empty but gets set to fun1
    call1->print(empty_string_string);
    //_fun (x) x
    //std::cout << empty_string_string.str() << std::endl;
    CHECK( (empty_string_string.str() == "(_fun (x) x) (10)") );
    
//    CallExpr Interp
//    PTR(Val) CallExpr::interp() {
//
//        return to_be_called->interp()->call(actual_arg->interp());
//        //
//
//    }

    // Interp:
    PTR(Expr) num1 = NEW (NumExpr)(1);
    PTR(VarExpr) y = NEW (VarExpr)("y");

    PTR(Expr) fun1 = NEW (FunExpr)("y", NEW (AddExpr)(y, num1));
    PTR(Expr) call_expr1 = NEW (CallExpr) (fun1, num1);
    CHECK(call_expr1->interp()->equals(NEW (NumVal)(2)));
    
    
//CallExpr::subst:
    
// fun1(y) y+1
//fun1(1)
    CHECK(call_expr1->subst("y", NEW (VarExpr)("x"))->equals(call_expr1));
    
}

TEST_CASE("fan_val") {
    
    CHECK_THROWS_WITH((NEW (BoolVal)(true))->call(NULL),"unable to call a bool");
    // FunVal::call.
    //return this->body->subst(formal_arg, actual_arg->to_expr())->interp();
    CHECK((NEW (FunVal)("x", NEW (NumExpr)(1)))->equals(NEW (FunVal)("x", NEW (NumExpr)(1))));
    
    //FunVal::call:
    PTR(Expr) n1 = NEW (NumExpr)(1);
    PTR(Val) num1 = NEW (NumVal)(1);
    
    CHECK((NEW (FunVal)("y", n1))->call(num1)->equals(NEW (NumVal)(1)));
    
   
    
    
    
//    FunVal::FunVal(std::string formal_arg, PTR(Expr) body) {
//        this->formal_arg = formal_arg;
//        this->body = body;
//    }
    
//    PTR(Val) FunVal::call(PTR(Val) actual_arg) {
//        //f(2) , Val* actual_arg is 2
//        //want to return the result of subst 2 into the function f
//        //called on a FunVal, all FunVals have a string formal_arg and a Expr* body
//        //_let f = _fun (x = formal_arg) Expr* body = x*x  // this is a function
//        // when calling a function I pass a actual argument = _in  f(2)
//        // this is the result of let which format it like this = (_fun (x) x*x)(2)
//        //2*2 = replace the formal argument x which with actual arguament which 2
//        // then evaluate with interp() which will give a 4:
//        return this->body->subst(formal_arg, actual_arg->to_expr())->interp();
//    }
    
    
}





// NOTE from Matthew about the homework: Looks generally right, but I'm not seeing direct tests for CallExpr::subst, FunExpr::interp, or FunVal::call. (Those might get triggered by other tests, but there should be direct tests of those methods.) Let me know when you've added those, and then I'll take another look.
//Matthew Flatt  6:01 PM
//I made a first pass grading the homework on adding functions to MSDscript. For many of you, I asked for some corrections or improvements, so please see comments for the assignment in Canvas. If you don’t yet have a grade, add a comment after you’ve made the improvement, and I’ll take another look. (Usually, the requested improvement is to add some missing tests. Let me know if I just overlooked tests that are already there.)

//void FunExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
//    //_fun expressions need parentheses in the same contexts where _let would need parentheses. Add a newline after the argument parentheses for _fun and indent the body two spaces more than the column where _fun starts
//
//    // add a parenthesis
//    if(prettyValue == print_group_add_or_mult){
//        stream << "(";
//    }
//    stream << "_fun (";
//    //formal_arg, body)
//    stream << formal_arg;
//    stream << ")\n";
//
//    stream << "  ";
//    body->pretty_print_at(stream, print_group_add);
//    if(prettyValue == print_group_add_or_mult){
//        stream << ")";
//    }














// IF PRETTY PRINT
//
////void IfExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){
////
//////    // add a parenthesis
//if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
//    stream << "(";
//
//    stream << " _if ";
//    _if->pretty_print_at(stream, print_group_add);
//    stream << " _then ";
//    _then->pretty_print_at(stream, print_group_none);
//    stream << " _else ";
//    _else->pretty_print_at(stream, print_group_none); // find out which print group is this here
//    if(prettyValue == print_group_add_or_mult || prettyValue == print_group_add){
//        stream << ")";
//    }


//
//  LET PRETTY PRINT:
//    void LetExpr::pretty_print_at(std::ostream &stream, print_mode_t prettyValue){ // the prettyValue is used to determine if I need parenthesis or not
//
//        //==== _LET ==//
//        // if come from an add or a mult add the open bracket
//        if(prettyValue == print_group_add || prettyValue == print_group_add_or_mult || prettyValue == print_group_let){
//            stream << "(_let " ;
//            stream << lhs->val;
//            //lhs->pretty_print_at(stream, print_group_add);
//            stream << " = ";
//            rhs->pretty_print_at(stream, print_group_none);
//            stream << "     _in ";
//            body->pretty_print_at(stream, print_group_let);
//            stream << ")";
//        }
//    }





