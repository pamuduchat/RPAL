#include "CSEMachine.h"

CSEMachine::CSEMachine(treeNode* topNode) {
    this->top = topNode;
}

CSEMachine::CSEMachine(){
    numEnvironment = -1;
    primitiveEnv = createNewEnvironment();
    environmentStack.push(primitiveEnv);
    controlStructures = new vector<Control *>;
    rootDeltaControl = new Control(Control::DELTA, controlStructures->size());
}

bool CSEMachine::checkInbuilt(string func) {
    if (std::find(inbuiltFunctions.begin(), inbuiltFunctions.end(), func) != inbuiltFunctions.end()){
        return true;
    } else {
        return false;
    }
}
void CSEMachine::executeBinaryOperation(int type){
    control.pop_back();
    Control *rand1 = execStack.top() ;
    execStack.pop();
    Control *rand2 = execStack.top() ;
    execStack.pop();
    Control *result = new Control() ;
    result->type = Control::INTEGER;
    switch(type)
      {
      case Control::AUG :
    result->type = Control::TUPLE;
    result->ctrlTuples;
    if( rand1->type != Control::NIL ){
      if( rand1->type == Control::TUPLE){
        for(int i=0;i<rand1->ctrlTuples.size(); i++)
          result->ctrlTuples.push_back(rand1->ctrlTuples.at(i));
      }
      else{
        result->ctrlTuples.push_back(rand1) ;
      }
    }
    if( rand2->type != Control::NIL ){
      if( rand2->type == Control::TUPLE){
        for(int i=0;i<rand2->ctrlTuples.size(); i++)
          result->ctrlTuples.push_back(rand2->ctrlTuples.at(i));
      }
      else
        result->ctrlTuples.push_back(rand2);
    }
    break ;
      case Control::EXP :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER) {
        result->ctrlVal = to_string(pow(atoi(rand1->ctrlVal.c_str()), atoi(rand2->ctrlVal.c_str())));
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::GR :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER){
      if( atoi(rand1->ctrlVal.c_str()) > atoi(rand2->ctrlVal.c_str()) )
        result->type = Control::TRUE;
      else
        result->type = Control::FALSE;
      break ;
    }
    else{
      exit(1) ;
    }
    break ;
      case Control::GE :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER) {
        if( atoi(rand1->ctrlVal.c_str()) >= atoi(rand2->ctrlVal.c_str()) )
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::LS :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER) {
        if( atoi(rand1->ctrlVal.c_str()) < atoi(rand2->ctrlVal.c_str()) )
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::LE :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER) {
        if( atoi(rand1->ctrlVal.c_str()) <= atoi(rand2->ctrlVal.c_str()) )
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::EQ :
    if( rand1->type == Control::STRING && rand2->type == Control::STRING) {
        if( rand1->ctrlVal.compare(rand2->ctrlVal) == 0)
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
                }
    else if( rand1->type == Control::INTEGER && rand2->type == Control::INTEGER )  {
        if( rand1->ctrlVal == rand2->ctrlVal )
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
      }
    else if((rand1->type == Control::TRUE || rand1->type == Control::FALSE) && (rand1->type == Control::TRUE || rand2->type == Control::FALSE)){
        result->type = rand1->type == rand2->type?Control::TRUE: Control::FALSE;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::NE :
    if( rand1->type == Control::STRING && rand2->type == Control::STRING ) {
        if( rand1->ctrlVal.compare(rand2->ctrlVal) != 0)
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
                }
    else if( rand1->type == Control::INTEGER && rand2->type == Control::INTEGER ) {
        if( rand1->ctrlVal != rand2->ctrlVal)
          result->type = Control::TRUE;
        else
          result->type = Control::FALSE;
      }
    else if((rand1->type == Control::TRUE || rand1->type == Control::FALSE) && (rand1->type == Control::TRUE || rand2->type == Control::FALSE)){
        result->type = rand1->type != rand2->type?Control::TRUE: Control::FALSE;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::OR :
    if( (rand1->type == Control::TRUE || rand1->type == Control::FALSE ) &&
        (rand2->type == Control::TRUE || rand2->type == Control::FALSE) ) {
        bool op1 = (rand1->type == Control::TRUE )? true : false ;
        bool op2 = ( rand2->type == Control::TRUE )? true : false ;
        bool res = op1 | op2 ;
        result->type =res? Control::TRUE : Control::FALSE;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::AND_LOGICAL :
    if( (rand1->type == Control::TRUE || rand1->type == Control::FALSE ) &&
        (rand2->type == Control::TRUE || rand2->type == Control::FALSE) ) {
        bool op1 = (rand1->type == Control::TRUE)?true:false;
        bool op2 = (rand2->type == Control::TRUE)?true:false;
        bool res = op1 & op2;
        result->type = res? Control::TRUE : Control::FALSE;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::ADD :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER){
        result->ctrlVal = to_string(atoi(rand1->ctrlVal.c_str()) + atoi(rand2->ctrlVal.c_str()));
        break ;
      }
    else{

        exit(1) ;
      }
    break ;

      case Control::SUBTRACT :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER){
        result->ctrlVal = to_string(atoi(rand1->ctrlVal.c_str()) - atoi(rand2->ctrlVal.c_str()));
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
      case Control::MULTIPLY :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER){
        result->ctrlVal = to_string(atoi(rand1->ctrlVal.c_str()) * atoi(rand2->ctrlVal.c_str()));
        break ;
      }
    else{
        exit(1) ;
      }
    break ;
      case Control::DIVIDE :
    if(rand1->type == Control::INTEGER && rand2->type == Control::INTEGER) {
        result->ctrlVal = to_string(atoi(rand1->ctrlVal.c_str()) / atoi(rand2->ctrlVal.c_str()));
        break ;
      }
    else {
        exit(1) ;
      }
    break ;
    }
    execStack.push(result) ;

}



void CSEMachine::escapePrintStr(string string){
  for( int i = 0 ; i < string.length() ; i++ ){
  char character1 = string.at(i) ;
    if( character1 == '\\'){
      i++ ;
      if( i < string.length() ){
        char character2 = string.at(i) ;
        if( character2 == 'n' )
      cout << endl;
        else if( character2 == 't' )
      cout << "\t" ;
        else
      cout <<  character1 << character2 ;
      }
    }
    else
      cout << character1 ;
    }
    cout.flush();
}

void CSEMachine::executeOperator(Control* rator) {
    Control* temp;
    Control* toPush = nullptr;

    // Helper function to create a new boolean Control with the given value
    auto createBoolControl = [](bool value) -> Control* {
        Control* boolControl = new Control();
        boolControl->type = value ? Control::TRUE : Control::FALSE;
        return boolControl;
    };
    if (rator->variables.front() == "Print") {
        string print_str = execStack.top()->toStr();
        escapePrintStr(print_str);
        execStack.pop();
        toPush = new Control(Control::DUMMY);
    } else if (rator->variables.front() == "Order") {
        Control* tuple = execStack.top();
        execStack.pop();
        Control* order = new Control();
        order->type = Control::INTEGER;

        if (tuple->type == Control::TUPLE) {
            order->ctrlVal = to_string(tuple->ctrlTuples.size());
        } else if (tuple->type == Control::NIL) {
            order->ctrlVal = to_string(0);
        } else {
            exit(1);
        }
        toPush = order;
    } else if (rator->variables.front() == "Isinteger") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::INTEGER);
    } else if (rator->variables.front() == "Istruthvalue") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::TRUE || temp->type == Control::FALSE);
    } else if (rator->variables.front() == "Isstring") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::STRING);
    } else if (rator->variables.front() == "Istuple") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::TUPLE || temp->type == Control::NIL);
    } else if (rator->variables.front() == "Isfunction") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::LAMBDA);
    } else if (rator->variables.front() == "Isdummy") {
        temp = execStack.top();
        execStack.pop();
        toPush = createBoolControl(temp->type == Control::DUMMY);
    } else if (rator->variables.front() == "Stem") {
        if (execStack.top()->type == Control::STRING) {
            Control* strControl = new Control(Control::STRING);
            strControl->ctrlVal = execStack.top()->ctrlVal.substr(0, 1);
            execStack.pop();
            toPush = strControl;
        } else {
            exit(1);
        }
    } else if (rator->variables.front() == "Stern") {
        if (execStack.top()->type == Control::STRING) {
            Control* strControl = new Control(Control::STRING);
            strControl->ctrlVal = execStack.top()->ctrlVal.substr(1, execStack.top()->ctrlVal.length() - 1);
            execStack.pop();
            toPush = strControl;
        } else {
            exit(1);
        }
    } else if (rator->variables.front() == "ItoS") {
        if (execStack.top()->type == Control::INTEGER) {
            Control* strControl = new Control(Control::STRING);
            strControl->ctrlVal = execStack.top()->ctrlVal;
            execStack.pop();
            toPush = strControl;
        } else {
            exit(1);
        }
    } else if (rator->variables.front() == "Conc") { // Could have check for string here
        Control* concl = new Control(Control::NAME);
        concl->variables.push_back("Conclambda");
        concl->variables.push_back(execStack.top()->ctrlVal);
        execStack.pop();
        toPush = concl;
    } else if (rator->variables.front() == "Conclambda") {
        Control* concatVars = new Control(Control::STRING, rator->variables.at(1) + execStack.top()->ctrlVal);
        execStack.pop();
        toPush = concatVars;
    } else if (rator->variables.front() == "Null") {
        Control* boolR = new Control();
        if (execStack.top()->type == Control::NIL || (execStack.top()->type == Control::TUPLE && execStack.top()->ctrlTuples.empty()))
            boolR->type = Control::TRUE;
        else
            boolR->type = Control::FALSE;
        execStack.pop();
        toPush = boolR;
    } else {
        return;
    }

    execStack.push(toPush);
}


