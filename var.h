#ifndef VAR_H
#define VAR_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CONTAINER_SIZE 15
#define MAX_VARIABLE_NAME 30

typedef struct Variable {
    char name[MAX_VARIABLE_NAME];
    int value;
} Variable;

typedef struct VariableContainerNode {
    Variable *variables;
    int currentLength;
    struct VariableContainerNode *next;
} VariableContainerNode;

VariableContainerNode *createVariableContainerNodeList(void);

VariableContainerNode *addNewVariableContainerNode(VariableContainerNode *lastNodeInList);

VariableContainerNode *getLastVariableContainerNode(VariableContainerNode *root);

Variable *createVariable(char *name, int value);

Variable *getVariableFromList(VariableContainerNode *root, char *variableName);

void deleteVariableFromList(VariableContainerNode *root,Variable *variable);

void deleteVariableContainerList(VariableContainerNode *root);

Variable *createNewVariableInList(VariableContainerNode *root, char *variableName, int value);


#endif // VAR_H
