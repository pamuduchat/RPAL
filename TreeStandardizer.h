#ifndef TREESTANDARDIZER_HEADER
#define TREESTANDARDIZER_HEADER

#include "lexicalanalyzer.h"
#include "treeNode.h"

using namespace std;

class TreeStandardizer {
    void standardize(treeNode*);
    void standardizeLET(treeNode*);
    void standardizeWHERE(treeNode*);
    void standardizeWITHIN(treeNode*);
    void standardizeREC(treeNode*);
    void standardizeFCNFORM(treeNode*);
    void standardizeLAMBDA(treeNode*);
    void standardizeAND(treeNode*);
    void standardizeAT(treeNode*);

public:
    TreeStandardizer(treeNode* topNode);
};

#endif 