void CSEMachine::handleName(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    if(checkInbuilt(currentControl->variables.front())){
        control.pop_back();
        execStack.push(currentControl) ;
    } else {
        temp = currentEnvironment->lookup(currentControl->variables.front());
        if(temp != NULL){
            control.pop_back();
            execStack.push(temp) ;
        } 
    }
}

void CSEMachine::rule11(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
newEnvironment = createNewEnvironment();
newEnvironment->assignParent(environmentMap[rator->associatedENV]);
currentEnvironment = newEnvironment;

if (rator->variables.size() == 1) {
    // Single variable case
    currentEnvironment->symTable[rator->variables[0]] = execStack.top();
    execStack.pop();
} else {
    // Tuple assignment case
    temp = execStack.top();
    execStack.pop();
    if (temp->type == Control::TUPLE && rator->variables.size() == temp->ctrlTuples.size()) {
        for (int i = 0; i < rator->variables.size(); i++) {
            currentEnvironment->symTable[rator->variables[i]] = temp->ctrlTuples[i];
        }
    } else {
        exit(1); // Error: Incompatible tuple assignment
    }
}

environmentStack.push(currentEnvironment);
// Push a new Control node representing the environment onto the control stack and execStack
control.push_back(new Control(Control::ENV, currentEnvironment->envId, false));
execStack.push(new Control(Control::ENV, currentEnvironment->envId, false));

// Push the control structures of the rator's index onto the control stack
for (int i = 0; i < controlStructures->at(rator->index)->ctrlStruct->size(); i++) {
    control.push_back(controlStructures->at(rator->index)->ctrlStruct->at(i));
}

}

