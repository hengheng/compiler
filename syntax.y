%{
    #include "lex.yy.c"
    #include "all.h"
    int errorOccur = 0;
    #define        YYSTYPE        treeNode

/* assistant function 
 * to fill with $$
 */
void fill_non_terminal(YYSTYPE* yyval,char* name,int lineno){
    yyval->type = SYNTAX;
    memset(yyval->string_content,0,MAX_NAME_LENGTH);
    strcpy(yyval->string_content,name);
    yyval->string_content[strlen(name)] = 0;
    yyval->lineno = lineno;
    yyval->sibling = 0;
    yyval->firstChild = 0;
}

    
%}

/* declared terminal tokens */
%token        INT 
%token        FLOAT
%token        ID
%token        SEMI COMMA    
%token        TYPE
%token        LC RC
%token        STRUCT
%token        RETURN
%token        IF
%token        ELSE
%token        WHILE
%token         ASSIGNOP
%token         OR
%token         AND
%token         RELOP
%token         PLUS MINUS
%token         STAR DIV
%token        UMINUS NOT 
%token        LP RP LB RB DOT

%token        SYNTAX

/* declared precedence and associativity of the opeartors */
%right        ASSIGNOP
%left        OR
%left        AND
%left        RELOP
%left        PLUS MINUS
%left        STAR DIV
%right        UMINUS NOT
%left        LP RP LB RB DOT
/* deal with if-else conflict */
%nonassoc    LOWER_THAN_ELSE
%nonassoc    ELSE


%%

/* High-Level Definitions */
Program             :       ExtDefList                      {    
                                                                fill_non_terminal(&$$,"Program",$1.lineno);
                                                                treeNode* node = treeNodeMalloc(&$$);
                                                                insert(node,&$1);
                                                                root = node;
                                                            }
                    ;
ExtDefList          :       ExtDef ExtDefList               {        
                                                                fill_non_terminal(&$$,"ExtDefList",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);            
                                                            }
                    |       /* empty */                     {    
                                                                fill_non_terminal(&$$,"ExtDefList",NULL_LINE);
                                                            }
                    ;
