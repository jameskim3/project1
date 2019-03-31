#include<iostream>
#include<time.h>
#include<process.h>

static char CELL[5000][5000];
static char CB[5000][5000];
static int NB[4][2];
void func1(void* param);
void func2(void* param);
static int seed = 3;
static int pseudo_rand()
{
	seed = (214011 * seed + 2531011);
	return (seed >> 16) & 0x7fff;
}
static void build(){
	for (int i = 0; i < 5000; i++){
		for (int j = 0; j < 5000; j++){
			CELL[i][j] = CB[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; ){
		int x = pseudo_rand() % 5000;
		int y = pseudo_rand() % 5000;
		if (CELL[y][x] != 0)continue;
		CELL[y][x] = CB[y][x] = (i + 1)*-1;
		NB[i][0] = x, NB[i][1] = y;
		i++;
	}
	for (int i = 0; i < 250000;){
		int x = pseudo_rand() % 5000;
		int y = pseudo_rand() % 5000;
		if (CELL[y][x] != 0)continue;
		CELL[y][x] = CB[y][x] = (pseudo_rand() % 4) + 1;
		i++;
	}
}
int cal_dist(int sy, int sx, int ty, int tx){
	int v = (sy - ty)*(sy - ty);
	v += (sx - tx)*(sx - tx);
	return v;
}
double LOSS;
int DONE;
void calc(){
	int NBUE[4] = { 0 };
	for (int c = 0; c < 4; c++){
		if (CELL[NB[c][1]][NB[c][0]] >= 0)
			LOSS += 1000000000;
	}
	for (int y = 0; y < 5000; y++){
		for (int x = 0; x < 5000; x++){
			if (CB[y][x] == 0 && CELL[y][x] != 0 ||
				CB[y][x] != 0 && CELL[y][x] == 0)
				LOSS += 1000000000;

			if (CELL[y][x] >= 1 && CELL[y][x] <= 4){
				int idx = CELL[y][x] - 1;
				int dx = NB[idx][0] - x;
				int dy = NB[idx][1] - y;
				NBUE[idx]++;
				LOSS += dx*dx + dy*dy;
			}
		}
	}
	int v = 0;
	for (int i = 0; i < 4; i++){
		v += NBUE[i];
	}
	if (v != 250000)
		LOSS += 1000000000;
	for (int i = 0; i < 4; i++){
		if (NBUE[i] > 67500)
			LOSS += (NBUE[i] - 67500)*50000000.0;
	}
}

int main(){
	time_t start = clock();
	LOSS = 0.;
	for (int tc = 0; tc < 10; tc++){
		build();
		DONE = 0;
		_beginthread(func1, 0, (void*)CELL);
		_beginthread(func2, 0, (void*)CELL);

		while (DONE == 0);
		calc();
	}
	time_t end = clock();
	int PERFORM = end - start;
	printf("LOSS:%.1f(dB), PERFORM:%d\n", LOSS, PERFORM);
	return 0;
}