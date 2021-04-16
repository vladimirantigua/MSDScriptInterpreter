//
//  test.cpp
//  MSDscript
//
//  Created by Vladimir Antigua on 4/10/21.
//

#include <stdio.h>

#include<iostream>
#include <string>
#include <stdexcept>
#include<sstream>
#include "catch.h"
#include "expr.h"
#include "parse.h"
#include "val.h"
#include "env.h"
#include "pointer.h"
#include "step.h"
#include "cont.h"


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
    // pass this into all interp(Env::empty) test cases:
    CHECK((  (Num2->interp(Env::empty) )->equals(NEW (NumVal)(333)) == true));// num2 has a attribute call val set to 333 which the interp retrieve 333 value
    
    PTR(Expr) num1 = NEW (NumExpr)(1);
    CHECK(((NEW (LetExpr)(NEW (VarExpr)("x"), num1, num1))->interp(Env::empty)->equals(NEW (NumVal)(1))) == true);
    
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
    CHECK((((NEW (AddExpr)(num1, num2))->interp(Env::empty))->equals(num3->interp(Env::empty))) == true); // 3 == 3 // interp will be adding 1+2=3
    
    PTR(AddExpr) add3 = NEW (AddExpr)(NEW (VarExpr)("this is a variable"), NEW (NumExpr)(2)); // trying to string create an instance with the lhs and rhs
    CHECK_THROWS_WITH( add3->interp(NEW(ExtendedEnv)("x", NEW(NumVal)(1),
                                                     NEW(EmptyEnv)())), "free variable: this is a variable" ); // checks that add3->interp()
    
    PTR(MultExpr) mult2 = NEW (MultExpr)(NEW (NumExpr)(7), NEW (NumExpr)(6)); // create an instance with the lhs and rhs
    CHECK((mult2->interp(Env::empty)->equals(NEW (NumVal) (42)) == true)); // interp will be adding 7*6=42
    
    PTR(Expr) mult3 = NEW (MultExpr)(NEW (VarExpr)("trying adding String to Multiply class"), NEW (NumExpr)(10)); // trying to string create an instance with the lhs and rhs
    CHECK_THROWS_WITH( mult3->interp(NEW(ExtendedEnv)("x", NEW(NumVal)(1),
                                                      NEW(EmptyEnv)())), "free variable: trying adding String to Multiply class" ); // checks that add3->interp()
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
    CHECK((let2->interp(Env::empty)->equals(NEW  (NumVal)(7)) == true)); // interp will be adding 7*6=42
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
    CHECK(bool1->interp(Env::empty)->equals(NEW (BoolVal)(bool1->rep)) == true);
    
    // has variable:
    
    PTR(BoolExpr) trueBool = NEW (BoolExpr)(true);
    CHECK(trueBool->has_variable() == false);
    
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
    CHECK(equalexpr->interp(Env::empty)->equals(NEW (BoolVal)(true)) == true);
    
    PTR(EqExpr) equalexpr2 = NEW (EqExpr)(NEW (NumExpr) (1), NEW (NumExpr) (3) );
    CHECK(equalexpr2->interp(Env::empty)->equals(NEW (BoolVal)(false)) == true);
    
    PTR(Expr) muilt2 =  NEW (MultExpr)(NEW (NumExpr)(8), NEW (NumExpr)(4)); // creating new Num object to assign memory for that object Making a pointer to the Expr class
    PTR(NumExpr) num2 = NEW (NumExpr)(2);
    CHECK(num2->equals(muilt2 ) == false);
    
    // has_variable  y == 6
    CHECK( ((NEW (EqExpr)(NEW (VarExpr)("y"), NEW (NumExpr)(6)))
            ->has_variable()) == true );
    
    // has_variable 8 == 6
    CHECK( ((NEW (EqExpr)(NEW (NumExpr)(8), NEW (NumExpr)(6)))
            ->has_variable()) == false );
    
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
    CHECK(if_expr->interp(Env::empty)->equals(NEW (NumVal)(1)));
    
    PTR(IfExpr) if_expr2 = NEW (IfExpr)(NEW (BoolExpr)(false),NEW (NumExpr)(1), NEW (NumExpr)(2));
    CHECK(if_expr2->interp(Env::empty)->equals(NEW (NumVal)(2)) );
    
    //equals:
    
    //true
    
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
    
    //    FunExpr::interp:
    PTR(Expr) n1 = NEW (NumExpr)(1);
    PTR(Expr) f1 = NEW (FunExpr)("y", n1);
    
    CHECK(f1->interp(Env::empty)->equals(n1->interp(Env::empty)) == false);
    
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
    //_fun (y) y+1
    PTR(Expr) fun1 = NEW (FunExpr)("y", NEW (AddExpr)(y, num1));
    PTR(Expr) call_expr1 = NEW (CallExpr) (fun1, num1);
    CHECK(call_expr1->interp(NEW(ExtendedEnv)("y", NEW(NumVal)(1), NEW(EmptyEnv)()))->equals(NEW (NumVal)(2)));
    
    //CallExpr::subst:
    
    // fun1(y) y+1
    //fun1(1)
    //    CHECK(call_expr1->subst("y", NEW (VarExpr)("x"))->equals(call_expr1));
    //
    
}

