all:	
	g++ -std=c++11 token.cpp lexicalanalyzer.cpp Control.cpp parser.cpp cse.cpp env.cpp standardizer.cpp program.cpp -o rpal20
cl: 
	rm -f p1;
