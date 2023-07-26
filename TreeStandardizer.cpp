#include "TreeStandardizer.h"

TreeStandardizer::TreeStandardizer(treeNode* topNode) {
    standardize(topNode);
}

void TreeStandardizer::standardizeLET(treeNode* topNode){
    treeNode* p;
    topNode->type = treeNode::GAMMA;
    topNode->nodeString = "gamma";
    topNode->childNode->type = treeNode::LAMBDA;
    topNode->childNode->nodeString = "lambda";
    p = topNode->childNode->siblingNode;
    topNode->childNode->siblingNode = topNode->childNode->childNode->siblingNode;
    topNode->childNode->childNode->siblingNode = p;

}

void TreeStandardizer::standardizeWHERE(treeNode* topNode){
    treeNode* p, *x, *e;
    topNode->type = treeNode::GAMMA;
    topNode->nodeString = "gamma";
    p = topNode->childNode;
    e = topNode->childNode->siblingNode->childNode->siblingNode;
    x = topNode->childNode->siblingNode->childNode;
    x->siblingNode = NULL;
    p->siblingNode = NULL;
    topNode->childNode = new treeNode();
    topNode->childNode->type = treeNode::LAMBDA;
    topNode->childNode->nodeString = "lambda";
    topNode->childNode->siblingNode = e;
    topNode->childNode->childNode = x;
    x->siblingNode = p;
}

void TreeStandardizer::standardizeWITHIN(treeNode* topNode){
    treeNode *x1, *x2, *e1;
    topNode->type = treeNode::BINDING;
    x1 = topNode->childNode->childNode;
    x2 = topNode->childNode->siblingNode->childNode;
    e1 = x1->siblingNode;
    x1->siblingNode = x2->siblingNode;
    x2->siblingNode = new treeNode();
    x2->siblingNode->type = treeNode::GAMMA;
    x2->siblingNode->nodeString = "gamma";
    x2->siblingNode->childNode = new treeNode();
    x2->siblingNode->childNode->type = treeNode::LAMBDA;
    x2->siblingNode->childNode->nodeString = "lambda";
    x2->siblingNode->childNode->siblingNode = e1; 
    x2->siblingNode->childNode->childNode = x1; 
    topNode->childNode = x2;

}

void TreeStandardizer::standardizeREC(treeNode* topNode){
    treeNode *x, *e, *tempNode;
    topNode->type = treeNode::BINDING;
    x = topNode->childNode->childNode;
    e = topNode->childNode->childNode->siblingNode;
    x->siblingNode = NULL;
    topNode->childNode = x; 
    tempNode = new treeNode();
    tempNode->type = treeNode::GAMMA;
    tempNode->nodeString = "gamma";
    x->siblingNode = tempNode;
    tempNode->childNode = new treeNode();
    tempNode->childNode->type = treeNode::YSTAR;
    tempNode->childNode->nodeString = "<Y*>";
    tempNode->childNode->siblingNode = new treeNode();
    tempNode->childNode->siblingNode->type = treeNode::LAMBDA;
    tempNode->childNode->siblingNode->nodeString = "lambda";
    tempNode->childNode->siblingNode->childNode = new treeNode();
    tempNode->childNode->siblingNode->childNode->type = x->type;
    tempNode->childNode->siblingNode->childNode->nodeString = x->nodeString;
    tempNode->childNode->siblingNode->childNode->siblingNode = e;
}

void TreeStandardizer::standardizeFCNFORM(treeNode* topNode){
    treeNode *tempNode, *newNode;
    topNode->type = treeNode::BINDING;
    topNode->nodeString = "=";
    tempNode = topNode->childNode;
    while (tempNode->siblingNode->siblingNode != NULL){
        newNode = new treeNode();
        newNode->type = treeNode::LAMBDA;
        newNode->nodeString = "lambda";
        newNode->childNode = tempNode->siblingNode;
        tempNode->siblingNode = newNode;
        tempNode = newNode->childNode;
    }
}

void TreeStandardizer::standardizeLAMBDA(treeNode* topNode){
    treeNode *tempNode, *newNode;
    tempNode = topNode->childNode;
    while (tempNode->siblingNode->siblingNode != NULL){
        newNode = new treeNode();
        newNode->type = treeNode::LAMBDA;
        newNode->nodeString = "lambda";
        newNode->childNode = tempNode->siblingNode;
        tempNode->siblingNode = newNode;
        tempNode = tempNode->siblingNode;
    }
}

void TreeStandardizer::standardizeAND(treeNode* topNode){
    treeNode* tempNode;
    treeNode* tauNode, *commaNode, **currTauChild, **currCommaChild;
    topNode->type = treeNode::BINDING;
    topNode->nodeString = "=";
    tempNode = topNode->childNode;
    tauNode = new treeNode();
    commaNode = new treeNode();
    tauNode->type = treeNode::TAU;
    tauNode->nodeString = "tau";
    tauNode->childNode = NULL;
    tauNode->siblingNode = NULL;
    commaNode->type = treeNode::COMMA;
    commaNode->nodeString = ",";
    commaNode->childNode = NULL;
    commaNode->siblingNode = NULL;
    topNode->childNode = commaNode;
    topNode->childNode->siblingNode = tauNode;
    currTauChild = &(tauNode->childNode);
    currCommaChild = &(commaNode->childNode);
    while (tempNode != NULL){
        *currTauChild = tempNode->childNode->siblingNode;
        tempNode->childNode->siblingNode = NULL;
        *currCommaChild = tempNode->childNode;
        tempNode = tempNode->siblingNode;
        currCommaChild = &((*currCommaChild)->siblingNode); 
        currTauChild = &((*currTauChild)->siblingNode);
    }

}

void TreeStandardizer::standardizeAT(treeNode* topNode){
    treeNode* E1, *N, *E2;
    E1 = topNode->childNode;
    N = E1->siblingNode;
    E2 = N->siblingNode;
    topNode->type = treeNode::GAMMA;
    topNode->nodeString = "gamma";
    topNode->childNode = new treeNode();
    topNode->childNode->type = treeNode::GAMMA;
    topNode->childNode->nodeString = "gamma";
    topNode->childNode->siblingNode = E2;
    topNode->childNode->childNode = N;
    N->siblingNode = NULL;
    topNode->childNode->childNode->siblingNode = E1;
    E1->siblingNode = NULL;

}

void TreeStandardizer::standardize(treeNode* topNode){
    treeNode *p, *e, *e1, *e2, *x, *x1, *x2, *n, *tempNode;
    string original = topNode->nodeString;
    if (topNode->childNode != NULL)
        standardize(topNode->childNode);
    if (topNode->siblingNode != NULL)
        standardize (topNode->siblingNode);

    switch(topNode->type){
    case treeNode::LET:
        standardizeLET(topNode);
        break;
    case treeNode::WHERE:
        standardizeWHERE(topNode);
        break;
    case treeNode::WITHIN:{
        standardizeWITHIN(topNode);
        break;
    }
    case treeNode::REC:{
        standardizeREC(topNode);
        break;
    }
    case treeNode::FCN_FORM:{
        standardizeFCNFORM(topNode);
        break;
    }
    case treeNode::LAMBDA:
        standardizeLAMBDA(topNode);
        break;
    case treeNode::AND:
        standardizeAND(topNode);
        break;
    case treeNode::AT:
        standardizeAT(topNode);
        break;
    }
}
