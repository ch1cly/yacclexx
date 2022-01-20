#include "var.h"

VariableContainerNode *createVariableContainerNodeList(void) {
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
    printf("45---\n,%s\n",newVariable->name);
    return newVariable;
}

Variable *getVariableFromList(VariableContainerNode *root, char *name) {
    VariableContainerNode *currentNode = root;
    while (currentNode != NULL) {
        for (int i = 0; i < currentNode->currentLength; i++) {
            Variable *currentVariable = (&currentNode->variables[i]);
            printf("12---\n");
            printf("45---huew||%s = %d\n",currentVariable->name,currentVariable->value);
            printf("45---\n,%s\n",name);
            printf("121---\n");
            if (strcmp(currentVariable->name, name) == 0) {
                printf("34---\n");
                return currentVariable;
            }
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

void deleteLastVariableNode(VariableContainerNode *root) {
    if (root == NULL) {
        return;
    }
    VariableContainerNode *currentNode = root;
    VariableContainerNode *prevNode = currentNode->next;
    while (currentNode->next != NULL) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    free(currentNode->variables);
    free(currentNode);
    prevNode->next = NULL;
}

void deleteVariableFromList(VariableContainerNode *root,Variable *variable){
    VariableContainerNode *currentNode = root;
    while (currentNode != NULL) {
        for (int i = 0; i < currentNode->currentLength; i++) {
            Variable *currentVariable = &currentNode->variables[i];
            if (currentVariable == variable) {
                VariableContainerNode *lastNode = getLastVariableContainerNode(currentNode);
                
                Variable *lastVariable = &lastNode->variables[lastNode->currentLength];
                if(currentVariable == lastVariable){
                    currentNode->currentLength = currentNode->currentLength - 1;
                } else {
                    currentVariable->value = lastVariable->value;
                    strcpy(currentVariable->name, lastVariable->name);
                    lastNode->currentLength--;
                }
                if (lastNode->currentLength == 0) {
                    deleteLastVariableNode(root);
                }
            }
        }
        currentNode = currentNode->next;
    }
    
}

void deleteVariableContainerList(VariableContainerNode *root) {
    while(root != NULL) {
        free(root->variables);
        VariableContainerNode *next = root->next;
        free(root);
        root = next;
    }
}

Variable *createNewVariableInList(VariableContainerNode *root, char *variableName, int value) {
    Variable *newVariable = createVariable(variableName, value);
    VariableContainerNode *lastNode = getLastVariableContainerNode(root);
    if (lastNode->currentLength >= CONTAINER_SIZE) {
        lastNode = addNewVariableContainerNode(lastNode);
    }
    lastNode->variables[lastNode->currentLength] = *newVariable;
    lastNode->currentLength++;
    return NULL;
}
