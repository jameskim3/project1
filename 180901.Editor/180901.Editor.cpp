#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static char document[1024 * 1024 + 2];
static int DS;
static int SCORE = 0;
static int PANELTY = 0;
static int seed = 3;

static void verify(char* document);

extern void create();
extern void putChar(char a);
extern void putEnter();
extern void putBackSpace();
extern void moveUp(int n);
extern void moveDown(int n);
extern void moveLeft(int n);
extern void moveRight(int n);
extern void close(char* document);

static int peuso_rand()
{
	seed = (214013 * seed + 2531011);
	return (seed >> 16) & 32767;
}
int TC = 100;
int main()
{
	freopen("in.txt", "r", stdin);
	time_t start = clock();
	for (register int tc = 0; tc < TC; tc++)
	{
		create();
		DS = 0;
		int count = 0;
		int char_cnt;
		while (DS < 1024*1024 - 1)
		{
			if (peuso_rand() % 100 == 99)
			{
				putEnter();
				DS++;
			}
			if (peuso_rand() % 100 == 99)
			{
				switch (peuso_rand() % 4)
				{
				case 0: moveUp(peuso_rand() % 100); break;
				case 1: moveDown(peuso_rand() % 100); break;
				case 2: moveLeft(peuso_rand() % 100); break;
				case 3: moveRight(peuso_rand() % 100); break;
				}
			}
			if (peuso_rand() % 100 == 99)
			{
				if (DS != 0)
				{
					putBackSpace();
					DS--;
				}
			}
			putChar('A' + peuso_rand() % 26);
			DS++;
		}
		close(document);
		verify(document);
	}
	SCORE += (clock() - start) / (CLOCKS_PER_SEC / 1000);
	printf("SCORE:%d", SCORE + PANELTY);
}
static void verify(char* document)
{
	unsigned long hash = 5381;
	for (int i = 0; i < 1024 * 1024 - 1; i++)
	{
		hash = (((hash << 5) + hash) + document[i]) % 2531011;
	}

	printf("\n%d", hash);
	int ans_val;
	scanf("%d", &ans_val);
	if (hash != ans_val)
		PANELTY += 1000000;
}

/*
1239608 661 111 98 102 69 175 87 3 483 31
1459589 110 33 234 3 6 449 149 13 51 253
256761 96 66 233 1 66 6 46 74 20
*/