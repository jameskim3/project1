#include <iostream>

int TC, B, L, N;
int map[401][2];
short ln[80200 + 10];
double dp[80200 + 10];
int S = 0;
int E = 1;

double dfs(int floor, int n)
{
	if (floor == 1)
		return B*750.0;

	int u, l, r;
	int line=ln[n];

	l = n - line;
	r = l + 1;
	u = r - (line - 1);

	double ret = 0.;
	if (n<=3)
		ret = (dfs(floor - 1, 1) - 250.0) / 3.;
	else
	{
		double temp[3] = { 0.0 };
		if (l >= map[line - 1][S] && l <= map[line - 1][E])
			temp[0] = (dfs(floor - 1, l) - 250.0) / 3.;
		if (r >= map[line - 1][S] && r <= map[line - 1][E])
			temp[1] = (dfs(floor - 1, r) - 250.0) / 3.;
		if (u >= map[line - 2][S] && u <= map[line - 2][E])
			temp[2] = (dfs(floor - 1, u) - 250.0) / 3.;
		for (int i = 0; i < 3; i++)
		{
			if (temp[i] > 0.)ret += temp[i];
		}
	}
	return ret;
}
double dfs(int floor, int n)
{
	int f = 1;
	int cnt;
	double ret = 0.;
	while (1)
	{
		if (f == floor && cnt == n)
			break;
	}
	return ret;
}
int main()
{
	freopen("in.txt", "r", stdin);
	map[0][S] = 0;
	map[0][E] = -1;
	map[1][S] = 1;
	map[1][E] = 1;
	for (int i = 2; i < 401; i++)
	{
		map[i][S] = map[i - 1][S] + i -1;
		map[i][E] = map[i][S] + i - 1;
	}

	int num = 2;
	ln[1] = 1;
	for (int i = 2;i<80210; )
	{
		for (int cnt = 0; cnt < num; cnt++)
		{
			if (i + cnt >= 80210)break;
			ln[i + cnt] = num;
		}
		i += num;
		num++;
	}
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		scanf("%d %d %d", &B, &L, &N);
		//double ret = dfs(L, N);
		double ret = dfs2(L, N);
		if (ret >= 250.0)ret = 250.0;
		printf("#%d %.8f\n", tc + 1, ret);
	}
	return 0;
}