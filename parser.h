#ifndef PARSER_HEADER
#define PARSER_HEADER
#include "standardizer.h"
#include "lexicalanalyzer.h"
#include <stack>
#include "cse.h"

using namespace std;

class parser {
public:
	parser (lexer*);
    void evaluateProgram();

private:
    lexer* lexAnalyzer;
    stack <treeNode*> treeStack;
    token *nextToken;

	void E();
	void Ew();
	void T();
	void Ta();
	void Tc();
	void B();
	void Bt();
	void Bs();
	void Bp();
	void A();
	void At();
	void Af();
	void Ap();
	void R();
	void Rn();
	void D();
	void Da();
	void Dr();
	void Db();
	void Vb();
	void Vl();

	void parse();
	void standardize(treeNode*);
    void buildAST(string, int); 
    void buildAST(string, int, int);
    void readToken(string);
	bool isKeywordSymbol(string);
};

#endif 
