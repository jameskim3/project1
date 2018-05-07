#include "define.h"
#include <malloc.h>

pnode create_node(int id, int size)
{
	pnode n = (pnode)malloc(sizeof(node));
	n->child = 0;
	n->hash = HASH[id%PN]; HASH[id%PN] = n;
	n->id = id;
	n->next = 0;
	n->origin = size;
	n->size = size;
	n->parent = 0;

	return n;
}

pnode find_node(int pid)
{
	pnode h = HASH[pid%PN];
	while (h->id != pid) h = h->hash;
	return h;
}
int insert(int pid, int id, int size)
{
	pnode p = find_node(pid);
	if (p->size != 0)
		int a = 1;

	pnode n = create_node(id, size);
	n->parent = p;

	pnode c = p->child;
	if (c != 0)
	{
		while (c->next != 0) c = c->next;
		c->next = n;
	}
	else
		p->child = n;

	return 0;
}