
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
	token* takeNextToken();

private:
    ifstream* sourceFile;

    int numberOfLines, numOfCharacters;

    string tokenIdentifier();// extractTokenIdentifier
    string extractTokenInteger();
    string extractTokenStrings();
    string extractTokenSpaces();
    string tokenComment();
    string tokenOperator();
    string tokenPunction();
	bool isPunctuation(char);
	bool isOperator(char);
	bool isCommentSymbol(char);
	bool isKeywordSymbol(string);
};

#endif 
