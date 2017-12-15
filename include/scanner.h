/*******************************************************************************
 * Name            : scanner.h
 * Project         : fcal
 * Module          : scanner
 * Description     : Header file for scanner module
 * Copyright       : 2017 CSCI3081W Staff. All rights reserved.
 * Original Author : Eric Van Wyk
 * Modifications by: John Harwell
 ******************************************************************************/

#ifndef PROJECT_INCLUDE_SCANNER_H_
#define PROJECT_INCLUDE_SCANNER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <regex.h>
#include <map>
#include <string>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/* below are the possible terminal types for each token */

enum kTokenEnumType {
    /*0*/ kIntKwd,
    kFloatKwd,
    kBoolKwd,
    kTrueKwd,
    kFalseKwd,
    kStringKwd,
    kMatrixKwd,
    /*7*/ kLetKwd,
    kInKwd,
    kEndKwd,
    kIfKwd,
    kThenKwd,
    kElseKwd,
    /*13*/ kRepeatKwd,
    kWhileKwd,
    kPrintKwd,
    kToKwd,

    // Constants
    /*17*/ kIntConst,
    kFloatConst,
    kStringConst,

    // Names
    /*20*/ kVariableName,

    // Punctuation
    /*21*/ kLeftParen,
    kRightParen,
    kLeftCurly,
    kRightCurly,
    /*25*/ kLeftSquare,
    kRightSquare,

    kSemiColon,
    kColon,

    // Operators
    /*29*/ kAssign,
    kPlusSign,
    kStar,
    kDash,
    kForwardSlash,
    /*34*/ kLessThan,
    kLessThanEqual,
    kGreaterThan,
    kGreaterThanEqual,
    /*38*/ kEqualsEquals,
    kNotEquals,
    /*40*/ kAndOp,
    kOrOp,
    kNotOp,

    // Special terminal types
    /*43*/ kEndOfFile,
    kLexicalError
};

typedef enum kTokenEnumType TokenType;

struct match_result {
    TokenType type;
    int num_matched;
};
/*******************************************************************************
 * Class Definitions
 *
 * You will need to define a Token class (remember, a pointer of type Token *
 * is returned by the scan method of the scanner class.)
 * Also, Classes are typically declared (and sometimes also defined) in
 * their own header files
 *
 * You will also need to define a Scanner class with a scan and other methods
 ******************************************************************************/

// namespace TokenType{

class Token {
 private:
  TokenType terminal_;
  std::string lexeme_;
  Token *next_;
  int lexemeLength;

 public:
  Token();
  Token(TokenType, std::string, Token *);
  Token(std::string stringInput, TokenType term,  Token *nextToken);
  TokenType terminal();
  std::string lexeme();
  Token *next();
  int getlexemelength();
  void setTokenType(TokenType);
  void setLexeme(std::string);
  void setNextToken(Token *);
  void setlexemeLength();

  // line and column number on in the file where the lexeme is found NEEDED
};

class Scanner {
 public:
  Token *Scan(const char *);
  std::map<TokenType, regex_t *> dictionary;
  Scanner();
  void try_match(regex_t *re, const char *text, int *max_num_matched_chars,
                 match_result *res, TokenType type);
  void find_match(const char *text, int *max_num_matched_chars,
                  match_result *res);
};
//} /*namespace Token Type*/
} /* namespace scanner */
} /* namespace fcal */
#endif  // PROJECT_INCLUDE_SCANNER_H_
