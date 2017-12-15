#Note, you may have to update CXX_DIR and
#CXXTEXT to point the right locations and executables
#to get it to work - look at your Lab 3 Makefile
CXX_DIR = ./lib/cxxtest
CXXTEST = $(CXX_DIR)/bin/cxxtestgen
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -I. -std=c++11 -g

test: run-tests check-style
# Program files.
read_input.o:	src/read_input.cc include/read_input.h
	g++ $(FLAGS) -c src/read_input.cc 

regex.o:	src/regex.cc include/regex.h
	g++ $(FLAGS) -c src/regex.cc 

scanner.o: 	src/regex.cc include/regex.h src/scanner.cc include/scanner.h
	g++ $(FLAGS) -c src/scanner.cc

parser.o:	src/parser.cc include/regex.h include/parser.h include/scanner.h include/ext_token.h include/ast.h
	g++ $(FLAGS) -c src/parser.cc 

ext_token.o:	src/ext_token.cc include/regex.h src/scanner.cc include/scanner.h
	g++ $(FLAGS) -c src/ext_token.cc

ast.o:	src/ast.cc include/ast.h
	g++ $(FLAGS) -c src/ast.cc

Matrix.o:	src/Matrix.cc include/Matrix.h
	g++ $(FLAGS) -c src/Matrix.cc

# Below is a possible way to make scanner
# Yours may vary depending on your implementation
#scanner.o:	src/scanner.cc include/scanner.h include/regex.h
#	g++ $(FLAGS) -c src/scanner.cc 



# Testing files and targets.  
# run-tests should work once 
# and run regex_tests once you put the files
# we gave you in the right places
# and update the CXX_DIR and CXXTEST variables so they
# reference the correct directory locations
# Add scanner_tests to the dependency list and uncomment when
# you are ready to start testing units with scanner_tests.
run-tests:	regex_tests scanner_tests parser_tests ast_tests codegeneration_tests
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
	./codegeneration_tests

#This should work once you put the files
#we gave you in the right places
regex_tests:	regex_tests.cc regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o regex_tests regex.o regex_tests.cc

regex_tests.cc:	include/regex.h tests/regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cc tests/regex_tests.h

# Below is a possible way to make scanner_tests and scanner_tests.cc
# Yours may vary depending on your design and implementation 
scanner_tests:	scanner_tests.cc scanner.o regex.o read_input.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o scanner_tests \
		scanner.o regex.o read_input.o scanner_tests.cc

scanner_tests.cc:	scanner.o tests/scanner_tests.h include/read_input.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cc tests/scanner_tests.h


parser_tests:	parser_tests.cc parser.o scanner.o regex.o read_input.o ext_token.o ast.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o parser_tests \
		scanner.o regex.o read_input.o parser.o ext_token.o ast.o parser_tests.cc

parser_tests.cc:	parser.o tests/parser_tests.h include/read_input.h include/ext_token.h
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cc tests/parser_tests.h

ast_tests:	ast_tests.cc ast.o parser.o read_input.o scanner.o ext_token.o regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o ast_tests \
		ext_token.o regex.o scanner.o ast.o read_input.o parser.o ast_tests.cc

codegeneration_tests:	codegeneration_tests.cc ast.o parser.o read_input.o scanner.o ext_token.o regex.o Matrix.o
	g++ $(FLAGS) -I$(CXX_DIR) -I. -o codegeneration_tests \
		Matrix.o ext_token.o regex.o scanner.o ast.o read_input.o parser.o codegeneration_tests.cc

codegeneration_tests.cc:	ast.o tests/codegeneration_tests.h include/read_input.h include/parser.h
	$(CXXTEST) $(CXXFLAGS) -o codegeneration_tests.cc tests/codegeneration_tests.h

ast_tests.cc:	ast.o tests/ast_tests.h include/read_input.h include/parser.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cc tests/ast_tests.h

check-style:    cpplint.py
	python cpplint.py --repository=.. {src,include}/*

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cc \
		scanner_tests scanner_tests.cc 

docs: src/*.cc include/*.h
	doxygen doxyfile 2> docs/doxgen-errors.txt
	cd docs/latex/ && make && cp refman.pdf ../../iter3Documentation.pdf
