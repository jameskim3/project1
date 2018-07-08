#include <iostream>
#include <time.h>

char SRC[256];
char TAR[256];
char RET[600];
#define MIN 64
#define MAX 128
extern void mat(char ret[600], char src[256], char tar[256]);
typedef unsigned long long ULL;
ULL N_Num = 36;
ULL ARR[12];
int DIV = 6;

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
		c = rand() % N_Num;
		if (n == 0 && c == 0)continue;
		if (c < 10) c += '0';
		else c += 'A'-10;
		break;
	}
	return c;
}

int changeInt(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A'+10;

	return n;
}
char changeChar(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A'-10;

	return c;
}

int main()
{
	initArr(); 
	int i, j;
	ULL src_val, tar_val,ret_val;
	time_t s = clock();
	for (int tc = 0; tc < 10; tc++)
	{
		for(int rep = 0; rep < 10000; rep++)
		{
			memset(SRC, 0, sizeof(SRC));
			memset(TAR, 0, sizeof(TAR));
			memset(RET, 0, sizeof(RET));

			int a = MIN + rand() % (MAX - MIN);
			int b = MIN + rand() % (MAX - MIN);

			for (i = 0; i < a; i++)
			{
				SRC[i] = makeChar(i);
			}
			for (i = 0; i < b; i++)
			{
				TAR[i] = makeChar(i);
			}

			mat(RET, SRC, TAR);

			j = strlen(RET);
		}
		printf("%d: %s, %llu\n", tc, RET);
	}
	time_t e = clock();
	printf("time: %.3f", (e - s) / 1000.0);
}