//TOTAL = 1642.4406854700, PERFORMANCE = -40026

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <algorithm> 

const int FLOOR = 10000;

int p[3] = { 0, };//shelter
int g[3] = { 0, };//group sum
int sum[10002] = { 0, }; //partial sum
int num[10002] = { 0, }; //room count copied from house

struct data {
	int num, cnt, cost, target;
	bool operator<(const data &r) const
	{
		return cost * r.cnt < r.cost * cnt; // cost/cnt < r.cost/r.cnt
	}
}a[20010];

int abs(int x) { return x>0 ? x : -x; }

void moves(int house[10000], int idx, int cnt)
{
	int i, j, k, an = 0, chk[10000] = { 0, };
	for (i = 0; i < 10000; i++)
	{
		if (num[i] == idx)
		{
			a[an].num = i;
			a[an].cnt = house[i];
			if (idx == 1)
			{
				//to 0
				a[an].cost = abs(p[0] - i) - abs(p[idx] - i);
				a[an].target = 0;
				an++;
				a[an] = a[an - 1];
				a[an].cost = abs(p[2] - i) - abs(p[1] - i);
				a[an].target = 2;
			}
			else
			{
				a[an].cost = abs(p[1] - i) - abs(p[idx] - i);
				a[an].target = 1;
			}
			an++;
		}
	}
	std::sort(a, a + an);
	for (i = 0; cnt > 0 && i < an; i++)
	{
		if (idx == 1 && (chk[a[i].num] || g[a[i].target] + a[i].cnt > 20000))
			continue;

		num[a[i].num] = a[i].target;
		g[idx] -= a[i].cnt;
		g[a[i].target] += a[i].cnt;
		cnt -= a[i].cnt;
		chk[a[i].num] = 1;
	}

	for (--i; i >= 0; i--)
	{
		if (cnt + a[i].cnt <= 0)
		{
			num[a[i].num] = idx;
			g[idx] += a[i].cnt;
			g[a[i].target] -= a[i].cnt;
			cnt += a[i].cnt;
			if (cnt == 0) break;
		}
	}
}

void assign(int house[FLOOR][10000])
{
	int i, j, k = 0, f;
	for (f = 0; f < FLOOR; f++)
	{
		k = 0;
		sum[0] = house[f][0];
		if (house[f][0] == 0)
			p[k++] = 0;
		for (i = 1; i < 10000; i++)
		{
			if (house[f][i] == 0)
				p[k++] = i;
			sum[i] = sum[i - 1] + house[f][i];
		}

		int flag1, flag2;
		flag1 = (p[0] + p[1]) / 2;
		flag2 = (p[1] + p[2]) / 2;
		g[0] = sum[flag1];
		g[1] = sum[flag2] - sum[flag1];
		g[2] = sum[9999] - sum[flag2];

		for (i = 0; i <= flag1; i++)
			num[i] = 0;
		for (; i <= flag2; i++)
			num[i] = 1;
		for (; i < 10000; i++)
			num[i] = 2;

		if (g[0]>20000)
			moves(house[f], 0, g[0] - 20000);
		if (g[2] > 20000)
			moves(house[f], 2, g[2] - 20000);
		if (g[1] > 20000)
			moves(house[f], 1, g[1] - 20000);

		for (i = 0; i < 10000; i++)
			house[f][i] = p[num[i]];

		house[f][p[0]] = house[f][p[1]] = house[f][p[2]] = 0;
	}
}