all:	
	g++ -std=c++11 token.cpp TreeStandardizer.cpp lexer.cpp Control.cpp parser.cpp Environment.cpp CSEMachine.cpp program.cpp -o rpal20
cl: 
	rm -f p1;
