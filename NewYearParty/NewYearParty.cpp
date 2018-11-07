#include <iostream>

int TC, B, L, N;
int map[401][2];
double dp[2][80200 + 10];
int fi[80200 + 10];

int main()
{
	freopen("in.txt", "r", stdin);

	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		int S = 0;
		int E = 1;

		scanf("%d %d %d", &B, &L, &N);

		for (int s = 0; s < 2; s++)
			for (int t = 0; t < 80200 + 10; t++)
				dp[s][t] = 0.;

		int cnt = 1;
		int f = 1;
		while (cnt < 80200)
		{
			for (int i = 0; i < f; i++)
				fi[cnt++] = f;
			f++;
		}

		int sum = 1;
		double tmp = 0.;
		dp[S][1] = 750.0*B;
		for (int f = 1; f < L; f++, sum += f)
		{
			for (int t = 1; t <= sum; t++)
				dp[E][t] = 0.;

			for (int i = 1; i <= sum; i++)
			{
				if (dp[S][i]>250.0)
				{
					tmp = (dp[S][i] - 250.0) / 3.0;
					dp[E][i] += tmp;
					dp[E][i + fi[i]] += tmp;
					dp[E][i + fi[i]+ 1] += tmp;
				}
			}
			S = 1 - S;
			E = 1 - E;
		}
		double ret = dp[S][N];
		if (ret >= 250.0)ret = 250.0;
		printf("#%d %.8f\n", tc + 1, ret);
	}
	return 0;
}