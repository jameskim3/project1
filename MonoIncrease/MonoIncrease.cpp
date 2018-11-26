#include <iostream>

int map[30000 + 10];
int buf[30000 + 10];
int N;
void msort(int s, int e)
{
	if (s >= e)return;
	int i, j, k, mid;
	mid = (s + e) / 2;
	msort(s, mid);
	msort(mid + 1, e);
	i = k = s;
	j = mid+1;

	while (i <= mid && j <= e)
		buf[k++] = map[i] > map[j] ? map[i++] : map[j++];
	while (i <= mid)
		buf[k++] = map[i++];
	while (j <=e)
		buf[k++] = map[j++];

	for (int c = s; c <= e; c++)
		map[c] = buf[c];
}
int mono(int v)
{
	int digit[100];
	int cnt = 0;
	while (v > 0)
	{
		digit[cnt++] = v % 10;
		v /= 10;
	}
	int vali = 1;
	for (int i = 0; i < cnt-1; i++)
	{
		if (digit[i] < digit[i + 1])return 0;
	}
	return 1;
}
int main()
{
	int TC;
	freopen("in.txt", "r", stdin);
	scanf("%d", &TC);
	for (int i = 0; i < TC; i++)
	{
		scanf("%d", &N);
		for (int j = 0; j < N;j++)
			scanf("%d", &map[j]);

		msort(0,N-1);
		int max = 0;
		int t1 = 0;
		int t2 = N-1;
		for (int j = 0; j < N;j++)
		{
			for (int k = j + 1; k < N && k<t2; k++)
			{
				int cal = map[j] * map[k];
				if ( cal > max && mono(cal))
				{
					t1 = j, t2 = k;
					max = map[j] * map[k];
				}
			}
		}
		if (max == 0)max = -1;
		printf("#%d %d\n", i + 1, max);
	}
}