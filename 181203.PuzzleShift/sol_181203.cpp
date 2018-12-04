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
typedef struct {
	int y, x, dir;
}HIST;
PT src, tar, zr_src, zr_tar;
HIST nd[10000];
int rp = 0;
extern int shift(int y, int x, int dir);
int MyShift(int y, int x, int dir){
	if (y + path2[dir][0] < 0 || y + path2[dir][0] >= 5)return 0;
	if (x + path2[dir][1] < 0 || x + path2[dir][1] >= 5)return 0;
	int tar_y = y + path2[dir][0];
	int tar_x = x + path2[dir][1];
	if (board2[tar_y][tar_x] != 0 && board2[y][x] != 0)return 0;
	int t = board2[y][x];
	board2[y][x] = board2[tar_y][tar_x], board2[tar_y][tar_x] = t;
	nd[rp].y = y, nd[rp].x = x, nd[rp].dir = dir, rp++;
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
int visited[5][5];
int visited_zr[5][5];
int fixed[5][5];
void scansrc(int val){
	int min = 100;
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 5; x++){
			if (board2[y][x] == val && fixed[y][x]==0){
				int dist = abs(tar.y - y) + abs(tar.x - x);
				if (dist < min){
					min = dist;
					src.y = y, src.x = x;
				}
			}
		}
	}
}
int isPoss(PT t, int opt){
	if (t.y < 0 || t.y >= 5)return 0;
	if (t.x < 0 || t.x >= 5)return 0;
	if (opt == 0){
		if (visited[t.y][t.x])return 0;
		if (fixed[t.y][t.x])return 0;
	}
	else{
		if (visited_zr[t.y][t.x])return 0;
		if (fixed[t.y][t.x])return 0;
		if (t.y == src.y&&t.x == src.x)return 0;
	}
	return 1;
}
void makeDir(PT s, PT t, int dir[4],int dist[4], int opt){
	int cnt= 0;
	for (int i = 0; i < 4; i++){
		dir[i] = i;
		PT nt;
		nt.y = s.y + path2[i][0];
		nt.x = s.x + path2[i][1];
		if (isPoss(nt, opt) == 0){
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
void reset_visited(int opt){
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 5; x++){
			if(opt==0) visited[y][x] = 0;
			else visited_zr[y][x] = 0;
		}
	}
}
int dfs(PT s, PT t, int opt){
	if (s.y == t.y&&s.x == t.x)return 1;
	if(opt==0)
		visited[s.y][s.x] = 1;
	else 
		visited_zr[s.y][s.x] = 1;
	int dir[4],dist[4];
	makeDir(s, t, dir, dist, opt);
	for (int i = 0; i < 4; i++){
		if (dist[i] == 10000)continue;
		PT ns, nt;
		if (opt == 0){
			scanzero();
			nt.y = s.y + path2[dir[i]][0];
			nt.x = s.x + path2[dir[i]][1];
			ns.y = zr_src.y;
			ns.x = zr_src.x;
			dfs(ns, nt, 1);
			reset_visited(1);
		}
		MyShift(s.y, s.x, dir[i]);
		ns.y = s.y + path2[dir[i]][0];
		ns.x = s.x + path2[dir[i]][1];
		if (opt == 0)src = ns;
		if (dfs(ns, t, opt) == 1)return 1;
		int rev_dir;
		if (dir[i] == 0) rev_dir = 1;
		if (dir[i] == 1) rev_dir = 0;
		if (dir[i] == 2) rev_dir = 3;
		if (dir[i] == 3) rev_dir = 2;
		MyShift(ns.y, ns.x, rev_dir);
	}
	if (opt == 0)
		visited[s.y][s.x] = 0;
	else 
		visited_zr[s.y][s.x] = 0;
	return 0;
}
void run(int board[5][5], int map[3][3]){
	for (int i = 0; i < 2; i++){
		for (int y = 0; y < 5; y++){
			for (int x = 0; x < 5; x++){
				board2[y][x] = board[y][x];
				visited[y][x] = 0;
				visited_zr[y][x] = 0;
				fixed[y][x] = 0;
			}
		}
		for (int y = 0; y < 3; y++){
			for (int x = 0; x < 3; x++){
				map2[y][x] = map[y][x];
			}
		}
		rp = 0;
		if (i == 0){
			for (int p = 0; p<9; p++){
				tar.y = (p / 3) + 1;
				tar.x = (p % 3) + 1;
				scansrc(map2[p / 3][p % 3]);
				dfs(src, tar, 0);
				fixed[tar.y][tar.x] = 1;
				reset_visited(0);
			}
		}
		else{
			for (int p = 8; p>=0; p--){
				tar.y = (p / 3) + 1;
				tar.x = (p % 3) + 1;
				scansrc(map2[p / 3][p % 3]);
				dfs(src, tar, 0);
				fixed[tar.y][tar.x] = 1;
				reset_visited(0);
			} 
		}
		if (rp <500)
		{
			for (int h = 0; h < rp; h++){
				shift(nd[h].y, nd[h].x, nd[h].dir);
			}
			break;
		}
	}
}