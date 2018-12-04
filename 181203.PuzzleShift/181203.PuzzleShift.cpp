#include<iostream>
#include<time.h>
int board[5][5];
int map[3][3];
extern void run(int board[5][5], int map[3][3]);
void mixBoard(){
	int cnt = 0;
	for (int i = 1; i <= 6; i++){
		for (int j = 0; j < 4; j++){
			int y = cnt / 5;
			int x = cnt % 5;
			board[y][x] = i;
			cnt++;
		}
	}
	board[4][4] = 0;
	for (int i = 0; i < 1000;){
		int a1 = rand() % 5;
		int b1 = rand() % 5;
		int a2 = rand() % 5;
		int b2 = rand() % 5;
		if (a1 == a2 && b1==b2)continue;
		int t = board[a1][b1];
		board[a1][b1] = board[a2][b2], board[a2][b2] = t, i++;
	}
}
void buildMap(){
	int cnt = 0;
	int visited[7] = { 0 };
	while (cnt < 9){
		int a = rand() % 6 + 1;
		if (visited[a] >= 4)continue;
		visited[a]++;
		int y = cnt / 3;
		int x = cnt % 3;
		map[y][x] = a;
		cnt++;
	}
}
int path[4][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1},
};
int shift_cnt;
int shift(int y,int x, int dir){
	if (y + path[dir][0] < 0 || y + path[dir][0] >= 5)return 0;
	if (x + path[dir][1] < 0 || x + path[dir][1] >= 5)return 0;
	int tar_y = y + path[dir][0];
	int tar_x = x + path[dir][1];
	if (board[tar_y][tar_x] != 0 && board[y][x] != 0)return 0;
	int t = board[y][x];
	board[y][x] = board[tar_y][tar_x], board[tar_y][tar_x] = t;
	shift_cnt++;
	return 1;
}
int main(){
	time_t start = clock();
	int TC = 50000;
	int SCORE = 0;
	double SHIFT_AVG = 0.;
	for (int tc = 0; tc < TC; tc++){
		mixBoard();
		buildMap();
		shift_cnt = 0;
		run(board,map);
		int score = 100;
		for (int y = 0; y < 3; y++){
			for (int x = 0; x < 3; x++){
				if (board[y + 1][x + 1] != map[y][x])score = 0;
			}
		}
		//printf("#%d %d %d\n",tc+1,score,shift_cnt);
		SHIFT_AVG += double(shift_cnt);
		if (score == 100 && shift_cnt < 500)
			SCORE += 2;
	}
	time_t end= clock();
	printf("Score:%d, SHIFT=%.3f Performance:%d\n", SCORE, SHIFT_AVG/TC, end - start);

}
