//SCORE: 10179418

#define NN 4096 
#define NM 256 

void flip(unsigned char bitmap[NM][NM / 8], int mode);
void rotate(unsigned char bitmap[NM][NM / 8], int angle);

void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN])
{
	for (int i = 0; i < NN; i++)
	{
		int row = i / 32;
		int col = i % 32;

		int bit_arr[4] = { 0, };
		for (int j = 0; j < 4; j++)
		{
			bit_arr[j] = data[i] >> j & 0x01;
		}


		for (int y = row * 2; y < row * 2 + 2; y++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (bit_arr[j])
				{
					bitmap[y][col] |= 0x01 << (j * 2);
					bitmap[y][col] |= 0x01 << (j * 2 + 1);
				}
			}
		}
		for (int y = 1; y < 6; y += 2)
		{
			for (int x = 0; x < 16; x++)
			{
				for (int j = 0; j < 4; j++)
				{
					bitmap[y][x] |= 0x01 << (j * 2 + 1);
				}
			}
		}
	}
}

void modify(unsigned char bitmap[NM][NM / 8], int c)
{
	switch (c)
	{
	case 0:
		break;
	case 1:
		rotate(bitmap, 1);
		break;
	case 2:
		rotate(bitmap, 2);
		break;
	case 3:
		rotate(bitmap, 3);
		break;
	case 4:
		flip(bitmap, 1);
		break;
	case 5:
		flip(bitmap, 2);
		break;
	case 6:
		rotate(bitmap, 1);
		flip(bitmap, 2);
		break;
	case 7:
		rotate(bitmap, 1);
		flip(bitmap, 1);
		break;
	}
}
int getSum(unsigned char bitmap[NM][NM / 8], int c)
{
	unsigned char buf[NM][NM / 8] = { 0, };
	for (int y = 0; y < NM; y++)
	{
		for (int x = 0; x < NM / 8; x++)
		{
			buf[y][x] = bitmap[y][x];
		}
	}

	modify(buf, c);

	int sum = 0;
	for (int y = 1; y < 6; y += 2)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int j = 0; j < 4; j++)
			{
				int ret = (buf[y][x] >> (j * 2 + 1)) & 0x01;
				if (ret)
					sum++;
			}
		}
	}
	return sum;
}

void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8])
{
	int sum[8] = { 0, };

	for (int i = 0; i < 8; i++)
	{
		sum[i] = getSum(bitmap, i);
	}

	int idx = 0;
	int max = -1;
	for (int i = 0; i < 8; i++)
	{
		if (sum[i]>max)
		{
			max = sum[i];
			idx = i;
		}
	}

	modify(bitmap, idx);

	for (int i = 0; i < NN; i++)
	{
		int row = i / 32;
		int col = i % 32;

		int bit_arr[4] = { 0, };

		for (int y = row * 2; y < row * 2 + 2; y++)
		{
			for (int j = 0; j < 4; j++)
			{
				int a = (bitmap[y][col] >> (j * 2)) & 0x01;
				int b = (bitmap[y][col] >> (j * 2 + 1)) & 0x01;

				if (a) bit_arr[j]++;
				if (b) bit_arr[j]++;
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (bit_arr[j] <= 2)
				bit_arr[j] = 0;
			else
				bit_arr[j] = 1;
		}

		int tmp = 0;
		for (int j = 0; j < 4; j++)
		{
			if (bit_arr[j])
				tmp |= 0x01 << j;
		}
		data[row * 32 + col] = tmp;
	}
}

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