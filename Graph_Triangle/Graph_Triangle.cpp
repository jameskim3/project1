#include <iostream>

int TC, N, M, ret;
int map[51][51];
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &TC);
	int x, y;
	for (int i = 0; i < TC; i++)
	{
		for (y = 0; y < 51; y++)
			for (x = 0; x < 51; x++)
				map[y][x] = 0;

		scanf("%d %d", &N, &M);
		ret = 0;
		for (int j = 0; j < M; j++)
		{
			scanf("%d %d", &x, &y);
			map[x][y] = 1;
			map[y][x] = 1;
		}

		for (int a = 1; a <= N; a++)
			for (int b = 1; b <= N; b++)
				for (int c = 1; c <= N; c++)
				{
					if (a == b || b == c || c == a)continue;
					if (map[a][b] == 1 && map[b][c] == 1 && map[c][a] == 1)
						ret++;
				}
		printf("#%d %d\n", i + 1, ret/6);
	}
	return 0;
}