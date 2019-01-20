#define LM  3
void copy_cube(int src[6][LM][LM], int tar[6][LM][LM]);
void rotate(int face, int cw);
void myRotate(int c[6][3][3], int face, int cw)
{
	int local[6][LM][LM];
	copy_cube(c, local);

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[2][2][i] = local[4][3 - 1 - i][2];
				c[4][i][2] = local[3][0][i];
				c[3][0][i] = local[5][3 - 1 - i][0];
				c[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[4][3 - 1 - i][2] = local[2][2][i];
				c[3][0][i] = local[4][i][2];
				c[5][3 - 1 - i][0] = local[3][0][i];
				c[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[5][i][2] = local[3][2][3 - 1 - i];
				c[3][2][i] = local[4][i][0];
				c[4][i][0] = local[2][0][3 - 1 - i];
				c[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[3][2][3 - 1 - i] = local[5][i][2];
				c[4][i][0] = local[3][2][i];
				c[2][0][3 - 1 - i] = local[4][i][0];
				c[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[0][0][i] = local[5][0][i];
				c[5][0][i] = local[1][0][i];
				c[1][0][i] = local[4][0][i];
				c[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[5][0][i] = local[0][0][i];
				c[1][0][i] = local[5][0][i];
				c[4][0][i] = local[1][0][i];
				c[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[0][2][i] = local[4][2][i];
				c[4][2][i] = local[1][2][i];
				c[1][2][i] = local[5][2][i];
				c[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[4][2][i] = local[0][2][i];
				c[1][2][i] = local[4][2][i];
				c[5][2][i] = local[1][2][i];
				c[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[0][i][0] = local[2][i][0];
				c[2][i][0] = local[1][3 - 1 - i][2];
				c[1][i][2] = local[3][3 - 1 - i][0];
				c[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[2][i][0] = local[0][i][0];
				c[1][3 - 1 - i][2] = local[2][i][0];
				c[3][3 - 1 - i][0] = local[1][i][2];
				c[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				c[0][i][2] = local[3][i][2];
				c[3][i][2] = local[1][3 - 1 - i][0];
				c[1][i][0] = local[2][3 - 1 - i][2];
				c[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				c[3][i][2] = local[0][i][2];
				c[1][3 - 1 - i][0] = local[3][i][2];
				c[2][3 - 1 - i][2] = local[1][i][0];
				c[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}
//hash
#define MAX_TABLE 300000
#define MAX_NODE 300000
unsigned long hash(int c[6][3][3])
{
	unsigned long hash = 5381;
	int i, j, k;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				hash = (((hash << 5) + hash) + c[i][j][k]) % MAX_TABLE;
	return hash % MAX_TABLE;
}

//LinkedList
typedef struct ListNode
{
	int cube[6][3][3];
	int hash;
	int path[5][2];
	int cnt;
	ListNode* next;
} ListNodeHeap;
ListNodeHeap list[MAX_NODE];
ListNodeHeap* heap[MAX_NODE];
int rp;
void appendListNode(int c[6][3][3], int path[5][2], int cnt)
{
	unsigned long h = hash(c);
	list[rp].cnt = cnt;
	int i, j, k;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				list[rp].cube[i][j][k] = c[i][j][k];
	for (i = 0; i < cnt; i++)
		for (j = 0; j < 2; j++)
			list[rp].path[i][j] = path[i][j];
	list[rp].hash = h;
	list[rp].next = heap[h];
	heap[h] = &list[rp];
	rp++;
}

int isMatch(int c[6][3][3], int d[6][3][3])
{
	int i, j, k;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				if (c[i][j][k] != d[i][j][k])
					return 0;
	return 1;
}
ListNode* findNode(int c[6][3][3])
{
	unsigned long h = hash(c);
	ListNode* pnode = heap[h];
	while (pnode)
	{
		if (isMatch(c, pnode->cube))
			return pnode;
		pnode = pnode->next;
	}

	return 0;
}

int myCube[6][3][3];
int ans_path[5][2];
int rot_path[5][2];
ListNode* ans;
int ans_cnt;

void make_map(int n)
{
	if (n >= 5) return;
	int i, j, k;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 2; j++)
		{
			rot_path[n][0] = i;
			rot_path[n][1] = j;
			myRotate(myCube, i, j);
			appendListNode(myCube, rot_path, n + 1);
			make_map(n + 1);
			myRotate(myCube, i, 1 - j);
		}
}

void dfs(int n)
{
	if (n >= 5) return;
	if (ans_cnt <= n) return;
	int i, j, k;

	ListNode* pnode = findNode(myCube);
	if (pnode != 0 && n < ans_cnt)
	{
		ans_cnt = n;
		for (i = 0; i < n; i++)
			for (j = 0; j < 2; j++)
				ans_path[i][j] = rot_path[i][j];
		ans = pnode;
	}
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 2; j++)
		{
			rot_path[n][0] = i;
			rot_path[n][1] = j;
			myRotate(myCube, i, j);
			dfs(n + 1);
			myRotate(myCube, i, 1 - j);
		}
	}
}

void runTest(int local[6][3][3])
{
	int i, j, k;

	if (rp == 0)
	{
		for (i = 0; i < 6; i++)
			for (j = 0; j < 3; j++)
				for (k = 0; k < 3; k++)
					myCube[i][j][k] = i;
		make_map(0);
	}
	copy_cube(local, myCube);

	ans = 0;
	ans_cnt = 99;

	dfs(0);

	for (i = 0; i < ans_cnt; i++)
		rotate(ans_path[i][0], ans_path[i][1]);
	for (i = ans->cnt - 1; i >= 0; i--)
		rotate(ans->path[i][0], 1 - ans->path[i][1]);

	return;
}