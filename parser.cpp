#include "parser.h"

parser::parser(lexer* lexr){
	this->lexAnalyzer = lexr;//lexer
	nextToken = NULL;
}

void parser::evaluateProgram(){
    parse();
    TreeStandardizer *standadizer = new TreeStandardizer(treeStack.top());
    CSEMachine* cseMachine = new CSEMachine();
    cseMachine->run(treeStack.top());
}

void parser::parse(){
	do {
		nextToken = lexAnalyzer->takeNextToken();  
	}while (nextToken->type == TOK_DELETE);
	E();
	if ((!treeStack.empty() && treeStack.size() != 1) || (lexAnalyzer->takeNextToken()->type != TOK_EOF)){
		printf ("Error");
		exit(0);
	} 
}

// checkKeyword
bool parser::isKeywordSymbol(string val) {
    // Array to store the keyword symbols
    const string keywords[] = {
        "in", "where", ".", "aug", "and", "or",
        "&", "not", "gr", "ge", "ls", "le",
        "eq", "ne", "+", "-", "*", "/",
        "**", "@", "within", "rec", "let", "fn"
    };

    for (const string& keyword : keywords) {
        if (val == keyword) {
            return true;
        }
    }

    // If the value does not match any keyword, return false
    return false;
}

// readToken
void parser::readToken(string tokStr){ 
    if (!(nextToken->value == tokStr)){
        printf ("error");
        exit(0);
    }
    do {
        nextToken = lexAnalyzer->takeNextToken();
    }while (nextToken->type == TOK_DELETE); 
}

//buildAST
void parser::buildAST(string nodeStr, int childNodeCount, int type){
    int finalSize = treeStack.size() - childNodeCount + 1;
    treeNode* newNode = new treeNode();
    treeNode* tempNode = new treeNode();
    newNode->nodeString = nodeStr;
    newNode->type = type;
    if (childNodeCount == 0){
        treeStack.push(newNode);
        return;
    }
    if (treeStack.empty()){
        return;
    } else {
        while ((childNodeCount - 1) > 0){
            if (!treeStack.empty()){
                tempNode = treeStack.top();
                treeStack.pop();
                if (treeStack.size() != 0){
                    treeStack.top()->siblingNode = tempNode;
                } else if (treeStack.size() == 0) {
                    exit(0);
                }
                childNodeCount--;
            } else {
                return;
            }
        }
        tempNode = treeStack.top();
        newNode->childNode = tempNode;
        treeStack.pop();
    }
    treeStack.push(newNode);
}


/* E    -> ’let’ D ’in’ E                          => ’let’
        -> ’fn’ Vb+ ’.’ E                          => ’lambda’
         ->  Ew;
*/
void parser::E(){
	//tokenValue
	if (nextToken->value == "let")
	{
		readToken("let");
		D();
		readToken ("in");
		E();
		buildAST("let", 2, treeNode::LET);

	} else if (nextToken->value == "fn"){
		readToken("fn");
		int n = 0;
		do {
			Vb();
			n++;
		}while(nextToken->value == "(" || nextToken->type == TOK_IDENTIFIER);
		readToken(".");
		E();
		buildAST("lambda", n+1, treeNode::LAMBDA);
	} else {
		Ew();
	}
}

/* Ew   -> T ’where’ Dr                            => ’where’
        -> T;*/
 void parser::Ew(){
 	T();
 	if (nextToken->value == "where")
 	{
 		readToken("where");
 	 	Dr();
 	 	buildAST("where",2, treeNode::WHERE);
 	}
 }

 /* T    -> Ta ( ’,’ Ta )+                          => ’tau’
         -> Ta ;
*/
 void parser::T(){
	 int n = 0;
	 Ta();
	 if (nextToken->value == ","){
		 do {
			 readToken(",");
			 Ta();
			 n++;
		 }while (nextToken->value == ",");
		 buildAST("tau", n+1, treeNode::TAU);
	 }
 }

 /* Ta   -> Ta ’aug’ Tc                             => ’aug’
         -> Tc ;
*/
 void parser::Ta(){
	 Tc();
	 while (nextToken->value == "aug"){
		 readToken("aug");
		 Tc();
		 buildAST("aug", 2, treeNode::AUG);
	 }
 }

 /* Tc   -> B ’->’ Tc ’|’ Tc                      => '->'
         -> B ;
  */
 void parser::Tc(){
	 B();
	 if (nextToken->value == "->"){
		 readToken("->");
		 Tc();
		 readToken("|");
		 Tc();
		 buildAST("->", 3, treeNode::TERNARY);
	 }
 }

/* B    -> B ’or’ Bt                               => ’or’
        -> Bt ;
*/
void parser::B(){
	Bt();
	while (nextToken->value == "or"){
		readToken ("or");
		Bt();
		buildAST("or", 2, treeNode::OR);
	}
}

