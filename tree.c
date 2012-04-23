#include "all.h"

treeNode* root = NULL;
treeNode* treeNodeMalloc(treeNode* copy){
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	memcpy((char*)node,(char*)copy,sizeof(treeNode));
	node->firstChild = NULL;
	node->sibling = NULL;
	return node;
}

void insert(treeNode* parent,treeNode* child){
    if(child->lineno != NULL_LINE)
    {
	    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	    memcpy((char*)node,(char*)child,sizeof(treeNode));
	    node->sibling = parent->firstChild;
	    parent->firstChild = node;
	}
}







