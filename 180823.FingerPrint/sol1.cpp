#include <iostream>
char origin[256][256];
char devide[5][128][128];
int M2;
int map_cnt;
typedef unsigned long long ULL;

void init()
{
	map_cnt = 0;
}

void assign_img(int seq[4], char img[256][256])
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < M2; i++)
		{
			for (int j = 0; j < M2; j++)
			{
				int a = i + (k / 2)*M2;
				int b = j + (k % 2)*M2;
				int t = devide[seq[k]][i][j];
				img[a][b] = t;
			}
		}
	}
}
int chk_img(char buf[256][256], char reg[128][128])
{
	for (int off_y = 0; off_y < M2; off_y++)
	{
		for (int off_x = 0; off_x < M2; off_x++)
		{
			int valid = 1;
			for (int y = 0; y < M2 && valid ==1; y++)
			{
				for (int x = 0; x < M2; x++)
				{
					if (reg[y][x] != buf[y+off_y][x+off_x])
					{
						valid = 0;
						break;
					}
				}
			}
			if (valid == 1) return 1;
		}
	}
	return 0;
}
void build_map()
{
	register int i, j, k,l,m,y,x;
	int chk = 0;
	int bm;
	char buf[256][256];
	for (i = 0; i < 5; i++)
	{
		chk += (1 << i);
		for (j = 0; j < 5; j++)
		{
			if (((chk >> j) & 1) == 1)continue; chk += (1 << j);
			for (k = 0; k < 5; k++)
			{
				if (((chk >> k) & 1) == 1)continue; chk += (1 << k);
				for (l = 0; l < 5; l++)
				{
					if (((chk >> l) & 1) == 1)continue; chk += (1 << l);
					for (m = 0; m < 5; m++)
					{
						if (((chk >> m) & 1) == 1)continue; 

						int seq[4] = { i, j, k, l };
						assign_img(seq, buf);

						if (chk_img(buf, devide[m]) == 1)
						{
							assign_img(seq,origin);
							return;
						}
					}
					chk -= (1 << l);
				}
				chk -= (1 << k);
			}
			chk -= (1 << j);
		}
		chk -= (1 << i);
	}
}

void send_map(int n, char img[128][128])
{
	M2 = n;
	register int i, j, k;
	for (i = 0; i < M2; i++)
	{
		for (j = 0; j < M2; j++)
		{
			devide[map_cnt][i][j] = img[i][j];
		}
	}
	map_cnt++;

	if (map_cnt == 5)build_map();
}

int checkReg(int y, int x, ULL bitmap[32][32], ULL reg[3][16][16])
{
	int ret = 0;
	int min = 999999;
	register int i, j, k, s, t, u;
	for (k = 0; k < 3; k++)
	{
		ret = 0;
		for (i = 0; i < M2 / 8; i++)
		{
			for (j = 0; j < M2 / 8; j++)
			{
				ULL bitcomp = bitmap[i + y][j + x] ^ reg[k][i][j];
				while (bitcomp != 0)
				{
					bitcomp &= (bitcomp - 1LL);
					ret++;
				}
			}
		}
		if (min > ret)min = ret;
	}
	return min;
}
int checkModel(int n, char img[128][128])
{
	int ret=0;
	ULL bitmap[32][32];
	ULL reg[3][16][16];
	register int i, j, k, s, t, u, y,x;
	for (y = 0; y < M2 * 2/8; y++)
	{
		for (x = 0; x < M2 * 2/8; x++)
		{
			bitmap[y][x] = 0;
			for (i = 0; i < 8; i++)
			{
				for (j = 0; j < 8; j++)
				{
					s = y * 8;
					t = x * 8;
					u = i * 8 + j;
					bitmap[y][x] += ULL(origin[s + i][t + j]) << u;
				}
			}
		}
	}

	char buf[3][128][128];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			buf[0][i][j] = img[i][j];
			buf[1][i][j] = img[n - 1 - j][i];
			buf[2][i][j] = img[j][n-1-i];
		}
	}
	for (k = 0; k < 3; k++)
	{
		for (y = 0; y < M2 / 8; y++)
		{
			for (x = 0; x < M2 / 8; x++)
			{
				reg[k][y][x] = 0;
				for (i = 0; i < 8; i++)
				{
					for (j = 0; j < 8; j++)
					{
						s = y * 8;
						t = x * 8;
						u = i * 8 + j;
						reg[k][y][x] += ULL(buf[k][s + i][t + j]) << u;
					}
				}
			}
		}
	}

	int cnt = 0;
	int threshold_cnt = double(M2*M2)*0.12;
	for (y = 0; y <= M2 / 8; y++)
	{
		for (x = 0; x <= M2 / 8; x++)
		{
			cnt = checkReg(y, x, bitmap, reg);
			if (threshold_cnt >= cnt)
				return cnt;
		}
	}

	return 0;
}