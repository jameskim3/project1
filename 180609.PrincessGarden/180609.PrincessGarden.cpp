#include <iostream>

int N;
struct data1
{
	int s, e;
} item[100010],buff[100010];

void msort(int s, int e)
{
	if (s >= e)
		return;
	int mid;
	mid = (s + e) / 2;
	msort(s, mid);
	msort(mid + 1, e);

	int i = s, j = mid + 1, k = s;
	while (i <= mid && j <= e)
	{
		item[i].s < item[j].s ? buff[k++] = item[i++] : buff[k++] = item[j++];
	}
	while (i <= mid) buff[k++] = item[i++];
	while (j <= e) buff[k++] = item[j++];

	for (int t = s; t <= e; t++)
		item[t] = buff[t];
}
int greedy()
{
	int flag = 301;
	int max_end = 0;
	int cnt = 1;
	for (int i = 1; i <= N; i++)
	{
		if (item[i].s <= flag)
		{
			if (max_end < item[i].e)
				max_end = item[i].e;
		}
		else
		{
			cnt++;
			flag = max_end;
			if (item[i].s>flag)
				return 0;
			max_end = item[i].e;
		}
		if (max_end > 1130)
			return cnt;
	}
	return 0;
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	int sm, sd, em, ed;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d %d %d", &sm, &sd, &em, &ed);
		item[i].s = sm * 100 + sd;
		item[i].e = em * 100 + ed;
	}

	msort(1, N);

	printf("%d\n", greedy());
}