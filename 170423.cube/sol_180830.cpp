//Performance = 4201, Final=650
extern void rotate(int face, int cw);

const int LM = 3;
int rp = 0;

int myCube[6][3][3];
int myPath[12][2];
const int DEF_MAX_HASH = 300000;
typedef struct INFO {
	unsigned long hash;
	int path[12][2];
	int cube[6][3][3];
	int n;
	INFO* next;
}info;

info heap[300000];
info* HashTable[300000];

void mycopy_cube(int src[6][LM][LM], int tar[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				tar[face][i][j] = src[face][i][j];
}
void myRotate(int cube[6][3][3], int face, int cw)
{
	int local[6][LM][LM];
	mycopy_cube(cube, local);

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[2][2][i] = local[4][3 - 1 - i][2];
				cube[4][i][2] = local[3][0][i];
				cube[3][0][i] = local[5][3 - 1 - i][0];
				cube[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[4][3 - 1 - i][2] = local[2][2][i];
				cube[3][0][i] = local[4][i][2];
				cube[5][3 - 1 - i][0] = local[3][0][i];
				cube[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[5][i][2] = local[3][2][3 - 1 - i];
				cube[3][2][i] = local[4][i][0];
				cube[4][i][0] = local[2][0][3 - 1 - i];
				cube[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[3][2][3 - 1 - i] = local[5][i][2];
				cube[4][i][0] = local[3][2][i];
				cube[2][0][3 - 1 - i] = local[4][i][0];
				cube[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][0][i] = local[5][0][i];
				cube[5][0][i] = local[1][0][i];
				cube[1][0][i] = local[4][0][i];
				cube[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[5][0][i] = local[0][0][i];
				cube[1][0][i] = local[5][0][i];
				cube[4][0][i] = local[1][0][i];
				cube[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][2][i] = local[4][2][i];
				cube[4][2][i] = local[1][2][i];
				cube[1][2][i] = local[5][2][i];
				cube[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[4][2][i] = local[0][2][i];
				cube[1][2][i] = local[4][2][i];
				cube[5][2][i] = local[1][2][i];
				cube[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][i][0] = local[2][i][0];
				cube[2][i][0] = local[1][3 - 1 - i][2];
				cube[1][i][2] = local[3][3 - 1 - i][0];
				cube[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[2][i][0] = local[0][i][0];
				cube[1][3 - 1 - i][2] = local[2][i][0];
				cube[3][3 - 1 - i][0] = local[1][i][2];
				cube[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				cube[0][i][2] = local[3][i][2];
				cube[3][i][2] = local[1][3 - 1 - i][0];
				cube[1][i][0] = local[2][3 - 1 - i][2];
				cube[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				cube[3][i][2] = local[0][i][2];
				cube[1][3 - 1 - i][0] = local[3][i][2];
				cube[2][3 - 1 - i][2] = local[1][i][0];
				cube[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}

unsigned long hash(int cube[6][3][3])
{
	unsigned long hash = 5381;
	int c;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				hash = (((hash << 5) + hash) + cube[i][j][k]) % DEF_MAX_HASH;
			}
		}
	}

	return hash % DEF_MAX_HASH;
}

void addHashTable(info t)
{

}

void register_cube(int cube[6][3][3], int face, int cw, int n)
{
	unsigned long h = hash(cube);

	info *t = &heap[rp++];
	mycopy_cube(cube, t->cube);
	t->hash = h;
	t->n = n + 1;
	myPath[n][0] = face;
	myPath[n][1] = cw;

	for (int i = 0; i < t->n; i++)
	{
		t->path[i][0] = myPath[i][0];
		t->path[i][1] = myPath[i][1];
	}

	t->next = HashTable[h];
	if (HashTable[h] != 0)
	{
		int a123 = 1;
		int b234 = 2;
	}
	HashTable[h] = t;
}
void make_map(int n)
{
	int i, j, k;
	if (n == 5)return;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 2; j++)
		{
			int face = i;
			int cw = j;
			myRotate(myCube, face, cw);
			register_cube(myCube, face, cw, n);
			make_map(n + 1);
			myRotate(myCube, face, 1 - cw);
		}
	}
}

int mycheck_cube(int src[6][LM][LM], int tar[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				if (src[face][i][j] != tar[face][i][j])
					return 0;

	return 1;
}

int ans_cnt;
int ans_path[12][2];
info* ans_heap;
int temp_path[12][2];

info* find_hash_table(int cube[6][3][3])
{
	unsigned long h = hash(cube);
	if (HashTable[h] != 0)
	{
		info *t1 = HashTable[h];
		while (t1 != 0)
		{
			if (mycheck_cube(cube, t1->cube) == 1)
				return t1;
			t1 = t1->next;
		}
	}
	return 0;
}
void dfs(int n)
{
	register int i, j, k;
	if (ans_cnt <= n)return;
	if (n >= 5)return;

	info* t1 = find_hash_table(myCube);
	if (t1 != 0)
	{
		ans_heap = t1;
		ans_cnt = n;

		for (k = 0; k < n; k++)
		{
			ans_path[k][0] = temp_path[k][0];
			ans_path[k][1] = temp_path[k][1];
		}
	}

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 2; j++)
		{
			myRotate(myCube, i, j);
			temp_path[n][0] = i;
			temp_path[n][1] = j;

			dfs(n + 1);
			myRotate(myCube, i, 1 - j);
		}
	}
}
void runTest(int local[6][LM][LM])
{
	register int i, j, k;
	if (rp == 0)
	{
		for (i = 0; i < 6; i++)
			for (j = 0; j < 3; j++)
				for (k = 0; k < 3; k++)
					myCube[i][j][k] = i;
		make_map(0);
	}

	mycopy_cube(local, myCube);
	ans_cnt = 10;
	dfs(0);

	for (i = 0; i < ans_cnt; i++)
	{
		rotate(ans_path[i][0], ans_path[i][1]);
	}
	for (i = ans_heap->n - 1; i >= 0; i--)
	{
		rotate(ans_heap->path[i][0], 1 - ans_heap->path[i][1]);
	}
}