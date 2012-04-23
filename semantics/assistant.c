#include <stdlib.h>
#include <time.h>
#include "allheader.h"
#include <string.h>

char* randGenString()
{
    int position = 0;
    char* string = (char*)malloc(8);
    
    srand((unsigned)time(0));
    for(position = 0;position < 8;position++)
    {
        string[position] = (rand() % 26) + 0x61;
    }
    return string;
}

void nameCopy(char** dst,char* src)
{
    *dst = (char*)malloc(strlen(src) + 1);
    strcpy(*dst,src);
}

void p_printType(struct Type* type)
{
    if(type->typeId == BASIC)
    {
        if(type->t_basic == INT)
            printf("int\n");
        else if(type->t_basic == FLOAT)
            printf("float\n");
    }
    else if(type->typeId == ARRAY)
    {
        struct Type* tempType = type; 
        while(tempType != 0 && tempType->typeId == ARRAY)
        {
            printf("%d\n",tempType->t_array.size);
            tempType = tempType->t_array.nextLevel;
        }
    }
}

void printType(struct entryInSymbolTable* entry)
{
    if(entry->symbol.typeId == BASIC)
        p_printType(entry->symbol.s_var.type);
    else if(entry->symbol.typeId == ARRAY)
        p_printType(entry->symbol.s_array.type);
    else if(entry->symbol.typeId == FUNCTION)
    {
        p_printType(entry->symbol.s_func.returnType);
        //printf("\n");
        //p_printType(entry->symbol.s_func.paramType);
    }
}

void traverseTable()
{
    int i = 0;
    for(i = 0;i < ST_SIZE;i++)
    {
        struct entryInSymbolTable* entry = symbolTable[i];
        while(entry != 0)
        {
            if(entry->symbol.typeId == ARRAY)
            {
                printf("ARRAY : ");
                printType(entry);
            }
            if(entry->symbol.typeId == BASIC)
            {
                printf("BASIC : ");
                printType(entry);
            }
            if(entry->symbol.typeId == FUNCTION)
            {
                printf("Function : ");
                printType(entry);
            }
            printf("name :  %s\n",entry->symbol.name);
            entry = entry->nextEntry;
        }
    }
}

