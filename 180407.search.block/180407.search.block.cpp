#include <iostream>

using namespace std;
typedef unsigned long long ULL;

typedef struct node {
	ULL data;
	node* left;
	node* right;
}*pnode;
ULL convert_ull(char str[11])
{
	ULL a = 0;
	for (int i = 0; i < 10; i++)
	{
		if (str[i] == 0)
			break;
		ULL b = str[i] - 'a' + 1;
		ULL c = b << (i * 5);
		a += c;
	}
	return a;
}

void convert_str(char str2[11], ULL a)
{
	for (int i = 0; i < 10; i++)
	{
		int b = a >> (i * 5);
		str2[i] = b & 31;
		if (str2[i] == 0)
			break;
		str2[i] += 'a' - 1;
	}
}
pnode add_node(pnode p, pnode n)
{
	if (p == NULL)
		return n;

	if (n->data < p->data)
		p->left = add_node(p->left, n);
	else
		p->right = add_node(p->right, n);

	return p;
}
pnode new_node(ULL data)
{
	pnode tmp;
	tmp = (pnode)malloc(sizeof(node));
	tmp->data = data;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
pnode min_node(pnode p)
{
	while (p->left != NULL)
		p = p->left;

	return p;
}
pnode delete_node(pnode p, ULL data)
{
	if (p == NULL)
		return NULL;

	if (data < p->data)
		p->left = delete_node(p->left, data);
	else if (data>p->data)
		p->right = delete_node(p->right, data);
	else
	{
		if (p->left == NULL)
		{
			pnode tp = p->right;
			free(p);
			p = NULL;
			return tp;
		}
		else if (p->right == NULL)
		{
			pnode tp = p->left;
			free(p);
			p = NULL;
			return tp;
		}
		else
		{
			pnode tp = min_node(p->right);
			p->data = tp->data;
			p = delete_node(p->right, tp->data);
		}
	}
	return p;
}
int cnt;

void print_tree(pnode p)
{
	if (p == NULL)
		return;
	print_tree(p->left);
	char str[11] = { 0, };
	convert_str(str, p->data);
	printf("%d. %llu : %s\n", ++cnt, p->data, str);
	print_tree(p->right);
}
void erase_tree(pnode p)
{
	if (p == NULL)
		return;

	erase_tree(p->left);
	erase_tree(p->right);
	free(p);
	p = NULL;
}



pnode root;
ULL item;
int main()
{
	//make string
	for (int tc = 0; tc < 2000000; tc++)
	{
		char str[11] = { 0, };

		str[0] = rand() % 26 + 'a';
		for (int i = 1; i < 10; i++)
		{
			if (rand() % 10 == 0)
				break;
			str[i] = rand() % 26 + 'a';
		}

		//change to ULL
		ULL a = convert_ull(str);

		//convert to string
		char str2[11] = { 0, };
		convert_str(str2, a);
		
		pnode tp = new_node(a);
		root = add_node(root, tp);

		if (rand() % 2 == 0)
			item = a;

		if (item != 0)
		{
			delete_node(root, item);
			item = 0;
		}
	}

	print_tree(root);

	erase_tree(root);
	root = NULL;

	//string comparez
	return 0;
}