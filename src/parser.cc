/*******************************************************************************
 * Name            : parser.h
 * Project         : fcal
 * Module          : parser
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Erik Van Wyk
 * Modifications by: Dan Challou, John Harwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/parser.h"
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include "include/ext_token.h"
#include "include/scanner.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace parser {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
/*!
 * Parser Destructor
 */
Parser::~Parser() {
  if (scanner_) delete scanner_;

  scanner::ExtToken *to_delete1;
  curr_token_ = tokens_;
  while (curr_token_) {
    to_delete1 = curr_token_;
    curr_token_ = curr_token_->next();
    delete to_delete1;
  } /* while() */

  scanner::Token *curr_scanner_token = stokens_;
  scanner::Token *to_delete2;
  while (curr_scanner_token) {
    to_delete2 = curr_scanner_token;
    curr_scanner_token = curr_scanner_token->next();
    delete to_delete2;
  } /* while() */
} /* Parser::~Parser() */

/*!
 * Parses text
 * @param[in] text c_string text to parse
 * */
ParseResult Parser::Parse(const char *text) {
  assert(text != nullptr);

  ParseResult pr;
  try {
    scanner_ = new scanner::Scanner();
    stokens_ = scanner_->Scan(text);
    tokens_ = tokens_->ExtendTokenList(this, stokens_);
    assert(tokens_ != nullptr);
    curr_token_ = tokens_;
    pr = ParseProgram();
  } catch (std::string errMsg) {
    pr.ok(false);
    pr.errors(errMsg);
    pr.ast(nullptr);
  }
  return pr;
} /* Parser::parse() */

/*
 * parse methods for non-terminal symbols
 * --------------------------------------
 */

// Program
/*!
 * Parses the program
 * */
ParseResult Parser::ParseProgram() {
  ParseResult pr;
  // root
  // Program ::= varName '(' ')' '{' Stmts '}'
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  ast::varName *var = new ast::varName(name);
  match(scanner::kLeftParen);
  match(scanner::kRightParen);
  match(scanner::kLeftCurly);
  ParseResult pr_stmts = parse_stmts();
  ast::Stmts *s = nullptr;

  if (pr_stmts.ast()) {
    s = dynamic_cast<ast::Stmts *>(pr_stmts.ast());
    if (!s) throw((std::string) "Bad cast of state in parseprogram");
  }
  // else{
  // throw((std::string) "Unable to parse stmts");
  //}
  match(scanner::kRightCurly);
  match(scanner::kEndOfFile);
  pr.ast(new ast::Root(var, s));

  return pr;
} /* Parser::ParseProgram() */

// MatrixDecl
// identical purpose of parse_decl, handles special matrix syntax.
/*!
 * Parses matrixDecl
 * */
