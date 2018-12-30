//SCORE: 10238594
#define NN 4096 
#define NM 256 
extern void flip(unsigned char bitmap[NM][NM / 8], int mode);
extern void rotate(unsigned char bitmap[NM][NM / 8], int angle);
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
			setpixel(bitmap, x * 8 + j * 2, y * 2, v);
			setpixel(bitmap, x * 8 + j * 2 + 1, y * 2, v);
			setpixel(bitmap, x * 8 + j * 2, y * 2 + 1, v);
			setpixel(bitmap, x * 8 + j * 2 + 1, y * 2 + 1, v);
		}
	}
	for (x = 0; x < 128; x += 2)
	{
		for (y = 0; y < 8; y += 2)
		{
			setpixel(bitmap, x + 1, y + 1, 1);
		}
	}

}
void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8])
{
	int psum[8] = { 0 };
	register int i, j, k, s, t, u, y, x;

	for (x = 0; x< 128; x += 2)
	{
		for (y = 0; y < 8; y += 2)
		{
			psum[0] += getpixel(bitmap, x + 1, y + 1);
			psum[1] += getpixel(bitmap, 128 + x, y + 1);
			psum[2] += getpixel(bitmap, x + 1, 255 - 1 - y);
			psum[3] += getpixel(bitmap, 128 + x, 255 - 1 - y);
		}
	}

	for (y = 0; y < 128; y += 2)
	{
		for (x = 0; x < 8; x += 2)
		{
			psum[4] += getpixel(bitmap, 255 - 1 - x, y + 1);
			psum[5] += getpixel(bitmap, 255 - 1 - x, y + 128);
			psum[6] += getpixel(bitmap, x + 1, y + 1);
			psum[7] += getpixel(bitmap, x + 1, y + 128);
		}
	}

	int c = 0;
	int max = 0;
	for (i = 0; i < 8; i++)
	{
		if (max < psum[i])
		{
			max = psum[i];
			c = i;
		}
	}

	switch (c)
	{
	case 1:
		flip(bitmap, 2);
		break;
	case 2:
		flip(bitmap, 1);
		break;
	case 3:
		rotate(bitmap, 2);
		break;
	case 4:
		rotate(bitmap, 3);
		break;
	case 5:
		flip(bitmap, 1);
		rotate(bitmap, 3);
		break;
	case 6:
		flip(bitmap, 2);
		rotate(bitmap, 3);
		break;
	case 7:
		rotate(bitmap, 1);
		break;
	}

	int onecnt[4];
	int v = 0;
	for (y = 0; y < 128; y++)
	{
		for (x = 0; x < 32; x++)
		{
			v = 0;
			for (i = 0; i < 4; i++)
			{
				onecnt[i] = 0;
				onecnt[i] += getpixel(bitmap, x * 8 + i * 2 + 0, y * 2 + 0) == 1 ? 1 : 0;
				onecnt[i] += getpixel(bitmap, x * 8 + i * 2 + 1, y * 2 + 0) == 1 ? 1 : 0;
				onecnt[i] += getpixel(bitmap, x * 8 + i * 2 + 0, y * 2 + 1) == 1 ? 1 : 0;
				onecnt[i] = onecnt[i]>1 ? 1 : 0;

				v |= (onecnt[i] << i);
			}
			data[y * 32 + x] = v;
		}
	}
}
