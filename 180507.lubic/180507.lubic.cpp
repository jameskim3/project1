#include <iostream>

int a[4][4];
int ans = 8;
struct data {
	int rc, wi, ca;
} moves[9], ans_mov[9];
int f_count()
{
	int i, j, cnt = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (a[i][j] == i * 4 + j + 1) cnt++;
		}
	}
	return 16 - cnt;
}

void r_move(int x)
{
	int i, tmp = a[x][3];
	for (i = 3; i > 0; i--)
		a[x][i] = a[x][i - 1];
	a[x][0] = tmp;
}
void c_move(int y)
{
	int i, tmp = a[3][y];
	for (i = 3; i > 0; i--)
		a[i][y] = a[i - 1][y];
	a[0][y] = tmp;
}
void f(int n)
{
	int i, j, cnt = f_count();
	if (cnt > (ans - n - 1) * 4)
		return;
	if (cnt == 0)
	{
		ans = n;
		for (i = 0; i <= n; i++)
			ans_mov[i] = moves[i];
		return;
	}
	for (i = 0; i < 4; i++)
	{
		moves[n].wi = i + 1;
		for (j = 1; j < 4; j++)
		{
			moves[n].rc = 1;
			moves[n].ca = j;
			r_move(i);
			f(n + 1);
		}
		r_move(i);
		for (j = 1; j < 4; j++)
		{
			moves[n].rc = 2;
			moves[n].ca = j;
			c_move(i);
			f(n + 1);
		}
		c_move(i);
	}
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			scanf("%d", &a[i][j]);

	}
	f(0);
	printf("%d\n", ans);
	for (i = 0; i < ans; i++)
	{
		printf("%d %d %d\n", ans_mov[i].rc, ans_mov[i].wi, ans_mov[i].ca);
	}
	return 0;
}