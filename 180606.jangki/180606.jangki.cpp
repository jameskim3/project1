#include <iostream>

int N, M, R, C, S, K;

struct stt1 {
	int y;
	int x;
};
stt1 path[8] = {
	{ -2, -1 },
	{ -2, 1 },
	{ -1, 2 },
	{ 1, 2 },
	{ 2, -1 },
	{ 2, 1 },
	{ -1, -2 },
	{ 1, -2 },
};

stt1 Q[50000];


int solve()
{
	int chk[110][110];
	
	int cnt = 0;
	int qs = 0, qe = 0;
	Q[qe++] = { R, C };
	chk[R][C] = 1;
	Q[qe++] = { -1, -1 };
	for (qs = 0; qs < qe; qs++)
	{
		if (Q[qs].x == -1)
		{
			cnt++;
			Q[qe++] = { -1, -1 };
			continue;
		}
		for (int i = 0; i < 8; i++)
		{
			int y = Q[qs].y + path[i].y;
			int x = Q[qs].x + path[i].x;

			if (chk[y][x] == 1 || y<1 || y>N || x<1 || x>M)
			{
				continue;
			}

			if (y == S && x == K)
				return cnt;

			chk[y][x] = 1;
			Q[qe++] = { y, x };
		}
	}
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d %d %d %d %d %d", &N, &M, &R, &C, &S, &K);

	printf("%d\n", solve()+1);
	return 0;
}