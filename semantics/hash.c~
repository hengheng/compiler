/* the implementation of the hash function */

#include "allheader.h"
#include <string.h>


void initTable()
{
    int i = 0;
    for(i = 0;i < ST_SIZE;i++)
    {
        symbolTable[i] = (void*)0;
    }
}

/* hash function for symbol */
unsigned int DJBHashForSymbol(char* str)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for(i = 0; i < ST_SIZE; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }
   
   return hash % ST_SIZE;
}

/* hash function for type */
unsigned int DJBHashForType(char* str)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for(i = 0; i < TT_SIZE; str++, i++)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

void insertEntryInSymbolTable(struct entryInSymbolTable* entry)
{
    unsigned int hashPos = DJBHashForSymbol(entry->symbol.name);
    entry->nextEntry = symbolTable[hashPos];
    symbolTable[hashPos] = entry;
    entry->nextEntryInTheSameDomain = current->esPointer;
    current->esPointer = entry;
}

/*
void insertEntryInTypeTable(struct entryInTypeTable* entry)
{
    unsigned int hashPos = DJBHashForType(entry->field.name);
    entry->nextEntry = typeTable[hashPos];
    typeTable[hashPos] = entry;
    entry->nextEntryInTheSameDomain = current->etPointer;
    current->etPointer = entry;
}*/

struct entryInSymbolTable* findInSymbolTable(char* name)
{
    unsigned int hashPos = DJBHashForSymbol(name);
    struct entryInSymbolTable* target = symbolTable[hashPos];
    
    /*while(target != (void*)0)
    {
        //if(equal(name,target->symbol.name))
           // return target;
        target = target->nextEntry;
    }*/
    return target;
}

/*
struct entryInTypeTable* findInTypeTable(char* name)
{
    unsigned int hashPos = DJBHashForType(name);
    struct entryInTypeTable* target =  typeTable[hashPos];

    while(target != 0)
    {
        if(0 == strcmp(name,target->field.name))
            return target;
    }
    return target;

}*/
