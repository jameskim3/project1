#include <iostream>

int map[30][30];
int merged[30][30];
int TC, N;
int getDir(char* d)
{
	int ret = 0;
	switch (d[0])
	{
	case 'l': ret = 0;
		break;
	case 'r':ret = 1;
		break;
	case 'u':ret = 2;
		break;
	case 'd':ret = 3;
		break;
	}
	return ret;
}
void push(int a, int b, int dir)
{
	if (dir == 0)
	{
		for (int i = 0; i < N - b; i++)
		{
			map[a][b + i] += map[a][b + i + 1];
			map[a][b + i + 1] = 0;
		}
	}
	else if (dir==1)
	{
		for (int i = 0; i <b; i++)
		{
			map[a][b - i] += map[a][b - i - 1];
			map[a][b - i - 1] = 0;
		}
	}
	else if (dir == 2)
	{
		for (int i = 0; i <N-a; i++)
		{
			map[a + i][b] += map[a + i + 1][b];
			map[a + i + 1][b] = 0;
		}
	}
	else if (dir == 3)
	{
		for (int i = 0; i <a; i++)
		{
			map[a - i][b] += map[a - i - 1][b];
			map[a - i - 1][b] = 0;
		}
	}

}
void proc(int i, int j, int ox, int oy, int d)
{
	int cnt = 0;
	while (cnt < N)
	{
		if (map[i][j] != 0)
		{
			if (map[i + oy][j + ox] == 0)
			{
				push(i, j, d);
				cnt++;
			}
			else if (map[i][j] == map[i + oy][j + ox])
			{
				push(i, j, d);
				break;
			}
			else
				break;
		}
		else
		{
			push(i, j, d);
			cnt++;
		}
	}
}
void solve(int d)
{
	int i, j, k;
	int ox, oy;
	if (d == 0){ ox = 1; oy = 0; }
	if (d == 1){ ox = -1; oy = 0; }
	if (d == 2){ ox = 0; oy = 1; }
	if (d == 3){ ox = 0; oy = -1; }

	if (d == 0 || d==2)
	{
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				proc(i, j, ox, oy, d);
			}
		}
	}
	else 
	{
		for (i = N; i >= 1; i--)
		{
			for (j = N; j >= 1; j--)
			{
				proc(i, j, ox, oy, d);
			}
		}
	}
}
int main()
{
	freopen("in.txt", "r", stdin);
	char cmd[10];
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		for (int i = 1; i <= 30; i++)
		{
			for (int j = 1; j <= 30; j++)
			{
				map[i][j] = 0;
			}
		}

		scanf("%d %s", &N, cmd);
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}

		int d = getDir(cmd);
		solve(d);

		printf("#%d\n", tc + 1);
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}