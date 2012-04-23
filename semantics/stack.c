#include "allheader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 定义栈顶 */
static int stackTop = 0;
void popStack()
{
    if(stackTop != 0)
    { 
        /* 循环删除当前作用域内的符号以及定义的类型 */   
        struct entryInSymbolTable* esPointer = current->esPointer;
        struct entryInTypeTable* etPointer = current->etPointer;
        while(esPointer != 0)
        {
            unsigned int hashPos = DJBHashForSymbol(esPointer->symbol.name);
            symbolTable[hashPos] = esPointer->nextEntry;
            current->esPointer = esPointer->nextEntryInTheSameDomain;
            esPointer = current->esPointer;
        }
        while(etPointer != 0)
        {
            unsigned int hashPos = DJBHashForType(etPointer->field.name);
            typeTable[hashPos] = etPointer->nextEntry;
            current->etPointer = etPointer->nextEntryInTheSameDomain;
            etPointer = current->etPointer;
        }
        stackTop--;
        current = &stack[stackTop-1];
    }
       
}

void pushStack(char* domainName)
{
    if(stackTop == STACK_SIZE)
    {
        printf("Stack is overflow !!!\n");
        return;
    }
    stack[stackTop].domainName = (char*)malloc(strlen(domainName) + 1);
    strcpy(stack[stackTop].domainName,domainName);
    current = &stack[stackTop];
    current->esPointer = 0;
    current->etPointer = 0;
    stackTop++;
}

struct entryInStack* getEntryInStack(int pos)
{
    if(pos <= stackTop && pos > 0){
        return &stack[pos-1];
    }
    else return (void*)0;
}