TEST_CASE("fan_val") {
    
    CHECK_THROWS_WITH((NEW (BoolVal)(true))->call(NULL),"unable to call a bool");
    // FunVal::call.
    //return this->body->subst(formal_arg, actual_arg->to_expr())->interp();
    CHECK((NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)()))->equals(NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)())));
    
    std::string formal_arg;
 
    
    //FunVal::call:
    PTR(Expr) n1 = NEW (NumExpr)(1);
    PTR(Val) num1 = NEW (NumVal)(1);
    
    CHECK((NEW (FunVal)("y", n1,NEW(EmptyEnv)()))->call(num1)->equals(NEW (NumVal)(1)));
}

TEST_CASE("test_val") {
    CHECK((NEW(NumVal)(1))->equals(NULL) == false);
    CHECK((NEW(NumVal)(2))->equals(NEW(NumVal)(2)) == true);
    
    //    "NumVal is not a Bool value"
    CHECK_THROWS_WITH((NEW(NumVal)(1))->is_true(), "NumVal is not a Bool value");
    CHECK((NEW(NumVal)(1))->to_string() == "1");
    //"unable to call a number"
    CHECK_THROWS_WITH((NEW(NumVal)(1))->call_step(NEW(NumVal)(2), NEW(DoneCont)()), "unable to call a number");
    //"NumVal unable to call a number"
    CHECK_THROWS_WITH((NEW(NumVal)(1))->call(NEW(NumVal)(2)), "unable to call a number");
    
    //"add of non-number"
    CHECK_THROWS_WITH( (NEW(MultExpr)(NEW(NumExpr)(1),NEW(NumExpr)(4)))->interp(Env::empty)->add_to(NULL),"add of non-number");
    //"mult of non-number"
    CHECK_THROWS_WITH( (NEW(AddExpr)(NEW(NumExpr)(2),NEW(NumExpr)(5)))->interp(Env::empty)->mult_to(NULL),"mult of non-number");
    
    CHECK((NEW(BoolVal)(true))->equals(NULL) == false);
    CHECK((NEW(BoolVal)(false))->to_string() == "_false");
    CHECK((NEW(BoolVal)(true))->to_string() == "_true");
    //"This is a Bool value unable to add..."
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->add_to(NEW(NumVal)(2)), "This is a Bool value unable to add...");
    //"This is a Bool value unable to multipy..."
    CHECK_THROWS_WITH((NEW(BoolVal)(true))->mult_to(NEW(NumVal)(2)), "This is a Bool value unable to multipy...");
    //"unable to call a bool"
    CHECK_THROWS_WITH((NEW(BoolVal)(false))->call_step(Step::val, Step::cont), "unable to call a bool");
    
                //x = formal_arg Body = NumExpr)(1) env = NEW(EmptyEnv
    CHECK_THROWS_WITH((NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)()))->add_to(NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)())), "unable to add two functions...");
    
    //x = formal_arg Body = NumExpr)(1) env = NEW(EmptyEnv
CHECK_THROWS_WITH((NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)()))->mult_to(NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)())), "unable to multiply two functions...");
    
CHECK_THROWS_WITH((NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)()))->is_true(), "This is not a Bool value..");

CHECK((NEW (FunVal)("x", NEW (NumExpr)(1), NEW(EmptyEnv)()))->to_string() == "[function]");
}

