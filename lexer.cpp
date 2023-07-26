
#include "lexer.h"
#include <algorithm>

using namespace std;

// Constructor for the lexer class
lexer::lexer(std::ifstream* source) {
	sourceFile = source; 
	numberOfLines = 1;
	numOfCharacters = 1;
}

// Function to check if a character is a punctuation symbol
bool lexer::isPunctuation(char target){
	char arr[] = {'(', ')', ';', ','};
	int n = 4;
	bool exists = find(arr, arr+n, target)!= arr + n;
	return exists;
}

// Function to check if a character is an operator symbol
bool lexer::isOperator(char target){
	char arr[] = {'+', '-', '*', '<', '>', '*', '&', '.', '@', '/', ':', '=', '~', '|', '$', '!', '"', '`', '?'};
    int n = 19;
    bool exists = find(arr, arr + n, target) != arr + n;
	   return exists;
}

// Function to check if a character is not a comment symbol (i.e., not a single quote)
bool lexer::isCommentSymbol(char c) {
    return ('\'' != c);
}

// Function to extract an identifier token
string lexer::tokenIdentifier(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	numOfCharacters++;
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	while (!(EOF == nextPeek) && ( isalpha(nextPeek) || (nextPeek == '_') || isdigit(nextPeek))){
		sourceFile->get(nextChar);
		numOfCharacters++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	}
	return tokStr;
}

// Function to extract an integer token
string lexer::extractTokenInteger(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	numOfCharacters++;
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	while (!(EOF == nextPeek) && isdigit(nextPeek)){
		sourceFile->get(nextChar);
		numOfCharacters++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	}
	return tokStr;
}

// Function to extract a string token (enclosed in single quotes)
string lexer::extractTokenStrings(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	numOfCharacters++;
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	if (nextChar == '\\'){
		if (!(nextPeek == 't' || nextPeek == 'n' || nextPeek == '\\' || nextPeek == '\''))
			{
		        printf ("Error \n");
		        exit(0);
		    }
		}
	while (!(EOF == nextPeek) && !('\'' == nextPeek)){
		sourceFile->get(nextChar);
		numOfCharacters++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
		if (nextChar == '\\'){
			if ((nextPeek == 't' || nextPeek == 'n' || nextPeek == '\\' || nextPeek == '\'')){
				continue; 
			}else{
				printf("Error \n");
				exit(0);
			}
		}
	}
	sourceFile->get(nextChar);
	tokStr += nextChar;
	return tokStr;
}

// Function to extract spaces 
string lexer::extractTokenSpaces(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	numOfCharacters++;
	if (nextChar == 10 || nextChar == 13){
		numOfCharacters = 1;
		numberOfLines++;
		}
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	while (!(EOF == nextPeek) && isspace(nextPeek)){
		sourceFile->get(nextChar);
		numOfCharacters++;
		if (nextChar == 10 || nextChar == 13){
			numOfCharacters = 1;
			numberOfLines++;
		}
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	} 
	return tokStr;
}


// Function to handle comment tokens
string lexer::tokenComment(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	numOfCharacters++;
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	if (nextPeek == '/'){
		sourceFile->get(nextChar);
		tokStr += nextChar;
		sourceFile->get(nextChar);
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
		while (!(EOF == nextPeek) && !(nextPeek == 10 || nextPeek  == 13)){
			sourceFile->get(nextChar);
			tokStr += nextChar;
			nextPeek = sourceFile->peek();
	 }
	 return tokStr;
	}
	else{
		return tokStr;
		}
}



// Function to extract an operator token
string lexer::tokenOperator(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
 numOfCharacters++;
 tokStr += nextChar;
 nextPeek = sourceFile->peek();
 while (!(EOF == nextPeek) && isOperator(nextPeek)){
		sourceFile->get(nextChar);
		numOfCharacters++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	}
 return tokStr;
}

// Function to read and process the next token from the input source file
token* lexer::takeNextToken(){
	token* tok = new token();
	string tokenizedLex; 
	int nextChar; 
	char readNext; 
	nextChar = sourceFile->peek();
	if (isalpha(nextChar)){
		tokenizedLex = tokenIdentifier();
        tok->type = TOK_IDENTIFIER;
	} else if (isdigit(nextChar)) {
		tokenizedLex = extractTokenInteger();
		tok->type = TOK_INTEGER;
	} else if ('\'' == nextChar){
		tokenizedLex = extractTokenStrings();
		tok->type = TOK_STRING;
	} else if (isspace(nextChar)){
		tokenizedLex = extractTokenSpaces();
		tok->type = TOK_DELETE;
	} else if (isPunctuation(nextChar)){
		sourceFile->get(readNext);
		numOfCharacters++;
		tokenizedLex = readNext;
		tok->type = TOK_PUNCTION;
	} else if (nextChar == '/' ) {
		tokenizedLex = tokenComment();
		if (!tokenizedLex.compare("/")){
			tok->type = TOK_OPERATOR;
		} else{
			tok->type = TOK_DELETE;
		}
	} else if (isOperator(nextChar)){
		tokenizedLex = tokenOperator();
		tok->type = TOK_OPERATOR;
	} else if (EOF == nextChar) {
		tok->type = TOK_EOF;
	}
	tok->value = tokenizedLex;
	tok->numOfCharacters = numOfCharacters;
	tok->numOfLines = numberOfLines;
	return tok;
}

