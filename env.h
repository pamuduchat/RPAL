#ifndef RPAL_COMPILER_ENVIRONMENT_HEADER
#define RPAL_COMPILER_ENVIRONMENT_HEADER

#include <map>
#include <string>
#include "control.h"

using namespace std;

class Environment {
public:
    int envId;
    Environment *parent;
    void assignParent(Environment* );
    Control* lookup(string);
    Environment(int);
    map<string, Control *> symTable;
};

#endif 