//Performance = 4328, Final=650
const int LM = 3;
const int max_val = 300000;
extern void rotate(int face, int cw);
extern int check_cube(int src[6][LM][LM]);
extern void copy_cube(int src[6][LM][LM], int tar[6][LM][LM]);
extern void initial_cute(int cube[6][LM][LM]);
int rp;
struct INFO {
	int face[6];
	int cw[6];
	int n;
	int cube[6][LM][LM];
	INFO* next;
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
unsigned long getHash(int c[6][LM][LM])
{
	unsigned long hash = 5381;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				hash = (hash * 33 + c[i][j][k]) % max_val;
			}
		}
	}

	return hash % max_val;
}
void addHeap(int n, int f, int c)
{
	unsigned long h = getHash(mapCube);
	INFO* d = &nd[rp++];
	copy_cube(mapCube, d->cube);

	path_map.cw[n] = c;
	path_map.face[n] = f;
	d->n = n + 1;

	for (int i = 0; i < n + 1; i++)
	{
		d->cw[i] = path_map.cw[i];
		d->face[i] = path_map.face[i];
	}

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
			addHeap(n, i, j);
			make_map(n + 1);
			rotate2(mapCube, i, 1 - j);
		}
	}
}

INFO ans_path;
INFO temp_path;
INFO* ans_map;
int ans_cnt;
int chk_cube(int cube1[6][LM][LM], int cube2[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				if (cube1[face][i][j] != cube2[face][i][j])
					return 0;
	return 1;
}
INFO* isMatch(int cube1[6][LM][LM])
{
	int h = getHash(cube1);
	INFO* iter = heap[h];
	while (iter != 0)
	{
		if (chk_cube(cube1, iter->cube))
			return iter;
		iter = iter->next;
	}
	return 0;
}
void solve(int n)
{
	register int i, j, k;
	if (ans_cnt <= n)return;
	if (n >= 5)return;

	INFO* t1 = isMatch(mapCube);
	if (t1 != 0)
	{
		ans_map = t1;
		ans_cnt = n;

		for (k = 0; k < n; k++)
		{
			ans_path.face[k] = temp_path.face[k];
			ans_path.cw[k] = temp_path.cw[k];
		}
	}

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 2; j++)
		{
			rotate2(mapCube, i, j);
			temp_path.face[n] = i;
			temp_path.cw[n] = j;

			solve(n + 1);
			//if (ans_map != 0)return;
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
	ans_cnt = 12;
	copy_cube(a, mapCube);
	solve(0);
	for (int i = 0; i < ans_cnt; i++)
	{
		rotate(ans_path.face[i], ans_path.cw[i]);
	}
	int cnt = ans_map->n - 1;
	while (cnt >= 0)
	{
		rotate(ans_map->face[cnt], 1 - ans_map->cw[cnt]);
		cnt--;
	}
}


