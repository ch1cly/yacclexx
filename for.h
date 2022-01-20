//
//  forStruct.h
//  lexyacc
//
//  Created by Timur Bikbulatov on 27.11.2021.
//

#ifndef forStruct_h
#define forStruct_h

#include <stdio.h>
#include "var.h"
#include "scope.h"

typedef struct For {
    int step;
    Variable * iterator;
    struct For *next;
    int finalValue;
} For;


For *createForStack(void);

For *addNewForInStack(For *lastNodeInList);

For *deleteTopForFromStack(For *root);

void assignIterator(Scope *scope, For *forStruct, char *variableName);

void assignFinalValue(For *forStruct, int finalValue);


#endif /* forStruct_h */
