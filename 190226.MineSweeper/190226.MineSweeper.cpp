#include<stdio.h>
#define MAXN 100
extern void find(int N, int callcntLimit);
static int orgBoard[MAXN][MAXN];
static int curBoard[MAXN][MAXN];
static int T, tc;
static int SIZE, LIMIT;
int getCount(int x, int y){
	LIMIT--;
	if (x >= 0 && x < SIZE&&y >= 0 && y < SIZE){
		int cnt = 0;
		for (int i = y - 1; i < y + 2; i++){
			if (i < 0 || i >= SIZE){
				continue;
			}
			for (int j = x - 1; j < x + 2; j++){
				if (j < 0 || j >= SIZE)continue;
				if (orgBoard[i][j] == 9){
					cnt++;
				}
			}
		}
		return cnt;
	}
	return -1;
}
int open(int x, int y){
	if (x >= 0 && x < SIZE&&y >= 0 && y < SIZE){
		if (curBoard[y][x] != -1)return curBoard[y][x];
		curBoard[y][x] = orgBoard[y][x];
		return orgBoard[y][x];
	}
	return -1;
}
static int seed = 3;
static int pseudo_rand()
{
	seed = (214011 * seed + 2531011);
	return (seed >> 16) & 0x7fff;
}
void build(){
	//int tot = pseudo_rand() % 5 + 45;
	int tot = pseudo_rand() % 5 +10;
	tot = SIZE*SIZE*tot / 100;

	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			curBoard[i][j] = -1;
			orgBoard[i][j] = -1;
		}
	}
	int cnt = 0;
	int y, x;
	while (cnt < tot){
		y = pseudo_rand() % (SIZE - 2) + 1;
		x = pseudo_rand() % (SIZE - 2) + 1;
		if (orgBoard[y][x]>-1)continue;
		orgBoard[y][x] = 9;
		cnt++;
	}
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (orgBoard[i][j] != 9){
				orgBoard[i][j] = getCount(j, i);
			}
		}
	}
}
static bool run(){
	SIZE = 50;// pseudo_rand() % 10 + 10;
	LIMIT = 0;

	build();
	LIMIT = SIZE*SIZE / 2;
	find(SIZE, LIMIT);
	//if (LIMIT < 0)return false;
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (orgBoard[i][j] == 9){
				if (curBoard[i][j] != -1)return false;
			}
			else if (orgBoard[i][j] != curBoard[i][j])return false;
		}
	}
	return true;
}
int main(){
	setbuf(stdout, NULL);
	T = 100;
	for (tc = 0; tc < T; tc++){
		printf("#%d %d\n", tc, run() ? 100 : 0);
	}
	return 0;
}
