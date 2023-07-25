
#ifndef LEXER_HEADER
#define LEXER_HEADER
using namespace std;
#define STANDARDIZERLOGS 0

#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include "token.h"

class lexer {
public:
	lexer(std::ifstream*);
	token* getNextToken();

private:
    ifstream* sourceFile;
    int lineCount, charCount;
    string tokenIdentifier();
    string tokenInteger();
    string tokenStrings();
    string tokenSpaces();
    string tokenComment();
    string tokenOperator();
    string tokenPunction();

	bool isPunction(char);
	bool isOperatorSymbol(char);
	bool isSpaces(char);
	bool isEOL(char);
	bool isEOF(char);
	bool isCommentChar(char);
	bool isKeyword(string);
};

#endif 
