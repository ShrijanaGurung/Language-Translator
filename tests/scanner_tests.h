/*******************************************************************************
 * Name            : scanner_tests.h
 * Project         : fcal
 * Module          : tests
 * Description     : Tests of scanner
 * Original Author : Luke Erlandson and Shrijana Gurung
 * Copyright       : Luke Erlandson and Shrijana Gurung 
 ******************************************************************************/
#include <cxxtest/TestSuite.h>
#include <stdio.h>
#include <string>
#include "include/read_input.h"
#include "include/regex.h"
#include "include/scanner.h"

using namespace std;
namespace scanner = fcal::scanner;
class ScannerTestSuite : public CxxTest::TestSuite {
 public:
  /* A Scanner object is created in the test_setup_code method.
     This is a test, beginning with "test_", so that it is executed
     by the testing framework.  The scanner is used in some tests of
     the method "scan".
   */
  scanner::Scanner *s;
  void test_setup_code() { s = new scanner::Scanner(); }

  // Tests for components and functions used by "scan"
  // --------------------------------------------------

  /* You should test the regular expressions you use to make and match
     regular expressions,and the functions used by makeRegex and
     matchRegex regex_tests.h.
     However, You will likely need to write several tests to
     adequately test  the functions that are called from "scan".
     Once you are confident that the components used by "scan"
     work properly, then you can run tests on the "scan" method itself.
  */

  // You should place tests for these other functions used by
  // scan below.

  void test_make_match_regex(const char* given_input, scanner::TokenType given_token ,int match_char) {
      auto it = s->dictionary.find(given_token);
      TS_ASSERT(it->second);
      int num_matched_chars = scanner::match_regex(it->second, given_input);
      TS_ASSERT_EQUALS(num_matched_chars, match_char);
  }

  void test_make_match_regex_intKwd(void) { test_make_match_regex("int", scanner::kIntKwd, 3); }

  void test_make_match_regex_floatKwd(void) { test_make_match_regex( "float", scanner::kFloatKwd, 5);}

  void test_make_match_regex_boolKwd(void) { test_make_match_regex( "boolean", scanner::kBoolKwd, 7); }

  void test_make_match_regex_trueKwd(void) { test_make_match_regex( "True", scanner::kTrueKwd, 4); }

  void test_make_match_regex_falseKwd(void) { test_make_match_regex( "False", scanner::kFalseKwd, 5); }

  void test_make_match_regex_stringKwd(void) { test_make_match_regex( "string", scanner::kStringKwd, 6); }

  void test_make_match_regex_matrixKwd(void) { test_make_match_regex( "matrix", scanner::kMatrixKwd, 6); }
  
  void test_make_match_regex_letKwd(void) { test_make_match_regex("let", scanner::kLetKwd, 3); }
  
  void test_make_match_regex_inKwd(void) { test_make_match_regex( "in", scanner::kInKwd, 2); }

  void test_make_match_regex_ifKwd(void) { test_make_match_regex("if", scanner::kIfKwd, 2); }

  void test_make_match_regex_thenKwd(void) { test_make_match_regex( "then", scanner::kThenKwd, 4); }

  void test_make_match_regex_elseKwd(void) { test_make_match_regex( "else", scanner::kElseKwd, 4); }
  
  void test_make_match_regex_repeatKwd(void) { test_make_match_regex( "repeat", scanner::kRepeatKwd, 6); }

  void test_make_match_regex_whileKwd(void) { test_make_match_regex( "while" , scanner::kWhileKwd, 5); }

  void test_make_match_regex_printKwd(void) {test_make_match_regex( "print", scanner::kPrintKwd, 5); }

  void test_make_match_regex_toKwd(void) { test_make_match_regex( "to", scanner::kToKwd, 2); }

  void test_make_match_regex_intConst(void) { test_make_match_regex( "123", scanner::kIntConst, 3); }

  void test_make_match_regex_floatConst(void) { test_make_match_regex( "1.345", scanner::kFloatConst , 5); }

  void test_make_match_regex_stringConst(void) { test_make_match_regex( "\"sample\"", scanner::kStringConst, 8); }

  void test_make_match_regex_variableName(void) { test_make_match_regex( "variable", scanner::kVariableName, 8); }

  void test_make_match_regex_leftParen(void) { test_make_match_regex( "(", scanner::kLeftParen, 1); }

  void test_make_match_regex_rightParen(void) { test_make_match_regex( ")" , scanner::kRightParen, 1); }

