/*181224
old solution is greedy algorithm
it changes no->1match->2match->3match
now i try to solve it in dfs
*/
//32
const int BLOCK = 32;
const int X = 2048/2;
const int Y = 2048/2;
//64
const int BCNT = X / BLOCK;
const int ALL_BLK = BCNT*BCNT;
unsigned long long gc;
struct BL{
	int chk[4];
	int right[ALL_BLK];
	int down[ALL_BLK];
	int info[4][64];
	int rc, dc;
};
BL ND[ALL_BLK];
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
			if (isSameLine(ND[i].info[2], ND[j].info[3])){
				int *tp = &ND[i].rc;
				ND[i].right[*tp] = j;
				*tp += 1;
			}
			if (isSameLine(ND[i].info[1], ND[j].info[0])){
				int *tp = &ND[i].dc;
				ND[i].down[*tp] = j;
				*tp += 1;
			}
		}
	}
}
char Mybitmap[Y][X];
void swap(int src, int tar)
{
	if (src == tar)return;
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
		int *cnt = &ND[src].dc;
		for (int i = 0; i < *cnt; i++){
			if (ND[src].down[i] == tar)return 1;
		}
	}
	else{
		int *cnt = &ND[src].rc;
		for (int i = 0; i < *cnt; i++){
			if (ND[src].right[i] == tar)return 1;
		}
	}
	return 0;
}
int checkValid(int n, int tp){
	if (visited[tp])return 0;
	if (n%BCNT == 0){
		if (ND[tp].chk[3]>0)return 0;
	}
	if (n%BCNT == BCNT - 1){
		if (ND[tp].chk[2]>0)return 0;
	}
	if (n<BCNT){
		if (ND[tp].chk[0]>0)return 0;
	}
	if (n>=BCNT*(BCNT-1)){
		if (ND[tp].chk[1]>0)return 0;
	}
	return 1;
}
void dfs(int n){
	gc++;
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
		for (int i = 0; i < ND[left].rc; i++){
			for (int j = 0; j < ND[up].dc; j++){
				gc++;
				if (ND[left].right[i] == ND[up].down[j]){
					int tp = ND[left].right[i];
					if (!checkValid(n,tp))continue;
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
		for (int i = 0; i < ND[left].rc; i++){
			gc++;
			int tp = ND[left].right[i];
			if (!checkValid(n, tp))continue;
			MyPath[n] = tp;
			visited[tp] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[tp] = 0;
		}
	}
	else if (uchk){
		for (int i = 0; i < ND[up].dc; i++){
			gc++;
			int tp = ND[up].down[i];
			if (!checkValid(n, tp))continue;
			MyPath[n] = tp;
			visited[tp] = 1;
			dfs(n + 1);
			if (AnsCnt > 0)return;
			visited[tp] = 0;
		}
	}
	else{
		for (int i = 0; i < ALL_BLK; i++){
			gc++;
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
	gc = 0;
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			Mybitmap[i][j] = bitmap[i][j];
		}
	}
	for (int i = 0; i < BCNT; i++){
		for (int j = 0; j < BCNT; j++){
			int pos = i*BCNT + j;
			int y = i * BLOCK;
			int x = j * BLOCK;
			ND[pos].chk[0] = 0;
			ND[pos].chk[1] = 0;
			ND[pos].chk[2] = 0;
			ND[pos].chk[3] = 0;

			for (int k = 0; k < BLOCK; k++){
				ND[pos].info[0][k] = bitmap[y][x + k];
				ND[pos].info[1][k] = bitmap[y+31][x + k];
				ND[pos].info[2][k] = bitmap[y+k][x + 31];
				ND[pos].info[3][k] = bitmap[y+k][x];
			}
			for (int k = 0; k < BLOCK; k++){
				if (ND[pos].info[0][k] == 1)ND[pos].chk[0] = 1;
				if (ND[pos].info[1][k] == 1)ND[pos].chk[1] = 1;
				if (ND[pos].info[2][k] == 1)ND[pos].chk[2] = 1;
				if (ND[pos].info[3][k] == 1)ND[pos].chk[3] = 1;
			}
			ND[pos].rc = ND[pos].dc = 0;
		}
	}
	makeDic();
	AnsCnt = 0;
	for (int i = 0; i < ALL_BLK; i++){
		visited[i]= 0;
	}
	dfs(0);
	int cnt = 0;
	for (int i = 0; i < ALL_BLK; i++){
		visited[i] = i;
	}
	while (cnt < ALL_BLK - 1){
		int tar = AnsPath[cnt];
		if (tar != visited[cnt]){
			int corr = -1;
			for (int i = cnt; i < ALL_BLK; i++){
				if (visited[i] == tar){
					corr = i;
					break;
				}
			}
			swap(cnt, corr);
			int st = visited[corr];
			visited[corr] = visited[cnt];
			visited[cnt] = st;
		}
		cnt++;
	}
	for (int i = 0; i < Y; i++){
		for (int j = 0; j < X; j++){
			bitmap[i][j] = Mybitmap[i][j];
		}
	}
}