const int max_buf = 500;
typedef struct pz
{
	short face[4][16];
	int right[max_buf];
	int down[max_buf];
	int r, d;
}PZ;
pz map[49 * 49 + 10];

int gN, gM, gK, cnt;
int ans[49 * 49 + 10];
int path[49 * 49 + 10];
int chk[49 * 49 + 10];
int find = 0;
void init(int N, int M, int K)
{
	gN = N;
	gM = M;
	gK = K;
	for (int i = 0; i < 49 * 49 + 10; i++)
	{
		chk[i] = 0;
		path[i] = -1;
		ans[i] = -1;
		map[i].r = map[i].d = 0;
		for (int j = 0; j < max_buf; j++)
		{
			map[i].right[j] = 0;
			map[i].down[j] = 0;
		}
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				map[i].face[j][k] = 0;
			}
		}
	}
	cnt = 0;
}
void addPiece(int piece[])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < gM; j++)
		{
			map[cnt].face[i][j] = piece[i*gM + j];
		}
	}
	cnt++;
}
int ismatching(short* a, short* b, int len)
{
	int cnt = 0;
	while (cnt++ < len)
	{
		if (a[cnt] + b[cnt] != 0)return 0;
	}
	return 1;
}
void dfs2(int n)
{
	if (n == gN*gN)
	{
		for (int i = 0; i < gN*gN; i++)
		{
			ans[i] = path[i];
		}
		find = 1;
		return;
	}
	if (n%gN == 0)
	{
		int ppos = path[n - gN];
		for (int i = 0; i < map[ppos].d; i++)
		{
			int curpos = map[ppos].down[i];
			if (chk[curpos] == 1)continue;
			chk[curpos] = 1; path[n] = curpos;
			dfs2(n + 1);
			if (find == 1)return;
			chk[curpos] = 0; path[n] = -1;
		}
	}
	else
	{
		int ppos = path[n - 1];
		for (int i = 0; i < map[ppos].r; i++)
		{
			int curpos = map[ppos].right[i];
			if (chk[curpos] == 1)continue;
			chk[curpos] = 1; path[n] = curpos;
			dfs2(n + 1);
			if (find == 1)return;
			chk[curpos] = 0; path[n] = -1;
		}
	}
}
void make_link()
{
	for (int i = 0; i < gN*gN + gK; i++)
	{
		for (int j = 0; j < gN*gN + gK; j++)
		{
			if (i == j)continue;
			if (ismatching(map[i].face[1], map[j].face[3], gM))
			{
				int *r = &map[i].r;
				map[i].right[(*r)++] = j;
			}
			if (ismatching(map[i].face[2], map[j].face[0], gM))
			{
				int *d = &map[i].d;
				map[i].down[(*d)++] = j;
			}
		}
	}
}
int findCenterPiece()
{
	find = 0;
	make_link();
	for (int i = 0; i < gN*gN + gK; i++)
	{
		chk[i] = 1; path[0] = i;
		dfs2(1);
		if (find)break;
		chk[i] = 0; path[0] = -1;
	}
	return ans[gN*gN / 2];
}