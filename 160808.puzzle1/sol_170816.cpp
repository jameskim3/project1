
//#include <stdio.h> 
//#include <string.h> 
//#include <stdlib.h> 
//#include <time.h> 

//#define SWAP(x,y) { int z=x; x=y; y=z;}
void SWAP(int *a, int *b){
	int t = *a;
	*a = *b;
	*b = t;
}

using namespace std;
const int BLOCK = 32;
const int X = 2048;
const int Y = 2048;
const int N = 100;
const int M = 64;
const int B = 32;

int b[M + 2][M + 2][4], n[M + 2][M + 2];
int yy[4] = { -1, 1, 0, 0 };
int xx[4] = { 0, 0, -1, 1 };
int join[4] = { 1, 0, 3, 2 };

void output()
{
	int i, j, cnt[5] = { 0, };
	for (i = 0; i < M + 2; i++)
	{
		for (j = 0; j < M + 2; j++)
		{
//			printf("%d", n[i][j]);
			cnt[n[i][j]]++;
		}
//		printf("\n");
	}
//	printf("%d %d %d %d\n\n", cnt[0], cnt[1], cnt[2], cnt[3]);
}

int match_cnt(int sy, int sx, int ey, int ex)
{
	int cnt = 0, ny, nx;
	for (int i = 0; i < 4; i++)
	{
		ny = sy + yy[i];
		nx = sx + xx[i];

		if (ny<0 || ny>65 || nx<0 || nx>65)
			cnt++;
		else
			cnt += (b[ey][ex][i] == b[ny][nx][join[i]]);
	}
	return cnt;
}

void swap_bit(char bitmap[][X], int sy, int sx, int dy, int dx)
{
	int y, x;
	for (y = 0; y < 32; y++)
	{
		for (x = 0; x < 32; x++)
		{
			int t = bitmap[sy + y][sx + x];
			bitmap[dy + y][dx + x] = bitmap[sy + y][sx + x];
			bitmap[sy + y][sx + x] = t;
		}
	}
}

void swap(char bitmap[][X], int sy, int sx, int ey, int ex)
{
	int i, j, tmp;
	for (i = 0; i < 4; i++)
	{
		SWAP(&b[sy][sx][i], &b[ey][ex][i]);
		n[sy + yy[i]][sx + xx[i]] = match_cnt(sy + yy[i], sx + xx[i], sy + yy[i], sx + xx[i]);
		n[ey + yy[i]][ex + xx[i]] = match_cnt(ey + yy[i], ex + xx[i], ey + yy[i], ex + xx[i]);
	}
	n[sy][sx] = match_cnt(sy, sx, sy, sx);
	n[ey][ex] = match_cnt(ey, ex, ey, ex);
	swap_bit(bitmap, (sy - 1) * 32, (sx - 1) * 32, (ey - 1) * 32, (ex - 1) * 32);
}

void change(char bitmap[][X], int y, int x, int k)
{
	int i, j;
	for (i = 1; i <= M; i++)
	{
		for (j = 1; j <= M; j++)
		{
			if (n[i][j] == 4)
				continue;

			if (match_cnt(y, x, i, j) >= k && match_cnt(i, j, y, x) >= n[i][j])
				swap(bitmap, y, x, i, j);
		}
	}
}
void move1(char bitmap[][X])
{
	int i, j, k, p;
	for (p = 0; p <4; p++)
	{
		for (k = 4; k > p; k--)
		{
			for (i = 1; i <= M; i++)
			{
				for (j = 1; j <= M; j++)
				{
					if (n[i][j] == p)
					{
						change(bitmap, i, j, k);
					}
				}
			}
		}
	}
}

void move2(char bitmap[][X])
{
	int sy, sx, ey, ex;
	for (sy = 1; sy <= M; sy++)
	{
		for (sx = 1; sx <= M; sx++)
		{
			if (n[sy][sx - 1] == 3 && n[sy][sx] == 3 && n[sy][sx + 1] == 3)
			{
				for (ey = 1; ey <= M; ey++)
				{
					for (ex = 1; ex <= M; ex++)
					{
						if (n[ey][ex - 1] == 3 && n[ey][ex] == 3 && n[ey][ex + 1] == 3 &&
							b[sy][sx - 1][3] == b[ey][ex][2])
						{
							swap(bitmap, sy, sx, ey, ex);
							swap(bitmap, sy, sx + 1, ey, ex + 1);
						}
					}
				}
			}
			if (n[sy - 1][sx] == 3 && n[sy][sx] == 3 && n[sy + 1][sx] == 3)
			{
				for (ey = 1; ey <= M; ey++)
				{
					for (ex = 1; ex <= M; ex++)
					{
						if (n[ey - 1][ex] == 3 && n[ey][ex] == 3 && n[ey + 1][ex] == 3 &&
							b[sy - 1][sx][1] == b[ey][ex][0])
						{
							swap(bitmap, sy, sx, ey, ex);
							swap(bitmap, sy, sx + 1, ey, ex + 1);
						}
					}
				}
			}
		}
	}
}
void move3(char bitmap[][X])
{
	int sy, sx, ey, ex;
	for (sy = 1; sy <= M; sy++)
	{
		for (sx = 1; sx <= M; sx++)
		{
			if (b[sy][sx][0] != b[sy - 1][sx][1]
				|| b[sy][sx][2] != b[sy][sx - 1][3])
			{
				for (ey = sy; ey <= M; ey++)
				{
					for (ex = 1; ex <= M; ex++)
					{
						if (n[ey][ex] == 4) continue;
						if (b[ey][ex][0] == b[sy - 1][sx][1] && b[ey][ex][2] == b[sy][sx - 1][3]
							&& n[ey][ex] <= match_cnt(ey, ex, sy, sx))
						{
							swap(bitmap, sy, sx, ey, ex);
						}
					}
				}
			}
		}
	}
}

int chk()
{
	for (int i = 0; i <= 65; i++)
	{
		for (int j = 0; j <= 65; j++)
		{
			if (n[i][j] < 4) return 0;
		}
	}

	return 1;
}

void test(char bitmap[][X])
{
	int i, j, k;
	for (i = 0; i < M + 2; i++)
	{
		for (j = 0; j < M + 2; j++)
		{
			for (k = 0; k < 4; k++)
				b[i][j][k] = 0;
			n[i][j] = 0;
		}
	}
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			for (k = 1; k < 31; k++)
			{
				b[i + 1][j + 1][0] = b[i + 1][j + 1][0] * 2 + bitmap[i * 32][j * 32 + k];
				b[i + 1][j + 1][1] = b[i + 1][j + 1][1] * 2 + bitmap[i * 32 + 31][j * 32 + k];
				b[i + 1][j + 1][2] = b[i + 1][j + 1][2] * 2 + bitmap[i * 32 + k][j * 32];
				b[i + 1][j + 1][3] = b[i + 1][j + 1][3] * 2 + bitmap[i * 32 + k][j * 32 + 31];
			}
		}
	}
	for (i = 0; i < M + 2; i++)
	{
		for (j = 0; j < M + 2; j++)
		{
			n[i][j] = match_cnt(i, j, i, j);
		}
	}

	move1(bitmap);
	move1(bitmap);
	output();
	move1(bitmap);
	move2(bitmap);
	move3(bitmap);
}