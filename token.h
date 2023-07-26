#include <string>
#ifndef TOKEN_HEADER
#define TOKEN_HEADER

enum tokenType{
	TOK_DEFAULT = 0,
	TOK_KEYWORD = 1,
	TOK_IDENTIFIER = 2,
	TOK_OPERATOR = 3,
	TOK_WHITESPACE = 4,
	TOK_COMMENT = 5,
	TOK_STRING = 6,
	TOK_INTEGER = 7,
	TOK_PUNCTION = 8,
	TOK_EOF = 9,
	TOK_DELETE = 10,
	TOK_ERROR,
	TOK_ANY
};

class token {

public:
	token();
	// type
	int type;
	// value
	std::string value;
	//numOfLines numOfCharacters 
	 int numOfLines, numOfCharacters;
};

#endif 
