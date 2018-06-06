#include <iostream>

int N, M;
int x[1100], y[1100];
int Q[2200];

int ans;

int dis(int a, int b)
{
	int t1 = x[a] - x[b];
	int t2 = y[a] - y[b];
	return (t1*t1) + (t2*t2);
}

int check(int mid)
{
	int chk[2200] = { 0 }, qe = 0;
	int cnt = 0;
	Q[qe++] = 0;
	Q[qe++] = -1;
	for (int qs = 0; qs < qe; qs++)
	{
		if (Q[qs] == -1)
		{
			cnt++;
			if (cnt > M) return 0;
			Q[qe++] = -1;
			continue;
		}

		for (int j = 1; j <= N; j++)
		{
			int t1 = Q[qs];
			if (chk[j] == 0 && dis(Q[qs], j) <= mid*mid * 100)
			{
				Q[qe++] = j;
				chk[j] = 1;
				if (j == N)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int main()
{
#ifdef _WIN32
	freopen("in2.txt", "r", stdin);
#endif
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &x[i], &y[i]);
	}
	N++;
	x[N] = 10000; y[N] = 10000;

	int s = 1, e = 1500;
	int mid;
	while (s <= e)
	{
		mid = (s + e) / 2;
		if (check(mid) == 1)
		{
			e = mid - 1;
			ans = mid;
		}
		else
		{
			s = mid + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}