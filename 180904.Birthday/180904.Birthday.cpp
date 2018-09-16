#include <iostream>

int item[510][510];
int N, M;
int a, b;
int chk[510];
int visited[510];
int ans;

int main()
{
	freopen("in.txt", "r", stdin);
	int TC;
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		scanf("%d %d", &N, &M);
		for (int i = 0; i < M; i++)
		{
			scanf("%d %d", &a, &b);
			item[a][b] = 1;
			item[b][a] = 1;
		}

		for (int i = 2; i <= N; i++)
		{
			if (item[1][i] == 1)
			{
				chk[i]++;
				for (int j = 2; j <= N; j++)
				{
					if (i == j)continue;
					if (item[i][j] == 1)
						chk[j]++;
				}
			}
		}

		ans = 0;
		for (int i = 0; i <= N; i++)
		{
			if (chk[i] > 0)ans++;
		}
		printf("#%d %d\n", tc + 1, ans);

		for (int i = 0; i <510; i++)
		{
			for (int j = 0; j <510; j++)
			{
				item[i][j] = 0;
			}
			chk[i] = 0;
			visited[i] = 0;
		}
	}

}