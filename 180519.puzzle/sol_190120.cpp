const int WD = 10;
const int PE = 4;
typedef struct pz{
	unsigned char map[4][256][WD];
	int rcandi[256];
	int dcandi[256];
	int rcnt;
	int dcnt;
	int peak[4][256];
	int peak_cnt[4];
}PZ;
PZ ND[256];
int tmp_path[256];
int ans_path[256];
unsigned char mymap[4097][4097];
int isPossible(int pos, int n){
	if (n / 16 == 0){
		for (int i = 0; i < 256; i++){
			if (ND[pos].map[0][i][0] >0 || ND[pos].map[0][i][1] > 0)return 0;
		}
	}
	if (n / 16 == 15){
		for (int i = 0; i < 256; i++){
			if (ND[pos].map[1][i][0] >0 || ND[pos].map[1][i][1] > 0)return 0;
		}
	}
	if (n % 16 == 0){
		for (int i = 0; i < 256; i++){
			if (ND[pos].map[2][i][0] >0 || ND[pos].map[2][i][1] > 0)return 0;
		}
	}
	if (n % 16 == 15){
		for (int i = 0; i < 256; i++){
			if (ND[pos].map[3][i][0] >0 || ND[pos].map[3][i][1] > 0)return 0;
		}
	}
	int match1 = 0;
	int match2 = 0;
	if (n % 16 != 0){
		int p1 = tmp_path[n - 1];
		int p2 = pos;
		int match = 0;
		for (int i = 1; i < 255; i++){
			if (ND[p1].peak[3][i] == ND[p2].peak[2][i])match1++;
		}
		if (match1 < 240)return 0;
	}
	if (n / 16 != 0){
		int p1 = tmp_path[n - 16];
		int p2 = pos;
		int match = 0;
		for (int i = 1; i < 255; i++){
			if (ND[p1].peak[1][i] == ND[p2].peak[0][i])match2++;
		}
		if (match2 < 240)return 0;
	}
	return 1;
}
void makeDic(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 256; i++){
		int y = i / 16;
		int x = i % 16;
		y *= 256, x *= 256;
		for (int j = 0; j < 256; j++){
			for (int c = 0; c < WD; c++){
				ND[i].map[0][j][c] = newmap[y + c][x + j];
				ND[i].map[1][j][c] = newmap[y - WD + c + 256][x + j];
				ND[i].map[2][j][c] = newmap[y + j][x + c];
				ND[i].map[3][j][c] = newmap[y + j][x + -WD + c + 256];
			}
		}
		for (int s = 0; s < 4; s++){
			for (int t = 0; t < 256; t++)
				ND[i].peak[s][t] = 0;
			ND[i].peak_cnt[s] = 0;
		}
	}
	for (int i = 0; i < 256; i++){
		for (int c = 0; c < 4; c++){
			for (int j = 1; j < 255; j++){
				int sum[256] = { 0 };
				for (int k = 0; k < WD; k++){
					sum[ND[i].map[c][j][k]] += 1;
				}
				int max = -1;
				int max_idx = 0;
				for (int k = 0; k < 256; k++){
					if (sum[k] > max){
						max_idx = k;
						max = sum[k];
					}
				}
				ND[i].peak[c][j] = max_idx;
			}
		}
	}
}
int chk[256];
int dfs(int pos, int n){
	tmp_path[n] = pos;
	chk[pos] = 1;

	if (n >= 255){
		for (int i = 0; i < 256; i++){
			ans_path[i] = tmp_path[i];
		}
		return 1;
	}
	for (int i = 0; i < 256; i++){
		if (chk[i])continue;
		if (!isPossible(i, n + 1))continue;
		chk[i] = 1;
		if (dfs(i, n + 1))return 1;
		chk[i] = 0;
	}
	return 0;
}
void test(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 4096; i++){
		for (int j = 0; j < 4096; j++){
			mymap[i][j] = newmap[i][j];
		}
	}
	makeDic(newmap);
	for (int i = 0; i < 256; i++){
		chk[i] = 0;
	}

	for (int i = 0; i < 256; i++){
		if (isPossible(i, 0)){
			if (chk[i])continue;
			chk[i] = 1;
			if (dfs(i, 0))break;
			chk[i] = 0;
		}
	}
	for (int i = 0; i < 256; i++){
		int tar = ans_path[i];
		int y = i / 16;
		int x = i % 16;
		int ty = tar / 16;
		int tx = tar % 16;
		y *= 256; x *= 256;
		ty *= 256; tx *= 256;
		for (int j = 0; j < 256; j++){
			for (int k = 0; k < 256; k++){
				newmap[y + j][x + k] = mymap[ty + j][tx + k];
			}
		}
	}
}