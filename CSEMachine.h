#ifndef RPAL_COMPILER_CSEMACHINE_H_
#define RPAL_COMPILER_CSEMACHINE_H_
#include <vector>
#include <stack>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "Environment.h"

using namespace std;

static vector <string> inbuiltFunctions = {
                                            "Order",
                                            "Print",
                                            "Isinteger",
                                            "Istruthvalue",
                                            "Isstring",
                                            "Istuple",
                                            "Isfunction"
                                            "Isdummy",
                                            "Stem",
                                            "Stern",
                                            "Conc",
                                            "Conc2",
                                            "ItoS",
                                            "Null"
                                            };

class CSEMachine {
    void flattenDeltaThen(treeNode*, Control *,vector<Control *> *);
    void flattenDeltaElse(treeNode*, Control *,vector<Control *> *);
    void flattenLAMBDA(treeNode*, Control *,vector<Control *> *);
    void flattenTernary(treeNode*, Control *,vector<Control *> *);
    void flattenTree(treeNode*, Control *,vector<Control *> *);
    void initializaCseMachine(treeNode*);
    void deltaPrint();
    void applyBinaryOperator(int);
    void applyOperator(Control*);
    void printCS();
    bool checkInbuilt(string);
    void escapePrintStr(string);
    void rule11(Control*, Control*, Control*, Environment*, int);
    void rule12(Control*, Control*, Control*, Environment*, int);
    void rule13(Control*, Control*, Control*, Environment*, int);
    void rule10(Control*, Control*, Control*, Environment*, int);
    void handleNeg(Control*, Control*, Control*, Environment*, int);
    void handleEnvironment(Control*, Control*, Control*, Environment*, int);
    void handleTau(Control*, Control*, Control*, Environment*, int);
    void handleBeta(Control*, Control*, Control*, Environment*, int);
    void handleName(Control*, Control*, Control*, Environment*, int);
    void handleGAMMA(Control*, Control*, Control*, Environment*, int);

    treeNode* top;
    vector<Control *> *controlStructures;
    Control *rootDeltaControl;
    int numEnvironment;
    vector<Control *> control;
    stack<Control *> execStack;
    Environment *currentEnvironment;
    Environment *tempEnvironment;
    Environment *PE;
    stack<Environment*> environmentStack;
    map<int, Environment *> environmentMap;
public:
    CSEMachine();
    CSEMachine(treeNode*);
    Environment* primitiveEnv;
    void run(treeNode*);
    Environment* createNewEnvironment();
    void execCSE();
};


#endif 
