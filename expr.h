//
//  expr.h
//  MSDscript Command Line
//
//  Created by Vladimir Antigua on 1/24/21.
//

#ifndef expr_h
#define expr_h
#include <stdio.h>
#include <string>
#include "pointer.h"
#include "env.h"
#include "step.h"

// outside of parent class
typedef enum {
    print_group_none, // nothing need parenthesis possible values
    print_group_add, // need parenthesis if adding expression possible values
    print_group_add_or_mult, // use parenthesis if mult or add possible values
    print_group_let // this is the print group for the _let
} print_mode_t; // this is the Type name

// leave it unchage 
class Val; //In "expr.h", use a class Val; declaration near the top so that the declaration of

class Env;

// parent class
//class T { .... };  CLASS (T) { .... };

CLASS (Expr) {
public:
    virtual bool equals(PTR(Expr) other) = 0;
    //Refactor your MSDscript implementation so that Expr::interp returns Val* instead of int.
    //virtual PTR(Val) interp(PTR(Env) env) = 0;
    virtual PTR(Val) interp(PTR(Env) env) = 0; // changed to virtual int interp() = 0;
    virtual bool has_variable() = 0;
    
    virtual void print(std::ostream &stream) = 0;
    
    //Although it's not required, consider adding a (non-virtual) to_strin*g me*thod to Expr. That method can call print, but in many cases (like testing), getting a string back will be more convenient than setting up a std::ostream for every test:
    std::string to_string(); // non-virtual
    
    // to_string_pretty()
    std::string to_string_pretty();// non-virtual
    
    //add pretty_print method to Expr: uncomment below and find out why it is failing:
    
    void pretty_print(std::ostream &stream);//non-virtual
    
    // Helper fucntion pretty_print_at:
    virtual void pretty_print_at(std::ostream &stream, print_mode_t prettyValue) = 0;
    virtual void step_interp() = 0;
    
    //parse-str:
//    static PTR(Expr) parse_str(std::string s);
    
};

// subclass
class NumExpr : public Expr { // subclass Num extends parent class Expr
public:
    int rep;
    
    //constructor
    NumExpr(int val);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); // it is a non vitual no needed
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    void step_interp();
};

// subclass VARIABLE
class VarExpr : public Expr {
public:
    std::string val;
    
    //constructor
    VarExpr(std::string val);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream);
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    
    void step_interp();
};

// subclass ADD
class AddExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    
    //constructor
    AddExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); non virtual
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue); // only add it on add and multipy because are the only subclasses needing parenthesis
    
    void step_interp();
    
};

// subclass MULTIPLY
class MultExpr : public Expr {
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    
    //constructor
    MultExpr(PTR(Expr) lhs, PTR(Expr) rhs);
    // in main create a object representation for the constructor:
    // new add(new Num(42), new Num(2)); means: 42+2
    
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //        void pretty_print(std::ostream &stream); non virtual
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue); //
    void step_interp();
};

// subclass _let
class LetExpr : public Expr {
public:
    //    Variable *lhs;//this should be a variable type because the let keyword should be a variable
    PTR(VarExpr) lhs; // std::string lhs;
    PTR(Expr) rhs;
    PTR(Expr) body;
    
    //constructor
    LetExpr(PTR(VarExpr) lhs, PTR(Expr) rhs, PTR(Expr) body);
    //    LetExpr(std::string lhs, Expr *rhs, Expr *body);
    
    // Implement Equals: public is like extends in Java
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); non virtual
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue); // only add it on add and multipy because are the only subclasses needing parenthesis PTR(Val)
    
    void step_interp();
    
};

// subclass ifExpr:

class IfExpr : public Expr { // subclass Num extends parent class Expr
public:
    
    PTR(Expr) _if;
    PTR(Expr) _then;
    PTR(Expr) _else;
    
    
    //constructor
    IfExpr(PTR(Expr) _if, PTR(Expr) _then, PTR(Expr) _else);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); // it is a non vitual no needed
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    
    void step_interp();
};

// subclass BoolExpr:
class BoolExpr : public Expr { // subclass Num extends parent class Expr
public:
    //std::string rep;
    bool rep;
    
    //constructor
    //BoolExpr(std::string val);
    BoolExpr(bool rep);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); // it is a non vitual no needed
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    
    void step_interp();
};

// subclass EqExpr:
// <expr> == <expr>
class EqExpr : public Expr { // subclass Num extends parent class Expr
public:
    
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    
    //constructor
    EqExpr (PTR(Expr) lhs, PTR(Expr) rhs);
    
    // Implement Equals: public is like extends in Java
    virtual bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &stream);
    //    void pretty_print(std::ostream &stream); // it is a non vitual no needed
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    
    void step_interp();
};

// subclasses use lowercase class like usual
class FunExpr : public Expr {
public:
    
    std::string formal_arg;
    PTR(Expr) body;
    
    //contructor:
    FunExpr(std::string formal_arg,  PTR(Expr) body);
  
    bool equals(PTR(Expr) other);
    
    PTR(Val) interp(PTR(Env) env); //
    
    bool has_variable();
    
    void print(std::ostream &stream);
    
    void pretty_print(std::ostream &stream);
    
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
   
    void step_interp();
};

class CallExpr : public Expr {
public:
    
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;
    
    CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg);
    
    bool equals(PTR(Expr) other);
    
    PTR(Val) interp(PTR(Env) env);
    
    bool has_variable();
    
    void print(std::ostream &stream);
    
    void pretty_print(std::ostream &stream);
    
    void pretty_print_at(std::ostream &stream, print_mode_t prettyValue);
    
    void step_interp();
};

#endif /* expr_h */

