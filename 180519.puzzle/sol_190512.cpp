
unsigned char mymap[4096][4096];
const int DEPTH = 10;
int ans_cnt;
int ans_arr[256];
int loc_cnt;
int loc_arr[256];
typedef struct block{
	int info[4][DEPTH][256];
	int peak[4][256];
	int rcnt;
	int rarr[256];
	int dcnt;
	int darr[256];
	int edge[4];
}BLOCK;
BLOCK ND[256];
void makedic(){
	for (int i = 0; i < 256; i++){
		int sx, sy, tx, ty;
		sy = 256 * (i / 16);
		sx = 256 * (i % 16);

		for (int depth = 0; depth < DEPTH; depth++){
			for (int j = 0; j < 256; j++){
				ND[i].info[0][depth][j] = mymap[sy + depth][sx + j];
				ND[i].info[1][depth][j] = mymap[sy - depth + 255][sx + j];
				ND[i].info[2][depth][j] = mymap[sy + j][sx + depth];
				ND[i].info[3][depth][j] = mymap[sy + j][sx - depth + 255];
			}
		}
		for (int side = 0; side < 4; side++){
			for (int j = 0; j < 256; j++){
				int sum[256] = { 0 };
				for (int depth = 0; depth < DEPTH; depth++){
					int tmp = ND[i].info[side][depth][j];
					sum[tmp] += 1;
				}
				int idx = -1;
				int val = -1;
				for (int chk = 0; chk < 256; chk++){
					if (val < sum[chk]){
						idx = chk, val = sum[chk];
					}
				}
				ND[i].peak[side][j] = idx;
			}

			ND[i].edge[side] = 1;
			for (int depth = 0; depth < 10; depth++){
				for (int j = 0; j < 256; j++){
					if (ND[i].info[side][depth][j] >0){
						ND[i].edge[side] = 0;
						break;
					}
				}
				if (ND[i].edge[side] == 0)break;
			}					
		}
	}
	for (int i = 0; i < 256; i++){
		for (int j = 0; j < 256; j++){
			if (i == j)continue;
			int sum = 0;
			for (int ch = 1; ch < 255; ch++){
				if (ND[i].peak[1][ch] == ND[j].peak[0][ch])
					sum++;
			}
			if (sum > 245){
				ND[i].darr[ND[i].dcnt] = j;
				ND[i].dcnt += 1;
			}
			sum = 0;
			for (int ch = 1; ch < 255; ch++){
				if (ND[i].peak[3][ch] == ND[j].peak[2][ch])
					sum++;
			}
			if (sum > 240){
				ND[i].rarr[ND[i].rcnt] = j;
				ND[i].rcnt += 1;
			}
		}
	}
}
int ispossible(int n, int candi){
	if (n / 16 == 0 && ND[candi].edge[0] == 0)return 0;
	if (n / 16 == 15 && ND[candi].edge[1] == 0)return 0;
	if (n % 16 == 0 && ND[candi].edge[2] == 0)return 0;
	if (n % 16 == 15 && ND[candi].edge[3] == 0)return 0;

	if (n / 16 > 0){
		int old = loc_arr[n - 16];
		int cnt = ND[old].dcnt;
		int finded = 0;
		for (int i = 0; i < cnt; i++){
			if (ND[old].darr[i] == candi){
				finded = 1;
				break;
			}
		}
		if (!finded)
			return 0;
	}
	if (n % 16 > 0){
		int old = loc_arr[n - 1];
		int cnt = ND[old].rcnt;
		int finded = 0;
		for (int i = 0; i < cnt; i++){
			if (ND[old].rarr[i] == candi){
				finded = 1;
				break;
			}
		}
		if (!finded)
			return 0;
	}
	return 1;
}
int visited[256];
int dfs(int n){
	if (n >= 256){
		for (int i = 0; i < 256; i++){
			ans_arr[i] = loc_arr[i];
			ans_cnt = 256;
		}
		return 1;
	}
	for (int i = 0; i < 256; i++){
		if (visited[i])continue;
		if (ispossible(n, i)){
			visited[i] = 1;
			loc_arr[n] = i;
			if (dfs(n + 1))
				return 1;
			visited[i] = 0;
		}
	}
	return 0;
}
void test(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 4096; i++){
		for (int j = 0; j < 4096; j++){
			mymap[i][j] = newmap[i][j];
		}
	}
	ans_cnt = loc_cnt = 0;
	for (int i = 0; i < 256; i++){
		ans_arr[i] = loc_arr[i] = -1;
		visited[i] = 0;
	}
	makedic();
	dfs(0);
	for (int i = 0; i < 256; i++){
		int sx, sy, tx, ty;
		sy = 256 * (ans_arr[i] / 16);
		sx = 256 * (ans_arr[i] % 16);
		ty = 256 * (i / 16);
		tx = 256 * (i % 16);
		for (int y = 0; y < 256; y++){
			for (int x = 0; x < 256; x++){
				newmap[ty+y][tx+x] = mymap[sy+y][sx+x];
			}
		}
	}
}
