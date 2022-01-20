//
//  variables.c
//  lexyacc
//
//  Created by Timur Bikbulatov on 11.12.2021.
//

#include "variables.h"

VariableContainerNode *createVariableContainerNodeList() {
    VariableContainerNode *root = (VariableContainerNode*)malloc(sizeof(VariableContainerNode));
    root->variables = (Variable*)malloc(CONTAINER_SIZE*sizeof(Variable));
    root->currentLength = 0;
    root->next = NULL;
    return root;
}

VariableContainerNode *addNewVariableContainerNode(VariableContainerNode *lastNodeInList) {
    if (lastNodeInList == NULL) {
        return NULL;
    }
    VariableContainerNode *newNode = (VariableContainerNode*)malloc(sizeof(VariableContainerNode));
    newNode->variables = (Variable*)malloc(CONTAINER_SIZE*sizeof(Variable));
    newNode->currentLength = 0;
    newNode->next = NULL;
    lastNodeInList->next = newNode;
    return newNode;
}

VariableContainerNode *getLastVariableContainerNode(VariableContainerNode *root) {
    if (root == NULL) {
        return NULL;
    }
    VariableContainerNode *currentNode = root;
    while(currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

Variable *createVariable(char *name, int value) {
    Variable *newVariable = (Variable*)malloc(sizeof(Variable));
    newVariable->value = value;
    strcpy(newVariable->name, name);
    return newVariable;
}

Variable *getVariableFromList(VariableContainerNode *root, char *name) {
    VariableContainerNode *currentNode = root;
    while (currentNode != NULL) {
        for (int i = 0; i < currentNode->currentLength; i++) {
            Variable *currentVariable = (&currentNode->variables[i]);
            if (strcmp(currentVariable->name, name) == 0) {
                return currentVariable;
            }
        }
        currentNode = currentNode->next;
    }
    return NULL;
}


Variable *assignVariable(VariableContainerNode *root, char *name, int value)
{
    Variable* variable = getVariableFromList(root, name);
    if (variable == NULL) {
        Variable *newVariable = createVariable(name, value);
        VariableContainerNode *lastNode = getLastVariableContainerNode(root);
        if (lastNode->currentLength >= CONTAINER_SIZE) {
            lastNode = addNewVariableContainerNode(lastNode);
        }
        lastNode->variables[lastNode->currentLength] = *newVariable;
        lastNode->currentLength++;
        return newVariable;
    }
    variable->value = value;
    strcpy(variable->name, name);
    return variable;
}


void deleteAllVariables(VariableContainerNode *root){
    VariableContainerNode *temp;
    while(root){
        free(root->variables);
        temp = root;
        root = root->next;
        free(temp);
    }
}

void showAllVariables(VariableContainerNode *root){
    VariableContainerNode *currentNode = root;
    while (currentNode != NULL) {
        printf("%p\n",currentNode);
        printf("volume of VariableContainerNode = %d\n",currentNode->currentLength);
        for (int i = 0; i < currentNode->currentLength; i++) {
            printf("name of var = %s valu of var = %d\n",currentNode->variables[i].name,currentNode->variables[i].value);
            }
        currentNode = currentNode->next;
        }
    
}
    
