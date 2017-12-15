/*******************************************************************************
 * Name            : regex.h
 * Project         : fcal
 * Module          : ast
 * Description     : Header file for AST
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_AST_H_
#define PROJECT_INCLUDE_AST_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include "include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace ast {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

class Node {
 public:
  virtual std::string Unparse(void) = 0;
  virtual std::string CppCode(void) = 0;
  virtual ~Node(void) {}
};

class varName : public Node {
 public:
  explicit varName(std::string);
  std::string Unparse(void);
  std::string CppCode(void);
  // std::string get_varName(void) {};
 private:
  std::string var_;
};

// Decl, Stmt, Stmts, Expr are all empty classes that inherits from Node
class Decl : public Node {};
class Stmt : public Node {};
class Stmts : public Node {};
class Expr : public Node {};

// Program is an empty class that inherits from Node
class Program : public Node {};

class Root : public Program {
 public:
  Root(varName *, Stmts *);
  ~Root();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
  Stmts *Stmts_;
};

// Stmts ::= <<empty>>

class emptyStmts : public Stmts {
 public:
  emptyStmts();
  std::string Unparse(void);
  std::string CppCode(void);
};

// Stmts ::= Stmt Stmts
class multipleStmts : public Stmts {
 public:
  multipleStmts(Stmt *, Stmts *);
  ~multipleStmts();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Stmt *Stmt_;
  Stmts *Stmts_;
};

// Stmt ::= Decl
class declStmt : public Stmt {
 public:
  explicit declStmt(Decl *);
  ~declStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Decl *Decl_;
};

// Stmt ::= '{' Stmts '}'
class stmtsStmt : public Stmt {
 public:
  explicit stmtsStmt(Stmts *);
  std::string Unparse(void);
  std::string CppCode(void);
  ~stmtsStmt();

 private:
  Stmts *Stmts_;
};

// Stmt ::= 'if' '(' Expr ')' Stmt
class ifStmt : public Stmt {
 public:
  ifStmt(Expr *, Stmt *);
  ~ifStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
  Stmt *Stmt_;
};

// Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
class ifElseStmt : public Stmt {
 public:
  ifElseStmt(Expr *, Stmt *, Stmt *);
  ~ifElseStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
  Stmt *Stmt_1;
  Stmt *Stmt_2;
};

// Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']' '=' Expr ';'
class assignStmt1 : public Stmt {
 public:
  assignStmt1(varName *, Expr *);
  ~assignStmt1();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
  Expr *Expr_;
};

class assignStmt2 : public Stmt {
 public:
  assignStmt2(varName *, Expr *, Expr *, Expr *);
  ~assignStmt2();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
  Expr *Expr_1_;
  Expr *Expr_2_;
  Expr *Expr_3_;
};

// Stmt ::= 'print' '(' Expr ')' ';'

class printStmt : public Stmt {
 public:
  explicit printStmt(Expr *);
  ~printStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
};

// Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
class repeatStmt : public Stmt {
 public:
  repeatStmt(varName *, Expr *, Expr *, Stmt *);
  ~repeatStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
  Expr *Expr_1_;
  Expr *Expr_2_;
  Stmt *Stmt_;
};

// Stmt ::= 'while' '(' Expr ')' Stmt
class whileStmt : public Stmt {
 public:
  whileStmt(Expr *, Stmt *);
  ~whileStmt();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
  Stmt *Stmt_;
};

// Stmt ::= ';'
class semiColonStmt : public Stmt {
 public:
  semiColonStmt();
  std::string Unparse(void);
  std::string CppCode(void);
};

// Decl ::= 'int' varName ';'
class intDecl : public Decl {
 public:
  explicit intDecl(varName *);
  ~intDecl();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
};

// Decl ::= 'float' varName ';'
class floatDecl : public Decl {
 public:
  explicit floatDecl(varName *);
  ~floatDecl();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
};

// Decl ::= 'string' varName ';'
class stringDecl : public Decl {
 public:
  explicit stringDecl(varName *);
  ~stringDecl();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
};

// Decl ::= 'boolean' varName ';'
class boolDecl : public Decl {
 public:
  explicit boolDecl(varName *);
  ~boolDecl();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
};

// Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr
// ';'
class matrixDecl : public Decl {
 public:
  matrixDecl(varName *, varName *, varName *, Expr *, Expr *, Expr *);
  ~matrixDecl();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_1_;
  varName *varName_2_;
  varName *varName_3_;
  Expr *Expr_1_;
  Expr *Expr_2_;
  Expr *Expr_3_;
};

// Decl ::= 'matrix' varName '=' Expr ';'
class matrixDecl2 : public Decl {
 public:
  matrixDecl2(varName *, Expr *);
  ~matrixDecl2();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
  Expr *Expr_;
};

// Expr::= varName
class varNameExpr : public Expr {
 public:
  explicit varNameExpr(varName *);
  ~varNameExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  varName *varName_;
};

// Expr::= intergerConst| floatConst| stringConst

class intExpr : public Expr {
 public:
  explicit intExpr(std::string);
  ~intExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  std::string int_;
};

class floatExpr : public Expr {
 public:
  explicit floatExpr(std::string);
  ~floatExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  std::string float_;
};

class stringExpr : public Expr {
 public:
  explicit stringExpr(std::string);
  ~stringExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  std::string string_;
};

// Expr ::= "True' | 'False'

class trueExpr : public Expr {
 public:
  trueExpr();
  ~trueExpr();
  std::string Unparse(void);
  std::string CppCode(void);
};

class falseExpr : public Expr {
 public:
  falseExpr();
  ~falseExpr();
  std::string Unparse(void);
  std::string CppCode(void);
};

// // Expr ::= Expr '*' Expr
// class mulExpr : public Expr {
//  public:
//   mulExpr(Expr *, Expr *);
//   ~mulExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '/' Expr
//
// class divExpr : public Expr {
//  public:
//   divExpr(Expr *, Expr *);
//   ~divExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '+' Expr
// class plusExpr : public Expr {
//  public:
//   plusExpr(Expr *, Expr *);
//   ~plusExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '-' Expr
//
// class subExpr : public Expr {
//  public:
//   subExpr(Expr *, Expr *);
//   ~subExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };

// Relational Expression
class relationalExpr : public Expr {
 public:
  relationalExpr(Expr *l, Expr *r, std::string op)
      : Expr_1_(l), Expr_2_(r), op_(op) {}
  ~relationalExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_1_;
  Expr *Expr_2_;
  std::string op_;
};

// // Expr ::= Expr '>' Expr
// class greaterExpr : public Expr {
//  public:
//   greaterExpr(Expr *, Expr *);
//   ~greaterExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
// // Expr ::= Expr '>=' Expr
//
// class greaterEqExpr : public Expr {
//  public:
//   greaterEqExpr(Expr *, Expr *);
//   ~greaterEqExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
// // Expr ::= Expr '<' Expr
//
// class lessExpr : public Expr {
//  public:
//   lessExpr(Expr *, Expr *);
//   ~lessExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '<=' Expr
//
// class lessEqExpr : public Expr {
//  public:
//   lessEqExpr(Expr *, Expr *);
//   ~lessEqExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
// // Expr ::= Expr '==' Expr
// class equalsExpr : public Expr {
//  public:
//   equalsExpr(Expr *, Expr *);
//   ~equalsExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '!=' Expr
//
// class notEqualsExpr : public Expr {
//  public:
//   notEqualsExpr(Expr *, Expr *);
//   ~notEqualsExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '&&' Expr
//
// class andExpr : public Expr {
//  public:
//   andExpr(Expr *, Expr *);
//   ~andExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };
//
// // Expr ::= Expr '||' Expr
// class orExpr : public Expr {
//  public:
//   orExpr(Expr *, Expr *);
//   ~orExpr();
//   std::string Unparse(void);
//
//  private:
//   Expr *Expr_1_;
//   Expr *Expr_2_;
// };

// Expr ::= varName '[' Expr ':' Expr ']'   //MatrixREf
class matrixExpr : public Expr {
 public:
  matrixExpr(Expr *, Expr *, varName *);
  ~matrixExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_1_;
  Expr *Expr_2_;
  varName *var_;
};

// Expr ::= varName '(' Expr ')'        //NestedOrFunctionCall

class nestedExpr : public Expr {
 public:
  nestedExpr(Expr *, varName *);
  ~nestedExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
  varName *var_;
};

// Expr ::= '(' Expr ')'

class parenExpr : public Expr {
 public:
  explicit parenExpr(Expr *);
  ~parenExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
};

// Expr ::= 'let' Stmts 'in' Expr 'end'  //LetExpr

class letExpr : public Expr {
 public:
  letExpr(Stmts *, Expr *);
  ~letExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
  Stmts *Stmts_;
};

// Expr ::= 'if' Expr 'then' Expr 'else' Expr    //IfExpr
class ifExpr : public Expr {
 public:
  ifExpr(Expr *, Expr *, Expr *);
  ~ifExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_1_;
  Expr *Expr_2_;
  Expr *Expr_3_;
};
// Expr ::= '!' Expr                          //NotExpr
class notExpr : public Expr {
 public:
  explicit notExpr(Expr *);
  ~notExpr();
  std::string Unparse(void);
  std::string CppCode(void);

 private:
  Expr *Expr_;
};

} /* namespace ast */
} /* namespace fcal */

#endif  // PROJECT_INCLUDE_AST_H_
