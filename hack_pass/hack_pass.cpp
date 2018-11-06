#include <iostream>

typedef unsigned long long ull;
ull ret;
int A, B;

void dfs(int cur, int r)
{
	if (cur >= B)
	{
		ret++;
		return;
	}
	if (B - cur > r)return;

}

int main()
{
	int TC;
	scanf("%d", &TC);
	for (int i = 0; i < TC; i++)
	{
		scanf("%d %d", &A, &B);
		ret = 0;
		dfs(0, A);
	}
}