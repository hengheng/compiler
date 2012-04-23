#ifndef     TYPE_H
#define     TYPE_H

/* 
 * definitions of the symbol table
 * and the type table 
 *    1.use the symbol table to record the variable and function
 *    2.use the type table to record the type, such as the structure you defined
 */

/* Type类型可以用来表示一个结构体，或者表示函数的参数 
 * Type类型使用链表串起来
 */
typedef struct Type* Type_p;
typedef struct Field* Field_p;

struct Type
{
    int typeId;
    union {
       int t_basic;
       struct {int size;Type_p nextLevel;} t_array;
       Field_p t_structure;  
    }u ; 
    #define     t_basic         u.t_basic
    #define     t_array         u.t_array
    #define     t_structure     u.t_structure
};

/* 使用链表管理复杂数据类型 */
struct Field
{
    char* name;
    Type_p type;
    Field_p tail;       
};

/* */

/* 普通变量定义 */
struct VariableType 
{
    Type_p type;//变量类型
    union value {
        int intValue;
        float floatValue;
    } value;
    
    #define     intValue    value.intValue
    #define     floatValue  value.floatValue
};

struct ArrayType
{
    Type_p type;//数组类型名
    int dimension;
};

/* definition of the function recorded in the symbol table */
struct FuncType
{
    int paramNum;
    Type_p returnType; //返回值类型名
    Type_p paramType;  //参数类型
    int funcState;      //defined or declared
};
#define     DEFINED         127
#define     DECLARED        128


/* 定义symbol */
struct Symbol
{
    int typeId;
    char* name;
    union {
        struct VariableType s_var;
        struct ArrayType  s_array;
        struct FuncType s_func;
        struct Field s_field;
    } element;
    #define         s_func            element.s_func
    #define         s_var             element.s_var
    #define         s_array           element.s_array
    #define         s_field           element.s_field
};


/* definetion of the entry in the symbol table */
struct entryInSymbolTable
{
    struct Symbol symbol;
    struct entryInSymbolTable* nextEntry;
    struct entryInSymbolTable* nextEntryInTheSameDomain;      
};

/* you can assign "typeId" with the values below */
/* INT and FLOAT has been defined in syntax.tab.h */
#define     COMMON      2
#define     STRUCT      3
#define     ARRAY       4
#define     FUNCTION    5
#define     BASIC       6

/* define the entry in the type table */
struct entryInTypeTable
{
    struct Field field;
    struct entryInTypeTable* nextEntry;
    struct entryInTypeTable* nextEntryInTheSameDomain;
};

#endif
