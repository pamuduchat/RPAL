#include "Environment.h"

Environment::Environment(int id) {
    this->id = id;
}

void Environment::assignParent(Environment* parent){
    this->parent = parent;
}

Control* Environment::lookup(string str) {
    map<string, Control *>::iterator it;
    it = symbolTable.find(str);
    if(symbolTable.end() == it)
        return parent->lookup(str);
    else
        return (*it).second;
}