  void test_make_match_regex_leftCurly(void) { test_make_match_regex("{", scanner::kLeftCurly, 1); }

  void test_make_match_regex_rightCurly(void) { test_make_match_regex( "}", scanner::kRightCurly, 1);}

  void test_make_match_regex_leftSquare(void) { test_make_match_regex( "[", scanner::kLeftSquare, 1); }

  void test_make_match_regex_rightSquare(void) { test_make_match_regex( "]", scanner::kRightSquare, 1); }

  void test_make_match_regex_semiColon(void) { test_make_match_regex( ";", scanner::kSemiColon, 1); }

  void test_make_match_regex_colon(void) { test_make_match_regex( ":", scanner::kColon, 1); }

  void test_make_match_regex_assign(void) { test_make_match_regex( "=", scanner::kAssign, 1); }

  void test_make_match_regex_plusSign(void) { test_make_match_regex( "+", scanner::kPlusSign, 1); }

  void test_make_match_regex_star(void) { test_make_match_regex( "*", scanner::kStar, 1); }

  void test_make_match_regex_dash(void) { test_make_match_regex( "-", scanner::kDash, 1); }

  void test_make_match_regex_forwardSlash(void) { test_make_match_regex( "/", scanner::kForwardSlash, 1); }

  void test_make_match_regex_lessThan(void) { test_make_match_regex( "<", scanner::kLessThan, 1); }

  void test_make_match_regex_lessThanEqual(void) { test_make_match_regex( "<=", scanner::kLessThanEqual, 2); }

  void test_make_match_regex_greaterThan(void) { test_make_match_regex( ">", scanner::kGreaterThan, 1); }

  void test_make_match_regex_greaterThanEqual(void) { test_make_match_regex( ">=", scanner::kGreaterThanEqual, 2); }

  void test_make_match_regex_equalsEquals(void) { test_make_match_regex( "==", scanner::kEqualsEquals, 2); }

  void test_make_match_regex_notEquals(void) { test_make_match_regex( "!=", scanner::kNotEquals, 2); }

  void test_make_match_regex_andOp(void) { test_make_match_regex( "&&", scanner::kAndOp, 2); }

  void test_make_match_regex_orOp(void) { test_make_match_regex( "||", scanner::kOrOp, 2); }

  void test_make_match_regex_notOp(void) { test_make_match_regex( "!", scanner::kNotOp, 1); }

  // test for keywords

  void test_terminal(const char* value, scanner::TokenType test_token) {
      scanner::Token *tks = s->Scan(value);
      TS_ASSERT_EQUALS(tks->terminal(), test_token);
  }

  void test_terminal_kIntKwd() { test_terminal("int", scanner::kIntKwd);}
  
  void test_terminal_kFloatKwd() { test_terminal("float",scanner::kFloatKwd);}

  void test_terminal_kBoolKwd() { test_terminal("boolean", scanner::kBoolKwd);}

  void test_terminal_kTrueKwd() { test_terminal("True",scanner::kTrueKwd);}

  void test_terminal_kFalseKwd() { test_terminal("False", scanner::kFalseKwd);}

  void test_terminal_kStringKwd() { test_terminal("string", scanner::kStringKwd);}

  void test_scan_kMatrixKwd() { test_terminal("matrix", scanner::kMatrixKwd);}

  void test_terminal_kLetKwd() { test_terminal("let", scanner::kLetKwd);}

  void test_terminal_kInKwd() { test_terminal("in", scanner::kInKwd);}

  void test_scan_kEndKwd() { test_terminal("end", scanner::kEndKwd);}

  void test_terminal_kIfKwd() { test_terminal("if", scanner::kIfKwd);}

  void test_terminal_kThenKwd() { test_terminal("then", scanner::kThenKwd);}

  void test_scan_kElseKwd() { test_terminal("else", scanner::kElseKwd);}

  void test_terminal_kRepeatKwd() { test_terminal("repeat", scanner::kRepeatKwd);}

  void test_terminal_kWhileKwd() { test_terminal("while", scanner::kWhileKwd);}

  void test_terminal_kPrintKwd() { test_terminal("print", scanner::kPrintKwd);}

  void test_terminal_kToKwd() { test_terminal("to", scanner::kToKwd);}

  // test for constants

  void test_terminal_kIntConst() { test_terminal("1234", scanner::kIntConst);}

  void test_terminal_kFloatConst() { test_terminal("1.234" , scanner::kFloatConst); }

