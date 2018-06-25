#include <iostream>

struct data1
{
	int s, e, v;
	bool operator<(const data1 &r) const {
		return s < r.s;
	}
}item[10000+10],buff[10000+10];
int N, C, M;

void msort(int s, int e)
{
	if (s >= e)		return;
	int m = (s + e) / 2;
	msort(s, m);
	msort(m + 1, e);

	int i, j, k;
	i = k = s;
	j = m+1;
	while (i <= m && j <= e) item[i].e < item[j].e ? buff[k++] = item[i++] : buff[k++] = item[j++];
	while (i <= m) buff[k++] = item[i++];
	while (j <= e) buff[k++] = item[j++];

	for (int t = s; t <= e; t++)
		item[t] = buff[t];
}
int greedy()
{
	int cnt = 0;
	int capa[2000 + 10] = { 0 };

	for (int i = 1; i <= M; i++)
	{
		int empty = 9999999, load;
		int s = item[i].s, e = item[i].e;
		for (int j = s; j < e; j++)
		{
			if (C - capa[j] < empty)
				empty = C - capa[j];
		}
		if (empty < 0)
			empty = 0;

		if (empty >= item[i].v)
			load = item[i].v;
		else
			load = empty;

		cnt += load;
		for (int j = s; j < e; j++)
			capa[j] += load;
	}

	return cnt;
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif

	scanf("%d %d %d", &N, &C, &M);
	for (int i = 1; i <= M; i++)
	{
		scanf("%d %d %d", &item[i].s, &item[i].e, &item[i].v);
	}

	msort(1, M);

	printf("%d\n", greedy());

	return 0;
}