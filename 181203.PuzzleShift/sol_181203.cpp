int board2[5][5];
int map2[3][3];
int path2[4][2] = {
	{ -1, 0 },
	{ 1, 0 },
	{ 0, -1 },
	{ 0, 1 },
};
typedef struct {
	int y, x;
}PT;
PT src, tar, zr_src,zr_tar;
extern int shift(int y, int x, int dir);
int MyShift(int y, int x, int dir){
	if (y + path2[dir][0] < 0 || y + path2[dir][0] >= 5)return 0;
	if (x + path2[dir][1] < 0 || x + path2[dir][1] >= 5)return 0;
	int tar_y = y + path2[dir][0];
	int tar_x = x + path2[dir][1];
	if (board2[tar_y][tar_x] != 0 && board2[y][x] != 0)return 0;
	int t = board2[y][x];
	board2[y][x] = board2[tar_y][tar_x], board2[tar_y][tar_x] = t;
	return 1;
}
void scanzero(){
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 5; x++){
			if (board2[y][x] == 0){
				zr_src.y = y, zr_src.x = x;
				return;
			}
		}
	}
}
int abs(int a){
	return a > 0 ? a : -a;
}
void scansrc(int val){
	int min = 100;
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 5; x++){
			if (board2[y][x] == val){
				int dist = abs(tar.y - y) + abs(tar.x - x);
				if (dist < min){
					min = dist;
					src.y = y, src.x = x;
				}
			}
		}
	}
}
int visited[5][5];
int fixed[5][5];
int isPoss(PT t){
	if (t.y < 0 || t.y >= 5)return 0;
	if (t.x < 0 || t.x >= 5)return 0;
	if (visited[t.y][t.x])return 0;
	if (fixed[t.y][t.x])return 0;
	return 1;
}
void makeDir(PT s, PT t, int dir[4],int dist[4]){
	int cnt= 0;
	for (int i = 0; i < 4; i++){
		dir[i] = i;
		PT nt;
		nt.y = s.y + path2[i][0];
		nt.x = s.x + path2[i][1];
		if (isPoss(nt) == 0){
			dist[i] = 10000;
			continue;
		}
		dist[i] = abs(t.y - nt.y) + abs(t.x - nt.x);
	}
	for (int i = 0; i < 4; i++){
		for (int j = i + 1; j < 4; j++){
			if (dist[i] > dist[j]){
				int t = dist[i];
				dist[i] = dist[j], dist[j] = t;
				t = dir[i];
				dir[i] = dir[j], dir[j] = t;
			}
		}
	}
}
int dfs(PT s, PT t){
	if (s.y == t.y&&s.x == t.x)return 1;
	visited[s.y][s.x] = 1;
	int dir[4],dist[4];
	makeDir(s, t, dir,dist);
	for (int i = 0; i < 4; i++){
		if (dist[i] == 10000)continue;
		PT ns, nt;
		scanzero();
		nt.y = s.y + path2[dir[i]][0];
		nt.x = s.x + path2[dir[i]][1];
		ns.y = zr_src.y;
		ns.x = zr_src.x;
		dfs(ns, nt);
		MyShift(s.y, s.x, dir[i]);
		shift(s.y, s.x, dir[i]);
		ns.y = s.y + path2[dir[i]][0];
		ns.x = s.x + path2[dir[i]][1];
		if (dfs(ns, t) == 1)return 1;
		int rev_dir;
		if (dir[i] == 0) rev_dir = 1;
		if (dir[i] == 1) rev_dir = 0;
		if (dir[i] == 2) rev_dir = 3;
		if (dir[i] == 3) rev_dir = 2;
		MyShift(s.y, s.x, rev_dir);
		shift(s.y, s.x, rev_dir);
	}
	visited[s.y][s.x] = 0;
}
void run(int board[5][5], int map[3][3]){
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 5; x++){
			board2[y][x] = board[y][x];
			visited[y][x] = 0;
			fixed[y][x] = 0;
		}
	}
	for (int y = 0; y < 3; y++){
		for (int x = 0; x <3; x++){
			map2[y][x] = map[y][x];
		}
	}
	for (int y = 0; y < 3; y++){
		for (int x = 0; x < 3; x++){
			tar.y = y + 1;
			tar.x = x + 1;
			scansrc(map2[y][x]);
			visited[src.y][src.x] = 1;
			dfs(src, tar);
			fixed[tar.y][tar.x] = 1;
		}
	}
}