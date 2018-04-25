#include <iostream>
#include <time.h>
using namespace std;

typedef unsigned long long ULL;

ULL item[2000000+10];
ULL buf[2000000 + 10];

void swap(int a, int b)
{
	ULL c = item[a];
	item[a] = item[b];
	item[b] = c;
}
void push_heap(int pos)
{
	if (pos <= 1 || item[pos / 2] >= item[pos]) return;

	swap(pos, pos / 2);

	push_heap(pos / 2);
}

void pop_heap(int pos, int n)
{
	int ch = pos * 2;
	if (ch < n && item[ch] < item[ch + 1])  ch++;
	if (ch > n || item[pos] >= item[ch]) return;

	swap(pos, ch);
	pop_heap(ch, n);
}

ULL M = 20000;

void msort(int s, int e)
{
	if (s >= e) return;

	int i, j, k, m;
	m = (s + e) / 2;

	msort(s, m);
	msort(m + 1, e);

	i = s;
	j = m + 1;
	k = s;

	while (i <= m && j <= e) item[i] < item[j] ? buf[k++] = item[i++] : buf[k++] = item[j++];
	while (i <= m) buf[k++] = item[i++];
	while (j <= e) buf[k++] = item[j++];

	for (int t = s; t <= e; t++)
		item[t] = buf[t];
}

int main()
{
	//heap sort
	time_t start = clock();
	for (int i = 1; i <= M; i++)
	{
		item[i] = rand();
		push_heap(i);
	}

	//heap sort
	for (int i = M; i > 1; i--)
	{
		swap(1, i);
		pop_heap(1, i - 1);
	}

	for (int i = 1; i < M; i++)
	{
		if (item[i] > item[i + 1])
			printf("bad\n");
	}

	printf("ellapse(heap sort) : %.1f\n", double((clock() - start))/CLOCKS_PER_SEC);


	//merge sort
	start = clock();
	for (int i = 1; i <= M; i++)
	{
		item[i] = rand();
	}

	msort(1, M);
	for (int i = 1; i < M; i++)
	{
		if (item[i] > item[i + 1])
			printf("bad\n");
	}
	printf("ellapse(merge sort) : %.1f\n", double((clock() - start)) / CLOCKS_PER_SEC);

	//insert sort
	start = clock();
	for (int i = 1; i <= M; i++)
	{
		item[i] = rand();
	}

	for (int i = 1; i < M; i++)
	for(int j = i; j < M; j++)
	{
		if (item[i] > item[j])
			swap(i, j);
	}
	for (int i = 1; i < M; i++)
	{
		if (item[i] > item[i + 1])
			printf("bad\n");
	}
	printf("ellapse(insert sort) : %.1f", double((clock() - start)) / CLOCKS_PER_SEC);

	return 0;
}