/*  Bt   -> Bt ’&’ Bs                               => ’&’
         -> Bs ;
*/
void parser::Bt(){
	Bs();
	while (nextToken->value == "&"){
		readToken("&");
		Bs();
		buildAST("&", 2, treeNode::AND_LOGICAL);
	}
}

/* Bs   -> ’not’ Bp                                => ’not’
        -> Bp ;
*/
void parser::Bs(){
	if (nextToken->value == "not"){
		readToken ("not");
		Bp();
		buildAST("not", 1, treeNode::NOT);
	}else {
		Bp();
	}
}

/* Bp   -> A (’gr’ | ’>’ ) A                       => ’gr’
        -> A (’ge’ | ’>=’) A                       => ’ge’
        -> A (’ls’ | ’<’ ) A                       => ’ls’
        -> A (’le’ | ’<=’) A                       => ’le’
        -> A ’eq’ A                                => ’eq’
        -> A ’ne’ A                                => ’ne’
        -> A ;
*/
void parser::Bp(){
	A();
	if (nextToken->value == "gr" || nextToken->value == ">"){
		if (nextToken->value == "gr")
			readToken("gr");
		else if (nextToken->value == ">")
			readToken(">");
		A();
		buildAST("gr", 2, treeNode::GR);
	}else if (nextToken->value == "ge" || nextToken->value == ">="){
		if (nextToken->value == "ge")
			readToken("ge");
		else if (nextToken->value == ">=")
			readToken(">=");
		A();
		buildAST("ge", 2, treeNode::GE);
	}else if (nextToken->value == "ls" || nextToken->value == "<"){
		if (nextToken->value == "ls")
			readToken("ls");
		else if (nextToken->value == "<")
			readToken("<");
		A();
		buildAST("ls", 2, treeNode::LS);
	}else if (nextToken->value == "le" || nextToken->value == "<="){
		if (nextToken->value == "le")
			readToken("le");
		else if (nextToken->value == "<=")
			readToken("<=");
		A();
		buildAST("le", 2, treeNode::LE);
	}else if (nextToken->value == "eq"){
		readToken("eq");
		A();
		buildAST("eq", 2, treeNode::EQ);
	}else if (nextToken->value == "ne"){
		readToken("ne");
		A();
		buildAST("ne", 2, treeNode::NE);
	}
}

/* A    -> A ’+’ At                                => ’+’
        -> A ’-’ At                                => ’-’
        ->   ’+’ At
        ->   ’-’ At                                => ’neg’
        -> At ;
*/
void parser::A(){
	string treeStr;
	if (nextToken->value == "+"){
		readToken("+");
		At();
	} else if (nextToken->value == "-"){
		readToken("-");
		At();
		buildAST ("neg", 1, treeNode::NEG);
	} else {
		At();
	}
	while (nextToken->value == "+" || nextToken->value == "-"){
		if (nextToken->value == "+"){
			readToken("+");
			treeStr = "+";
		} else {
			readToken("-");
			treeStr = "-";
		}
		At();
		buildAST(treeStr, 2, treeStr == "+" ? treeNode::ADD: treeNode::SUBTRACT);
	}
}

/* 
	At   -> At ’*’ Af                               => ’*’
        -> At ’/’ Af                               => ’/’
        -> Af ;
*/
void parser::At(){
	string treeStr;
	Af();
	while(nextToken->value == "*" || nextToken->value == "/"){
		if (nextToken->value == "*"){
			readToken("*");
			treeStr = "*";
		} else {
			readToken("/");
			treeStr = "/";
		}
		Af();
		buildAST(treeStr, 2, treeStr == "*" ? treeNode::MULTIPLY: treeNode::DIVIDE);
	}
}

/* Af   -> Ap ’**’ Af                              => ’**’
        -> Ap ;
*/
void parser::Af(){
	Ap();
	if (nextToken->value == "**"){
		readToken("**");
		Af();
		buildAST("**", 2, treeNode::EXPONENTIAL);
	}
}

/* Ap   -> Ap ’@’ ’<IDENTIFIER>’ R                 => ’@’
        -> R ;
*/
void parser::Ap(){
	R();
	while (nextToken->value == "@"){
		readToken("@");
		buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
		readToken(nextToken->value);
		R();
		buildAST("@", 3, treeNode::AT);
	}
}

/* R    -> R Rn                                    => ’gamma’
        -> Rn ;
*/
void parser::R(){
	Rn();
	while ( (TOK_IDENTIFIER == nextToken->type  || TOK_INTEGER == nextToken->type|| TOK_STRING == nextToken->type
			||"(" == nextToken->value || "false" == nextToken->value
			|| "true" == nextToken->value || "nil" == nextToken->value || "dummy" == nextToken->value) && !isKeywordSymbol(nextToken->value)){
		Rn();
		buildAST("gamma", 2, treeNode::GAMMA);
	}
}

