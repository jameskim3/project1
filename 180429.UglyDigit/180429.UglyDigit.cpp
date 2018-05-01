#include <iostream>

typedef unsigned long long ULL;
ULL item[1000000];
void swap(int a, int b)
{
	ULL c = item[a];
	item[a] = item[b];
	item[b] = c;
}
void hpush(int pos)
{
	if (pos <= 1 || item[pos / 2] <= item[pos]) return;
	swap(pos, pos / 2);
	hpush(pos / 2);
}
void hpop(int pos, int n)
{
	int ch = pos * 2;
	if (ch<n && item[ch]>item[ch + 1]) ch++;
	if (ch > n || item[pos] < item[ch]) return;
	swap(pos, ch);
	hpop(ch, n);
}
ULL sol(int cnt)
{
	ULL ans = 1;
	int n = 1;
	int local = 1;
	item[1] = 1;

	while (1)
	{
		item[++n] = item[1] * 2; hpush(n);
		item[++n] = item[1] * 3; hpush(n);
		item[++n] = item[1] * 5; hpush(n);

		ans = item[1];
		if (local == cnt)
			break;

		while (1)
		{
			item[1] = item[n]; n--;
			hpop(1, n);
			if (item[1] != ans)
				break;
		}

		local++;
	}

	return ans;
}
int main()
{
	int n;
	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;

		printf("%llu\n", sol(n));
	}

	return 0;
}