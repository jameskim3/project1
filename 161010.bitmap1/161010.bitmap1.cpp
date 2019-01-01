
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <memory.h> 
#define NN 4096 
#define NM 256 

extern void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN]);
extern void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8]);

static void setpixel(unsigned char bitmap[NM][NM / 8], int x, int y, int pixel)
{
	unsigned char mask = 0x80 >> (x % 8);

	if (pixel == 0) bitmap[y][x / 8] &= ~mask;
	else bitmap[y][x / 8] |= mask;
}

static int getpixel(unsigned char bitmap[NM][NM / 8], int x, int y)
{
	unsigned char mask = 0x80 >> (x % 8);

	if ((bitmap[y][x / 8] & mask) == 0) return 0;
	else return 1;
}

static void noise(unsigned char bitmap[NM][NM / 8])
{
	for (register int y = 0; y < NM; y += 2)
		for (register int x = 0; x < NM; x += 2)
		{
			setpixel(bitmap, x + rand() % 2, y + rand() % 2, 0);
			setpixel(bitmap, x + rand() % 2, y + rand() % 2, 1);
		}
}

void rotate(unsigned char bitmap[NM][NM / 8], int angle)
{
	static unsigned char buffer[NM][NM / 8];

	if (angle != 0)
	{
		switch (angle)
		{
		case 1: // 90 
			for (register int y = 0; y < NM; y++)
				for (register int x = 0; x < NM; x++)
					setpixel(buffer, x, y, getpixel(bitmap, y, NM - 1 - x));
			break;
		case 2: // 180 
			for (register int y = 0; y < NM; y++)
				for (register int x = 0; x < NM; x++)
					setpixel(buffer, x, y, getpixel(bitmap, NM - 1 - x, NM - 1 - y));
			break;
		case 3: // 270 
			for (register int y = 0; y < NM; y++)
				for (register int x = 0; x < NM; x++)
					setpixel(buffer, x, y, getpixel(bitmap, NM - 1 - y, x));
			break;
		}

		for (register int y = 0; y < NM; y++)
			for (register int x = 0; x < NM; x++)
				setpixel(bitmap, x, y, getpixel(buffer, x, y));
	}
}

void flip(unsigned char bitmap[NM][NM / 8], int mode)
{
	static unsigned char buffer[NM][NM / 8];

	if (mode != 0)
	{
		switch (mode)
		{
		case 1: // horizontal 
			for (register int x = 0; x < NM; x++)
				for (register int y = 0; y < NM; y++)
					setpixel(buffer, x, y, getpixel(bitmap, x, NM - 1 - y));
			break;
		case 2: // vertical 
			for (register int y = 0; y < NM; y++)
				for (register int x = 0; x < NM; x++)
					setpixel(buffer, x, y, getpixel(bitmap, NM - 1 - x, y));
			break;
		}

		for (register int y = 0; y < NM; y++)
			for (register int x = 0; x < NM; x++)
				setpixel(bitmap, x, y, getpixel(buffer, x, y));
	}
}

int main(void)
{
	static const int TCSIZE = 1024;

	static unsigned char data[TCSIZE][NN] = { 0 };
	static unsigned char org[TCSIZE][NN] = { 0 };
	static unsigned char result[TCSIZE][NN] = { 0 };
	static unsigned char bitmap[TCSIZE][NM][NM / 8] = { 0 };

	srand(1); // The seed will be changed. 

	for (register int TC = 0; TC < TCSIZE; TC++)
		for (register int c = 0; c < NN; c++)
			org[TC][c] = data[TC][c] = rand() % 15;

	int PERFORMANCE = 10000;

	time_t start = clock();
	for (register int TC = 0; TC < TCSIZE; TC++)
		encode(bitmap[TC], data[TC]);
	PERFORMANCE -= (clock() - start) / (CLOCKS_PER_SEC / 1000);

	for (register int TC = 0; TC < TCSIZE; TC++)
	{
		noise(bitmap[TC]);
		rotate(bitmap[TC], rand() % 4);
		flip(bitmap[TC], rand() % 3);
	}

	start = clock();
	for (register int TC = 0; TC < TCSIZE; TC++)
		decode(result[TC], bitmap[TC]);
	PERFORMANCE -= (clock() - start) / (CLOCKS_PER_SEC / 1000);
	int PASS = 0;

	for (register int TC = 0; TC < TCSIZE; TC++)
	{
		if (memcmp(org[TC], result[TC], NN) == 0)
			PASS++;
	}

	printf("SCORE: %d\n", PASS * 10000 + PERFORMANCE);
}