ParseResult Parser::parse_matrix_decl() {
  ParseResult pr;
  match(scanner::kMatrixKwd);
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  ast::varName *var = new ast::varName(name);

  // Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '='
  // Expr ';'
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult Expr_1 = parse_expr(0);
    ast::Expr *ex_1 = nullptr;
    if (Expr_1.ast()) {
      ex_1 = dynamic_cast<ast::Expr *>(Expr_1.ast());
      if (!ex_1) throw((std::string) "Bad cast of state in parse_matrix_decl");
    }

    match(scanner::kColon);
    ParseResult Expr_2 = parse_expr(0);
    ast::Expr *ex_2 = nullptr;
    if (Expr_2.ast()) {
      ex_2 = dynamic_cast<ast::Expr *>(Expr_2.ast());
      if (!ex_2) throw((std::string) "Bad cast of state in parse_matrix_decl");
    }
    match(scanner::kRightSquare);
    match(scanner::kVariableName);
    std::string name_2(prev_token_->lexeme());
    ast::varName *var_2 = new ast::varName(name_2);
    match(scanner::kColon);
    match(scanner::kVariableName);
    std::string name_3(prev_token_->lexeme());
    ast::varName *var_3 = new ast::varName(name_3);
    match(scanner::kAssign);
    ParseResult Expr_3 = parse_expr(0);
    ast::Expr *ex_3 = nullptr;
    if (Expr_3.ast()) {
      ex_3 = dynamic_cast<ast::Expr *>(Expr_3.ast());
      if (!ex_3) throw((std::string) "Bad cast of state in parse_matrix_decl");
    }
    pr.ast(new ast::matrixDecl(var, var_2, var_3, ex_1, ex_2, ex_3));
  } else if (attempt_match(scanner::kAssign)) {
    // Decl ::= 'matrix' varName '=' Expr ';'
    ParseResult Expr_1 = parse_expr(0);
    ast::Expr *ex_1 = nullptr;
    if (Expr_1.ast()) {
      ex_1 = dynamic_cast<ast::Expr *>(Expr_1.ast());
      if (!ex_1) throw((std::string) "Bad cast of state in parse_matrix_decl");
    }
    pr.ast(new ast::matrixDecl2(var, ex_1));
  } else {
    throw((std::string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
  }

  match(scanner::kSemiColon);

  return pr;
}
// standardDecl
// Decl ::= integerKwd varName | floatKwd varName | stringKwd varName
/*!
 * Parses standardDecl
 * */
ParseResult Parser::parse_standard_decl() {
  ParseResult pr;
  char type;
  if (attempt_match(scanner::kIntKwd)) {  // Type ::= intKwd
    type = 'I';
  } else if (attempt_match(scanner::kFloatKwd)) {  // Type ::= floatKwd
    type = 'F';
  } else if (attempt_match(scanner::kStringKwd)) {  // Type ::= stringKwd
    type = 'S';
  } else if (attempt_match(scanner::kBoolKwd)) {  // Type ::= boolKwd
    type = 'B';
  }
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  ast::varName *var = new ast::varName(name);
  match(scanner::kSemiColon);
  switch (type) {
    case 'I': {
      pr.ast(new ast::intDecl(var));
      break;
    }
    case 'F': {
      pr.ast(new ast::floatDecl(var));
      break;
    }
    case 'S': {
      pr.ast(new ast::stringDecl(var));
      break;
    }
    case 'B': {
      pr.ast(new ast::boolDecl(var));
      break;
    }
  }

  return pr;
}

// Decl
/*!
 * Parses decl
 * */
ParseResult Parser::parse_decl() {
  ParseResult pr;
  // Decl :: matrix variableName ....
  if (next_is(scanner::kMatrixKwd)) {
    pr = parse_matrix_decl();
  } else {
    // Decl ::= Type variableName semiColon
    pr = parse_standard_decl();
  }
  return pr;
}

// Stmts
/*!
 * Parses Stmts
 * */
ParseResult Parser::parse_stmts() {
  ParseResult pr;
  if (!next_is(scanner::kRightCurly) && !next_is(scanner::kInKwd)) {
    // Stmts ::= Stmt Stmts
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *st = nullptr;

    if (pr_stmt.ast()) {
      st = dynamic_cast<ast::Stmt *>(pr_stmt.ast());
      if (!st) throw((std::string) "Bad cast of state in parseprogram");
    }
    ParseResult pr_stmts = parse_stmts();
    ast::Stmts *s = nullptr;

    if (pr_stmts.ast()) {
      s = dynamic_cast<ast::Stmts *>(pr_stmts.ast());
      if (!s) throw((std::string) "Bad cast of state in parseprogram");
    }
    pr.ast(new ast::multipleStmts(st, s));
  } else {
    // Stmts ::=
    // nothing to match.k
    pr.ast(new ast::emptyStmts());
  }
  return pr;
}

// Stmt
/*!
 * Parses stmt
 */
ParseResult Parser::parse_stmt() {
  ParseResult pr;

  // Stmt ::= Decl
  if (next_is(scanner::kIntKwd) || next_is(scanner::kFloatKwd) ||
      next_is(scanner::kMatrixKwd) || next_is(scanner::kStringKwd) ||
      next_is(scanner::kBoolKwd)) {
    ParseResult pr_decl = parse_decl();
    ast::Decl *d = nullptr;

    if (pr_decl.ast()) {
      d = dynamic_cast<ast::Decl *>(pr_decl.ast());
      pr.ast(new ast::declStmt(d));
      if (!d) throw((std::string) "Bad cast of state in parseprogram");
    }
  } else if (attempt_match(scanner::kLeftCurly)) {
    // Stmt ::= '{' Stmts '}'
    ParseResult pr_stmts = parse_stmts();
    ast::Stmts *s = nullptr;

    if (pr_stmts.ast()) {
      s = dynamic_cast<ast::Stmts *>(pr_stmts.ast());
      if (!s) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightCurly);
    pr.ast(new ast::stmtsStmt(s));
  } else if (attempt_match(scanner::kIfKwd)) {
    // Stmt ::= 'if' '(' Expr ')' Stmt
    // Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    match(scanner::kLeftParen);
    ParseResult prExpr = parse_expr(0);
    ast::Expr *ex = nullptr;
    if (prExpr.ast()) {
      ex = dynamic_cast<ast::Expr *>(prExpr.ast());
      if (!ex) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *st = nullptr;

    if (pr_stmt.ast()) {
      st = dynamic_cast<ast::Stmt *>(pr_stmt.ast());
      if (!st) throw((std::string) "Bad cast of state in parseprogram");
    }

    pr.ast(new ast::ifStmt(ex, st));

    if (attempt_match(scanner::kElseKwd)) {
      ParseResult pr_stmt = parse_stmt();
      ast::Stmt *st1 = nullptr;

      if (pr_stmt.ast()) {
        st1 = dynamic_cast<ast::Stmt *>(pr_stmt.ast());
        if (!st1) throw((std::string) "Bad cast of state in parseprogram");
      }
      pr.ast(new ast::ifElseStmt(ex, st, st1));
    }
  } else if (attempt_match(scanner::kVariableName)) {
    /*
     * Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']'
     * '=' Expr ';'
     */
    std::string name(prev_token_->lexeme());
    ast::varName *var = new ast::varName(name);
    ast::Expr *ex1 = nullptr;
    ast::Expr *ex2 = nullptr;
    if (attempt_match(scanner::kLeftSquare)) {
      ParseResult prExpr1 = parse_expr(0);
      if (prExpr1.ast()) {
        ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());

        if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
      }
      match(scanner::kColon);
      ParseResult prExpr2 = parse_expr(0);
      if (prExpr2.ast()) {
        ex2 = dynamic_cast<ast::Expr *>(prExpr2.ast());
        if (!ex2) throw((std::string) "Bad cast of state in parseprogram");
      }
      match(scanner::kRightSquare);
    }
    match(scanner::kAssign);
    ParseResult expr3 = parse_expr(0);
    ast::Expr *ex3 = nullptr;
    if (expr3.ast()) {
      ex3 = dynamic_cast<ast::Expr *>(expr3.ast());
      if (!ex3) throw((std::string) "Bad cast of state in parse_matrix_decl");
    }
    match(scanner::kSemiColon);
    if (ex1 == nullptr && ex2 == nullptr) {
      pr.ast(new ast::assignStmt1(var, ex3));
    } else {
      pr.ast(new ast::assignStmt2(var, ex1, ex2, ex3));
    }
  } else if (attempt_match(scanner::kPrintKwd)) {
    // Stmt ::= 'print' '(' Expr ')' ';'
    match(scanner::kLeftParen);
    ParseResult prExpr = parse_expr(0);
    ast::Expr *ex = nullptr;
    if (prExpr.ast()) {
      ex = dynamic_cast<ast::Expr *>(prExpr.ast());
      if (!ex) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightParen);
    match(scanner::kSemiColon);
    pr.ast(new ast::printStmt(ex));
  } else if (attempt_match(scanner::kRepeatKwd)) {
    // Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    match(scanner::kLeftParen);
    match(scanner::kVariableName);
    std::string name(prev_token_->lexeme());
    ast::varName *var = new ast::varName(name);
    match(scanner::kAssign);
    ParseResult prExpr = parse_expr(0);
    ast::Expr *ex = nullptr;
    if (prExpr.ast()) {
      ex = dynamic_cast<ast::Expr *>(prExpr.ast());
      if (!ex) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kToKwd);
    ParseResult prExpr1 = parse_expr(0);
    ast::Expr *ex1 = nullptr;
    if (prExpr1.ast()) {
      ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
      if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *st1 = nullptr;

    if (pr_stmt.ast()) {
      st1 = dynamic_cast<ast::Stmt *>(pr_stmt.ast());
      if (!st1) throw((std::string) "Bad cast of state in parseprogram");
    }
    pr.ast(new ast::repeatStmt(var, ex, ex1, st1));
  } else if (attempt_match(scanner::kWhileKwd)) {
    // Stmt ::= 'while' '(' Expr ')' Stmt
    match(scanner::kLeftParen);
    ParseResult prExpr = parse_expr(0);
    ast::Expr *ex = nullptr;
    if (prExpr.ast()) {
      ex = dynamic_cast<ast::Expr *>(prExpr.ast());
      if (!ex) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightParen);
    ParseResult pr_stmt = parse_stmt();
    ast::Stmt *st1 = nullptr;
    if (pr_stmt.ast()) {
      st1 = dynamic_cast<ast::Stmt *>(pr_stmt.ast());
      if (!st1) throw((std::string) "Bad cast of state in while");
    }
    pr.ast(new ast::whileStmt(ex, st1));
  } else if (attempt_match(scanner::kSemiColon)) {
    // Stmt ::= ';
    // parsed a skip
    pr.ast(new ast::semiColonStmt());
  } else {
    throw(make_error_msg(curr_token_->terminal()) +
          " while parsing a statement");
  }
  // Stmt ::= variableName assign Expr semiColon
  return pr;
}

// Expr
/*!
 * Parses expr
 * */
ParseResult Parser::parse_expr(int rbp) {
  /* Examine current token, without consuming it, to call its
     associated parse methods.  The ExtToken objects have 'nud' and
     'led' methods that are dispatchers that call the appropriate
     parse methods.*/
  ParseResult left = curr_token_->nud();

  while (rbp < curr_token_->lbp()) {
    left = curr_token_->led(left);
  }

  return left;
}

/*
 * parse methods for Expr productions
 * ----------------------------------
 */

// Expr ::= trueKwd
/*!
 *  Parses true keyword
 */
ParseResult Parser::parse_true_kwd() {
  ParseResult pr;
  match(scanner::kTrueKwd);
  pr.ast(new ast::trueExpr());
  return pr;
}

// Expr ::= trueKwd
/*!
 *  Parses false keyword
 */
ParseResult Parser::parse_false_kwd() {
  ParseResult pr;
  match(scanner::kFalseKwd);
  pr.ast(new ast::falseExpr());
  return pr;
}

// Expr ::= intConst
/*!
 *  Parses int const
 */
ParseResult Parser::parse_int_const() {
  ParseResult pr;
  match(scanner::kIntConst);
  std::string val(prev_token_->lexeme());
  pr.ast(new ast::intExpr(val));
  return pr;
}

// Expr ::= floatConst
/*!
 * Parses float const
 * */
ParseResult Parser::parse_float_const() {
  ParseResult pr;
  match(scanner::kFloatConst);
  std::string val(prev_token_->lexeme());
  pr.ast(new ast::floatExpr(val));
  return pr;
}

// Expr ::= stringConst
/*!
 * Parses string const
 * */
ParseResult Parser::parse_string_const() {
  ParseResult pr;
  match(scanner::kStringConst);
  std::string name(prev_token_->lexeme());
  pr.ast(new ast::stringExpr(name));
  return pr;
}

// Expr ::= variableName .....
/*!
 * Parses variable name
 * */
ParseResult Parser::parse_variable_name() {
  ParseResult pr;
  match(scanner::kVariableName);
  std::string name(prev_token_->lexeme());
  ast::varName *var = new ast::varName(name);
  if (attempt_match(scanner::kLeftSquare)) {
    ParseResult prExpr1 = parse_expr(0);
    ast::Expr *ex1 = nullptr;
    if (prExpr1.ast()) {
      ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
      if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kColon);
    ParseResult prExpr2 = parse_expr(0);
    ast::Expr *ex2 = nullptr;
    if (prExpr2.ast()) {
      ex2 = dynamic_cast<ast::Expr *>(prExpr2.ast());
      if (!ex2) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightSquare);
    pr.ast(new ast::matrixExpr(ex1, ex2, var));
  } else if (attempt_match(scanner::kLeftParen)) {
    // Expr ::= varableName '(' Expr ')'
    ParseResult prExpr = parse_expr(0);
    ast::Expr *ex = nullptr;
    if (prExpr.ast()) {
      ex = dynamic_cast<ast::Expr *>(prExpr.ast());
      if (!ex) throw((std::string) "Bad cast of state in parseprogram");
    }
    match(scanner::kRightParen);
    pr.ast(new ast::nestedExpr(ex, var));
  } else {
    // variable
    pr.ast(new ast::varNameExpr(var));
  }
  return pr;
}

// Expr ::= leftParen Expr rightParen
/*!
 * Parses nested expression
*/
ParseResult Parser::parse_nested_expr() {
  ParseResult pr;
  match(scanner::kLeftParen);
  ParseResult prExpr1 = parse_expr(0);
  ast::Expr *ex1 = nullptr;
  if (prExpr1.ast()) {
    ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
    if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
  }
  match(scanner::kRightParen);
  pr.ast(new ast::parenExpr(ex1));
  return pr;
}

// Expr ::= 'if' Expr 'then' Expr 'else' Expr

ParseResult Parser::parse_if_expr() {
  ParseResult pr;

  match(scanner::kIfKwd);
  ParseResult prExpr1 = parse_expr(0);
  ast::Expr *ex1 = nullptr;
  if (prExpr1.ast()) {
    ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
    if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
  }
  match(scanner::kThenKwd);
  ParseResult prExpr2 = parse_expr(0);
  ast::Expr *ex2 = nullptr;
  if (prExpr2.ast()) {
    ex2 = dynamic_cast<ast::Expr *>(prExpr2.ast());
    if (!ex2) throw((std::string) "Bad cast of state in parseprogram");
  }
  match(scanner::kElseKwd);
  ParseResult prExpr3 = parse_expr(0);
  ast::Expr *ex3 = nullptr;
  if (prExpr3.ast()) {
    ex3 = dynamic_cast<ast::Expr *>(prExpr3.ast());
    if (!ex3) throw((std::string) "Bad cast of state in parseprogram");
  }
  pr.ast(new ast::ifExpr(ex1, ex2, ex3));

  return pr;
}

// Expr ::= 'let' Stmts 'in' Expr 'end'
ParseResult Parser::parse_let_expr() {
  ParseResult pr;
  match(scanner::kLetKwd);
  ParseResult pr_stmts = parse_stmts();
  ast::Stmts *s = nullptr;
  if (pr_stmts.ast()) {
    s = dynamic_cast<ast::Stmts *>(pr_stmts.ast());
    if (!s) throw((std::string) "Bad cast of state in parseprogram");
  }
  match(scanner::kInKwd);
  ParseResult prExpr1 = parse_expr(0);
  ast::Expr *ex1 = nullptr;
  if (prExpr1.ast()) {
    ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
    if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
  }
  match(scanner::kEndKwd);
  pr.ast(new ast::letExpr(s, ex1));

  return pr;
}

// Expr ::= '!' Expr
/*!
 * Parses not expression
 * */
ParseResult Parser::parse_not_expr() {
  ParseResult pr;
  match(scanner::kNotOp);
  ParseResult prExpr1 = parse_expr(0);
  ast::Expr *ex1 = nullptr;
  if (prExpr1.ast()) {
    ex1 = dynamic_cast<ast::Expr *>(prExpr1.ast());
    if (!ex1) throw((std::string) "Bad cast of state in parseprogram");
  }
  pr.ast(new ast::notExpr(ex1));
  return pr;
}


// Expr ::= Expr equalEquals Expr
// Expr ::= Expr lessThanEquals Expr
// Expr ::= Expr greaterThanEquals Expr
// Expr ::= Expr notEquals Expr
// Expr ::= Expr leftAngle Expr
// Expr ::= Expr rightAngle Expr
/* Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
*/
ParseResult Parser::parse_relational_expr(ParseResult prLeft) {
  // parser has already matchekD left expression
  ParseResult pr;

  next_token();
  // just advance token, since examining it in parse_expr caused
  // this method being called.
  std::string op = prev_token_->lexeme();
  ast::Expr *l = nullptr;
  if (prLeft.ast()) {
    l = dynamic_cast<ast::Expr *>(prLeft.ast());
    if (!l) throw((std::string) "Bad cast to Expr in Parse Relational Expr");
  }
  ParseResult prRight = parse_expr(prev_token_->lbp());
  ast::Expr *r = nullptr;
  if (prRight.ast()) {
    r = dynamic_cast<ast::Expr *>(prRight.ast());
    if (!r) throw((std::string) "Bad cast to Expr in Parse Relational Expr");
  }
  pr.ast(new ast::relationalExpr(l, r, op));
  // parse_expr(prev_token_->lbp());
  return pr;
}

// Helper function used by the parser.

/*!
 * Matches a token
 * \param tt TokenType to match
 * */
void Parser::match(const scanner::TokenType &tt) {
  if (!attempt_match(tt)) {
    throw(make_error_msg_expected(tt));
  }
}

/*!
 *  Tries to match a token
 *  \param tt TokenType to match
 */
bool Parser::attempt_match(const scanner::TokenType &tt) {
  if (curr_token_->terminal() == tt) {
    next_token();
    return true;
  }
  return false;
}

/*!
 * Returns true if current token terminal is tt
 * \param tt TokenType to check
 * */
bool Parser::next_is(const scanner::TokenType &tt) {
  return curr_token_->terminal() == tt;
}

/*!
 * Returns next token
*/
void Parser::next_token() {
  if (curr_token_ == nullptr) {
    throw(std::string(
        "Internal Error: should not call nextToken in unitialized state"));
  } else if (curr_token_->terminal() == scanner::kEndOfFile &&
             curr_token_->next() == nullptr) {
    prev_token_ = curr_token_;
  } else if (curr_token_->terminal() != scanner::kEndOfFile &&
             curr_token_->next() == nullptr) {
    throw(make_error_msg("Error: tokens end with endOfFile"));
  } else {
    prev_token_ = curr_token_;
    curr_token_ = curr_token_->next();
  }
}

std::string Parser::terminal_description(const scanner::TokenType &terminal) {
  scanner::Token *dummy_token = new scanner::Token("", terminal, nullptr);
  scanner::ExtToken *dummy_ext_token = new scanner::ExtToken(this, dummy_token);
  dummy_ext_token->ExtendToken(this, dummy_token);
  std::string s = dummy_ext_token->description();
  delete dummy_token;
  delete dummy_ext_token;
  return s;
}

/*!
 * Makes an error message
 * */
std::string Parser::make_error_msg_expected(
    const scanner::TokenType &terminal) {
  std::string s = (std::string) "Expected " + terminal_description(terminal) +
                  " but found " + curr_token_->description();
  return s;
}

/*!
 * Makes an error message
 * */
std::string Parser::make_error_msg(const scanner::TokenType &terminal) {
  std::string s = "Unexpected symbol " + terminal_description(terminal);
  return s;
}

/*!
 * Makes an error message
 * */
std::string Parser::make_error_msg(const char *msg) { return msg; }

} /* namespace parser */
} /* namespace fcal */