void CSEMachine::rule12(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    Control *eta = new Control(execStack.top()) ;
    execStack.pop();
    eta->type = Control::ETA;
    execStack.push(eta);
}

void CSEMachine::rule13(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    control.push_back(new Control(Control::GAMMA));
    control.push_back(new Control(Control::GAMMA));
    execStack.push(rator);
    Control *lambda = new Control(Control::LAMBDA, &(rator->variables), NULL, rator->index) ;
    lambda->associatedENV = rator->associatedENV;
    execStack.push(lambda);
}
void CSEMachine::rule10(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    if (execStack.top()->type == Control::INTEGER) {
    int index = atoi(execStack.top()->ctrlVal.c_str()) - 1;
    execStack.pop();

    if (index >= 0 && index < rator->ctrlTuples.size()) {
        temp = rator->ctrlTuples[index];
        execStack.push(temp);
    } else {
        exit(1); // Error: Index out of range
    }
} else {
    exit(1); // Error: Operand is not an INTEGER
}

}
void CSEMachine::handleGAMMA(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    control.pop_back();
rator = execStack.top();
execStack.pop();

switch (rator->type) {
    case Control::LAMBDA:
        rule11(temp, currentControl, rator, newEnvironment, deltaIndex);
        break;
    case Control::YSTAR:
        rule12(temp, currentControl, rator, newEnvironment, deltaIndex);
        break;
    case Control::ETA:
        rule13(temp, currentControl, rator, newEnvironment, deltaIndex);
        break;
    case Control::TUPLE:
        rule10(temp, currentControl, rator, newEnvironment, deltaIndex);
        break;
    default:
        executeOperator(rator);
        break;
}

}
void CSEMachine::handleBeta(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    control.pop_back();
    if(execStack.top()->type == Control::TRUE){
        control.pop_back();
        if(control.at(control.size() - 1)->type == Control::DELTA){
            deltaIndex = control.at(control.size() -1)->index;
            control.pop_back();
        }else{
            exit(1);
        }
    }else if(execStack.top()->type == Control::FALSE){
        if(control.at(control.size() - 1)->type == Control::DELTA){
            deltaIndex = control.at(control.size() -1)->index;
            control.pop_back();
            control.pop_back();
        }else{
            exit(1);
        }
    }else{
        exit(1);
    }
    execStack.pop();
    for(int i=0; i< controlStructures->at(deltaIndex)->ctrlStruct->size() ; i++){
        control.push_back(controlStructures->at(deltaIndex)->ctrlStruct->at(i));
    }
}