/* Rn   -> ’<IDENTIFIER>’
        -> ’<INTEGER>’
        -> ’<STRING>’
        -> ’true’                                  => ’true’
        -> ’false’                                 => ’false’
        -> ’nil’                                   => ’nil’
        -> ’(’ E ’)’
        -> ’dummy’                                 => ’dummy’ ;
*/
void parser::Rn(){
	if("(" == nextToken->value){
		readToken("(");
		E();
		readToken(")");
	}
	else if(TOK_IDENTIFIER == nextToken->type || TOK_INTEGER == nextToken->type || TOK_STRING == nextToken->type){
		if("true" == nextToken->value){
			readToken("true");
			buildAST("<true>", 0, treeNode::TRUE);
		}
		else if("false" == nextToken->value){
			readToken("false");
			buildAST("<false>", 0, treeNode::FALSE);
		}
		else if("nil" == nextToken->value){
			readToken("nil");
			buildAST("<nil>", 0, treeNode::NIL);
		}
		else if("dummy" == nextToken->value){
			readToken("dummy");
			buildAST("<dummy>",0, treeNode::DUMMY);
		}
		else if(TOK_IDENTIFIER == nextToken->type){
			buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
			readToken(nextToken->value);
		}
		else if(TOK_STRING == nextToken->type){
			buildAST(nextToken->value, 0, treeNode::STRING);
			readToken(nextToken->value);
		}
		else if(TOK_INTEGER == nextToken->type){
			buildAST(nextToken->value, 0, treeNode::INTEGER);
			readToken(nextToken->value);
		}
	}
}

/* D    -> Da ’within’ D                           => ’within’
        -> Da ;
  */
void parser::D(){
	Da();
	if (nextToken->value == "within"){
		readToken("within");
		D();
		buildAST("within", 2, treeNode::WITHIN);
	}
}
/*     Da   -> Dr ( ’and’ Dr )+                        => ’and’
            -> Dr ;
*/
void parser::Da(){
	int n = 0;
	Dr();
	while (nextToken->value == "and"){
		readToken("and");
		Dr();
		n++;
	}
	if (n >0)
		buildAST("and", n+1, treeNode::AND);
}

/*      Dr   -> ’rec’ Db                                => ’rec’
             -> Db ;
*/
void parser::Dr(){
	if (nextToken->value == "rec"){
		readToken("rec");
		Db();
		buildAST("rec", 1, treeNode::REC);
	} else {
		Db();
	}
}

/* Db   -> Vl ’=’ E                              => ’=’
        -> ’<IDENTIFIER>’ Vb+ ’=’ E              => ’fcn_form’
        -> ’(’ D ’)’ ;
  */
void parser::Db(){
	if (nextToken->value == "("){
		readToken("(");
		D();
		readToken(")");
	} else if (nextToken->type == TOK_IDENTIFIER){
		buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
		readToken(nextToken->value);
		if (nextToken->value == "," || nextToken->value == "="){
			Vl();
			readToken("=");
			E();
			buildAST ("=", 2, treeNode::BINDING);
		} else {
			int n = 0;
			do {
				Vb();
				n++;
			}while (nextToken->value == "(" || nextToken->type == TOK_IDENTIFIER);
			readToken("=");
			E();
			buildAST("function_form", n+2, treeNode::FCN_FORM); 
		}
	}
}

/*    Vb   -> ’<IDENTIFIER>’
           -> ’(’ Vl ’)’
           -> ’(’ ’)’                                 => ’()’;
*/
void parser::Vb(){
	if(nextToken->type == TOK_IDENTIFIER){
		buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
		readToken(nextToken->value);
	}else if (nextToken->value == "("){
		readToken("(");
		if (nextToken->value == ")"){
			readToken(")");
			buildAST("()", 0, treeNode::PARANTHESES);
		} else if (nextToken->type == TOK_IDENTIFIER){
			buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
			readToken(nextToken->value);
			Vl();
			readToken(")");
		}
	}
}

//    Vl   -> ’<IDENTIFIER>’ list ’,’                 => ’,’?;
void parser::Vl(){
	int n = 0;
	while (nextToken->value == ","){
		readToken(",");
		if (nextToken->type == TOK_IDENTIFIER){
			buildAST(nextToken->value, 0, treeNode::IDENTIFIER);
			readToken(nextToken->value);
			n++;
		} else {
			printf ("ERROR In Vl()\n");
		}
	}
	if (n > 0)
		buildAST(",", n+1, treeNode::COMMA);
}