  void test_terminal_kStringConst() { test_terminal("\"apple\"" , scanner::kStringConst);}

  // test for namespace

  void test_terminal_kVariableName() { test_terminal("test_variable", scanner::kVariableName);}
  // tests for punctuation

  void test_terminal_kLeftParen() { test_terminal("(" , scanner::kLeftParen);}

  void test_terminal_kRightParen() { test_terminal(")", scanner::kRightParen);}

  void test_terminal_kLeftCurly() { test_terminal("{", scanner::kLeftCurly);}

  void test_terminal_kRightCurly() { test_terminal("}", scanner::kRightCurly);}

  void test_terminal_kLeftSquare() { test_terminal("[", scanner::kLeftSquare);}

  void test_terminal_kRightSquare() { test_terminal("]", scanner::kRightSquare); }

  void test_terminal_kSemiColon() { test_terminal(";", scanner::kSemiColon);}

  void test_terminal_Colon() { test_terminal(":", scanner::kColon);}

  // test for Operators

  void test_terminal_kAssign() { test_terminal("=" , scanner::kAssign);}

  void test_terminal_kPlusSign() { test_terminal("+", scanner::kPlusSign);}

  void test_terminal_kStar() { test_terminal("*", scanner::kStar);}

  void test_terminal_kDash() { test_terminal("-", scanner::kDash);}

  void test_terminal_kForwardSlash() { test_terminal("/", scanner::kForwardSlash);}

  void test_terminal_kLessThan() { test_terminal("<", scanner::kLessThan); }

  void test_terminal_kLessThanEqual() { test_terminal("<=", scanner::kLessThanEqual);}

  void test_terminal_kGreaterThan() { test_terminal(">", scanner::kGreaterThan);}

  void test_terminal_kGreaterThanEqual() { test_terminal(">=", scanner::kGreaterThanEqual);}

  void test_terminal_kEqualsEquals() { test_terminal("==", scanner::kEqualsEquals);}

  void test_terminal_kNotEquals() { test_terminal("!=", scanner::kNotEquals); }

  void test_terminal_kAndOp() { test_terminal("&&", scanner::kAndOp);}

  void test_terminal_kOrOp() { test_terminal("||", scanner::kOrOp);}

  void test_terminal_kNotOp() { test_terminal("!", scanner::kNotOp);}

  void test_terminal_kEndOfFile() { test_terminal("", scanner::kEndOfFile);} // need to fix it

  void test_terminal_kLexicalError() { test_terminal("$", scanner::kLexicalError);}

  /* Below is one of the tests for these components in the project
     solution created by your instructor.  It uses a helper
     function function called "tokenMaker_tester", which you have
     not been given.  You are expected to design your own components
     for "scan" and your own mechanisms for easily testing them.

      void xtest_TokenMaker_leftCurly () {
          tokenMaker_tester ("{ ", "^\\{", leftCurly, "{");
      }

      Note that this test is here named "xtest_Token..." The leading
      "x" is so that cxxTest doesn't scan the line above and think
      it is an actual test that isn't commented out.  cxxTest is
      very simple and doesn't even process block comments.
  */

  /* You must have at least one separate test case for each terminal
     symbol.  Thus, you need a test that will pass or fail based
     solely on the regular expression (and its corresponding code)
     for each terminal symbol.

     This requires a test case for each element of the enumerated
     type tokenType.  This may look something like the sample test
     shown in the comment above.
  */

  // Tests for "scan"
  // --------------------------------------------------

  /* Below are some helper functions and sample tests for testing the
     "scan" method on Scanner.
  */

  // Test that a list of tokens has no lexicalError tokens.
  bool noLexicalErrors(scanner::Token *tks) {
      scanner::Token *currentToken = tks;
      while (currentToken != NULL) {
          if (currentToken->terminal() == scanner::kLexicalError) {
              printf("problem: %s\n", currentToken->lexeme().c_str());
              fflush(stdout);
              return false;
          } else {
              currentToken = currentToken->next();
          }
      }  // while
      return true;
  }

  /* A quick, but inaccurate, test for scanning files.  It only
     checks that no lexical errors occurred, not that the right
     tokens were returned.
  */
  void scanFileNoLexicalErrors(const char *filename) {
      char *text = scanner::ReadInputFromFile(filename);
      TS_ASSERT(text);
      scanner::Token *tks = s->Scan(text);
      TS_ASSERT(tks != NULL);
      TS_ASSERT(noLexicalErrors(tks));
  }

