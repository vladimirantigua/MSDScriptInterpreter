//
//  step.hpp
//  MSDscript
//
//  Created by Vladimir Antigua on 3/31/21.
//

#ifndef step_hpp
#define step_hpp

#include <stdio.h>
#include "pointer.h"
#include "expr.h"
#include "env.h"
#include "cont.h"
#include "val.h"

class Env;
class Expr;
class Val;
class Cont;
//CLASS (Step);

class Step {
public:
    
    typedef enum {
        interp_mode,
        continue_mode
        
    } mode_t;
    
    static mode_t mode;    /* choosesmode */
    
    static PTR(Expr) expr; /* forinterp_mode */
    static PTR(Env)  env;  /* forinterp_mode */
    static PTR(Val)  val;  /* forcontinue_mode */
    static PTR(Cont) cont; /* allmodes */
    static PTR(Val) interp_by_steps(PTR(Expr) e);
};

#endif /* step_hpp */