void CSEMachine::handleEnvironment(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    temp = execStack.top() ;
    execStack.pop();
    if( execStack.top()->type == Control::ENV && execStack.top()->index == currentControl->index ){
        control.pop_back();
        execStack.pop();
        execStack.push(temp) ;
        environmentStack.pop() ;
        currentEnvironment = environmentStack.top() ;
    }else{
        exit(1) ;
    }
}


void CSEMachine::handleTau(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex) {
    control.pop_back();
    temp = new Control();
    temp->type = Control::TUPLE;
    temp->ctrlTuples.clear();

    int i = 0;
    while (i < currentControl->index) {
        temp->ctrlTuples.push_back(execStack.top());
        execStack.pop();
        i++;
    }

    execStack.push(temp);
}

void CSEMachine::handleNeg(Control* temp, Control* currentControl, Control* rator, Environment* newEnvironment, int deltaIndex){
    control.pop_back();
    if(execStack.top()->type == Control::INTEGER )
        execStack.top()->ctrlVal = to_string(-1*atoi(execStack.top()->ctrlVal.c_str()));
    else
    {
        exit(1) ;
    }
}


Environment* CSEMachine::createNewEnvironment(){
    tempEnvironment = new Environment(numEnvironment);
    environmentMap[numEnvironment] =  tempEnvironment;
    numEnvironment++;
    return tempEnvironment;
}
  void CSEMachine::execCSE() {
    Control* temp = nullptr;
    Control* currentControl = nullptr;
    Control* rator = nullptr;
    Environment* newEnvironment = nullptr;
    int deltaIndex = -1;

    while (!control.empty()) {
        currentControl = control.back();
        temp = nullptr;

        if (currentControl->type == Control::INTEGER ||
            currentControl->type == Control::STRING ||
            currentControl->type == Control::TRUE ||
            currentControl->type == Control::FALSE ||
            currentControl->type == Control::DUMMY ||
            currentControl->type == Control::YSTAR) {
            control.pop_back();
            execStack.push(currentControl);
        } else if (currentControl->type == Control::NAME) {
            handleName(temp, currentControl, rator, newEnvironment, deltaIndex);
        } else if (currentControl->type == Control::NIL) {
            currentControl->ctrlTuples.clear();
            control.pop_back();
            execStack.push(currentControl);
        } else if (currentControl->type == Control::LAMBDA) {
            currentControl->associatedENV = currentEnvironment->envId;
            control.pop_back();
            execStack.push(currentControl);
        } else if (currentControl->type == Control::GAMMA) {
            handleGAMMA(temp, currentControl, rator, newEnvironment, deltaIndex);
        } else if (currentControl->type == Control::NOT) {
            control.pop_back();
            temp = execStack.top();
            if (temp->type == Control::TRUE || temp->type == Control::FALSE) {
                temp->type = (temp->type == Control::TRUE) ? Control::FALSE : Control::TRUE;
            } else {
                exit(1);
            }
        } else if (currentControl->type == Control::GR ||
                   currentControl->type == Control::GE ||
                   currentControl->type == Control::LS ||
                   currentControl->type == Control::LE ||
                   currentControl->type == Control::EQ ||
                   currentControl->type == Control::NE ||
                   currentControl->type == Control::AUG ||
                   currentControl->type == Control::OR ||
                   currentControl->type == Control::AND_LOGICAL ||
                   currentControl->type == Control::ADD ||
                   currentControl->type == Control::SUBTRACT ||
                   currentControl->type == Control::MULTIPLY ||
                   currentControl->type == Control::DIVIDE ||
                   currentControl->type == Control::EXP) {
            executeBinaryOperation(currentControl->type);
        } else if (currentControl->type == Control::TAU) {
            handleTau(temp, currentControl, rator, newEnvironment, deltaIndex);
        } else if (currentControl->type == Control::NEG) {
            handleNeg(temp, currentControl, rator, newEnvironment, deltaIndex);
        } else if (currentControl->type == Control::ENV) {
            handleEnvironment(temp, currentControl, rator, newEnvironment, deltaIndex);
        } else if (currentControl->type == Control::BETA) {
            handleBeta(temp, currentControl, rator, newEnvironment, deltaIndex);
        }
    }
}


