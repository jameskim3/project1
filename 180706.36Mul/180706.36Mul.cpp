#include <iostream>
#include <time.h>

char SRC[256];
char TAR[256];
char RET[600];
char RET2[600];
#define MIN 64//64
#define MAX 128//128
extern void mat(char ret[600], char src[256], char tar[256]);
extern void mat2(char ret[600], char src[256], char tar[256]);
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

char* sd[5][2] = {
	{ "A", "ABCSSDHSWHW4563457RTJHERJHRJHE56767856785JTYJRETYJRTYJRTYJRTYURTYU2456345764567856785667985679567089" },
	{ "A", "ABCSSDHSWHW4563457RTJHERJHRJHE56767856785JTYJRETYJRTYJRTYJRTYURTYU245634576456785678566798567956708A" },
	{ "A", "ABCSSDHSWHW4563457RTJHERJHRJHE56767856785JTYJRETYJRTYJRTYJRTYURTYU245634576456785678566798567956708B" },
	{ "A", "ABCSSDHSWHW4563457RTJHERJHRJHE56767856785JTYJRETYJRTYJRTYJRTYURTYU245634576456785678566798567956708C" },
	{ "A", "ABCSSDHSWHW4563457RTJHERJHRJHE56767856785JTYJRETYJRTYJRTYJRTYURTYU245634576456785678566798567956708D" }
};

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
	initArr(); 
	int i, j;
	ULL src_val, tar_val,ret_val;
	time_t s = clock();
	int SCORE = 100;
	for (int tc = 0; tc < 10; tc++)
	{
		for(int rep = 0; rep < 10000; rep++)
		{
			memset(SRC, 0, sizeof(SRC));
			memset(TAR, 0, sizeof(TAR));
			memset(RET, 0, sizeof(RET));
			memset(RET2, 0, sizeof(RET2));

			int a = MIN + rand() % (MAX - MIN);
			int b = MIN + rand() % (MAX - MIN);
			
			//int cnt = 0;
			//while (1)
			//{
			//	if (sd[rep % 5][0][cnt] == 0)break;
			//	SRC[cnt] = sd[rep % 5][0][cnt++];
			//}
			//cnt = 0;
			//while (1)
			//{
			//	if (sd[rep % 5][1][cnt] == 0)break;
			//	TAR[cnt] = sd[rep % 5][1][cnt++];
			//}


			for (i = 0; i < a; i++)
			{
				SRC[i] = makeChar(i);
			}
			for (i = 0; i < b; i++)
			{
				TAR[i] = makeChar(i);
			}

			mat(RET, SRC, TAR);
			mat2(RET2, SRC, TAR);

			if (mystrcmp(RET, RET2) == 0)SCORE--;
		}
	}
	time_t e = clock();
	double PERFORMANCE = (e - s) / 1000.0;
	printf("Score:%d time: %.3f, ", SCORE, PERFORMANCE);
}

