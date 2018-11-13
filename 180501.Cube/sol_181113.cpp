
const int LM = 3;
const int max_val = 3000000;
extern void rotate(int face, int cw);
extern int check_cube(int src[6][LM][LM]);
extern void copy_cube(int src[6][LM][LM], int tar[6][LM][LM]);
extern void initial_cute(int cube[6][LM][LM]);
int rp;
struct INFO {
	int face[6];
	int cw[6];
	int n;
	INFO* next;
};
struct myLink
{
	INFO* info;
	myLink* next;
};
INFO nd[max_val];
INFO* heap[max_val];
INFO path_map;
int mapCube[6][LM][LM];
int curCube[6][LM][LM];
void rotate2(int c[6][LM][LM], int face, int cw)
{
	int i;
	int local[6][LM][LM];
	copy_cube(c, local);
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
int getHash(int c[6][LM][LM])
{
	unsigned int h = 5181;

	for (int j = 0; j < 6; j++)
		for (int k = 0; k < 3; k++)
			for (int l = 0; l < 3; l++)
				h = (h * 33 + c[j][k][l]) % max_val;
	return h%max_val;
}
void addHeap()
{
	int h = getHash(mapCube);
	INFO* d = &nd[rp++];

	for (int i = 0; i <= path_map.n; i++)
	{
		d->cw[i] = path_map.cw[i];
		d->face[i] = path_map.face[i];
	}
	d->n = path_map.n+1;

	d->next = heap[h];
	heap[h] = d;
}
void make_map(int n)
{
	if (n >= 5)return;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rotate2(mapCube, i, j);
			path_map.cw[n] = j;
			path_map.face[n] = i;
			path_map.n = n;
			addHeap();
			make_map(n + 1);
			rotate2(mapCube, i, 1 - j);
		}
	}
}

INFO ans_path;
INFO* ans_map;
int match_n;
INFO* isMatch()
{
	int h = getHash(mapCube);
	if (heap[h] != 0)
	{
		INFO* iter = heap[h];
		int c[6][LM][LM];

		while (iter != 0)
		{
			copy_cube(mapCube, c);
			for (int i = iter->n - 1; i >= 0; i--)
			{
				rotate2(c, iter->face[i], iter->cw[i]);
			}
			if (check_cube(c))
				return iter;
			iter = iter->next;
		}
	}
}
void solve(int n)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rotate2(mapCube, i, j);
			ans_path.cw[n] = j;
			ans_path.face[n] = i;
			ans_path.n = n;
			ans_map = isMatch();
			if (ans_map != 0)return;
			make_map(n + 1);
			if (ans_map != 0)
				return;
			rotate2(mapCube, i, 1 - j);
		}
	}
}
void runTest(int a[6][LM][LM])
{
	if (rp == 0)
	{
		initial_cute(mapCube);
		make_map(0);
	}
	ans_map = 0;
	copy_cube(a, mapCube);
	solve(0);
	for (int i = 0; i <= ans_path.n; i++)
	{
		rotate(ans_path.face[i], ans_path.cw[i]);
	}
	int cnt = ans_map->n - 1;
	while (cnt>=0)
	{
		rotate(ans_map->face[cnt], ans_map->cw[cnt]);
		cnt--;
	}
}
