%{
#define			YYSTYPE			treeNode
#include "all.h"

int comment_start;

void fill_yylval(treeNode* val,int type){
	val->type = type;
	val->lineno = yylineno;
	if(type != INT && type != FLOAT){
		memcpy(val->string_content,yytext,yyleng);
		val->string_content[yyleng] = 0;
	}
	val->sibling = NULL;
	val->firstChild = NULL;
}

#define		fyylval(type)		fill_yylval(&yylval,type)
%}





%option yylineno
%x	COMMENT

zero					0
deci_digit				[0-9]
deci_pos_digit			[1-9]
oct_digit				[0-7]
hex_digit				[0-9A-Fa-f]

deci_digits				({deci_pos_digit}({deci_digit}*))|{zero}
oct_digits				{zero}({oct_digit}+)
hex_digits				{zero}[xX]({hex_digit}+)

INT						({deci_digits})|({oct_digits})|({hex_digits})	
FLOAT					(({deci_digit}+)|(({deci_digit}*)\.({deci_digit}+)))(([eE][-+]?{deci_digit}+)?)

blank					[ \t\n]	
blank_segment			{blank}+				
letter					[_a-zA-Z]
ID						{letter}({letter}|{deci_digit})*

comment_style1			(\/)(\/)(.)*\n

%%
{blank_segment}			{/* just ignore them */}
";"						{fyylval(SEMI);return SEMI;}
","						{fyylval(COMMA);return COMMA;}
"="						{fyylval(ASSIGNOP);return ASSIGNOP;}
">"						|
"<"						|
">="					|
"<="					|
"=="					|
"!="					{fyylval(RELOP);return RELOP;}
"+"						{fyylval(PLUS);return PLUS;}
"-"						{fyylval(MINUS);return MINUS;}
"*"						{fyylval(STAR);return STAR;}
"/"						{fyylval(DIV);return DIV;}
"&&"					{fyylval(AND);return AND;}
"||"					{fyylval(OR);return OR;}
"."						{fyylval(DOT);return DOT;}
"!"						{fyylval(NOT);return NOT;}
"int"					|
"float"					{fyylval(TYPE);return TYPE;}
"("						{fyylval(LP);return LP;}
")"						{fyylval(RP);return RP;}
"["						{fyylval(LB);return LB;}
"]"						{fyylval(RB);return RB;}
"{"						{fyylval(LC);return LC;}
"}"						{fyylval(RC);return RC;}
"struct"				{fyylval(STRUCT);return STRUCT;}
"return"				{fyylval(RETURN);return RETURN;}
"if"					{fyylval(IF);return IF;}
"else"					{fyylval(ELSE);return ELSE;}
"while"					{fyylval(WHILE);return WHILE;}
{INT}					{
							yylval.int_content = atoi(yytext);
							fyylval(INT);
							return INT;
						}
{FLOAT}					{
							yylval.float_content = atof(yytext);
							fyylval(FLOAT);
							return FLOAT;
						}
{ID}					{fyylval(ID);return ID;}
{comment_style1}		{}
"/*"					{comment_start = yylineno;BEGIN COMMENT;}
<COMMENT>"*/"			{BEGIN 0;}
<COMMENT>"/*"			{	
							printf("Error type 3 at line %d: Comment error : \'%s\'\n", yylineno, yytext);
							errorOccur = 1;
						}
<COMMENT><<EOF>>		{printf("Line %d comment hasn't been finished !!\n",comment_start);BEGIN 0;}
<COMMENT>.|\n|\t		{/* Nothing need to do */}

.						{
							printf("Error type 1 at line %d: Mysterious character \'%s\'\n", yylineno, yytext);
							errorOccur = 1;
						}


%%
/*int main(int argc,char** argv){
	FILE *file;
	if(argc < 2){
		yylex();
		return 0;
	}
	else{
		int i;
		for(i=1;i<argc;i++){
			file = fopen(argv[i],"r");
			if(!file){
				printf("The file can't be open with readonly parameter !\n");
				exit(1);
			}
			yylineno = 0;
			yyrestart(file);
			yylex();
			fclose(file);	
		}
		return 0;
	}
}*/


