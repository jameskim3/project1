#include <iostream>


int N, M, item[110][110], chk[110][110];
int ans = 11000;

int path[][2] = {
	{ 0, 0 },
	{ -1, 0 },
	{ 1, 0 },
	{ 0, 1 },
	{ 0, -1 },
};

void dfs(int y, int x, int d, int cnt)
{
	if (item[y][x] == 0 || chk[y][x])
		return;

	int tmp = N - y + M - x;
	if (tmp >= ans - cnt)
		return;

	if (y == N && x == M)
	{
		if (cnt < ans)
			ans = cnt;
	}

	int nd;
	if (item[y][x] == 1 || item[y][x] == 2)
	{
		chk[y][x] = cnt;
		dfs(y + path[d][0], x + path[d][1], d, cnt + 1);
		chk[y][x] = 0;
	}
	else if (d < 3)
	{
		nd = 3;
		chk[y][x] = cnt;
		dfs(y + path[nd][0], x + path[nd][1], nd, cnt + 1);
		chk[y][x] = 0;
		nd = 4;
		chk[y][x] = cnt;
		dfs(y + path[nd][0], x + path[nd][1], nd, cnt + 1);
		chk[y][x] = 0;
	}
	else
	{
		nd = 1;
		chk[y][x] = cnt;
		dfs(y + path[nd][0], x + path[nd][1], nd, cnt + 1);
		chk[y][x] = 0;
		nd = 2;
		chk[y][x] = cnt;
		dfs(y + path[nd][0], x + path[nd][1], nd, cnt + 1);
		chk[y][x] = 0;
	}
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &item[i][j]); 

	if (item[1][1] == 1 || item[1][1] == 6)
		dfs(2, 1, 2, 2);
	else
		dfs(1, 2, 3, 2);

	printf("%d\n", ans);
	
	return 0;
}