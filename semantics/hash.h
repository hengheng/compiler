#ifndef     HASH_H
#define     HASH_H

/* definitions of the hash table and hash function */
#define     ST_SIZE     193
#define     TT_SIZE     79

/* symbol table entry */
struct entryInSymbolTable* symbolTable[ST_SIZE];

/* type table entry */
struct entryInTypeTable* typeTable[TT_SIZE];

/* 定义一个函数初始化两个表 */
void initTable();

/* this hash function is called DJB hash function */
unsigned int DJBHashForSymbol(char* str);
unsigned int DJBHashForType(char* str);

/* 在表中插入 */
void insertEntryInSymbolTable(struct entryInSymbolTable* entry);
void insertEntryInTypeTable(struct entryInTypeTable* entry);

/* 在表中查找 */
struct entryInSymbolTable* findInSymbolTable(char* name);
struct entryInTypeTable* findInTypeTable(char* name);
#endif