void CSEMachine::initializaCseMachine(treeNode* rootNode) {
    controlStructures->push_back(rootDeltaControl);
    flatternControlStructure(rootNode, rootDeltaControl, controlStructures);
    control.push_back(new Control(Control::ENV, 0, false));
    execStack.push(new Control(Control::ENV, 0, false));

    size_t i = 0;
    while (i < rootDeltaControl->ctrlStruct->size()) {
        control.push_back(rootDeltaControl->ctrlStruct->at(i));
        i++;
    }

    environmentStack.push(createNewEnvironment());
    environmentStack.top()->assignParent(primitiveEnv);
    currentEnvironment = environmentStack.top();
}

void CSEMachine::run(treeNode *root){
    initializaCseMachine(root);
    execCSE();
    printf ("\n");
}


void CSEMachine::flattenDeltaThen(treeNode* deltaThenNode, Control* deltaControl, vector<Control*>* controlStructures) {
    Control* newDeltaThen = new Control(Control::DELTA, controlStructures->size());
    controlStructures->push_back(newDeltaThen);
    deltaControl->ctrlStruct->push_back(new Control(Control::DELTA, controlStructures->size() - 1));

    if (deltaThenNode->childNode->siblingNode->type == treeNode::TERNARY) {
        flatternControlStructure(deltaThenNode->childNode->siblingNode, newDeltaThen, controlStructures);
    } else {
        vector<string>* tempVariables = NULL;
        if (deltaThenNode->childNode->siblingNode->type == treeNode::TAU) {
            treeNode* tempNode = deltaThenNode->childNode->siblingNode->childNode;
            tempVariables = new vector<string>();
            while (tempNode != NULL) {
                tempVariables->push_back(tempNode->nodeString);
                tempNode = tempNode->siblingNode;
            }
        }
        newDeltaThen->addControl(deltaThenNode->childNode->siblingNode, deltaThenNode->childNode->siblingNode->type, deltaThenNode->childNode->siblingNode->nodeString, tempVariables, newDeltaThen, controlStructures->size());
        
        if (deltaThenNode->childNode->siblingNode->childNode != NULL)
            flatternControlStructure(deltaThenNode->childNode->siblingNode->childNode, newDeltaThen, controlStructures);
    }
}



void CSEMachine::flattenDeltaElse(treeNode* deltaElseNode, Control* deltaControl, vector<Control*>* controlStructures) {
    Control* newDeltaElse = new Control(Control::DELTA, controlStructures->size());
    controlStructures->push_back(newDeltaElse);
    deltaControl->ctrlStruct->push_back(new Control(Control::DELTA, controlStructures->size() - 1));

    if (deltaElseNode->childNode->siblingNode->siblingNode->type == treeNode::TERNARY) {
        flatternControlStructure(deltaElseNode->childNode->siblingNode->siblingNode, newDeltaElse, controlStructures);
    } else {
        vector<string>* tempVariables = NULL;
        if (deltaElseNode->childNode->siblingNode->siblingNode->type == treeNode::TAU) {
            treeNode* tempNode = deltaElseNode->childNode->siblingNode->siblingNode->childNode;
            tempVariables = new vector<string>();
            while (tempNode != NULL) {
                tempVariables->push_back(tempNode->nodeString);
                tempNode = tempNode->siblingNode;
            }
        }
        newDeltaElse->addControl(deltaElseNode->childNode->siblingNode->siblingNode, deltaElseNode->childNode->siblingNode->siblingNode->type, deltaElseNode->childNode->siblingNode->siblingNode->nodeString, tempVariables, newDeltaElse, controlStructures->size());
        
        if (deltaElseNode->childNode->siblingNode->siblingNode->childNode != NULL)
            flatternControlStructure(deltaElseNode->childNode->siblingNode->siblingNode->childNode, newDeltaElse, controlStructures);
    }
}



