/*181224
old solution is greedy algorithm
it changes no->1match->2match->3match
now i try to solve it in dfs
*/
//32
const int BLOCK = 32;
const int X = 2048/4;
const int Y = 2048/4;
const int N = 100/4;
//64
const int BCNT = X / BLOCK;
const int ALL_BLK = BCNT*BCNT;

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
int visited[ALL_BLK];
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
	sy *= BLOCK, sx *= BLOCK, ty *= BLOCK, tx *= BLOCK;
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
	int uy, ux, ly, lx;
	int uchk, lchk;
	uchk = lchk = 1;
	if (n % BCNT == 0) lchk = 0;
	if (n < BCNT) uchk = 0;

	int left = lchk? MyPath[n - 1] : -1;
	int up = uchk ? MyPath[n - BCNT] : -1;
	uy = up / BCNT, ux = up % BCNT;
	ly = left / BCNT, lx = left % BCNT;

	if (lchk && uchk){
		for (int i = 0; i < ND[ly][lx].rc; i++){
			for (int j = 0; j < ND[uy][ux].dc; j++){
				if (ND[ly][lx].right[i] == ND[uy][ux].down[j]){
					int tp = ND[ly][lx].right[i];
					if (visited[tp])continue;
					MyPath[n] = tp;
					visited[tp] = 1;
					dfs(n + 1);
					if (AnsCnt > 0)return;
					visited[tp] = 0;
				}
			}
		}
	}
	else if (lchk){
		for (int i = 0; i < ND[ly][lx].rc; i++){
			int tp = ND[ly][lx].right[i];
			if (visited[tp])continue;
			MyPath[n] = tp;
			visited[tp] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[tp] = 0;
		}
	}
	else if (uchk){
		for (int i = 0; i < ND[uy][ux].dc; i++){
			int tp = ND[uy][ux].down[i];
			if (visited[tp])continue;
			MyPath[n] = tp;
			visited[tp] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[tp] = 0;
		}
	}
	else{
		for (int i = 0; i < ALL_BLK; i++){
			int tp = i;
			if (visited[tp])continue;
			MyPath[n] = tp;
			visited[tp] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[tp] = 0;
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
	for (int i = 0; i < ALL_BLK; i++){
		visited[i]= 0;
	}
	dfs(0);
	int cnt = 0;
	while (cnt < ALL_BLK - 1){
		int tar = AnsPath[cnt];
		for (int i = 0; i < ALL_BLK; i++){
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