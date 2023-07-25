
#include "lexer.h"

using namespace std;

lexer::lexer(std::ifstream* source) {
	sourceFile = source; 
	lineCount = 1;
	charCount = 1;
}

bool lexer::isPunction(char c){
  if('(' == c || ')' == c || ';' == c || ',' == c)
    return true;
  else
    return false;
}

bool lexer::isOperatorSymbol(char c){
	 if ('+' == c || '-' == c || '*' == c || '<' == c || '>' == c || '*' == c || '&' == c || '.' == c
	    || '@' == c|| '/' == c|| ':'== c || '=' == c|| '~' == c|| '|'== c || '$'== c || '!' == c
	    || '#'== c || '%'== c || '^'== c || '_'== c || '['== c || ']'== c || '{'== c || '}'== c
	    || '"'== c || '`'== c || '?'== c)
	        return true;
	    else
	        return false;
}

bool lexer::isCommentChar(char c){
	if ('\'' == c)  // char is '/'
		return true;
	else
		return false;
}

string lexer::tokenIdentifier(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	do {
		sourceFile->get(nextChar);
		charCount++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	}while (!(EOF == nextPeek) && (isalpha(nextPeek) || (nextPeek == '_') || isdigit(nextPeek)));
	return tokStr;
}

string lexer::tokenInteger(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	do {
		sourceFile->get(nextChar);
		charCount++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	}while (!(EOF == nextPeek) && isdigit(nextPeek));
	return tokStr;
}

string lexer::tokenStrings(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	do{
		sourceFile->get(nextChar);
		charCount++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
		if (nextChar == '\\'){
		    if ((nextPeek == 't' || nextPeek == 'n' || nextPeek == '\\' || nextPeek == '\''))
		    {
		        continue; //Valid escape sequence
		    } else {
		        printf ("Error \n");
		        exit(0);
		    }
		}
	} while (!(EOF == nextPeek) && !('\'' == nextPeek));
	sourceFile->get(nextChar);
	tokStr += nextChar;
	return tokStr;
}

string lexer::tokenSpaces(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	do{
		sourceFile->get(nextChar);
		charCount++;
		if (nextChar == 10 || nextChar == 13){
			charCount = 1;
			lineCount++;
		}
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	} while (!(EOF == nextPeek) && isspace(nextPeek));
	return tokStr;
}

string lexer::tokenComment(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	sourceFile->get(nextChar);
	charCount++;
	tokStr += nextChar;
	nextPeek = sourceFile->peek();
	if (nextPeek == '/'){
		sourceFile->get(nextChar);
		tokStr += nextChar;
		do{
			sourceFile->get(nextChar);
			tokStr += nextChar;
			nextPeek = sourceFile->peek();
		} while (!(EOF == nextPeek) && !(10 == nextPeek || 13 == nextPeek));
		return tokStr;
	} else {
		return tokStr;
	}
}

string lexer::tokenOperator(){
	string tokStr= "";
	char nextPeek;
	char nextChar;
	do{
		sourceFile->get(nextChar);
		charCount++;
		tokStr += nextChar;
		nextPeek = sourceFile->peek();
	} while (!(EOF == nextPeek) && isOperatorSymbol(nextPeek));
	return tokStr;
}

//This function is called by the read method in parser to fetch the new token.
//As per the rpal lexicon, the first character is used to determine which rule applies,
//a specialized function is called based on the rule that is applicable and
//subsequent characters are read till the newly read character differs from the selected rule.
//This marks the end of token, at which point it is passed to the parser.
token* lexer::getNextToken(){
	token* tok = new token();
	string tokenizedLex;
	int nextChar;
	char readNext;
	nextChar = sourceFile->peek();
	if (isalpha(nextChar)){
		tokenizedLex = tokenIdentifier();
        tok->tokType = TOK_IDENTIFIER;
	} else if (isdigit(nextChar)) {
		tokenizedLex = tokenInteger();
		tok->tokType = TOK_INTEGER;
	} else if ('\'' == nextChar){
		tokenizedLex = tokenStrings();
		tok->tokType = TOK_STRING;
	} else if (isspace(nextChar)){
		tokenizedLex = tokenSpaces();
		tok->tokType = TOK_DELETE;
	} else if (isPunction(nextChar)){
		sourceFile->get(readNext);
		charCount++;
		tokenizedLex = readNext;
		tok->tokType = TOK_PUNCTION;
	} else if (nextChar == '/' ) {
		tokenizedLex = tokenComment();
		if (!tokenizedLex.compare("/")){
			tok->tokType = TOK_OPERATOR;
		} else{
			tok->tokType = TOK_DELETE;
		}
	} else if (isOperatorSymbol(nextChar)){
		tokenizedLex = tokenOperator();
		tok->tokType = TOK_OPERATOR;
	} else if (EOF == nextChar) {
		tok->tokType = TOK_EOF;
	}
	tok->tokValue = tokenizedLex;
	tok->charCount = charCount;
	tok->lineCount = lineCount;
	return tok;
}
