#include "env.h"

Environment::Environment(int id) {
    this->envId = id;
}

// Function to assign a parent environment to the current environment
void Environment::assignParent(Environment* parent){
    this->parent = parent;
}

// Function to look up a variable in the symbol table of the current environment
Control* Environment::lookup(string str) {
    map<string, Control *>::iterator it;
    it = symTable.find(str);
    if(symTable.end() == it)
        return parent->lookup(str);
    else
        return (*it).second;
}

