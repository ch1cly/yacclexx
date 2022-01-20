//
//  scope.c
//  lexyacc
//
//  Created by Timur Bikbulatov on 27.11.2021.
//

#include "scope.h"

Scope *createScopeStack(void){
    Scope *root = (Scope*)malloc(sizeof(Scope));
    root->next = NULL;
    return root;
}

Scope *addNewScope(Scope *root){
    if (root == NULL) {
        return createScopeStack();
    }
    Scope *newNode = (Scope*)malloc(sizeof(Scope));
    newNode->next = root;
    
    return newNode;
}

Variable *assignVariable(Scope *root, char *name, int value) {
    Scope *currentScope = root;
    while (currentScope!=NULL) {
        Variable* variable = getVariableFromList(&currentScope->variableContainerList, name);
        
        if (variable != NULL) {
            variable->value = value;
            strcpy(variable->name, name);
            return variable;
        }
        currentScope = currentScope->next;
    }
    return createNewVariableInList(&root->variableContainerList, name, value);
}

Scope *deleteTopScope(Scope *root){
    Scope *temp = root;
    root = temp->next;
    
    deleteVariableContainerList(&temp->variableContainerList);
    free(temp);
    return root;
}

