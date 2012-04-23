#ifndef STACK_H
#define STACK_H

#include "mytype.h"
/* definition of the stack */

#define     STACK_SIZE      20

struct entryInStack
{
    char* domainName;
    struct entryInSymbolTable* esPointer;
    struct entryInTypeTable* etPointer;
};

/* stack and top pointer */
struct entryInStack stack[STACK_SIZE];
struct entryInStack* current;

void popStack();
void pushStack(char* domainName);
struct entryInStack* getEntryInStack(int pos);

#endif
