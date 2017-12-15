
/*******************************************************************************
 * Name            : scanner.cc
 * Project         : fcal
 * Module          : scanner
 * Description     : Implementation of scanner
 * Original Author : Luke Erlandson and Shrijana Gurung
 * Copyright       : Luke Erlandson and Shrijana Gurung
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <map>
#include <string>

#include "include/regex.h"
#include "include/scanner.h"

#define DEBUG

/*
 * This enumerated type is used to keep track of what kind of construct was
 * matched.
 */

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace fcal {
namespace scanner {

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/

int consume_whitespace_and_comments(regex_t *whiteSpace, regex_t *block_comment,
                                    regex_t *line_comment, const char *text);

regex_t *make_regex(const char *pattern);
int match_regex(regex_t *, const char *);

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 *
 *
 *
 *
 **/

/*******************************************************************************
 * Constructor/Destructor for Token
 ******************************************************************************/

/*!
 * Token default constructor
 * */
Token::Token() {
  terminal_ = kLexicalError;
  lexeme_ = "";
  next_ = nullptr;
}

/*!
 * Token constructor
 * */
Token::Token(TokenType term, std::string stringInput, Token *nextToken) {
  terminal_ = term;
  lexeme_ = stringInput;
  next_ = nextToken;
}

/*!
 * Token constructor
 * */
Token::Token(std::string stringInput, TokenType term, Token *nextToken) {
  terminal_ = term;
  lexeme_ = stringInput;
  next_ = nextToken;
}

/*******************************************************************************
 * Token Member Functions
 ******************************************************************************/

TokenType Token::terminal() { return terminal_; }

std::string Token::lexeme() { return lexeme_; }

Token *Token::next() { return next_; }

int Token::getlexemelength() { return lexemeLength; }

void Token::setTokenType(TokenType term) { terminal_ = term; }

void Token::setLexeme(std::string stringInput) { lexeme_ = stringInput; }

void Token::setNextToken(Token *nextToken) { next_ = nextToken; }

void Token::setlexemeLength() { lexemeLength = lexeme_.length(); }

Scanner::Scanner() {
  // Keywords
  //

  const char *regexs[] = {"^int",
                          "^float",
                          "^boolean",
                          "^True",
                          "^False",
                          "^string",
                          "^matrix",
                          "^let",
                          "^in",
                          "^end",
                          "^if",
                          "^then",
                          "^else",
                          "^repeat",
                          "^while",
                          "^print",
                          "^to",
                          "^[0-9]+",
                          "^[0-9]+\\.[0-9]+",
                          "^\"[ !#-~]+\"",
                          "^[a-zA-Z][a-zA-Z0-9_]*",
                          "^\\(",
                          "^\\)",
                          "^\\{",
                          "^}",
                          "^\\[",
                          "^]",
                          "^;",
                          "^:",
                          "^=",
                          "^\\+",
                          "^\\*",
                          "^-",
                          "^/",
                          "^<",
                          "^<=",
                          "^>",
                          "^>=",
                          "^==",
                          "^!=",
                          "^&&",
                          "^\\|\\|",
                          "^!"};
  const TokenType tokens[] = {kIntKwd,       kFloatKwd,
                              kBoolKwd,      kTrueKwd,
                              kFalseKwd,     kStringKwd,
                              kMatrixKwd,    kLetKwd,
                              kInKwd,        kEndKwd,
                              kIfKwd,        kThenKwd,
                              kElseKwd,      kRepeatKwd,
                              kWhileKwd,     kPrintKwd,
                              kToKwd,        kIntConst,
                              kFloatConst,   kStringConst,
                              kVariableName, kLeftParen,
                              kRightParen,   kLeftCurly,
                              kRightCurly,   kLeftSquare,
                              kRightSquare,  kSemiColon,
                              kColon,        kAssign,
                              kPlusSign,     kStar,
                              kDash,         kForwardSlash,
                              kLessThan,     kLessThanEqual,
                              kGreaterThan,  kGreaterThanEqual,
                              kEqualsEquals, kNotEquals,
                              kAndOp,        kOrOp,
                              kNotOp};
  // static_assert(regexs.size() == tokens.size());

  for (int i = 0; i <= kNotOp; i++) {
    dictionary.insert(
        std::pair<TokenType, regex_t *>(tokens[i], make_regex(regexs[i])));
  }
}

/*!
 * Scan text for regexs, returns a token chain
 *
 * \param text Text to scan
 * \return Head of token chain
 * */
Token *Scanner::Scan(const char *text) {
  // Create the compiled regular expressions.
  regex_t *white_space = make_regex("^[\n\t\r ]+");
  // dictionary.insert(std::pair<regex_t *, TokenType>(white_space,
  // TokenType::white_space));
  //
  regex_t *block_comment = make_regex("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
  regex_t *line_comment = make_regex("^//[^\n]*");
  // dictionary.insert(std::pair<regex_t *, TokenType>(block_comment,
  // TokenType::block_comment));

  int num_matched_chars = 0;

  // Consume leading white space and comments
  num_matched_chars = consume_whitespace_and_comments(
      white_space, block_comment, line_comment, text);
  /*
   * text is a character pointer that points to the current beginning of the
   * array of characters in the input. Adding an integer value to it advances
   * the pointer that many elements in the array. Thus, text is increased so
   * that it points to the current location in the input.
   */
  text = text + num_matched_chars;

  int max_num_matched_chars = 0;

  Token *initialToken = new Token;
  // Do stuff with initial token
  Token *currentToken = initialToken;
  // std::cout << "\n";
  while (text[0] != '\0') {
    max_num_matched_chars = 0;

    match_result match;
    match.num_matched = 0;
    match.type = kLexicalError;

    find_match(text, &max_num_matched_chars, &match);

    std::string lexeme = std::string(text, match.num_matched);
    Token *nextToken = new Token(match.type, lexeme, nullptr);
    currentToken->setNextToken(nextToken);

    /*
     * max_num_matched_chars is used to ensure that the regular expression that
     * matched the longest string is the one that we use. If two match then
     * priority is given to the first one that was tried. This is done by the
     * comparison (num_matched_chars > max_num_matched_chars) which is a
     * strictly greater than comparison.
    */

    if (match.type == kLexicalError) {
      // If we didn't match anything, then just skip the first character.
      text = text + 1;
    } else {
      // Consume the characters that were matched.
      text = text + max_num_matched_chars;
    }

    // Consume white space and comments before trying again for
    // another word or integer.
    num_matched_chars = consume_whitespace_and_comments(
        white_space, block_comment, line_comment, text);
    text = text + num_matched_chars;

    currentToken = currentToken->next();
  }
  Token *nextToken = new Token(kEndOfFile, "", nullptr);
  currentToken->setNextToken(nextToken);
  Token *retToken = initialToken->next();

  return retToken;
} /* main() */

/*!
 * Attempts to match regex
 * \param re regex to match
 * \param text text to match
 * \param[out] max_num_matched_chars Max number of matched chars
 * \param[out] res Result
 * \param[out] type  TokenType
 * */
void Scanner::try_match(regex_t *re, const char *text,
                        int *max_num_matched_chars, match_result *res,
                        TokenType type) {
  int num_matched_chars = match_regex(re, text);
  if (num_matched_chars > *max_num_matched_chars) {
    // std::cout << "Matched: " << num_matched_chars << " Wtih: " << type <<
    // "\n";
    *max_num_matched_chars = num_matched_chars;
    res->num_matched = num_matched_chars;
    res->type = type;
  }
}  // try_match

/*!
 * Tries to match all regexes in dictionary
 * \param text text to match
 * \param max_num_matched_chars max number of matched chars
 * \param res Result
 * */
void Scanner::find_match(const char *text, int *max_num_matched_chars,
                         match_result *res) {
  for (auto const &it : dictionary) {
    // if(it.first == 0) {
    //  std::cout << "Uh oh! second is : " << it.second << "\n";
    // exit(-1);
    //}
    // else{
    try_match(it.second, text, max_num_matched_chars, res, it.first);
    //}
    // std::cout << "TestLoopEnd \n";
  }
  if (res->type == kLexicalError) {
    // std::cout << "LexicalError: " << text[0] << "\n";
    *max_num_matched_chars = 1;
    res->num_matched = 1;
  }
}  // find_match

/*!
 * Consumes whitespace, block comment, and line comments given their regexes
 * \param whiteSpace whitespace regex
 * \param block_comment block comment regex
 * \param line_comment line comment regex
 * \param text text ta match
 * */
int consume_whitespace_and_comments(regex_t *white_space,
                                    regex_t *block_comment,
                                    regex_t *line_comment, const char *text) {
  int num_matched_chars = 0;
  int total_num_matched_chars = 0;
  int still_consuming_white_space;

  do {
    still_consuming_white_space = 0;  // exit loop if not reset by a match

    // Try to match white space
    num_matched_chars = match_regex(white_space, text);
    total_num_matched_chars += num_matched_chars;
    if (num_matched_chars > 0) {
      text = text + num_matched_chars;
      still_consuming_white_space = 1;
    }

    // Try to match line comment
    num_matched_chars = match_regex(line_comment, text);
    total_num_matched_chars += num_matched_chars;
    if (num_matched_chars > 0) {
      text = text + num_matched_chars;
      still_consuming_white_space = 1;
    }

    // Try to match block comments
    num_matched_chars = match_regex(block_comment, text);
    total_num_matched_chars += num_matched_chars;
    if (num_matched_chars > 0) {
      text = text + num_matched_chars;
      still_consuming_white_space = 1;
    }
  } while (still_consuming_white_space);

  return total_num_matched_chars;
} /* consume_whitespace_and_comments() */

} /* namespace scanner */
} /* namespace fcal */
