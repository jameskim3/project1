#include <iostream>
#include <time.h>

char SRC[256];
char TAR[256];
char RET[600];
char RET2[600];
#define MIN 64//64
#define MAX 128//128
extern void mat(char ret[600], char src[256], char tar[256]);
void mat2(char ret[600], char src[256], char tar[256]);
typedef unsigned long long ULL;
ULL N_Num = 36;
ULL ARR[12];
int DIV = 6;

int seed = 3;
static int pseudo_rand()
{
	seed = (214013 * seed + 2531011);
	return (seed >> 16) & 32767;
}
void initArr()
{
	int i;
	ARR[0] = 1;
	for (i = 1; i < 12; i++)
		ARR[i] = ARR[i - 1] * N_Num;
}
char makeChar(int n)
{
	char c;
	while (1)
	{
		c = pseudo_rand() % N_Num;
		if (n == 0 && c == 0)continue;
		if (c < 10) c += '0';
		else c += 'A' - 10;
		break;
	}
	return c;
}
int changeInt(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A' + 10;

	return n;
}
char changeChar(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A' - 10;

	return c;
}
int mystrcmp(char* a, char* b)
{
	int cnt = 0;
	while (a[cnt] != 0)
	{
		if (a[cnt] != b[cnt])
			break;
		cnt++;
	}
	if (a[cnt] == b[cnt])
		return 1;
	else
		return 0;

}
int main()
{
	freopen("o.txt", "r", stdin);
	initArr();
	int i, j;
	ULL src_val, tar_val, ret_val;
	time_t s = clock();
	int SCORE = 100;
	for (int tc = 0; tc < 10; tc++)
	{
		int verify = 0;
		for (int rep = 0; rep < 10000; rep++)
		{
			memset(SRC, 0, sizeof(SRC));
			memset(TAR, 0, sizeof(TAR));
			memset(RET, 0, sizeof(RET));
			memset(RET2, 0, sizeof(RET2));

			int a = MIN + pseudo_rand() % (MAX - MIN);
			int b = MIN + pseudo_rand() % (MAX - MIN);

			for (i = 0; i < a; i++)
			{
				SRC[i] = makeChar(i);
			}
			for (i = 0; i < b; i++)
			{
				TAR[i] = makeChar(i);
			}

			mat(RET, SRC, TAR);
			//test
			//mat2(RET2, SRC, TAR);
			//int tret = mystrcmp(RET, RET2);
			//if (tret == 0)SCORE--;

			verify = (verify+RET[pseudo_rand() % MIN])%32768;
		}
		int tmp;
		scanf("%d", &tmp);
		if (verify != tmp)SCORE -= 10;
	}
	time_t e = clock();
	double PERFORMANCE = (e - s) / 1000.0;
	printf("Score:%d time: %.3f, ", SCORE, PERFORMANCE);
}



//////////////////////////////////////////////////////////
int changeInt3(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A' + 10;

	return n;
}
char changeChar3(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A' - 10;

	return c;
}

void mat2(char ret[600], char src[256], char tar[256])
{
	int len1, len2;
	len1 = strlen(src);
	len2 = strlen(tar);
	int ret2[600] = { 0 };
	for (int i = len1 - 1; i >= 0; i--)
	{
		for (int j = len2 - 1; j >= 0; j--)
		{
			int p1 = len1 - 1 - i;
			int p2 = len2 - 1 - j;
			int val = changeInt3(src[i]) * changeInt3(tar[j]);
			ret2[p1 + p2] += val;
		}
	}
	int pos = 0;
	for (int i = 0; i < len1 + len2; i++)
	{
		if (ret2[i] != 0)pos = i;
		ret2[i + 1] += (ret2[i] / 36);
		ret2[i] = ret2[i] % 36;
	}
	for (int i = pos; i >= 0; i--)
	{
		int p1 = pos - i;
		ret[p1] = changeChar3(ret2[i]);
	}
}