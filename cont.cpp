//
//  cont.cpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/31/21.

#include <stdexcept>
#include "cont.h"
#include "step.h"
#include "expr.h"


PTR(Cont) Cont::done = NEW(DoneCont)();

DoneCont::DoneCont() { }

void DoneCont::step_continue() {
    throw std::runtime_error("can't continue done");
}

void IfBranchCont::step_continue()
{
    PTR(Val) test_val = Step::val;
    Step::mode = Step::interp_mode;
    if (test_val->is_true())
        Step::expr = then_part;
    else
        Step::expr = else_part;
    Step::env = env;
    Step::cont = rest;
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in IfBranchCont.." << std::endl;
//        
//    }
}

//contructor:
IfBranchCont::IfBranchCont(PTR(Expr) then_part, PTR(Expr) else_part, PTR(Env) env, PTR(Cont) rest){
    
    this->then_part = then_part;
    this->else_part = else_part;
    this->env = env;
    this->rest = rest;
}

void LetBodyCont::step_continue()
{
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(var,
                                 Step::val,
                                 env);
    Step::cont = rest;

    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in LetBodyCont..." << std::endl;
//        
//    }
}

//contructor:
LetBodyCont::LetBodyCont(std::string var, PTR(Expr) body, PTR(Env) env, PTR(Cont) rest){
    this->var = var;
    this->body = body;
    this->env = env;
    this->rest = rest;
}


//converting function call: 
void ArgThenCallCont::step_continue() {
    Step::mode = Step::interp_mode;
    Step::expr = actual_arg;
    Step::env = env;
    Step::cont = NEW(CallCont)(Step::val, rest);
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in ArgThenCallCont..." << std::endl;
//
//    }
}

//constructor:
ArgThenCallCont::ArgThenCallCont(PTR(Expr) actual_arg, PTR(Env) env, PTR(Cont) rest){
    
    this->actual_arg = actual_arg;
    this->env = env;
    this->rest = rest;
}

void CallCont::step_continue() {
    to_be_called_val->call_step(Step::val, rest);
}

//contructor implementation:
CallCont::CallCont(PTR(Val) to_be_called_val, PTR(Cont) rest){
    this->to_be_called_val = to_be_called_val;
    this->rest = rest;
}

RightThenAddCont::RightThenAddCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest) {
    this->rhs = rhs;
    this->env = env;
    this->rest = rest;
}

void RightThenAddCont::step_continue() {
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(AddCont)(Step::val, rest);
    
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in RightThenAddCont" << std::endl;
//
//    }
}

AddCont::AddCont(PTR(Val) lhs_val, PTR(Cont) rest) {
    this->lhs_val = lhs_val;
    this->rest = rest;
}

void AddCont::step_continue() {
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->add_to(Step::val);// need to have the add_to(Step::val) instead of the + sign
    Step::cont = rest;
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in AddCont" << std::endl;
//
//    }
}

RightThenMultCont::RightThenMultCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest){
    
    this->rhs = rhs;
    this->env = env;
    this->rest = rest;
}

void RightThenMultCont::step_continue() {
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(MultCont)(Step::val, rest);
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in RightThenMultCont" << std::endl;
//
//    }
}

void MultCont::step_continue() {
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->mult_to(Step::val);// need to have the add_to(Step::val) instead of the + sign
    Step::cont = rest;
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in MultCont" << std::endl;
//
//    }
}

MultCont::MultCont(PTR(Val) lhs_val, PTR(Cont) rest){
    this->lhs_val = lhs_val;
    this->rest = rest;
}

RightThenEqCont::RightThenEqCont(PTR(Expr)rhs,  PTR(Env) env, PTR(Cont) cont){
    this->rhs = rhs;
    this->env = env;
    this->cont = cont;
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in RightThenEqCont" << std::endl;
//
//    }
}

void RightThenEqCont::step_continue() {
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(EqCont)(Step::val, cont);
}

void EqCont::step_continue() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(lhs_val->equals(Step::val));// need to return a value object need to have the add_to(Step::val) instead of the + sign
    Step::cont = rest;
    
    //checking for null:
//    if(Step::cont == nullptr){
//        std::cout << "NULLPTR in EqCont" << std::endl;
//
//    }
}

EqCont::EqCont(PTR(Val) lhs_val, PTR(Cont) rest) {
    this->lhs_val = lhs_val;
    this->rest = rest;
}