void CSEMachine::flatternTernaryExpression(treeNode* ternaryNode, Control* deltaControl, vector<Control*>* controlStructures) {
    flattenDeltaThen(ternaryNode, deltaControl, controlStructures);
    flattenDeltaElse(ternaryNode, deltaControl, controlStructures);

    Control* betaControl = new Control(Control::BETA);
    deltaControl->ctrlStruct->push_back(new Control(Control::BETA, "beta"));
    deltaControl->addControl(ternaryNode->childNode, ternaryNode->childNode->type, ternaryNode->childNode->nodeString, NULL, NULL, controlStructures->size());

    if (ternaryNode->childNode->childNode != NULL) {
        flatternControlStructure(ternaryNode->childNode->childNode, deltaControl, controlStructures);
    }
}


void CSEMachine::flatternLambdaExpression(treeNode* lambdaNode, Control* deltaControl, vector<Control*>* controlStructures) {
    Control* tempControl = NULL;
    vector<string>* lambdaVariables = new vector<string>();

    if (treeNode::IDENTIFIER == lambdaNode->childNode->type) {
        lambdaVariables->push_back(lambdaNode->childNode->nodeString);
    } else if (treeNode::COMMA == lambdaNode->childNode->type) {
        for (treeNode* tempNode = lambdaNode->childNode->childNode; tempNode != NULL; tempNode = tempNode->siblingNode) {
            lambdaVariables->push_back(tempNode->nodeString);
        }
    }

    tempControl = new Control(Control::DELTA, controlStructures->size());
    controlStructures->push_back(tempControl);
    deltaControl->addControl(lambdaNode, lambdaNode->type, lambdaNode->nodeString, lambdaVariables, tempControl, controlStructures->size());

    flatternControlStructure(lambdaNode->childNode->siblingNode, tempControl, controlStructures);

    if (NULL != lambdaNode->siblingNode)
        flatternControlStructure(lambdaNode->siblingNode, deltaControl, controlStructures);
}

void CSEMachine::flatternControlStructure(treeNode* currentNode, Control* deltaControl, vector<Control*>* controlStructures) {
    Control* tempControlPtr = NULL;
    vector<string>* variables = NULL;

    // Check if the current node is a LAMBDA expression.
    if (treeNode::LAMBDA == currentNode->type) {
        // Flatten the LAMBDA expression and add it to the control structure.
        flatternLambdaExpression(currentNode, deltaControl, controlStructures);
    }
    // Check if the current node is a TERNARY expression.
    else if (currentNode->type == treeNode::TERNARY) {
        // Flatten the TERNARY expression and add it to the control structure.
        flatternTernaryExpression(currentNode, deltaControl, controlStructures);
    }
    // Handle other types of nodes (e.g., TAU).
    else {
        // Check if the current node is a TAU expression.
        if (currentNode->type == treeNode::TAU) {
            // Initialize the variables vector to store identifiers in the TAU expression.
            variables = new vector<string>();
            treeNode* tempNode = currentNode->childNode;
            // Iterate through child nodes to collect identifiers.
            for (; tempNode != NULL; tempNode = tempNode->siblingNode) {
                variables->push_back(tempNode->nodeString);
            }
        }

        // Add the current node to the delta control and the control structure.
        deltaControl->addControl(currentNode, currentNode->type, currentNode->nodeString, variables, tempControlPtr, controlStructures->size());

        // process the child nodes and sibling nodes.
        if (NULL != currentNode->childNode) {
            flatternControlStructure(currentNode->childNode, deltaControl, controlStructures);
        }
        if (NULL != currentNode->siblingNode) {
            flatternControlStructure(currentNode->siblingNode, deltaControl, controlStructures);
        }
    }
}




