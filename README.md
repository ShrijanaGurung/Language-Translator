# Language-Translator
Translates small domain-specific language (DSL) to C for execution

#Overview

This is a group project that I completed with one of my classmate, Luke Erlandson from CSIS3081W - Program Design and Development. The main goal of this project was to understand and fix existing project files and eventually add more functionality to it. While we changed most of the provided programs, the files that include my team’s original work are:

[ast.cc](src/ast.cc), [scanner.cc](src/scanner.cc) , [matrix.cc](src/matrix.cc) , [makefile](makefile) and [all test files in tests folder](test)

In this project, we release 4 iteration versions throughout the semester and below are brief summary of the changes in each version:

For Iteration one: We identified any problem that was in the provded source code to avoid redundancy, unnecessary functions calls, remove any integer literals; hence to make the code robust. Once this part was done, we assigned regular expression (regex) to given tokens and made test cases to ensure all token were assigned with the correct regex. Then, the [scanner.cc](src/scanner.cc) file was created which utilizes the dictionary/map function.

For Iteration two: We added new regex expressions and token to our existing list, created test cases respectively. In this iteration, the focus was on fixing [scanner.cc](src/scanner.cc) if needed. But since our iter1 version was working, this new release didn’t have much changes implemented.

For Iteration Three: We focused on implementing Abstract Syntax Tree (AST) classes and include respective methods (Constructor, Destructor and Unparse) in [ast.cc](src/ast.cc). The goal of creatng AST is to maintain original structure of the DSL program. Once completed, we created test cases to ensure that when a sample code is scanned and parsed, each text are assigned to correct tokens and form a correct logical AST.

For Iteration Four: We added CppCode method to the existing classes in [ast.cc](src/ast.cc). The CppCode method translated the given token (generated from a scanned and parsed FCAL code) into C language and once all the generated token are accessed, the AST ensured that the logic was intact. The translated C programs were compiled and executed.

Hence, for the final product, we created a Language Translator that maps a small domain-specific language for analyzing forest loss and translate to C for execution.
