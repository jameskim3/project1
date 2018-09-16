#include <iostream>
#include <time.h>

extern void init(int N, int M, int K);
extern void addPiece(int piece[]);
extern int findCenterPiece();

static int mSeed;
static int pseudo_rand()
{
	mSeed = mSeed * 431345 + 2531999;
	return mSeed & 0x7FFFFFFF;
}

static int run()
{
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	init(N, M, K);
	int piece[60];

	for (int i = 0; i < N*N + K; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			scanf("%d", &mSeed);
			int idx = k*M;
			piece[idx] = piece[idx + M - 1] = 0;
			if (mSeed > 0)
			{
				for (int m = 1; m < M - 1; m++)
					piece[idx + m] = pseudo_rand() % 3 - 1;
			}
			else
			{
				mSeed *= -1;
				for (int m = M - 2; m > 0; --m)
					piece[idx + m] = 1 - pseudo_rand() % 3;
			}
		}
		addPiece(piece);
	}
	int result = findCenterPiece();
	return result;
}

int piece[49 * 49 + 10][60];

int ans = 0;
static int run2()
{
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	init(N, M, K);
	mSeed = rand() % 32767;

	for (int i = 0; i < N*N + K; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			int idx = k*M;
			piece[i][idx] = piece[i][idx + M - 1] = 0;
			for (int m = 1; m < M - 1; m++)
				piece[i][idx + m] = pseudo_rand() % 3 - 1;
		}
	}
	for (int i = 0; i < N*N; ++i)
	{
		if (i / N == 0)continue;
		for (int k = 0; k < M; k++)
		{
			piece[i][k] = -1 * (piece[i - N][k + 2 * M]);
		}
	}
	for (int i = 0; i < N*N; ++i)
	{
		if (i%N == 0)continue;
		for (int k = 0; k < M; k++)
		{
			piece[i][k + 3 * M] = -1 * (piece[i - 1][k + 1 * M]);
		}
	}
	int chk[49 * 49 + 20] = { 0 };
	int cnt = 0;
	while (cnt < N*N + K)
	{
		int r = pseudo_rand() % (N*N + K);
		if (chk[r])continue;
		chk[r] = 1;
		addPiece(piece[r]);
		if (r == N*N / 2)
			ans = cnt;
		cnt++;
	}

	int result = findCenterPiece();
	return result;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("in.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	time_t start = clock();
	for (int t = 0; t < T; t++)
	{
		printf("#%d %d %d\n", t, ans, run2());
	}
	time_t end = clock();
	int performance = (end - start);
	printf("Performance %d\n", performance);
	return 0;
}
