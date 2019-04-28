
const int BLOCK = 32;
const int X = 2048;
const int Y = 2048;
const int N = 500;

typedef struct bl{
	char data[4][64];
	int r[100];
	int rcnt;
	int d[100];
	int dcnt;
	int edge[4];
}BL;
const int ALL = 32 * 32;
BL ND[ALL];
int rp;
char mymap[Y][X];
int ans_cnt;
int ans_path[ALL];
int loc_cnt;
int loc_path[ALL];

int match(char* src, char* tar, int n){
	int cnt = 0;
	while (cnt < n){
		if (src[cnt] != tar[cnt])
			return 0;
		cnt++;
	}
	return 1;
}
void makeDic(){
	for (int i = 0; i < ALL; i++){
		int sy = i / 32;
		int sx = i % 32;
		int ty = sy * 64;
		int tx = sx * 64;
		for (int y = ty; y < ty + 64; y++){
			ND[i].d[2] = mymap[y][tx];
			ND[i].d[3] = mymap[y][tx + 63];
		}
		for (int x = tx; x < tx + 64; x++){
			ND[i].d[0] = mymap[ty][x];
			ND[i].d[1] = mymap[ty+63][x];
		}
	}

	for (int i = 0; i < ALL; i++){
		for (int j = 0; j < ALL; j++){
			if (i == j)continue;
			if (match(ND[i].data[3], ND[j].data[2], 64)){
				int* t = &ND[i].rcnt;
				ND[i].r[*t] = j;
				*t += 1;
			}
			if (match(ND[i].data[1], ND[j].data[0], 64)){
				int* t = &ND[i].dcnt;
				ND[i].d[*t] = j;
				*t += 1;
			}
		}

		for (int edge = 0; edge < 4; edge++){
			ND[i].edge[edge] = 1;
			for (int j = 0; j < 64; j++){
				if (ND[i].)
			}
		}

		}
	}

}
int check(int n, int pos){
	return 1;
}
int dfs(int n, int pos){
	return 1;
}
void assign(char bitma[][X], int pos, int ans){

}
void test(char bitmap[][X]){
	rp = 0;
	for (int y = 0; y < Y; y++){
		for (int x = 0; x < X; x++){
			mymap[y][x] = bitmap[y][x];
		}
	}
	makeDic();
	for (int i = 0; i < ALL; i++){
		if (check(i, 0)){
			dfs(i, 0);
		}
	}
	for (int i = 0; i < ALL; i++){
		assign(bitmap, i, ans_path[i]);
	}
}
