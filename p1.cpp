#include <stdio.h>
#include <string.h>
#include <fstream>
#include "lexer.h"
#include "parser.h"

using namespace std;

ifstream source;

bool isEvaluateProg = true;


void exec() {
	lexer* rpalLexer = new lexer(&source);
	parser* rpalParser = new parser(rpalLexer);
	if (isEvaluateProg){
	    //sprintf ("Evaluate program\n");
	    rpalParser->evaluateProg();
	}
}

int main (int argc, char *argv[]){
	int i = 1;
	if (argc == 2){
	    char* filename = argv[argc-1];
	    source.open(filename);
	    if (!source.good()){
	        printf ("Invalid input file\n");
	        return 0;
	    }
		exec();
		source.close();
	}
	else {
		printf("Please enter \'./rpal20 {Test program name}\'");
	}
}
