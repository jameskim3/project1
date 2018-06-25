#include <iostream>

int N;
int item[15][15];
int ans;
int check[30];

void DFS(int pos, int cnt)
{
	int flag = 0;
	int i, j, y, x;
	if (pos >= N * 2)
	{
		if (ans < cnt)
			ans = cnt;
		return;
	}
	y = pos <= N ? pos : N;
	x = pos <= N ? 1 : pos%N + 1;

	for (; y>0 && x>0 && y<=N && x<=N; y--,x++)
	{
		if (item[y][x] && !check[N - (y-x)])
		{
			flag = 1;
			check[N - (y - x)] = 1;
			DFS(pos + 1, cnt + 1);
			check[N - (y - x)] = 0;
		}
	}
	
	if (flag == 0)
		DFS(pos + 1, cnt);
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			scanf("%d", &item[i][j]);
	}

	DFS(1,0);
	printf("%d\n",ans);
	return 0;
}