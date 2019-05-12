const int X = 2048 / 2;
const int Y = 2048 / 2;
const int N = 500;
const int BSIZE = 32;
const int BCNT = X / BSIZE;
const int ALL = BCNT*BCNT;

unsigned long long gc;

typedef struct bl{
	char map[4][BSIZE];
	char throu[4][BSIZE];
	int r[ALL];
	int rcnt;
	int d[ALL];
	int dcnt;
	int edge[4];
}BL;
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
		int ty = (i / BCNT) * BSIZE;
		int tx = (i%BCNT) * BSIZE;
		for (int y = 0; y <BSIZE; y++){
			ND[i].map[2][y] = mymap[y + ty][tx];
			ND[i].map[3][y] = mymap[y + ty][tx + BSIZE - 1];
			int ts = 0;
			for (int throu = 0; throu < BSIZE; throu++){
				if (mymap[y + ty][tx + throu] == 0)break;
				ts += mymap[y + ty][tx + throu];
			}
			ND[i].throu[2][y] = ts;
			ts = 0;
			for (int throu = BSIZE-1; throu >=0; throu--){
				if (mymap[y + ty][tx + throu] == 0)break;
				ts += mymap[y + ty][tx + throu];
			}
			ND[i].throu[3][y] = ts;
		}
		for (int x = 0; x <BSIZE; x++){
			ND[i].map[0][x] = mymap[ty][x + tx];
			ND[i].map[1][x] = mymap[ty + BSIZE - 1][x + tx];
			int ts = 0;
			for (int throu = 0; throu < BSIZE; throu++){
				if (mymap[ty + throu][x + tx] == 0)break;
				ts += mymap[ty + throu][x + tx];
			}
			ND[i].throu[0][x] = ts;
			ts = 0;
			for (int throu = BSIZE - 1; throu >= 0; throu--){
				if (mymap[ty + throu][x + tx] == 0)break;
				ts += mymap[ty + throu][x + tx];
			}
			ND[i].throu[1][x] = ts;
		}
	}

	for (int i = 0; i < ALL; i++){
		for (int j = 0; j < ALL; j++){
			if (i == j)continue;
			if (match(ND[i].map[3], ND[j].map[2], BSIZE)){
				int chk2 = 1;
				for (int thr = 1; thr < BSIZE - 1; thr++){
					if (ND[i].map[3][thr]>0){
						if (ND[i].throu[3][thr] + ND[j].throu[2][thr] < 32){
							chk2 = 0;
							break;
						}
					}
				}
				if (chk2 == 0)
					continue;
				int* t = &ND[i].rcnt;
				ND[i].r[*t] = j;
				*t += 1;
			}
			if (match(ND[i].map[1], ND[j].map[0], BSIZE)){
				int chk2 = 1;
				for (int thr = 1; thr < BSIZE - 1; thr++){
					if (ND[i].map[1][thr]>0){
						if (ND[i].throu[1][thr] + ND[j].throu[0][thr] < 32){
							chk2 = 0;
							break;
						}
					}
				}
				if (chk2 == 0)
					continue;
				int* t = &ND[i].dcnt;
				ND[i].d[*t] = j;
				*t += 1;
			}
		}

		for (int edge = 0; edge < 4; edge++){
			ND[i].edge[edge] = 1;
			for (int j = 0; j < BSIZE; j++){
				if (ND[i].map[edge][j]>0){
					ND[i].edge[edge] = 0;
					break;
				}
			}
		}
	}
}
int visited_n[ALL];
int edgecheck(int n, int pos){
	if (pos / BCNT == 0){//top
		if (ND[n].edge[0] == 0) return 0;
	}
	if (pos % BCNT == 0){
		if (ND[n].edge[2] == 0) return 0;
	}
	if (pos % BCNT == BCNT - 1){
		if (ND[n].edge[3] == 0) return 0;
	}
	if (pos / BCNT == BCNT - 1){
		if (ND[n].edge[1] == 0) return 0;
	}
	return 1;
}
int check(int n, int pos){
	int lchk, dchk;
	lchk = pos%BCNT > 0 ? 1 : 0;
	dchk = pos - BCNT >= 0 ? 1 : 0;
	int tmp;
	int cnt;
	if (dchk){
		tmp = loc_path[pos - BCNT];
		cnt = ND[tmp].dcnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			gc++;
			if (ND[tmp].d[ch] == n && edgecheck(n,pos)){
				valid = 1;
				break;
			}
			if (ND[tmp].d[ch]>n)break;
		}
		if (!valid)return 0;
	}
	if (lchk){
		tmp = loc_path[pos - 1];
		cnt = ND[tmp].rcnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			gc++;
			if (ND[tmp].r[ch] == n&& edgecheck(n, pos)){
				valid = 1;
				break;
			}
			if (ND[tmp].r[ch]>n)break;
		}
		if (!valid)return 0;
	}
	return 1;
}
int dfs(int pos){
	if (pos >= ALL){
		for (int i = 0; i < ALL; i++){
			ans_path[i] = loc_path[i];
		}
		return 1;
	}

	for (int i = 0; i < ALL; i++){
		if (visited_n[i])
			continue;
		if (check(i, pos) == 0)
			continue;
		loc_path[pos] = i;
		visited_n[i] = 1;
		if (dfs(pos + 1))
			return 1;
		visited_n[i] = 0;
	}
	return 0;
}
void assign(char bitmap[][X], int pos, int ans){
	int y = pos / BCNT;
	int x = pos % BCNT;
	y *= BSIZE;
	x *= BSIZE;
	int sy = ans / BCNT;
	int sx = ans % BCNT;
	sy *= BSIZE;
	sx *= BSIZE;
	for (int i = 0; i < BSIZE; i++){
		for (int j = 0; j < BSIZE; j++){
			bitmap[y + i][x + j] = mymap[sy + i][sx + j];
		}
	}
}
void test(char bitmap[][X]){
	gc = 0;
	for (int i = 0; i < ALL; i++){
		visited_n[i] = 0;
		loc_path[i] = -1;
		ND[i].dcnt = ND[i].rcnt = 0;
	}
	ans_cnt = 0;
	loc_cnt = 0;
	rp = 0;
	for (int y = 0; y < Y; y++){
		for (int x = 0; x < X; x++){
			mymap[y][x] = bitmap[y][x];
		}
	}
	makeDic();
	dfs(0);
	for (int i = 0; i < ALL; i++){
		assign(bitmap, i, ans_path[i]);
	}
}
