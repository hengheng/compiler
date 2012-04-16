#ifndef		TREE_H
#define		TREE_H

#define			MAX_NAME_LENGTH			32
typedef union {
	int int_content;
	float float_content;
	char string_content[MAX_NAME_LENGTH];
}nodeContent;

typedef struct Node {
	int type;
	nodeContent content;
	int lineno;
	struct Node* firstChild;
	struct Node* sibling;
	#define		int_content			content.int_content	
	#define		float_content		content.float_content	
	#define		string_content		content.string_content	
}treeNode;

extern treeNode* root;
extern treeNode* record;
extern int errorOccur;

void insert(treeNode* parent,treeNode* child);
treeNode* treeNodeMalloc();
void display(treeNode* p);
void traverse(treeNode* root,int i);
#endif
