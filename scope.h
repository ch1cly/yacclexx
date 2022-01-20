//
//  scope.h
//  lexyacc
//
//  Created by Timur Bikbulatov on 27.11.2021.
//

#ifndef scope_h
#define scope_h

#include <stdio.h>
#include "var.h"

typedef struct Scope {
    VariableContainerNode variableContainerList;
    struct Scope *next;
} Scope;


Scope *createScopeStack(void);

Scope *addNewScope(Scope *root);

Scope *deleteTopScope(Scope *root);

Variable *assignVariable(Scope *root, char *name, int value);

#endif /* scope_h */
