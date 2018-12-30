//SCORE: 9834
#define NN 4096 
#define NM 256 

void setpixel(unsigned char bitmap[NM][NM / 8], int x, int y, int pixel)
{
	unsigned char mask = 0x80 >> (x % 8);

	if (pixel == 0) bitmap[y][x / 8] &= ~mask;
	else bitmap[y][x / 8] |= mask;
}

int getpixel(unsigned char bitmap[NM][NM / 8], int x, int y)
{
	unsigned char mask = 0x80 >> (x % 8);

	if ((bitmap[y][x / 8] & mask) == 0) return 0;
	else return 1;
}

void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN])
{
	register int i, j, k, s, t, u, y, x, bit[4];
	for (i = 0; i < NN; i++)
	{
		int a1 = data[i];
		for (j = 0; j < 4; j++)
			bit[j] = (data[i] >> j) & 1;

		y = i / 32;
		x = i % 32;

		for (j = 0; j < 4; j++)
		{
			int v = bit[j];
			bitmap[y * 2][x] += v << (j * 2);
			bitmap[y * 2][x] += v << (j * 2 + 1);
			bitmap[y * 2 + 1][x] += v << (j * 2);
			bitmap[y * 2 + 1][x] += v << (j * 2 + 1);
		}
	}
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 8; k += 2)
			{
				bitmap[k + 1][i + 1] |= 1 << (j * 2 + 1);
			}
		}
	}

}
void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8])
{
	int psum[8] = { 0 };
	register int i, j, k, s, t, u, y, x;

	int cnt = 0;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 8; k += 2)
			{
				psum[0] += (bitmap[k + 1][i] >> (j * 2 + 1)) & 1;
				psum[1] += (bitmap[k + 1][i + 16] >> (j * 2)) & 1;
				psum[2] += (bitmap[255 - 1 - k][i] >> (j * 2 + 1)) & 1;
				psum[3] += (bitmap[255 - 1 - k][i + 16] >> (j * 2)) & 1;
				cnt++;
			}
		}
	}

	cnt = 0;
	for (i = 0; i < 128; i += 2)
	{
		for (j = 0; j < 8; j += 2)
		{
			int a234 = 235;
			psum[4] += (bitmap[i + 1][31] >> (j)) & 1;
			psum[5] += (bitmap[i + 128][31] >> (j)) & 1;
			psum[6] += (bitmap[i + 1][0] >> (j + 1)) & 1;
			psum[7] += (bitmap[i + 128][0] >> (j + 1)) & 1;
			cnt++;
		}
	}
	int a1234 = 123;
	int b234 = 345;

}