// TEST for:
//consume
//skip_whitespace
//parse_num (add other types later) - added
//parse_add (add other types later)
//parse_mult (add other types later)
//parse_variable(add other types later)
//parse_let (add other types later)

TEST_CASE("parse_test") { //NEW (NumExpr)
    CHECK( parse_str("10")->equals(NEW (NumExpr) (10))); // testing num
    CHECK( parse_str("feb")->equals(NEW (VarExpr)("feb"))); // testing variable
    CHECK( parse_str("-7")->equals(NEW (NumExpr) (-7))); // testing num
    
    PTR(Expr) ten_plus_one = NEW (AddExpr)(NEW (NumExpr)(10), NEW (NumExpr)(1));
    CHECK( parse_str("10+1")->equals(ten_plus_one)); // testing expression Add
    
    PTR(Expr) five_mult_two = NEW (MultExpr)(NEW (NumExpr)(5), NEW (NumExpr)(2));
    CHECK( parse_str("5*2")->equals(NEW (MultExpr)(NEW (NumExpr)(5), NEW (NumExpr)(2)))); // testing expression Mult
    CHECK( parse_str(" 2 ")->equals(NEW (NumExpr)(2))); // testing whitespace
    CHECK( parse_str(" (5) ")->equals(NEW (NumExpr)(5))); // testing whitespac
    CHECK_THROWS_WITH(parse_str(" (8 "), "missing close parenthesis"); //
    
//    if(n < 0){
//        throw std::runtime_error("Integer Overflow...! ");
    //parse a big number so it become negative and trigger the integer over flow message: "Integer Overflow...! "
    CHECK_THROWS_WITH(parse_str("100000000000000"), "Integer Overflow...! ");
  
    //    CHECK_THROWS_WITH(consume(1, 0), "consume mismatch"); // see how to test consume
    
    
    CHECK_THROWS_WITH(parse_str(" $ "), "invalid input"); //
    CHECK_THROWS_WITH(parse_str(" _leete "), "invalid keyword is not a _if or _let or _true or _false or _fun" ); // "it should have an _let"
    CHECK_THROWS_WITH(parse_str("_let x = 1 _innnN x + 2 "), "it should have an _in");//"it should have an _in"
    
    //_let f = _fun (x) x*x_in  f(2):
    
    CHECK( parse_str("(_fun (x) x + 1)(10)")
          ->interp(NEW(ExtendedEnv)("x", NEW(NumVal)(10),
                                    NEW(EmptyEnv)()))->equals(NEW (NumVal)(11))); // testing whitespace
    //std::cout << parse_str("(_fun (x) x + 1)(10)")->interp() <<std::endl;
    
    //Expr* parse_fun(std::istream &in){
    //_fun (〈variable〉)〈expr〉
    //
    //    //parse right handside:
    //    skip_whitespace(in);
    //    //_fun (x) x*x
    //    consume(in, '('); // add right (
    //    skip_whitespace(in);
    //    //std::string formal_arg:
    //    Expr *formal_arg = parse_var(in); // 〈variable〉 expression object but it is expecting a variable
    //    skip_whitespace(in);
    //    consume(in, ')'); // add left )
    //    skip_whitespace(in);
    //    Expr *body = parse_comparg(in); //〈expr〉
    //
    //    return NEW (FunExpr)(formal_arg->to_string(), body);
    //}
    
    CHECK_THROWS_WITH(parse_str("_let x + 17 _in x + 24")->interp(Env::empty), "consume mismatch");
    
    //    std::istringstream in("123 ");
    //    CHECK_THROWS_WITH(consume(in, '('), "consume mismatch"); // character '(' can be converted to ints but string cannot be converted to ints "("
    //     testing for parse_let (add other types later)
    //    _let x = 1 _ in x + 2
    //
    CHECK( parse_str("_let x = 1 _in x + 2 ")->equals(  (NEW (LetExpr)(NEW (VarExpr)("x"),
                                                                       NEW (NumExpr)(1), NEW (AddExpr)(NEW (VarExpr)("x"), NEW (NumExpr)(2)))))); // testing whitespace
    
    // if not _then throw an error: "it should have a _then"
    CHECK_THROWS_WITH( parse_str("_if _true _car _else 2 ")->equals( (NEW (IfExpr)(NEW (BoolExpr)(true),
                                                                                   NEW (NumExpr)(1), (NEW (NumExpr)((2)))))), "it should have a _then");
    // left handside = "_if _false _then 2 _else 1 " match it to right hand side:
    CHECK_THROWS_WITH( parse_str("_if _false _then 2 _basket 1 ")->equals( (NEW (IfExpr)(NEW (BoolExpr)(false),
                                                                                         NEW (NumExpr)(2), NEW (NumExpr)((1))))), "it should have a _else"); // testing whitespace
    
    // left handside = "_if _true _then 1 _else 2 " match it to right hand side:
    CHECK( parse_str("_if _true _then 1 _else 2 ")->equals( (NEW (IfExpr)(NEW (BoolExpr)(true),
                                                                          NEW (NumExpr)(1), NEW (NumExpr)((2)))))); // testing whitespace
    
    // left handside = "_if _false _then 2 _else 1 " match it to right hand side:
    CHECK( parse_str("_if _false _then 2 _else 1 ")->equals( (NEW (IfExpr)(NEW (BoolExpr)(false),
                                                                           NEW (NumExpr)(2), NEW (NumExpr)((1)))))); // testing whitespace
    
    std::stringstream empty_string_string("");
    CHECK( parse_str("1  == 1 ")->equals(  NEW (EqExpr)(NEW (NumExpr)(1), NEW (NumExpr)(1)))); // testing ==
    parse_str("1  == 1 ")->print(empty_string_string);
    std::cout << empty_string_string.str() << std::endl;
}