  /* This function checks that the terminal fields in the list of
     tokens matches a list of terminals.
  */
  bool sameTerminals(scanner::Token *tks, int numTerms,
                     scanner::TokenType *ts) {
      scanner::Token *currentToken = tks;
      int termIndex = 0;
      while (currentToken != NULL && termIndex < numTerms) {
          if (currentToken->terminal() != ts[termIndex]) {
              printf(
                  "item at index: %i: terminal: %i should be terminal: %i\n, "
                  "lexeme: %s",
                  termIndex, currentToken->terminal(), ts[termIndex],
                  currentToken->lexeme().c_str());
              fflush(stdout);
              return false;
          } else {
              ++termIndex;
              currentToken = currentToken->next();
          }
      }
      return true;
  }

  /* Below are the provided test files that your code should also
     pass.

     You may initially want to rename these tests to "xtest_..." so
     that the CxxTest framework does not see it as a test and won't
     run it as one.  This way you can focus on the tests that you'll
     write above for the individual terminal types first. Then focus
     on these tests.

  */

  // The "endOfFile" token is always the last one in the list of tokens.
  void test_scan_empty() {
      scanner::Token *tks = s->Scan("  ");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
      TS_ASSERT(tks->next() == NULL);
  }

  void test_scan_empty_comment() {
      scanner::Token *tks = s->Scan(" /* a comment */ ");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
      TS_ASSERT(tks->next() == NULL);
  }

  // When a lexical error occurs, the scanner creates a token with a
  // single-character lexeme and lexicalError as the terminal.
  void test_scan_lexicalErrors() {
      scanner::Token *tks = s->Scan("$&1  ");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
      TS_ASSERT_EQUALS(tks->lexeme(), "$");
      tks = tks->next();
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kLexicalError);
      TS_ASSERT_EQUALS(tks->lexeme(), "&");
      tks = tks->next();
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kIntConst);
      TS_ASSERT_EQUALS(tks->lexeme(), "1");
      tks = tks->next();
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal(), scanner::kEndOfFile);
      TS_ASSERT(tks->next() == NULL);
  }

  // A test for scanning numbers and a variable.

  void test_scan_nums_vars() {
      scanner::Token *tks = s->Scan(" 123 x 12.34 ");
      TS_ASSERT(tks != NULL);
      scanner::TokenType ts[] = {scanner::kIntConst, scanner::kVariableName,
                                 scanner::kFloatConst, scanner::kEndOfFile};
      TS_ASSERT(sameTerminals(tks, 4, ts));
  }

  /* This test checks that the scanner returns a list of tokens with
     the correct terminal fields.  It doesn't check that the lexemes
     are correct.
   */

  void test_scan_bad_syntax_good_tokens() {
      const char *filename = "./samples/bad_syntax_good_tokens.dsl";
      char *text = scanner::ReadInputFromFile(filename);
      TS_ASSERT(text);
      scanner::Token *tks = NULL;
      tks = s->Scan(text);
      TS_ASSERT(tks != NULL);
      scanner::TokenType ts[] = {scanner::kIntConst,
                                 scanner::kIntConst,
                                 scanner::kIntConst,
                                 scanner::kIntConst,
                                 scanner::kStringConst,
                                 scanner::kStringConst,
                                 scanner::kStringConst,
                                 scanner::kFloatConst,
                                 scanner::kFloatConst,
                                 scanner::kFloatConst,
                                 scanner::kMatrixKwd,
                                 scanner::kSemiColon,
                                 scanner::kColon,
                                 scanner::kToKwd,
                                 scanner::kLeftCurly,
                                 scanner::kLeftParen,
                                 scanner::kRightCurly,
                                 scanner::kRightParen,
                                 scanner::kPlusSign,
                                 scanner::kStar,
                                 scanner::kDash,
                                 scanner::kForwardSlash,
                                 scanner::kEqualsEquals,
                                 scanner::kLessThanEqual,
                                 scanner::kGreaterThanEqual,
                                 scanner::kNotEquals,
                                 scanner::kAssign,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kVariableName,
                                 scanner::kIntKwd,
                                 scanner::kFloatKwd,
                                 scanner::kStringKwd,
                                 scanner::kEndOfFile};
      int count = 38;
      TS_ASSERT(sameTerminals(tks, count, ts));
  }

  void test_scan_sample_forestLoss() {
      scanFileNoLexicalErrors("./samples/forest_loss_v2.dsl");
  }
};
