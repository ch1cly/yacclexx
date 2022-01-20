//
//  for.c
//  lexyacc
//
//  Created by Timur Bikbulatov on 27.11.2021.
//

#include "for.h"

For *createForStack(void){
    For *root = (For*)malloc(sizeof(For));
    root->iterator = (Variable*)malloc(sizeof(Variable));
    root->finalValue = 0;
    root->step = 1;
    root->next = NULL;
    return root;
}

For *addNewForInStack(For *root) {
    if (root == NULL) {
        return createForStack();
    }
    For *forStruct = (For*)malloc(sizeof(For));
    forStruct->iterator = NULL;
    forStruct->step = 1;
    forStruct->next = root;
    
    return forStruct;
}


For *deleteTopForFromStack(For *root) {
    For *temp = root;
    root = temp->next;
    free(temp);
    return root;
}

void assignIterator(Scope *scope, For *forStruct, char *variableName) {
    Variable *variable = getVariableFromList(&scope->variableContainerList, variableName);
    forStruct->iterator = variable;
}


void assignFinalValue(For *forStruct, int finalValue) {
    forStruct->finalValue = finalValue;
}
