#include <iostream>

int item[5][5];
struct data1 {
	int dir;
	int order;
	int num;
}ans_path[10],tmp_path[10];

int ans=8;

int fault_cnt()
{
	int f = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (item[i][j] != i * 4 + j + 1)
				f++;
	return f;
}

void dfs(int n)
{
	int f = fault_cnt();
	if (f > (ans - n - 1) * 4)
		return;
	if (f == 0)
	{
		ans = n;
		for (int i = 0; i < n; i++)
			ans_path[i] = tmp_path[i];
		return;
	}

	int dir = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			tmp_path[n].dir = dir;
			tmp_path[n].num= j;
			tmp_path[n].order = i+1;

			int tmp[10];
			for (int k = 0; k < 4; k++)
				tmp[(k + j)%4] = item[i][k];
			for (int k = 0; k < 4; k++)
				item[i][k] = tmp[k];
			
			dfs(n + 1);

			for (int k = 0; k < 4; k++)
				tmp[(k + (4-j)) % 4] = item[i][k];
			for (int k = 0; k < 4; k++)
				item[i][k] = tmp[k];
		}
	}
	dir = 2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			tmp_path[n].dir = dir;
			tmp_path[n].num = j;
			tmp_path[n].order = i+1;

			int tmp[10];
			for (int k = 0; k < 4; k++)
				tmp[(k + j) % 4] = item[k][i];
			for (int k = 0; k < 4; k++)
				item[k][i] = tmp[k];

			dfs(n + 1);

			for (int k = 0; k < 4; k++)
				tmp[(k + (4 - j)) % 4] = item[k][i];
			for (int k = 0; k < 4; k++)
				item[k][i] = tmp[k];
		}
	}
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	for (int i =0; i < 4; i++)
		for (int j =0; j < 4; j++)
			scanf("%d", &item[i][j]);

	dfs(0);

	printf("%d\n", ans);
	for (int i = 0; i < ans; i++)
	{
		printf("%d %d %d\n", ans_path[i].dir, ans_path[i].order, ans_path[i].num);
	}
}