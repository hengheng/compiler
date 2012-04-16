#include "all.h"
int errorOccur;

int main(int argc,char** argv){
	if(argc <= 1){
		return 1;
	}
	FILE* file = fopen(argv[1],"r");
	if(!file){
		perror(argv[1]);
		return 1;
	}
	yyrestart(file);
	yyparse();
	if(errorOccur == 0)traverse(root,0);
	return 0;
}
