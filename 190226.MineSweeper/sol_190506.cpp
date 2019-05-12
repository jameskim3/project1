int mymap[100][100];
extern int getCount(int x, int y);
extern int open(int x, int y);

int cnt_tot;
int cnt_digi;
int cnt_mine;
int BOUNDARY;

typedef struct ms{
	int mine;
	int hidden;
	int val;
}MS;

int path[8][2] = {
	{ -1, -1 },
	{ -1, 0 },
	{ -1, +1 },
	{ 0, -1 },
	{ 0, +1 },
	{ 1, -1 },
	{ 1, 0 },
	{ 1, +1 },
};

void get_neighber(int y,int x,int* hidden, int* mine){
	*hidden = *mine = 0;
	for (int p = 0; p < 8; p++){
		int ty = path[p][0] + y;
		int tx = path[p][1] + x;
		if (ty < 0 || ty >= BOUNDARY || tx<0 || tx>BOUNDARY)continue;
		if (mymap[ty][tx] == 9) *mine += 1;
		if (mymap[ty][tx] == -1) *hidden += 1;
	}
}
int judge(int y, int x){
	int hidden, mine;
	get_neighber(y, x, &hidden, &mine);
	int v = mymap[y][x];

	if (v == mine){//find all
		for (int p = 0; p < 8; p++){
			int ty = path[p][0]+y;
			int tx = path[p][1]+x;
			if (ty < 0 || ty >= BOUNDARY || tx<0 || tx>BOUNDARY)continue;
			if (mymap[ty][tx] == -1){
				mymap[ty][tx] = getCount(tx, ty);
				if (mymap[ty][tx] == 9)
					int a234 = 234;
				cnt_digi++;
			}
		}
	}
	if (v > mine && v - mine == hidden){
		for (int p = 0; p < 8; p++){
			int ty = path[p][0]+y;
			int tx = path[p][1]+x;
			if (ty < 0 || ty >= BOUNDARY || tx<0 || tx>BOUNDARY)continue;
			if (mymap[ty][tx] == -1){
				mymap[ty][tx] = 9;
				cnt_mine++;
			}
		}
	}

	return 0;
}
void find(int N, int callcntLimit){
	for (int y = 0; y < N; y++){
		for (int x = 0; x < N; x++){
			mymap[y][x] = -1;
		}
	}
	BOUNDARY = N;
	cnt_tot = N*N;
	cnt_digi = cnt_mine = 0;
	for (int i = 0; i < N; i++){
		mymap[0][i] = getCount(i, 0);
		mymap[N - 1][i] = getCount(i, N - 1);
		cnt_digi+=2;
	}
	for (int i = 1; i < N-1; i++){
		mymap[i][0] = getCount(0, i);
		mymap[i][N-1] = getCount(N-1, i);
		cnt_digi+=2;
	}

	int hidden, mine;
	MS info;
	while (cnt_digi + cnt_mine < cnt_tot){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				judge(i, j);
			}
		}
	}
	for (int y = 0; y < N; y++){
		for (int x = 0; x < N; x++){
			if (mymap[y][x] != 9)
				open(x, y);
		}
	}
}