// continueation test coverage:

TEST_CASE("continuations_testing") {
    
    //NumExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("1"))->equals(NEW(NumVal)(1)));
    
    //AddExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("1+3"))->equals(NEW(NumVal)(4)));
    
    //MultExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("2*3"))->equals(NEW(NumVal)(6)));
    
    //IfExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("_if _true _then 8 _else 9"))->equals(NEW(NumVal)(8)));
    CHECK( Step::interp_by_steps(parse_str("_if _false _then 4 _else 9"))->equals(NEW(NumVal)(9)));
    
    //BoolExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("_true"))->equals(NEW(BoolVal)(true)) );
    
    //FunExpr::step_interp():
    //    CHECK(Step::interp_by_steps(parse_str("(_fun (x) x) (20)"))->equals(NEW(NumVal(20))));
    
    //BoolExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("_false"))->equals(NEW(BoolVal)(false)) );
    CHECK( Step::interp_by_steps(parse_str("3 == 3"))->equals(NEW(BoolVal)(true)));
    CHECK( Step::interp_by_steps(parse_str("_true"))->equals(NEW(BoolVal)("true")) );
    //LetExpr::step_interp():
    CHECK( Step::interp_by_steps(parse_str("_let x = 3 _in x + 2"))->equals(NEW(NumVal)(5)));
    
    //VarExpr::step_interp():
    CHECK( parse_str("friday")->equals(NEW (VarExpr)("friday")));
    PTR(CallExpr) callExpr_step_interp = NEW(CallExpr)(NEW(FunExpr)("y", NEW(AddExpr)(NEW(VarExpr)("y"), NEW(NumExpr)(2))), NEW(NumExpr)(30));
    CHECK(Step::interp_by_steps(callExpr_step_interp)->equals(NEW(NumVal)(32)) == true);
    CHECK_THROWS(Cont::done->step_continue(), "can't continue done");
}





//     TEST_CASE("add_print") {
//         AddExpr* add25 = NEW (AddExpr)r(NEW (VarExpr)("a"), NEW (VarExpr)("b"));
//         std::stringstream empty_string_string(""); // empty but gets set to 5
//         add25->print(empty_string_string);
//         CHECK( (empty_string_string.str() == "(a+b)") );
//
//     }


//parse_expr:
//    Expr *parse_expr(std::istream &in) {
//        //    〈expr〉=〈comparg〉
//        //            |〈comparg〉==〈expr
//        Expr *e;
//        e = parse_comparg(in);
//
//        skip_whitespace(in);
//        int c = in.peek();
//        if (c == '=') {
//            consume(in, '='); //
//            consume(in, '='); //
//            Expr *rhs = parse_expr(in);
//            return NEW (EqExpr)(e, rhs);
//        } else
//            return e;
//    }


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





