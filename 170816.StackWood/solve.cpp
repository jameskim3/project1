
#include <algorithm>
#define LL long long
#define N 30000

const LL sav = 2222222222222222;

struct data {
	int num, h;
	LL p;
} a[N], b[N];

LL Min(LL a, LL b)
{
	return a > b ? b : a;
}

LL Max(LL a, LL b)
{
	return a > b ? a : b;
}

bool comp1(const data &l, const data &r)
{
	if (l.p != r.p)
		return l.p < r.p;
	else
		return l.h > r.h;
}
bool comp2(const data &l, const data &r)
{
	if (l.p != r.p)
		return l.p > r.p;
	else
		return l.h > r.h;
}

void rot(int m[][4])
{
	int i, j, x[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			x[i][j] = m[3 - j][i];
		}
	}
}

void cnt_block(int n, int m[][4])
{
	int i, j, r[4][4];
	LL p, q;
	a[n].num = b[n].num = n;
	a[n].h = 10;
	a[n].p = sav;
	b[n].h = 0;
	b[n].p = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			a[n].h = Min(a[n].h, m[i][j]);
			b[n].h = Max(b[n].h, m[i][j]);
		}
	}
	b[n].h -= 2;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			r[i][j] = m[i][j] - b[n].h;
			m[i][j] -= a[n].h;
		}
	}
	for (int k = 0; k < 4; k++)
	{
		p = 0;
		q = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				p = p * 10 + m[i][j];
				q = q * 10 + r[i][3 - j];
			}
		}
		a[n].p = Min(a[n].p, p);
		b[n].p = Max(b[n].p, q);
		rot(m);
		rot(r);
	}
}

bool chk[N];
int makeTree(int module[][4][4])
{
	int i, j, k, ans = 0;
	for (i = 0; i < N; i++)
		cnt_block(i, module[i]);

	std::sort(a, a + N, comp1);
	std::sort(b, b + N, comp2);

	i = j = 0;
	while (i < N && j < N)
	{
		if (chk[a[i].num])
			i++;
		else if (chk[b[j].num])
			j++;
		else if (a[i].num == b[j].num)
			i++;
		else if (a[i].p + b[j].p < sav)
			i++;
		else if (a[i].p + b[j].p > sav)
			j++;
		else
		{
			ans += a[i].h + b[j].h + 2;
			chk[a[i].num] = chk[b[j].num] = true;
			i++;
			j++;
		}
	}

	return ans;
}