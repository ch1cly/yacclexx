//
//  variables.h
//  lexyacc
//
//  Created by Timur Bikbulatov on 11.12.2021.
//

#ifndef variables_h
#define variables_h

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

Variable *assignVariable(VariableContainerNode *root, char *name, int value);

Variable *createVariable(char *name, int value);

Variable *getVariableFromList(VariableContainerNode *root, char *variableName);

void deleteAllVariables(VariableContainerNode *root);

void showAllVariables(VariableContainerNode *root);

#endif /* variables_h */

