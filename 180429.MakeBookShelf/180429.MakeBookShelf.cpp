#include <iostream>

int N;
int heap_n;

typedef unsigned long long ULL;
int item[200000];

void swap(int a, int b)
{
	ULL c = item[a];
	item[a] = item[b];
	item[b] = c;
}
void push(int pos)
{
	if (pos <= 1 || item[pos] > item[pos / 2]) return;
	swap(pos, pos / 2);
	push(pos / 2);
}
void pop(int pos, int n)
{
	int ch = pos * 2;
	if (ch<n && item[ch]>item[ch + 1]) ch += 1;
	if (ch> n || item[pos] < item[ch]) return;
	swap(pos, ch);
	pop(ch, n);
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	scanf("%d", &N);
	int temp;
	heap_n = 0;
	for (int i = 1; i <= N; i++)
	{
		heap_n++;
		scanf("%d", &temp);
		item[heap_n] = temp;
		push(heap_n);
	}

	ULL ans = 0;
	while (heap_n > 1)
	{
		temp = 0;
		for (int i = 0; i < 2; i++)
		{
			temp += item[1];
			item[1] = item[heap_n--];
			pop(1, heap_n);
		}
		ans += temp;
		item[++heap_n] = temp;
		push(heap_n);
	}

	printf("%llu", ans);

	return 0;
}