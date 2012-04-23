#include "all.h"
#include "semantics/allheader.h"

/*** 已完成函数 ***/
void doWhenProgram()
{
    /* 建立一个全局作用域并入栈*/
    pushStack("MainDomain");  
}

/*** 已完成函数 ***/
void doWhenCompSt()
{
    /* 重新建立作用域并入栈 */
    pushStack("NewDomain");
}

/* 返回一个此结构对应的名字，此函数将会把新结构自动插入到符号表 */
char* doWhenStructSpecifier(treeNode* StructSpecifier)
{
    char* name;
    treeNode* tag = StructSpecifier->firstChild->sibling; //Tag or OptTag
    treeNode* tagName = tag->firstChild; //tag ID
    
    if(tagName != 0)
        nameCopy(&name,tagName->string_content);
    else nameCopy(&name,randGenString());

    treeNode* lc = tag->sibling;
    if(lc == 0) // 表明StructSpecifier -> struct tag
    {
        struct entryInSymbolTable* temp = findInSymbolTable(name);
        if(temp == 0)
        {
            genError(UNDEFINED_STRUCT,StructSpecifier->lineno,UNDEFINED_STRUCT_INFO);      
        }
    }
    else if(lc != 0)    //产生式为StructSpecifier->STRUCT OptTag LC DefList RC
    {
        struct entryInSymbolTable* entry = malloc_symbol_entry();
        /* 以后完成接下来的任务 */
    }
    return name;
    
}

char* doWhenSpecifier(treeNode* Specifier)
{
    char* typeName;
    treeNode* childSpecifier = Specifier->firstChild;
    
    if(childSpecifier->type == TYPE)
    {
        if(equal("int",childSpecifier->string_content))
            nameCopy(&typeName,"int");
        else 
            nameCopy(&typeName,"float");           
    }
    else if(equal("StructSpecifier",childSpecifier->string_content))//处理结构体类型，将结构体类型插入符号表，并且返回结构体名 
    {
        typeName = doWhenStructSpecifier(childSpecifier);
    }
    return typeName;
}



/* 函数已完成 */
struct Field* doWhenVarDec(treeNode* VarDec)
{
    struct Type* record = 0;
    struct Type* type = 0;
    struct Field* field = 0;
    treeNode* temp = VarDec->firstChild;
    while(temp != 0)
    {
        if(temp->sibling != 0 && temp->sibling->type == LB)
        {
            type = malloc_type();
            if(temp->sibling->sibling != 0)
            {
                type->t_array.size = temp->sibling->sibling->int_content;              
            }
            type->t_array.nextLevel = record; //暂时不知道该数组是什么类型
            type->typeId = ARRAY;
            record = type;
        }
        else if(temp->type == ID)
        {
            field = malloc_field();
            nameCopy(&field->name,temp->string_content); //此时存储的是变量名，返回给上层使用
            field->type = record;
            field->tail = 0;
        }
        temp = temp->firstChild;
    }
    return field;
}

struct Type* doAccordingTypeName(char* typeName)
{
    struct Type* type = malloc_type();
    if(equal("int",typeName))   //specifier为一个int
    {
        type->typeId = BASIC;
        type->t_basic = INT;
    }
    else if(equal("float",typeName)) //specifier为一个float
    {
        type->typeId = BASIC;
        type->t_basic = FLOAT;
    }  
    else //specifier为一个结构体名
    {
        type->typeId = STRUCT;
        type->t_structure = malloc_field();
        nameCopy(&type->t_structure->name,typeName);
        type->t_structure->type = 0;
        type->t_structure->tail = 0;
    }
    return type;
}

//处理当specifier与varDec一起出现的情况，返回一个Field指针以供使用
struct Field* specifierAndVarDec(treeNode* specifier,treeNode* varDec)
{
    char* typeName = doWhenSpecifier(specifier);   
    struct Field* field = doWhenVarDec(varDec);//返回了一个Field域,可能为一个数组，也可能为单个变量
    struct Type* type = doAccordingTypeName(typeName);
    struct entryInSymbolTable* entry = malloc_symbol_entry();
            
    if(field->type == 0)    //这是一个普通变量
    {
        field->type = type;
    }
    else //这是一个数组 
    {
        struct Type* temp = field->type;
        while(temp->t_array.nextLevel != 0){
            temp = temp->t_array.nextLevel;
        }
        temp->t_array.nextLevel = type;          
    }
    return field;
}

