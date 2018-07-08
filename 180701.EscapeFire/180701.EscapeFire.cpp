#include <iostream>

struct data1 {
	int y, x, t, c;
}Q[5000];
struct data2 {
	int y, x;
};
data2 path[] =
{
	{ -1, 0 },
	{ 1, 0 },
	{ 0, 1 },
	{ 0, -1 },
};

int N, M, item[60][60], chk[60][60];
int ans,sx,sy,tx,ty;
int head, tail;

int enq(int y, int x, int t, int c)
{
	if (item[y][x] == 0 || chk[y][x] == 1)
		return 0;

	if (y == ty && x == tx)
	{
		if (t == 2)
			return 0;
		else
			return t;
	}

	chk[y][x] = 1;
	Q[tail].y = y; Q[tail].x = x; Q[tail].t = t; Q[tail].c = c;
	tail++;
	return 0;
}

int bfs()
{
	enq(sy, sx, 1, 0);
	while (head < tail)
	{
		for (int i = 0; i < 4; i++)
		{
			int ret = enq(Q[head].y + path[i].y, Q[head].x + path[i].x, Q[head].t, Q[head].c + 1);
			if (ret)
			{
				if (Q[head].t == 1)
					return Q[head].c + 1;
				else
					return 0;
			}
		}
		head++;
	}
	return 0;
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d %d", &N, &M);
	char t[100];
	for (int i = 1; i <= N; i++)
	{
		scanf("%s", t);
		for (int j = 1; j <= M; j++)
		{
			char c;
			c = t[j-1];
			item[i][j] = c;
			if (c == 'S')
			{
				sx = j; sy = i;
			}
			else if (c == 'D')
			{
				tx = j; ty = i;
			}
			else if (c == '*')
			{
				enq(i, j, 2,0);
			}
			else if (c == 'X')
			{
				chk[i][j] = 1;
			}
		}
	}

	ans = bfs();
	if (ans == 0)
		printf("impossible\n");
	else
		printf("%d\n", ans);

	return 0;
}