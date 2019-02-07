//RESULT: 42850900
extern void move_trash(int y, int x, int d);
typedef struct P{
	int y, x, src, tar,val;
}PQ;
typedef struct C{
	int y, x, cnt;
}CAN;
typedef struct Q{
	int y, x, dir, pre;
}QUE;
QUE que[2000000];
int wp, rp;
int mymap[1001][1001];
CAN can[4];

#define MAX_SIZE 2000000
PQ heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}
int heapPush(int y,int x,int src,int tar, int val){
	if (heapSize + 1 > MAX_SIZE)
	{
		return 0;
	}

	heap[heapSize].y = y;
	heap[heapSize].x = x;
	heap[heapSize].src = src;
	heap[heapSize].tar = tar;
	heap[heapSize].val = val;

	int current = heapSize;
	while (current > 0 && heap[current].val < heap[(current - 1) / 2].val)
	{
		PQ temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int heapPop(PQ *value)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1].val < heap[current * 2 + 2].val ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current].val < heap[child].val)
		{
			break;
		}

		PQ temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
}

int abs(int a){ return a>0 ? a : -a; }
int dist(int sy, int sx, int ty, int tx){
	return abs(sy - ty) + abs(sx - tx);
}
void inque(int y, int x, int val, int pre){
	que[wp].y = y;
	que[wp].x = x;
	que[wp].dir = val;
	que[wp++].pre = pre;
}
void deque(QUE* val){
	val->dir = que[rp].dir;
	val->pre = que[rp].pre;
	val->y= que[rp].y;
	val->x= que[rp++].x;
}
int yy[4] = { 1, -1, 0, 0 };
int xx[4] = { 0, 0, 1, -1 };
int chk[1001][1001];
void bfs(int c){
	for (int i = 0; i < 1001; i++){
		for (int j = 0; j < 1001; j++){
			chk[i][j] = 0;
		}
	}
	rp = wp = 0;
	inque(can[c].y, can[c].x, -1, -1);
	chk[can[c].y][can[c].x] = 1;
	QUE tmp;
	while (rp < wp){
		deque(&tmp);
		if (mymap[tmp.y][tmp.x] == c){
			mymap[tmp.y][tmp.x] = 0;
			while (tmp.pre >= 0){
				move_trash(tmp.y, tmp.x, tmp.dir);
				tmp = que[tmp.pre];
			}
		}
		for (int i = 0; i < 4; i++){
			int ty = yy[i] + tmp.y;
			int tx = xx[i] + tmp.x;
			if (ty >= 1000 || ty < 0 || tx >= 1000 || tx < 0)continue;
			if (chk[ty][tx] == 1)continue;
			if (mymap[ty][tx] == -4)continue;
			if (mymap[ty][tx] == 0 || mymap[ty][tx] == c){
				inque(ty, tx, i, rp - 1);
				chk[ty][tx] = 1;
			}
		}
	}
}
void test(int trash_map[1000][1000]){
	heapInit();
	int cnt = 1;
	for (int i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
			mymap[i][j] = trash_map[i][j];
			if (mymap[i][j]>0){
				cnt = mymap[i][j];
				can[cnt].y = i, can[cnt].x = j, can[cnt].cnt = 0;
				mymap[i][j] = -4;
			}
		}
	}
	for (int i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
			if (mymap[i][j] == -1){
				int min_idx;
				int min = 1000000;
				for (int c = 1; c < 4; c++){
					int val = dist(can[c].y, can[c].x, i, j);
					if (min > val){
						min = val, min_idx = c;
					}
				}
				mymap[i][j] = min_idx;
				can[min_idx].cnt++;
				for (int c = 1; c < 4; c++){
					if (c == min_idx)continue;
					int val = dist(can[c].y, can[c].x, i, j);
					int val2 = dist(can[min_idx].y, can[min_idx].x, i, j);
					heapPush(i, j, min_idx, c, abs(val-val2));
				}
			}
		}
	}
	int min_idx;
	int min_val=1000000;
	for (int c = 1; c < 4; c++){
		if (min_val > can[c].cnt){
			min_idx = c;
			min_val = can[c].cnt;
		}
	}
	PQ tmp;
	while (can[min_idx].cnt < 3000){
		heapPop(&tmp);
		if (tmp.tar != min_idx)continue;
		if (mymap[tmp.y][tmp.x] != tmp.src)continue;
		can[tmp.tar].cnt++;
		can[tmp.src].cnt--;
		mymap[tmp.y][tmp.x] = tmp.tar;
	}
	heapInit();
	for (int i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
			if (mymap[i][j] != min_idx && mymap[i][j]>0){
				for (int c = 1; c < 4; c++){
					//if (c == mymap[i][j] || c==min_idx)continue;
					if (c == mymap[i][j])continue;
					int val= dist(i, j, can[c].y, can[c].x);
					int val2 = dist(can[mymap[i][j]].y, can[mymap[i][j]].x, i, j);
					heapPush(i, j, mymap[i][j], c, abs(val-val2));
				}
			}
		}
	}
	while (can[1].cnt > 3500 || can[2].cnt>3500 || can[3].cnt>3500){
		heapPop(&tmp);
		if (can[tmp.src].cnt <= 3500)continue;
		if (mymap[tmp.y][tmp.x] != tmp.src)continue;
		can[tmp.tar].cnt++;
		can[tmp.src].cnt--;
		mymap[tmp.y][tmp.x] = tmp.tar;
	}
	for (int c = 1; c < 4; c++){
		bfs(c);
	}
}
