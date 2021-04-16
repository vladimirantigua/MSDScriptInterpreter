//
//  step.cpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/31/21.
//
//
#include "step.h"
#include "cont.h"
#include "expr.h"
#include "parse.h"
#include "catch.h"

Step::mode_t Step::mode;

PTR(Cont) Step::cont;

PTR(Expr) Step::expr; /* only for Step::interp_mode */

PTR(Val) Step::val;        /* only for Step::continue_mode */
PTR(Env) Step::env;

PTR(Val) Step::interp_by_steps(PTR(Expr) e) {
    Step::mode = Step::interp_mode;
    Step::expr = e;
    Step::env = Env::empty;
    Step::val = nullptr;
    
    Step::cont = Cont::done;
    
    while (1) {
        if (Step::mode == Step::interp_mode)
            Step::expr->step_interp();
        else {
            if (Step::cont == Cont::done)
                return Step::val;
            else
                Step::cont->step_continue();
        }
    }
}
