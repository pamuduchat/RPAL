#ifndef RPAL_COMPILER_ENVIRONMENT_HEADER
#define RPAL_COMPILER_ENVIRONMENT_HEADER

#include <map>
#include <string>
#include "Control.h"

using namespace std;

class Environment {
public:
    int id;
    Environment *parent;
    void assignParent(Environment* );
    Control* lookup(string);
    Environment(int);
    map<string, Control *> symbolTable;
};

#endif 