/* 函数已完成 */
struct Field* doWhenParamDec(treeNode* ParamDec)
{
    return specifierAndVarDec(ParamDec->firstChild,
        ParamDec->firstChild->sibling);
}

struct Filed* doWhenVarList(treeNode* VarList)
{
    treeNode* paramDec = VarList->firstChild;  
    struct Field* field = doWhenParamDec(paramDec);
    struct Field* record = field;
    struct Field* global = field;
    while(paramDec != 0)
    {
        if(paramDec->sibling != 0)
        {
            paramDec = paramDec->sibling->sibling->firstChild;
            field = doWhenParamDec(paramDec);
            record->tail = field;
            record = field; 
        } 
        else paramDec = 0;      
    }
    return global;
}

void doWhenExtDef(treeNode* ExtDef)
{
    treeNode* specifier = ExtDef->firstChild;
    
    // ExtDef -> specifier ExtDefList SEMI
    if(equal("ExtDecList",specifier->sibling->string_content))
    {
        treeNode* varDec = specifier->sibling->firstChild;
        do
        {           
            struct Field* field = specifierAndVarDec(specifier,varDec);//返回了一个Field域,可能为一个数组，也可能为单个变量
            struct Type* type = malloc_type();          
            struct entryInSymbolTable* entry = malloc_symbol_entry();
            if(field->type->typeId == BASIC)    //这是一个普通变量
            {
                entry->symbol.typeId = BASIC;
                nameCopy(&entry->symbol.name,field->name);
                entry->symbol.s_var.type = field->type;
            }
            else //这是一个数组 
            {
                entry->symbol.typeId = ARRAY;
                nameCopy(&entry->symbol.name,field->name);
                entry->symbol.s_array.type = field->type;              
            }
            insertEntryInSymbolTable(entry);
            if(varDec->sibling != 0)
                varDec = varDec->sibling->sibling->firstChild;
            else varDec = 0;
        }while(varDec != 0);
    }
    else if(0 == strcmp("FunDec",specifier->sibling->string_content))
    {
        char* typeName = doWhenSpecifier(specifier);
        treeNode* funcDec = specifier->sibling;
        treeNode* funcName = funcDec->firstChild;
        struct entryInSymbolTable* entry = malloc_symbol_entry();
        struct Type* paramType = malloc_type();
        entry->symbol.s_func.returnType = doAccordingTypeName(typeName);;
        nameCopy(&entry->symbol.name,funcName->string_content);
        entry->symbol.typeId = FUNCTION;
        
        if(funcDec->sibling->type == SEMI)
            entry->symbol.s_func.funcState = DECLARED;
        else entry->symbol.s_func.funcState = DEFINED;
        
        if(funcName->sibling->sibling->type == RP)
            entry->symbol.s_func.paramType = 0;
        else 
        {
            paramType->typeId = STRUCT;
            paramType->t_structure = doWhenVarList(funcName->sibling->sibling);
            entry->symbol.s_func.paramType = paramType;
        }
        insertEntryInSymbolTable(entry);
    }
}

struct Type* getExpType(treeNode* Exp)
{
}

void doWhenExp(treeNode* Exp)
{    
    treeNode* childExp = Exp->firstChild;
    if(childExp->type == ID && childExp->sibling == 0) //Exp->ID
    {
        struct entryInSymbolTable* entry = findInSymbolTable(childExp->string_content);
        if(entry == 0)
            genError(UNDEFINED_VAR,Exp->lineno,UNDEFINED_VAR_INFO);
    }
    
}

void traverseAndCheck(treeNode* root)
{
    if(root != 0)
    {
        if(root->type == SYNTAX)
        {
            if(equal("Program",root->string_content))
            {
                doWhenProgram();
            }
            else if(equal("CompSt",root->string_content))
            {
                doWhenCompSt();
            }
            else if(equal("ExtDef",root->string_content))
            {
                doWhenExtDef(root);
            }
            else if(equal("Def",root->string_content))
            {
            }
            else if(equal("Exp",root->string_content))
            {
                doWhenExp(root);
            }
        }
        root = root->firstChild;
        while(root != 0)
        {
            traverseAndCheck(root);
            root = root->sibling;
        }
    }
}
