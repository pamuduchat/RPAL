#ifndef PARSER_HEADER
#define PARSER_HEADER
#include "lexer.h"
#include <stack>
#include "TreeStandardizer.h"
#include "CSEMachine.h"

using namespace std;

class parser {
public:

	parser (lexer*);
    void evaluateProg();
	virtual ~parser();

private:
    lexer* lex;
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
    void buildTree(string, int); 
    void buildTree(string, int, int);
    void read(string);
	bool isKeyword(string);
};

#endif 
