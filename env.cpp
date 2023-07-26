#include "env.h"

Environment::Environment(int id) {
    this->envId = id;
}

void Environment::assignParent(Environment* parent){
    this->parent = parent;
}

Control* Environment::lookup(string str) {
    map<string, Control *>::iterator it;
    it = symTable.find(str);
    if(symTable.end() == it)
        return parent->lookup(str);
    else
        return (*it).second;
}


