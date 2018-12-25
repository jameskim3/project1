/*181224
old solution is greedy algorithm
it changes no->1match->2match->3match
now i try to solve it in dfs
*/
//32
const int BLOCK = 32;
//64
const int BCNT = 64;
//4096
const int ALL_BLK = BCNT*BCNT;
const int X = 2048;
const int Y = 2048;
const int N = 100;

struct BL{
	int chk[4];
	int right[ALL_BLK];
	int down[ALL_BLK];
	int info[4][64];
	int rc, dc;
};
BL ND[BCNT][BCNT];
int MyPath[ALL_BLK];
int AnsPath[ALL_BLK];
int AnsCnt;
int visited[BCNT][BCNT];
int isSameLine(int* sl, int* tl){
	for (int i = 0; i < BLOCK; i++){
		if (sl[i] != tl[i])return 0;
	}
	return 1;
}
void makeDic(){
	for (int i = 0; i < ALL_BLK; i++){
		for (int j = 0; j < ALL_BLK; j++){
			if (i == j)continue;
			int sy, sx, ty, tx;
			sy = i / BCNT, sx = i%BCNT;
			ty = j / BCNT, tx = j%BCNT;
			if (isSameLine(ND[sy][sx].info[2], ND[ty][tx].info[3])){
				int *tp = &ND[sy][sx].rc;
				ND[sy][sx].right[*tp] = j;
				*tp += 1;
			}
			if (isSameLine(ND[sy][sx].info[1], ND[ty][tx].info[0])){
				int *tp = &ND[sy][sx].dc;
				ND[sy][sx].down[*tp] = j;
				*tp += 1;
			}
		}
	}
}
char Mybitmap[Y][X];
void swap(int src, int tar)
{
	int sy, sx, ty, tx;
	sy = src / BCNT, sx = src % BCNT;
	ty = tar / BCNT, tx = tar % BCNT;
	sy *= BLOCK, sx *= BLOCK, ty *= BLOCK, ty *= BLOCK;
	for (int y = 0; y < BLOCK; y++) {
		for (int x = 0; x < BLOCK; x++) {
			int t = Mybitmap[sy + y][sx + x];
			Mybitmap[sy + y][sx + x] = Mybitmap[ty + y][tx + x];
			Mybitmap[ty + y][tx + x] = t;
		}
	}
}
int isMember(int src, int tar, int opt){
	int sy, sx, ty, tx;
	sy = src / BCNT, sx = src % BCNT;
	ty = tar / BCNT, tx = tar % BCNT;
	if (opt == 0){
		int *cnt = &ND[sy][sx].dc;
		for (int i = 0; i < *cnt; i++){
			if (ND[sy][sx].down[i] == tar)return 1;
		}
	}
	else{
		int *cnt = &ND[sy][sx].rc;
		for (int i = 0; i < *cnt; i++){
			if (ND[sy][sx].right[i] == tar)return 1;
		}
	}
	return 0;
}
void dfs(int n){
	//end
	if (AnsCnt > 0)return;
	if (n == ALL_BLK){
		for (int i = 0; i < ALL_BLK; i++){
			AnsPath[i] = MyPath[i];
			AnsCnt = ALL_BLK;
		}
		return;
	}
	//condition
	for (int i = 0; i < BCNT; i++){
		for (int j = 0; j < BCNT; j++){
			if (visited[i][j])continue;
			if (n < BCNT && ND[i][j].chk[0]>0)continue;
			if (n % BCNT == 0 && ND[i][j].chk[3]>0)continue;
			if (n >= BCNT * (BCNT-1) && ND[i][j].chk[1]>0)continue;
			if (n % BCNT == (BCNT-1) && ND[i][j].chk[2]>0)continue;
			int up = n - BCNT;
			if (up >= 0 && !isMember(MyPath[up], i * BCNT + j, 0))continue;
			int left = n - 1;
			if (left >= 0 && left % BCNT != (BCNT - 1) && !isMember(MyPath[left], i * BCNT + j, 1))continue;
			MyPath[n] = i * BCNT + j;
			visited[i][j] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[i][j] = 0;
		}
	}
}
void test(char bitmap[][X]){
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			Mybitmap[i][j] = bitmap[i][j];
		}
	}
	for (int i = 0; i < BCNT; i++){
		for (int j = 0; j < BCNT; j++){
			int y = i * BLOCK;
			int x = j * BLOCK;
			for (int k = 0; k < BLOCK; k++){
				ND[i][j].info[0][k] = bitmap[y][x + k];
				ND[i][j].info[1][k] = bitmap[y+31][x + k];
				ND[i][j].info[2][k] = bitmap[y+k][x + 31];
				ND[i][j].info[3][k] = bitmap[y+k][x];
			}
			for (int k = 0; k < BLOCK; k++){
				if (ND[i][j].info[0][k] == 1)ND[i][j].chk[0] = 1;
				if (ND[i][j].info[1][k] == 1)ND[i][j].chk[1] = 1;
				if (ND[i][j].info[2][k] == 1)ND[i][j].chk[2] = 1;
				if (ND[i][j].info[3][k] == 1)ND[i][j].chk[3] = 1;
			}
			ND[i][j].rc = ND[i][j].dc = 0;
		}
	}
	makeDic();
	AnsCnt = 0;
	for (int i = 0; i < BCNT; i++){
		for (int j = 0; j < BCNT; j++){
			visited[i][j] = 0;
		}
	}
	dfs(0);
	int cnt = 0;
	while (cnt < ALL_BLK - 1){
		int tar = AnsPath[cnt];
		for (int i = 0; i < BCNT; i++){
			if (tar == i){
				swap(cnt, i);
				break;
			}
		}
		cnt++;
	}
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			bitmap[i][j] = Mybitmap[i][j];
		}
	}
}