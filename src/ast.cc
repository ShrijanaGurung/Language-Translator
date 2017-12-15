/*******************************************************************************
 * Name            : ast.cc
 * Project         : fcal
 * Module          : AST
 * Description     : Implementation file for ast
 * Copyright       : 2017 CSCI3081W-Agamemnon. All rights reserved.
 * Original Author : Luke Erlandson and Shrijana Gurung
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/ast.h"
#include <stdio.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 *
 *
 *
 *
 **/

namespace fcal {
namespace ast {
/*******************************************************************************
 * Constructor/Destructor for our concrete classes
 ******************************************************************************/

// Constructor/Destructor/methods for Root
/*!
 * Root Constructor
 */
Root::Root(varName* v1, Stmts* s1) : Program() {
  varName_ = v1;
  Stmts_ = s1;
}

/*!
 * Root Destructor
 */
Root::~Root() {
  delete[] varName_;
  delete[] Stmts_;
}

/*!
 * Root Unparser
 */
std::string Root::Unparse() {
  return varName_->Unparse() + "() {\n" + Stmts_->Unparse() + "}";
}

/*!
 * Root CppCode
 */
std::string Root::CppCode() {
  return "#include <iostream>\n #include \"include/Matrix.h\"\n #include "
         "<math.h>\n "
         "using namespace std;\n int " +
         varName_->CppCode() + "() {\n" + Stmts_->CppCode() + "}";
}

// Constructor/Destructor/methods for varName
/*!
 * VarName constructor
 */
varName::varName(std::string s1) : Node() { var_ = s1; }

/*!
 * varName Unparser
 */
std::string varName::Unparse() { return var_; }

/*!
 * varName CppCode
 */
std::string varName::CppCode() { return var_; }

// Constructor/Destructor/methods for emptyStmts

/*!
 * emptyStmts Constructor
 */
emptyStmts::emptyStmts() : Stmts() {}

/*!
 * emptyStmts Unparser
 */
std::string emptyStmts::Unparse() { return ""; }

/*!
 * emptyStmts CppCode
 */
std::string emptyStmts::CppCode() { return ""; }

// Constructor/Destructor/methods for multipleStmts

/*!
 * multipleStmts Constructor
 */
multipleStmts::multipleStmts(Stmt* s1, Stmts* s2) : Stmts() {
  Stmt_ = s1;
  Stmts_ = s2;
}

/*!
 * multipleStmts Destructor
 */
multipleStmts::~multipleStmts() {
  delete[] Stmt_;
  delete[] Stmts_;
}

/*!
 * multipleStmts Unparser
 */
std::string multipleStmts::Unparse() {
  return Stmt_->Unparse() + " " + Stmts_->Unparse();
}

/*!
 * multipleStmts CppCode
 */
std::string multipleStmts::CppCode() {
  return Stmt_->CppCode() + " " + Stmts_->CppCode();
}

// Constructor/Destructor/methods for DeclStmt
/*!
 * declStmt Constructor
 */
declStmt::declStmt(Decl* d1) : Stmt() { Decl_ = d1; }

/*!
 * declStmt Destructor
 */
declStmt::~declStmt() { delete[] Decl_; }

/*!
 * declStmt Unparser
 */
std::string declStmt::Unparse() { return Decl_->Unparse(); }

/*!
 * declStmt CppCode
 */
std::string declStmt::CppCode() { return Decl_->CppCode(); }

// Constructor/Destructor/methods for stmtsStmt
/*!
 * stmtsStmt Constructor
 */
stmtsStmt::stmtsStmt(Stmts* s1) : Stmt() { Stmts_ = s1; }

/*!
 * stmtsStmt Destructor
 */
stmtsStmt::~stmtsStmt() { delete[] Stmts_; }

/*!
 * stmtsStmt Unparser
 */
std::string stmtsStmt::Unparse() { return "{ " + Stmts_->Unparse() + " }"; }

/*!
 * stmtsStmt CppCode
 */
std::string stmtsStmt::CppCode() { return "{ " + Stmts_->CppCode() + " }"; }

// Constructor/Destructor/methods for ifStmt
/*!
 * ifStmt Constructor
 */
ifStmt::ifStmt(Expr* e1, Stmt* s1) : Stmt() {
  Expr_ = e1;
  Stmt_ = s1;
}

/*!
 * ifStmt Destructor
 */
ifStmt::~ifStmt() {
  delete[] Expr_;
  delete[] Stmt_;
}

/*!
 * ifStmt Unparser
 */
std::string ifStmt::Unparse() {
  return "if(" + Expr_->Unparse() + ")" + Stmt_->Unparse();
}

/*!
 * ifStmt CppCode
 */
std::string ifStmt::CppCode() {
  return "if(" + Expr_->CppCode() + ")" + Stmt_->CppCode();
}

// Constructor/Destructor/methods for ifElseStmt
/*!
 * ifElseStmt Constructor
 */
ifElseStmt::ifElseStmt(Expr* e1, Stmt* s1, Stmt* s2) : Stmt() {
  Expr_ = e1;
  Stmt_1 = s1;
  Stmt_2 = s2;
}

/*!
 * ifElseStmt Destructor
 */
ifElseStmt::~ifElseStmt() {
  delete[] Expr_;
  delete[] Stmt_1;
  delete[] Stmt_2;
}

/*!
 * ifElseStmt Unparser
 */
std::string ifElseStmt::Unparse() {
  return "if(" + Expr_->Unparse() + ")" + Stmt_1->Unparse() + "else" +
         Stmt_2->Unparse();
}

/*!
 * ifElseStmt CppCode
 */
std::string ifElseStmt::CppCode() {
  return "if(" + Expr_->CppCode() + ")" + Stmt_1->CppCode() + "else" +
         Stmt_2->CppCode();
}

// Constructor/Destructor/methods for assignStmt1
assignStmt1::assignStmt1(varName* v1, Expr* e1) : Stmt() {
  Expr_ = e1;
  varName_ = v1;
}

/*!
 * assignStmt Destructor
 */
assignStmt1::~assignStmt1() {
  delete[] Expr_;
  delete[] varName_;
}

std::string assignStmt1::Unparse() {
  return varName_->Unparse() + " = " + Expr_->Unparse() + " ;\n";
}

/*!
 * assignStmt CppCode
 */
std::string assignStmt1::CppCode() {
  return varName_->CppCode() + " = " + Expr_->CppCode() + " ;\n";
}

// Constructor/Destructor/methods for assignStmt2
assignStmt2::assignStmt2(varName* v1, Expr* e1, Expr* e2, Expr* e3) : Stmt() {
  Expr_1_ = e1;
  Expr_2_ = e2;
  Expr_3_ = e3;
  varName_ = v1;
}

/*!
 * assignStmt2 Destructor
 */
assignStmt2::~assignStmt2() {
  delete[] Expr_1_;
  delete[] Expr_2_;
  delete[] Expr_3_;
  delete[] varName_;
}

std::string assignStmt2::Unparse() {
  return varName_->Unparse() + " [ " + Expr_1_->Unparse() + " : " +
         Expr_2_->Unparse() + " ] = " + Expr_3_->Unparse() + " ;\n";
}

/*!
 * assignStmt2 CppCode
 */
std::string assignStmt2::CppCode() {
  return "*(" + varName_->CppCode() + " .access( " + Expr_1_->CppCode() +
         " , " + Expr_2_->CppCode() + " )) = " + Expr_3_->CppCode() + " ;\n";
}

// Constructor/Destructor/methods for printStmt
/*!
 * printStmt Constructor
 */
printStmt::printStmt(Expr* e1) : Stmt() { Expr_ = e1; }

/*!
 * printStmt Destructor
 */
printStmt::~printStmt() { delete[] Expr_; }

/*!
 * printStmt Unparser
 */
std::string printStmt::Unparse() {
  return "print(" + Expr_->Unparse() + ")" + ";\n";
}

/*!
 * printStmt CppCode
 */
std::string printStmt::CppCode() {
  return "cout << " + Expr_->CppCode() + " ;\n";
}

// Constructor/Destructor/methods for repeatStmt
/*!
 * repeatStmt Constructor
 */
repeatStmt::repeatStmt(varName* v1, Expr* e1, Expr* e2, Stmt* s1) : Stmt() {
  varName_ = v1;
  Expr_1_ = e1;
  Expr_2_ = e2;
  Stmt_ = s1;
}

/*!
 * repeatStmt Destructor
 */
repeatStmt::~repeatStmt() {
  delete[] Expr_1_;
  delete[] Expr_2_;
  delete[] varName_;
  delete[] Stmt_;
}

/*!
 * repeatStmt Unparser
 */
std::string repeatStmt::Unparse() {
  return "repeat ( " + varName_->Unparse() + " = " + Expr_1_->Unparse() +
         " to " + Expr_2_->Unparse() + " ) " + Stmt_->Unparse();
}

/*!
 * repeatStmt CppCode
 */
std::string repeatStmt::CppCode() {
  return "for ( " + varName_->CppCode() + " = " + Expr_1_->CppCode() + " ; " +
         varName_->CppCode() + " <= " + Expr_2_->CppCode() + " ; " +
         varName_->CppCode() + "++  ) " + Stmt_->CppCode();
}

// Constructor/Destructor/methods for whileStmt
/*!
 * whileStmt Constructor
 */
whileStmt::whileStmt(Expr* e1, Stmt* s1) {
  Expr_ = e1;
  Stmt_ = s1;
}

/*!
 * whileStmt Destructor
 */
whileStmt::~whileStmt() {
  delete[] Expr_;
  delete[] Stmt_;
}

/*!
 * whileStmt Unparser
 */
std::string whileStmt::Unparse() {
  return "while(" + Expr_->Unparse() + ")" + Stmt_->Unparse();
}

/*!
 * whileStmt CppCode
 */
std::string whileStmt::CppCode() {
  return "while(" + Expr_->CppCode() + ")" + Stmt_->CppCode();
}

// Constructor/Destructor/methods for semiColonStmt

/*!
 * semiColonStmt Constructor
 */
semiColonStmt::semiColonStmt() {}

/*!
 * semiColonStmt Unparser
 */
std::string semiColonStmt::Unparse() { return ";\n"; }

/*!
 * semiColonStmt CppCode
 */
std::string semiColonStmt::CppCode() { return ";\n"; }

// Constructor/Destructor/methods for intDecl

/*!
 * intDecl Constructor
 */
intDecl::intDecl(varName* v1) : Decl() { varName_ = v1; }

/*!
 * intDecl Destructor
 */
intDecl::~intDecl() { delete[] varName_; }

/*!
 * intDecl Unparser
 */
std::string intDecl::Unparse() { return "int " + varName_->Unparse() + ";\n"; }

/*!
 * intDecl CppCode
 */
std::string intDecl::CppCode() { return "int " + varName_->Unparse() + ";\n"; }

// Constructor/Destructor/methods for floatDecl

/*!
 * floatDecl Constructor
 */
floatDecl::floatDecl(varName* v1) : Decl() { varName_ = v1; }

/*!
 * floatDecl Destructor
 */
floatDecl::~floatDecl() { delete[] varName_; }

/*!
 * floatDecl Unparser
 */
std::string floatDecl::Unparse() {
  return "float " + varName_->Unparse() + ";\n";
}

/*!
 * floatDecl CppCode
 */
std::string floatDecl::CppCode() {
  return "float " + varName_->CppCode() + ";\n";
}

// Constructor/Destructor/methods for stringDecl

/*!
 * stringDecl Constructor
 */
stringDecl::stringDecl(varName* v1) : Decl() { varName_ = v1; }

/*!
 * stringDecl Destructor
 */
stringDecl::~stringDecl() { delete[] varName_; }

/*!
 * stringDecl Unparser
 */
std::string stringDecl::Unparse() {
  return "string " + varName_->Unparse() + ";\n";
}

/*!
 * stringDecl CppCode
 */
std::string stringDecl::CppCode() {
  return "string " + varName_->CppCode() + ";\n";
}

// Constructor/Destructor/methods for boolDecl

/*!
 * boolDecl Constructor
 */
boolDecl::boolDecl(varName* v1) : Decl() { varName_ = v1; }

/*!
 * boolDecl Destructor
 */
boolDecl::~boolDecl() { delete[] varName_; }

/*!
 * boolDecl Unparser
 */
std::string boolDecl::Unparse() {
  return "boolean " + varName_->Unparse() + ";\n";
}

/*!
 * boolDecl CppCode
 */
std::string boolDecl::CppCode() {
  return "boolean " + varName_->CppCode() + ";\n";
}

// Constructor/Destructor/methods for matrixDecl

/*!
 * matrixDecl Constructor
 */
matrixDecl::matrixDecl(varName* v1, varName* v2, varName* v3, Expr* e1,
                       Expr* e2, Expr* e3)
    : Decl() {
  varName_1_ = v1;
  varName_2_ = v2;
  varName_3_ = v3;
  Expr_1_ = e1;
  Expr_2_ = e2;
  Expr_3_ = e3;
}

/*!
 * matrixDecl Destructor
 */
matrixDecl::~matrixDecl() {
  delete[] varName_1_;
  delete[] varName_2_;
  delete[] varName_3_;
  delete[] Expr_1_;
  delete[] Expr_2_;
  delete[] Expr_3_;
}

/*!
 * matrixDecl Unparser
 */
std::string matrixDecl::Unparse() {
  return "matrix " + varName_1_->Unparse() + " [" + Expr_1_->Unparse() + ":" +
         Expr_2_->Unparse() + "] " + varName_2_->Unparse() + ":" +
         varName_3_->Unparse() + " = " + Expr_3_->Unparse() + " ;\n";
}

/*!
 * matrixDecl Decoder
 */
std::string matrixDecl::CppCode() {
  return "matrix " + varName_1_->CppCode() + " (" + Expr_1_->CppCode() + "," +
         Expr_2_->CppCode() + "); \n for( int " + varName_2_->CppCode() +
         "=0;" + varName_2_->CppCode() + " < " + Expr_1_->CppCode() + ";" +
         varName_2_->CppCode() + "++) { \n for(int " + varName_3_->CppCode() +
         " = 0;" + varName_3_->CppCode() + "< " + Expr_2_->CppCode() + ";" +
         varName_3_->CppCode() + "++) { *(  " + varName_1_->CppCode() +
         ".access(" + varName_2_->CppCode() + "," + varName_3_->CppCode() +
         ")) = " + Expr_3_->CppCode() + " ;\n}}";
}

// Constructor/Destructor/methods for matrixDecl2

matrixDecl2::matrixDecl2(varName* v1, Expr* e1) : Decl() {
  varName_ = v1;
  Expr_ = e1;
}

/*!
 * matrixDecl Destructor
 */
matrixDecl2::~matrixDecl2() {
  delete[] varName_;
  delete[] Expr_;
}

std::string matrixDecl2::Unparse() {
  return "matrix " + varName_->Unparse() + " =  " + Expr_->Unparse() + ";\n";
}

std::string matrixDecl2::CppCode() {
  return "matrix " + varName_->CppCode() + " ( matrix::" + Expr_->CppCode() +
         ");\n";
}
// Expr::= varName
/*!
 * varNameExpr Constructor
 */
varNameExpr::varNameExpr(varName* v1) : Expr() { varName_ = v1; }

/*!
 * varNameExpr Destructor
 */
varNameExpr::~varNameExpr() { delete[] varName_; }

/*!
 * varNameExpr Unparser
 */
std::string varNameExpr::Unparse(void) { return varName_->Unparse(); }

/*!
 * varNameExpr Decoder
 */
std::string varNameExpr::CppCode(void) { return varName_->CppCode(); }

// Expr::= intergerConst| floatConst| stringConst

/*!
 * intExpr Constructor
 */
intExpr::intExpr(std::string i1) : Expr() { int_ = i1; }

/*!
 * intExpr Destructor
 */
intExpr::~intExpr() {}

/*!
 * intExpr Unparser
 */
std::string intExpr::Unparse(void) { return int_; }

/*!
 * intExpr Decoder
 */
std::string intExpr::CppCode(void) { return int_; }

/*!
 * floatExpr Constructor
 */
floatExpr::floatExpr(std::string f1) : Expr() { float_ = f1; }

/*!
 * floatExpr Destructor
 */
floatExpr::~floatExpr() {}

/*!
 * floatExpr Unparser
 */
std::string floatExpr::Unparse(void) { return float_; }

/*!
 * floatExpr Decoder
 */
std::string floatExpr::CppCode(void) { return float_; }

/*!
 * stringExpr Constructor
 */
stringExpr::stringExpr(std::string s1) : Expr() { string_ = s1; }

/*!
 * stringExpr Destructor
 */
stringExpr::~stringExpr() {}

/*!
 * stringExpr Unparser
 */
std::string stringExpr::Unparse(void) { return string_; }

/*!
 * stringExpr Decoder
 */
std::string stringExpr::CppCode(void) { return string_; }

// Expr ::= "True' | 'False'
/*!
 * trueExpr Constructor
 */
trueExpr::trueExpr() : Expr() {}
/*!
 * trueExpr Destructor
 */
trueExpr::~trueExpr() {}

/*!
 * trueExpr Unparser
 */
std::string trueExpr::Unparse(void) { return "true"; }

/*!
 * trueExpr Decoder
 */
std::string trueExpr::CppCode(void) { return "true"; }

/*!
 * falseExpr Constructor
 */
falseExpr::falseExpr() : Expr() {}

/*!
 * falseExpr Destructor
 */
falseExpr::~falseExpr() {}

/*!
 * falseExpr Unparser
 */
std::string falseExpr::Unparse(void) { return "false"; }

/*!
 * falseExpr Decoder
 */
std::string falseExpr::CppCode(void) { return "false"; }

/*!
 * Relational expression Destructor
 */
relationalExpr::~relationalExpr() {
  delete[] Expr_1_;
  delete[] Expr_2_;
}
/*!
 * Relational Expression Unparser
 */
std::string relationalExpr::Unparse() {
  return Expr_1_->Unparse() + op_ + Expr_2_->Unparse();
}

/*!
 * Relational Expression Decoder
 */
std::string relationalExpr::CppCode() {
  return Expr_1_->CppCode() + op_ + Expr_2_->CppCode();
}

// Expr ::= varName '[' Expr ':' Expr ']'   //MatrixREf

/*!
 * matrixExpr Constructor
 */
matrixExpr::matrixExpr(Expr* e1, Expr* e2, varName* v1) : Expr() {
  Expr_1_ = e1;
  Expr_2_ = e2;
  var_ = v1;
}

/*!
 * matrixExpr Destructor
 */
matrixExpr::~matrixExpr() {
  delete[] Expr_1_;
  delete[] Expr_2_;
  delete[] var_;
}

/*!
 * matrixExpr Unparser
 */
std::string matrixExpr::Unparse() {
  return var_->Unparse() + "[" + Expr_1_->Unparse() + ":" + Expr_2_->Unparse() +
         "]";
}

std::string matrixExpr::CppCode() {
  return "*(" + var_->CppCode() + ".access(" + Expr_1_->CppCode() + "," +
         Expr_2_->CppCode() + "))";
}
// Expr ::= varName '(' Expr ')'        //NestedOrFunctionCall

/*!
 * nestedExpr Constructor
 */
nestedExpr::nestedExpr(Expr* e1, varName* v1) : Expr() {
  Expr_ = e1;
  var_ = v1;
}

/*!
 * nestedExpr Destructor
 */
nestedExpr::~nestedExpr() {
  delete[] Expr_;
  delete[] var_;
}

/*!
 * nestedExpr Unparser
 */
std::string nestedExpr::Unparse() {
  return var_->Unparse() + "(" + Expr_->Unparse() + ")";
}

/*!
 * nestedExpr Decoder
 */
std::string nestedExpr::CppCode() {
  if (var_->Unparse() == "n_rows" || var_->Unparse() == "n_cols") {
    return Expr_->Unparse() + "." + var_->Unparse() + "()";
  }
  return var_->CppCode() + "(" + Expr_->CppCode() + ")";
}

// Expr ::= '(' Expr ')'

/*!
 * parenExpr Constructor
 */
parenExpr::parenExpr(Expr* e1) : Expr() { Expr_ = e1; }

/*!
 * parenExpr Destructor
 */
parenExpr::~parenExpr() { delete[] Expr_; }

/*!
 * parenExpr Unparser
 */
std::string parenExpr::Unparse() { return "(" + Expr_->Unparse() + ")"; }

/*!
 * parenExpr Decoder
 */
std::string parenExpr::CppCode() { return "(" + Expr_->CppCode() + ")"; }

// Expr ::= 'let' Stmts 'in' Expr 'end'  //LetExpr
/*!
 * letExpr Constructor
 */
letExpr::letExpr(Stmts* s1, Expr* e1) : Expr() {
  Expr_ = e1;
  Stmts_ = s1;
}

/*!
 * letExpr Destructor
 */
letExpr::~letExpr() {
  delete[] Expr_;
  delete[] Stmts_;
}

/*!
 * letExpr Unparser
 */
std::string letExpr::Unparse() {
  return "let " + Stmts_->Unparse() + " in " + Expr_->Unparse() + " end";
}

/*!
 * letExpr Decoder
 */
std::string letExpr::CppCode() {
  return "({  " + Stmts_->CppCode() + " \n (" + Expr_->CppCode() + "); })";
}

// Expr ::= 'if' Expr 'then' Expr 'else' Expr    //IfExpr

/*!
 * ifExpr Constructor
 */
ifExpr::ifExpr(Expr* e1, Expr* e2, Expr* e3) : Expr() {
  Expr_1_ = e1;
  Expr_2_ = e2;
  Expr_3_ = e3;
}

/*!
 * ifExpr Destructor
 */
ifExpr::~ifExpr() {
  delete[] Expr_1_;
  delete[] Expr_2_;
  delete[] Expr_3_;
}

/*!
 * ifExpr Unparser
 */
std::string ifExpr::Unparse() {
  return "if " + Expr_1_->Unparse() + " then " + Expr_2_->Unparse() + " else " +
         Expr_3_->Unparse();
}

/*!
 * ifExpr Cpp decoder
 */
std::string ifExpr::CppCode() {
  return "(" + Expr_1_->CppCode() + ") ? (" + Expr_2_->CppCode() +
         ") :" + Expr_3_->CppCode();
}

// Expr ::= '!' Expr                          //NotExpr
/*!
 * notExpr Constructor
 */
notExpr::notExpr(Expr* e1) : Expr() { Expr_ = e1; }

/*!
 * notExpr Destructor
 */
notExpr::~notExpr() { delete[] Expr_; }

/*!
 * notExpr Unparser
 */
std::string notExpr::Unparse() { return "!" + Expr_->Unparse(); }

/*!
 * notExpr Decoder
 */
std::string notExpr::CppCode() { return "!" + Expr_->CppCode(); }
}  // namespace ast
}  // namespace fcal
