#ifndef     ASSISTANT_H
#define     ASSISTANT_H

/* 此函数作为辅助函数，随机产生一个字符串 */
char* randGenString();
void nameCopy(char** dst,char* src);

/* 下面函数使用来测试的 */
void printType(struct entryInSymbolTable* entry);
void traverseTable();

#define         INT         258
#define         FLOAT       259

/* 定义出错信息 */
#define     UNDEFINED_VAR               1   //变量未定义
#define     UNDEFINED_FUNC              2   //函数未定义
#define     MULTI_DEFINED_VAR           3   //变量重复定义
#define     MULTI_DEFINED_FUNC          4   //函数重复定义
#define     ASSIGN_UNMATCH              5   //赋值号两边表达式不匹配
#define     ASSIGN_ERROR                6   //赋值号左边出现右值
#define     OPERTOR_UNMATCH             7   //操作数不匹配
#define     RETURN_VALUE_UNMATCH        8   //函数返回类型不匹配
#define     PARAMETER_UNMATCH           9   //函数参数不匹配  
#define     NOT_ARRAY                   10  //对非数组使用数组成员访问符
#define     NOT_FUNC                    11  //对非函数成员使用函数调用符
#define     ARRAY_ACCESS_ERROR          12  //数组访问符中出现非整数
#define     NOT_STRUCT                  13  //对非结构体使用DOT符号
#define     UNDEFINED_IN_STRUCT         14  //结构体中的域未定义
#define     MULTI_DEFINED_IN_STRUCT     15  //结构体中的域重复定义
#define     MULTI_DEFINED_STRUCT        16  //结构体重复定义
#define     UNDEFINED_STRUCT            17  //结构体未定义

#define     UNDEFINED_VAR_INFO              "Variable is not defined!"
#define     UNDEFINED_FUNC_INFO             "Function is not defines!"
#define     MULTI_DEFINED_VAR_INFO          "Multi-defined variable!"
#define     MULTI_DEFINED_FUNC_INFO         "Multi-defined function!"
#define     ASSIGN_UNMATCH_INFO             "Exps around '=' are unmatched!"
#define     ASSIGN_ERROR_INFO               "Assigning value failed!"
#define     OPERTOR_UNMATCH_INFO            "Parameters around operator are unmatched!"
#define     RETURN_VALUE_UNMATCH_INFO       "Returning value failed!"
#define     PARAMETER_UNMATCH_INFO          "Parameters can't match the function!" 
#define     NOT_ARRAY_INFO                  "This is not an array!"
#define     NOT_FUNC_INFO                   "This is not a function!"
#define     ARRAY_ACCESS_ERROR_INFO         "You must put an int in '[' and ']'!"
#define     NOT_STRUCT_INFO                 "This is not a struct!"
#define     UNDEFINED_IN_STRUCT_INFO        "This element is undefined in the struct!"
#define     MULTI_DEFINED_IN_STRUCT_INFO    "Multi-defined variable in struct!"
#define     MULTI_DEFINED_STRUCT_INFO       "Multi-defined struct!"
#define     UNDEFINED_STRUCT_INFO           "Undefined struct!"

#define     genError(type,lineno,explanation) \
            printf("Error type [%d] at line [%d] lineno : [%s]\n",type,lineno,explanation)
            
#define     malloc_symbol_entry()       ((struct entryInSymbolTable*)malloc(sizeof(struct entryInSymbolTable)))
#define     malloc_type_entry()         ((struct entryInTypeTable*)malloc(sizeof(struct entryInTypeTable)))
#define     malloc_field()              ((struct Field*)malloc(sizeof(struct Field)))
#define     malloc_type()               ((struct Type*)malloc(sizeof(struct Type)))

#define     equal(str1,str2)            (0 == strcmp((str1),(str2)))

#endif
