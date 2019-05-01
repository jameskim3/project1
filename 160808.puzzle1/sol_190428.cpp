const int X = 2048/4;
const int Y = 2048/4;
const int N = 500;
const int BSIZE = 32;
const int BCNT = X / BSIZE;

typedef struct bl{
	char map[4][BSIZE];
	int r[5000];
	int rcnt;
	int d[5000];
	int dcnt;
	int u[5000];
	int ucnt;
	int l[5000];
	int lcnt;
	int edge[4];
}BL;
const int ALL = BCNT*BCNT;
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
		int ty = (i/BCNT) * BSIZE;
		int tx = (i%BCNT) * BSIZE;
		for (int y = 0; y <BSIZE; y++){
			int a = mymap[y + ty][tx];
			int b = mymap[y + ty][tx + BSIZE - 1];
			ND[i].map[2][y] = mymap[y+ty][tx];
			ND[i].map[3][y] = mymap[y+ty][tx + BSIZE-1];
		}
		for (int x = 0; x <BSIZE; x++){
			ND[i].map[0][x] = mymap[ty][x+tx];
			ND[i].map[1][x] = mymap[ty+BSIZE-1][x+tx];
		}
	}

	for (int i = 0; i < ALL; i++){
		for (int j = 0; j < ALL; j++){
			if (i == j)continue;
			if (match(ND[i].map[3], ND[j].map[2], BSIZE)){
				int* t = &ND[i].rcnt;
				ND[i].r[*t] = j;
				*t += 1;
			}
			if (match(ND[i].map[1], ND[j].map[0], BSIZE)){
				int* t = &ND[i].dcnt;
				ND[i].d[*t] = j;
				*t += 1;
			}
			if (match(ND[i].map[0], ND[j].map[1], BSIZE)){
				int* t = &ND[i].ucnt;
				ND[i].u[*t] = j;
				*t += 1;
			}
			if (match(ND[i].map[2], ND[j].map[3], BSIZE)){
				int* t = &ND[i].lcnt;
				ND[i].l[*t] = j;
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
int check(int n, int pos){
	if (pos / BCNT == 0){//top
		if (ND[n].edge[0] == 0) return 0;
	}
	if (pos % BCNT == 0){
		if (ND[n].edge[2] == 0) return 0;
	}
	if (pos % BCNT == BCNT-1){
		if (ND[n].edge[3] == 0) return 0;
	}
	if (pos / BCNT == BCNT-1){
		if (ND[n].edge[1] == 0) return 0;
	}

	int tmp;
	int cnt;
	if (pos - BCNT >= 0 && loc_path[pos - BCNT]>=0){
		tmp = loc_path[pos - BCNT];
		cnt = ND[tmp].dcnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			if (ND[tmp].d[ch] == n){
				valid = 1;
				break;
			}
		}
		if (!valid)return 0;
	}
	if (pos + BCNT < ALL && loc_path[pos + BCNT]>=0){
		tmp = loc_path[pos + BCNT];
		cnt = ND[tmp].ucnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			if (ND[tmp].u[ch] == n){
				valid = 1;
				break;
			}
		}
		if (!valid)return 0;
	}
	if (pos % BCNT > 0 && loc_path[pos - 1]>=0){
		tmp = loc_path[pos - 1];
		cnt = ND[tmp].rcnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			if (ND[tmp].r[ch] == n){
				valid = 1;
				break;
			}
		}
		if (!valid)return 0;
	}
	if (pos % BCNT < BCNT - 1 && loc_path[pos + 1]>=0){
		tmp = loc_path[pos + 1];
		cnt = ND[tmp].lcnt;
		int valid = 0;
		for (int ch = 0; ch < cnt; ch++){
			if (ND[tmp].l[ch] == n){
				valid = 1;
				break;
			}
		}
		if (!valid)return 0;
	}
	return 1;
}
int getnewdir(int pos, int predir){
	if (predir == 0){
		if (pos - BCNT >= 0 && loc_path[pos - BCNT]<0)
			return 0;
		else 
			return getnewdir(pos, 3);
	}
	if (predir == 3){
		if (pos % BCNT < BCNT - 1 && loc_path[pos + 1]<0)
			return 3;
		else
			return getnewdir(pos, 1);
	}
	if (predir == 1){
		if (pos + BCNT < ALL && loc_path[pos + BCNT]<0)
			return 1;
		else
			return getnewdir(pos, 2);
	}
	if (predir == 2){
		if (pos % BCNT > 0 && loc_path[pos - 1]<0)
			return 2;
		else
			return getnewdir(pos, 0);
	}
}
int dfs(int n, int pos, int predir, int tot){
	loc_path[pos] = n;

	if (tot >= ALL - 1){
		for (int i = 0; i < ALL; i++){
			ans_path[i] = loc_path[i];
		}
		return 1;
	}

	int newpos;
	int newdir = getnewdir(pos, predir);
	if (newdir == 0) newpos = pos - BCNT;
	else if (newdir == 1) newpos = pos + BCNT;
	else if (newdir == 2) newpos = pos - 1;
	else if (newdir == 3) newpos = pos + 1;

	for (int i = 0; i < ALL; i++){
		if (visited_n[i])
			continue;
		if (check(i, newpos) == 0)
			continue;
		visited_n[i] = 1;
		if (dfs(i, newpos, newdir, tot+1))
			return 1;
		visited_n[i] = 0;
	}
	loc_path[pos] = -1;
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
	for (int i = 0; i < ALL; i++){
		visited_n[i] = 0;
		loc_path[i] = -1;
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
	for (int i = 0; i < ALL; i++){
		if (check(i, 0) == 0)
			continue;
		visited_n[i] = 1;
		if (dfs(i, 0, 3, 0))
			break;
		visited_n[i] = 0;
	}
	for (int i = 0; i < ALL; i++){
		assign(bitmap, i, ans_path[i]);
	}
}
