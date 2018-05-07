#include <stdio.h>
#include <stdlib.h>
#include "define.h"

pnode root;
pnode HASH[PN];
extern pnode find_node(pnode p, int id);
int init();
extern int insert(int pid, int id, int size);
int gSize;
int gCount;
int CalSizeCount(pnode n);
int CalSizeCount_all(pnode p);
int display_tree(pnode n, int depth);
extern pnode create_node(int id, int size);

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	root = create_node(1000, 0);

	srand(3);
	int N, id, pid, size, cmd;
	int ret;
	pnode n;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d %d", &pid, &id, &size, &cmd);
		switch (cmd)
		{
		case 0: //insert
			printf("\n_________________________________________________________________________________________________\n");
			ret = insert(pid, id, size);
			display_tree(root, 1);
			break;
		//case 1: //remove
		//	ret = remove(id);
		//	display_tree(root, 1);
		//	break;
		//case 2: //move
		//	ret = move(pid, id);
		//	display_tree(root, 1);
		//	break;
		//case 3: //inspect
		//	ret = inspect(id);
		//	display_tree(root, 1);
		//	break;
		//case 4: //recover
		//	ret = recover(id);
		//	display_tree(root, 1);
		//	break;
		//case 5: //init
		//	ret = init();
		//	break;
		}

	}

	init();
	return 0;
}


int display_tree(pnode n, int depth)
{
	if (n == NULL)
		return 0;

	for (int i = 0; i < depth; i++)
		printf("\t");
	int iSize = CalSizeCount(n);
	printf("%d[%d]\n", n->id, iSize);
	display_tree(n->child, depth + 1);
	display_tree(n->next, depth);

}
int CalSizeCount(pnode n)
{
	int Size = 0;

	if (n->size != 0)
	{
		Size = n->size;
	}
	else
	{
		Size = CalSizeCount_all(n->child);
	}

	return Size;
}
int CalSizeCount_all(pnode n)
{
	if (n == NULL) return 0;

	int size = 0;
	while (n != 0)
	{
		if (n->size == 0)
			size += CalSizeCount_all(n->child);
		else
			size += n->size;
		n = n->next;
	}
	
	return size;
}
int init()
{
	root->child = NULL;
	pnode tmp;
	for (int i = 0; i < PN; i++)
	{
		while (HASH[i] != NULL)
		{
			tmp = HASH[i]->hash;
			free(HASH[i]);
			HASH[i] = tmp;
		}
		HASH[i] = NULL;
	}

	return 0;
}