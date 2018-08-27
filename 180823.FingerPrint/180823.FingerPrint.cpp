#include <iostream>
#include <time.h>

const int mat[] = { 16, 32, 64, 128, 256, };
char origin_map[256][256];
char devide_map[128][128];
char model_map[128][128];
char valid_map[128][128];
int changeCnt;
int N,M;

extern void send_map(int n, char img[128][128]);
extern int checkModel(int n, char img[128][128]);
extern void init();
void make_map()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			origin_map[i][j] = rand() % 2;

			//printf("%d", origin_map[i][j]);
			//if (j == M - 1) printf(" ");
		}
		//printf("\n"); if (i == M - 1) printf("\n");
	}

	int chk = 0; 
	int offsetX, offsetY;
	while (chk != 31)
	{
		int t = rand() % 5;
		if (((0x01 << t)&chk) > 0)continue;
		chk+= 0x01<<t;
		if (t < 4)
		{
			offsetY = (t / 2)*(N/2);
			offsetX = (t % 2)*(N/2);
		}
		else
		{
			offsetY = rand() % ((N / 2) - 4) + 2; 
			offsetX = rand() % ((N / 2) - 4) + 2;
		}

		for (int i = 0; i < N / 2; i++)
		{
			for (int j = 0; j < N / 2; j++)
			{
				devide_map[i][j] = origin_map[i + offsetY][j + offsetX];
			}
		}
		send_map(N / 2, devide_map);
	}
}

void make_model()
{
	int off_y = rand()%(N/2);
	int off_x = rand() % (N / 2);
	off_y &= 0xfff8;
	off_x &= 0xfff8;
	register int i, j, k,y,x;

	char buf[256][256] = { 0 };
	for (y = 0; y < N / 2; y++)
	{
		for (x = 0; x < N / 2; x++)
		{
			buf[y][x] = origin_map[y + off_y][x + off_x];
		}
	}

	int rot = rand() % 3;
	switch (rot)
	{
	case 0:
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < M; j++)
			{
				model_map[i][j] = buf[i][j];
				valid_map[i][j] = model_map[i][j];
			}
		}
		break;
	case 1:
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < M; j++)
			{
				model_map[i][j] = buf[M - 1 - j][i];
				valid_map[i][j] = model_map[i][j];
			}
		}
		break;
	case 2:
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < M; j++)
			{
				model_map[i][j] = buf[j][M-1-i];
				valid_map[i][j] = model_map[i][j];
			}
		}
		break;
	}

	int ratio = rand() % 12 + 1;
	int iter = ratio*1.0 / 100. * double(M*M);
	for (i = 0; i < iter; i++)
	{
		y = rand() % M;
		x = rand() % M;

		model_map[y][x] ^= 1;
	}

	changeCnt = 0;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (model_map[i][j] != valid_map[i][j])changeCnt++;
		}
	}
}

int main()
{
	//freopen("out.txt", "w", stdout);
	int ret = 0;
	time_t start = clock();
	for (int tc = 0; tc < 1000; tc++)
	{
		init();
		N = mat[rand() % 5];
		M = N / 2;
		make_map();
		make_model();
		if (changeCnt == checkModel(M, model_map)) 
			ret++;
	}

	time_t end = clock();
	int performance =  end - start;

	printf("Perfomance:%d, Result:%d ", performance, ret);
	return 0;
}