ExtDef              :       Specifier ExtDecList SEMI       {
                                                                fill_non_terminal(&$$,"ExtDef",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       Specifier SEMI                  {
                                                                fill_non_terminal(&$$,"ExtDef",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       Specifier FunDec CompSt         {                    
                                                                fill_non_terminal(&$$,"ExtDef",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       error SEMI                                                
                    ;
ExtDecList          :       VarDec                          {    
                                                                fill_non_terminal(&$$,"ExtDecList",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    |       VarDec COMMA ExtDecList         {                    
                                                                fill_non_terminal(&$$,"ExtDecList",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    ;

/* Specifiers */
Specifier           :       TYPE                            {    
                                                                fill_non_terminal(&$$,"Specifier",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    |       StructSpecifier                 {    
                                                                fill_non_terminal(&$$,"Specifier",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    ;
StructSpecifier     :       STRUCT OptTag LC DefList RC     {
                                                                fill_non_terminal(&$$,"StructSpecifier",$1.lineno);
                                                                insert(&$$,&$5);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       STRUCT Tag                      {
                                                                fill_non_terminal(&$$,"StructSpecifier",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    ;
OptTag              :       ID                              {    
                                                                fill_non_terminal(&$$,"OptTag",$1.lineno);
                                                                insert(&$$,&$1);        
                                                            }
                    |       /* empty */                     {
                                                                fill_non_terminal(&$$,"OptTag",NULL_LINE);
                                                            }
                    ;
Tag                 :       ID                              {    
                                                                fill_non_terminal(&$$,"Tag",$1.lineno);
                                                                insert(&$$,&$1);        
                                                            }
                    ;
                    
/* Declarators */
VarDec              :       ID                              {    
                                                                fill_non_terminal(&$$,"VarDec",$1.lineno);
                                                                insert(&$$,&$1);
                                                            
                                                            }
                    |       VarDec LB INT RB                {
                                                                fill_non_terminal(&$$,"VarDec",$1.lineno);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    ;
FunDec              :       ID LP VarList RP                {
                                                                fill_non_terminal(&$$,"FunDec",$1.lineno);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                                
                                                            }
                    |       ID LP RP                        {
                                                                fill_non_terminal(&$$,"FunDec",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }
                    |       error RP
                    ;
VarList             :       ParamDec COMMA VarList          {
                                                                fill_non_terminal(&$$,"VarList",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                                            
                                                            }
                    |       ParamDec                        {    
                                                                fill_non_terminal(&$$,"VarList",$1.lineno);
                                                                insert(&$$,&$1);    
                                                            }
                    ;
ParamDec            :       Specifier VarDec                {
                                                                fill_non_terminal(&$$,"ParamDec",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    ;

/* Statement */
CompSt              :       LC DefList StmtList RC          {
                                                                fill_non_terminal(&$$,"CompSt",$1.lineno);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }
                    |       error RC                        
                    ;
StmtList            :       Stmt StmtList                   {
                                                                fill_non_terminal(&$$,"StmtList",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       /* empty */                     {
                                                                fill_non_terminal(&$$,"StmtList",NULL_LINE);
                                                            }                
                    ;
Stmt                :       Exp SEMI                        {
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);    
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                                    
                                                                
                                                            }        
                    |       CompSt                          {    
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    |       RETURN Exp SEMI                 {
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       IF LP Exp RP Stmt    %prec LOWER_THAN_ELSE            
                                                            {
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);
                                                                insert(&$$,&$5);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       IF LP Exp RP Stmt ELSE Stmt     {
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);
                                                                insert(&$$,&$7);
                                                                insert(&$$,&$6);
                                                                insert(&$$,&$5);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       WHILE LP Exp RP Stmt            {
                                                                fill_non_terminal(&$$,"Stmt",$1.lineno);
                                                                insert(&$$,&$5);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }            
                    |       error SEMI                     

/* Local Definitions */
DefList             :       Def DefList                     {
                                                                fill_non_terminal(&$$,"DefList",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       /* empty */                     {
                                                                fill_non_terminal(&$$,"DefList",NULL_LINE);
                                                            }
                    ;
Def                 :       Specifier DecList SEMI          {
                                                                fill_non_terminal(&$$,"Def",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       Specifier error SEMI        
                    ;
DecList             :       Dec                             {    
                                                                fill_non_terminal(&$$,"DecList",$1.lineno);    
                                                                insert(&$$,&$1);    
                                                            }
                    |       Dec COMMA DecList               {
                                                                fill_non_terminal(&$$,"DecList",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);            
                                                            }
                    ;
Dec                 :       VarDec                          {    
                                                                fill_non_terminal(&$$,"Dec",$1.lineno);    
                                                                insert(&$$,&$1);
                                                            }
                    |       VarDec ASSIGNOP Exp             {
                                                                fill_non_terminal(&$$,"Dec",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    ;
                    
/* Expressions */
Exp                 :       Exp ASSIGNOP Exp                {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       Exp AND Exp                     {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       Exp OR Exp                      {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       Exp RELOP Exp                   {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       Exp    PLUS Exp                 {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);            
                                                            }
                    |       Exp MINUS Exp                   {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }
                    |       Exp STAR Exp                    {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       Exp DIV Exp                     {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }
                    |       LP Exp RP                       {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       MINUS Exp    %prec UMINUS       {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }
                    |       NOT Exp                         {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       ID LP Args RP                   {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);    
                                                            }
                    |       ID LP RP                        {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }        
                    |       Exp LB Exp RB                   {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$4);
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);        
                                                            }    
                    |       Exp DOT ID                      {
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);        
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       ID                              {    
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$1);
                                                            }
                    |       INT                             {    
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);    
                                                                insert(&$$,&$1);
                                                            }
                    |       FLOAT                           {    
                                                                fill_non_terminal(&$$,"Exp",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    ;
Args                :       Exp COMMA Args                  {
                                                                fill_non_terminal(&$$,"Args",$1.lineno);    
                                                                insert(&$$,&$3);
                                                                insert(&$$,&$2);
                                                                insert(&$$,&$1);
                                                            }
                    |       Exp                             {    
                                                                fill_non_terminal(&$$,"Args",$1.lineno);
                                                                insert(&$$,&$1);
                                                            }
                    ;


%%
yyerror(char* msg){
    printf("Error type 2 at line %d: %s \'%s\'\n", yylineno, msg, yytext);
    errorOccur = 1;
}

                            
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
    

