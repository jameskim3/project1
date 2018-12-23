#ifndef ___HE___
#define ___HE___

typedef struct node
{
	int id, size, origin;
	int isFolder;
	node* parent;
	node* child;
	node* next;
	node* hash;
}*pnode;

const int PN = 10007;

extern pnode root;
extern pnode HASH[PN];


#endif