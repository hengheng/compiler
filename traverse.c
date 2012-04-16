#include "all.h"

void display(treeNode* p){
	switch(p->type){
		case INT:		printf("INT: %d\n",p->int_content);break;
		case FLOAT:		printf("FLOAT: %f\n",p->float_content);break;
		case TYPE:		printf("TYPE: %s\n",p->string_content);break;
		case ID:		printf("ID: %s\n",p->string_content);break;
		case SYNTAX:	{
							if(p->lineno != NULL_LINE)printf("%s (%d)\n",p->string_content,p->lineno);
							else printf("\n");
							break;	
						}
		case SEMI:		printf("SEMI\n");break;
		case COMMA:		printf("COMMA\n");break;
		case LC:		printf("LC\n");break;
		case RC:		printf("RC\n");break;
		case STRUCT:	printf("STRUCT\n");break;
		case RETURN:	printf("RETURN\n");break;
		case IF:		printf("IF\n");break;
		case ELSE:		printf("ELSE\n");break;
		case WHILE:		printf("WHILE\n");break;
		case ASSIGNOP:	printf("ASSIGNOP\n");break;
		case OR:		printf("OR\n");break;
		case AND:		printf("AND\n");break;
		case RELOP:		printf("RELOP\n");break;
		case PLUS:		printf("PLUS\n");break;
		case MINUS:		printf("MINUS\n");break;
		case STAR:		printf("STAR\n");break;
		case DIV:		printf("DIV\n");break;
		case NOT:		printf("NOT\n");break;
		case LP:		printf("LP\n");break;
		case RP:		printf("RP\n");break;
		case LB:		printf("LB\n");break;
		case RB:		printf("RB\n");break;
		case DOT:		printf("DOT\n");break;
		default:break;
	}
}
void printSpace(int i){
	int j;
	for(j=0;j<i;j++)
		printf(" ");
}


void traverse(treeNode* root,int i){	
	if(root != NULL && root->lineno != NULL_LINE){
		printSpace(i);
		display(root);
		root = root->firstChild;
		while(root != NULL && root->lineno != NULL_LINE){
			i = i+2;
			traverse(root,i);
			i = i-2;	
			root = root->sibling;
		}
	}
	
}
