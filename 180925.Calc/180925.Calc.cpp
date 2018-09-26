#include <iostream>

int TC = 100;
int SCORE;

extern void run(char *a, char *b);
void make_str(char* r, int a)
{
	r[0] = 0;
	int cnt = 0;
	char buf[1024];
	while (a > 0)
	{
		buf[cnt++] = a % 10;
		a = a / 10;
	}
	for (int i = 0; i < cnt; i++)
		r[i] = buf[cnt - 1 - i]+'0';
	r[cnt] = 0;
}
int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	char query[1024], ret[1024], ans[1024];
	char a[1024], b[1024], r[1024];
	scanf("%d", &TC);
	for (int tc = 0; tc < TC; tc++)
	{
		scanf("%s %s", query, ans);
		run(ret, query);
		if (strcmp(ans, ret) == 0)
			SCORE += 1;
		else
			SCORE -= 10000;
	}
	printf("SCORE: %d\n", SCORE);
}
