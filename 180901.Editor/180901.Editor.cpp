#include <iostream>
#include <time.h>

const int MAX_STR = 1024 * 1024;
const int MAX_TABLE = 300000;

extern void putChar(char a);
extern void putEnter();
extern void putBackSpace();
extern void moveUp(int n);
extern void moveDown(int n);
extern void moveLeft(int n);
extern void moveRight(int n);
extern void write(char a[MAX_STR], int *n);
char textData[MAX_STR];
int cn;

unsigned long hash(const char *str, int n)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}
unsigned int peuso_rand()
{
	static unsigned int nSeed = 5323;

	// Take the current seed and generate a new value from it
	// Due to our use of large constants and overflow, it would be
	// very hard for someone to predict what the next number is
	// going to be from the previous one.
	nSeed = (8253729 * nSeed + 2396403);

	// Take the seed and return a value between 0 and 32767
	return nSeed % 32767;
}
int TC = 30;
int main()
{
	//freopen("out.txt", "w", stdout);
	time_t start = clock();
	for (int tc = 0; tc < TC; tc++)
	{
		int MS = 0;
		int cs;
		while (MS < MAX_STR)
		{
			if (peuso_rand() % 100 == 99)
			{
				putEnter();
				MS++;
			}
			else if (peuso_rand() % 100 == 99)
			{
				if (MS != 0)
				{
					putBackSpace();
				}
			}
			else if (peuso_rand() % 100 == 99)
			{
				switch (peuso_rand() % 4)
				{
				case 0: moveUp(peuso_rand() % 100); break;
				case 1: moveDown(peuso_rand() % 100); break;
				case 2: moveLeft(peuso_rand() % 100); break;
				case 3: moveRight(peuso_rand() % 100); break;
				}
			}
			putChar('A' + peuso_rand() % 26);
			MS++;
		}
		cn = 0;
		write(textData, &cn);
		//unsigned int h = hash(textData, cn);
		//printf("\n%2d: %ul", tc, h);
	}
	int Performance = (clock() - start) / (1000 / CLOCKS_PER_SEC);
	printf("Perfomance:%d", Performance);
}