//SCORE: 10241409
#define NN 4096 
#define NM 256 

extern void flip(unsigned char bitmap[NM][NM / 8], int mode);
extern void rotate(unsigned char bitmap[NM][NM / 8], int angle);

void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN])
{
	register int i, j;
	int b[4] = { 0 };
	for (i = 0; i < 4096; i++)
	{
		int v = data[i];
		for (j = 0; j < 4; j++)
			b[j] = (v >> j) & 1;

		int y = i / 32;
		int x = i % 32;

		bitmap[y * 2 + 0][x] = 0;
		bitmap[y * 2 + 1][x] = 0;
		for (j = 0; j < 4; j++)
		{
			bitmap[y * 2 + 0][x] += (b[j] << (j * 2));
			bitmap[y * 2 + 0][x] += (b[j] << (j * 2 + 1));
			bitmap[y * 2 + 1][x] += (b[j] << (j * 2));
			bitmap[y * 2 + 1][x] += (b[j] << (j * 2 + 1));
		}

		if (y <4 && x<16)
		{
			for (j = 0; j < 4; j++)
				bitmap[y * 2 + 1][x] |= (1 << (j * 2 + 1));
		}
	}
}
void solve_rot(unsigned char bitmap[NM][NM / 8])
{
	register int i, j, k;
	int s[8] = { 0 };

	int cx, cy, ox,oy;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					switch (i)
					{
					case 0:
						cx = x, cy = y, ox = 1, oy = 1;
						break;
					case 1:
						cx = 31 - x, cy = y, ox = 0, oy = 1;
						break;
					case 2:
						cx = x, cy = 127 - y, ox = 1, oy = 0;
						break;
					case 3:
						cx = 31 - x, cy = 127 - y, ox = 0, oy = 0;
						break;
					}
					s[i] += (bitmap[cy * 2 + oy][cx] >> (j * 2 + ox)) & 1;
				}
			}
		}
	}
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 1; x++)
		{
			for (i = 4; i < 8; i++)
			{
				for (j = 0; j < 4; j++)
				{
					switch (i)
					{
					case 4:
						cx = 31, cy = y, ox = 1, oy = 0;
						break;
					case 5:
						cx = 31, cy = 64+y, ox = 1, oy = 1;
						break;
					case 6:
						cx = 0, cy = y, ox = 0, oy = 0;
						break;
					case 7:
						cx = 0, cy = 64 + y, ox = 0, oy = 1;
						break;
					}
					s[i] += (bitmap[cy * 2 + oy][cx] >> (j * 2 + ox)) & 1;
				}
			}
		}
	}
	int max_id = -1;
	int max_val = -1;
	for (i = 0; i < 8; i++)
	{
		if (s[i] > max_val)
		{
			max_id = i;
			max_val = s[i];
		}
	}

	switch (max_id)
	{
	case 0:
		break;
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
		rotate(bitmap, 3);
		flip(bitmap, 1);
		break;
	case 7:
		rotate(bitmap, 1);
		break;
	}
}
void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8])
{
	register int i, j, k;
	int b[4] = { 0 };
	solve_rot(bitmap);
	for (i = 0; i < 4096; i++)
	{
		int y = i / 32;
		int x = i % 32;

		for (j = 0; j < 4; j++)
		{
			b[j] = 0;
			b[j] += (bitmap[y * 2][x] >> (j * 2)) & 1;
			b[j] += (bitmap[y * 2][x] >> (j * 2+1)) & 1;
			b[j] += (bitmap[y * 2+1][x] >> (j * 2)) & 1;
		}

		data[i] = 0;
		for (j = 0; j < 4; j++)
			data[i] += (b[j] >= 2 ? (1 << j) : 0);
	}
}
