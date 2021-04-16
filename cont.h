//
//  cont.hpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/31/21.
//

#ifndef cont_hpp
#define cont_hpp

#include <stdio.h>
#include "pointer.h"
#include "expr.h"
#include "env.h"
#include "step.h"
#include "val.h"

class Cont;
class Env;
class Expr;
class Val;
class Step;

CLASS (Cont) {
public:
    virtual void step_continue() = 0;
    static PTR(Cont) done;
};

class RightThenAddCont : public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    RightThenAddCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
};

class AddCont : public Cont {
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    AddCont(PTR(Val) lhs_val, PTR(Cont) rest);
};

class RightThenMultCont : public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    RightThenMultCont(PTR(Expr) rhs, PTR(Env) env, PTR(Cont) rest);
};

class MultCont : public Cont {
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    MultCont(PTR(Val) lhs_val, PTR(Cont) rest);
};

class RightThenEqCont : public Cont {
public:
    
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) cont;
    void step_continue();
    RightThenEqCont(PTR(Expr)rhs,  PTR(Env) env, PTR(Cont) cont);
};

class EqCont : public Cont {
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    EqCont(PTR(Val) lhs_val, PTR(Cont) rest);
};

class IfBranchCont: public Cont {
public:
    PTR(Expr) then_part;
    PTR(Expr) else_part;
    PTR(Env) env;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    IfBranchCont(PTR(Expr) then_part, PTR(Expr) else_part, PTR(Env) env, PTR(Cont) rest);
};

class LetBodyCont : public Cont {
public:
    std::string var;
    PTR(Expr) body;
    PTR(Env) env;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    LetBodyCont(std::string var, PTR(Expr) body, PTR(Env) env, PTR(Cont) rest);
};

//converting function call: 
class ArgThenCallCont : public Cont {
public:
    PTR(Expr) actual_arg;
    PTR(Env) env;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    ArgThenCallCont(PTR(Expr) actual_arg, PTR(Env) env, PTR(Cont) rest);
};

class CallCont : public Cont {
public:
    PTR(Val) to_be_called_val;
    PTR(Cont) rest;
    void step_continue();
    //constructor:
    CallCont(PTR(Val) to_be_called_val, PTR(Cont) rest);
};

class DoneCont : public Cont {
public:
    //constructor:
    DoneCont();
    void step_continue();
};

#endif /* cont_hpp */
