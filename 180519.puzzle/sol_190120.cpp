typedef struct pz{
	unsigned char map[4][2][256];
	int rcandi[256];
	int dcandi[256];
	int rcnt;
	int dcnt;
	int peak[4][256];
}PZ;
PZ ND[256];
int tmp_path[256];
int ans_path[256];
unsigned char mymap[4097][4097];
int isPossible(int c, int n){
	if (n / 256 == 0){
		for (int i = 0; i < 256; i++){
			if (ND[c].map[0][0][i] >0 || ND[c].map[0][1][i] > 0)return 0;
		}
	}
	if (n % 256 == 0){
		for (int i = 0; i < 256; i++){
			if (ND[c].map[3][0][i] >0 || ND[c].map[3][1][i] > 0)return 0;
		}
	}
	if (n % 256 == 255){
		for (int i = 0; i < 256; i++){
			if (ND[c].map[2][0][i] >0 || ND[c].map[2][1][i] > 0)return 0;
		}
	}
	return 1;
}
void makeDic(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 256; i++){
		int y = i / 16;
		int x = i % 16;
		y *= 256, x *= 256;
		for (int j = 0; j < 256; j++){
			for (int c = 0; c < 2; c++){
				ND[i].map[0][c][j] = newmap[y + c][x + j];
				ND[i].map[1][c][j] = newmap[y + c + 254][x + j];
				ND[i].map[2][c][j] = newmap[y + j][x + c];
				ND[i].map[3][c][j] = newmap[y + j][x + c + 254];
			}
		}
		for (int s = 0; s < 4; s++){
			for (int t = 0; t < 256; t++)
				ND[i].peak[s][t] = 0;
		}
	}
	for (int c = 0; c < 4; c++){
		for (int i = 1; i < 255; i++){

		}
	}
}
int dfs(int n){

}
void test(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 4096; i++){
		for (int j = 0; j < 4096; j++){
			mymap[i][j] = newmap[i][j];
		}
	}
	makeDic(newmap);

	for (int i = 0; i < 256; i++){
		if (isPossible(i, 0)){
			if (dfs(i))break;
		}
	}
	for (int i = 0; i < 256; i++){
		int tar = ans_path[i];
		int y = i / 16;
		int x = i % 16;
		int ty = tar / 16;
		int tx = tar % 16;
		y *= 256; x *= 256;
		ty *= 256; tx *= 16;
		for (int i = 0; i < 256;i++){
			for (int j = 0; j < 256; j++){
				newmap[y + i][x + j] = mymap[ty + i][tx + j];
			}
		}
	}
}