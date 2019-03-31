//ERR:39266968095561, PERFORM : 5949
//ERR:38893783470342, PERFORM:6205

extern int DONE;
char MyCell[5000][5000];
int P[5][2];
#define MAX_SIZE 1000000
typedef struct pq{
	int src;
	int tar;
	int y;
	int x;
	int val;
}PQ;
PQ heap[4][MAX_SIZE];
int heapSize[4];


void heapInit(void)
{
	for (int i = 0; i < 4; i++)
		heapSize[i] = 0;
}
int heapPush(int src, int tar, int y, int x, int val){
	src -= 1;
	if (heapSize[src] + 1 > MAX_SIZE)
	{
		return 0;
	}

	heap[src][heapSize[src]].src = src;
	heap[src][heapSize[src]].tar = tar;
	heap[src][heapSize[src]].y = y;
	heap[src][heapSize[src]].x = x;
	heap[src][heapSize[src]].val = val;

	int current = heapSize[src];
	while (current > 0 && heap[src][current].val < heap[src][(current - 1) / 2].val)
	{
		PQ temp = heap[src][(current - 1) / 2];
		heap[src][(current - 1) / 2] = heap[src][current];
		heap[src][current] = temp;
		current = (current - 1) / 2;
	}

	heapSize[src] = heapSize[src] + 1;

	return 1;
}

int heapPop(int src, PQ *value)
{
	src -= 1;
	if (heapSize[src] <= 0)
	{
		return -1;
	}

	*value = heap[src][0];
	heapSize[src] = heapSize[src] - 1;

	heap[src][0] = heap[src][heapSize[src]];

	int current = 0;
	while (current * 2 + 1 < heapSize[src])
	{
		int child;
		if (current * 2 + 2 == heapSize[src])
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[src][current * 2 + 1].val < heap[src][current * 2 + 2].val ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[src][current].val < heap[src][child].val)
		{
			break;
		}

		PQ temp = heap[src][current];
		heap[src][current] = heap[src][child];
		heap[src][child] = temp;

		current = child;
	}
	return 1;
}

int cal_dist2(int sy, int sx, int ty, int tx){
	int v = (sy - ty)*(sy - ty);
	v += (sx - tx)*(sx - tx);
	return v;
}
int abs2(int a){
	return a > 0 ? a : -a;
}
void func1(void* param){
	heapInit();
	int cnt = 0;
	int psum[5];
	psum[1] = psum[2] = psum[3] = psum[4] = 0;
	char* ptr = (char*)param;
	for (int i = 0; i < 5000; i++){
		for (int j = 0; j < 5000; j++){
			MyCell[i][j] = ptr[i * 5000 + j];
			if (MyCell[i][j]<0){
				int idx = MyCell[i][j] * -1;
				P[idx][0] = i;
				P[idx][1] = j;
			}
		}
	}
	for (int i = 0; i < 5000; i++){
		for (int j = 0; j < 5000; j++){
			if (MyCell[i][j]>0){
				int min_idx;
				int min_val = 5000 * 5000 * 50;
				for (int c = 1; c < 5; c++){
					int v = cal_dist2(P[c][0], P[c][1], i, j);
					if (min_val > v){
						min_val = v;
						min_idx = c;
					}
				}
				MyCell[i][j] = min_idx;
				psum[min_idx]++;

				for (int c = 1; c < 5; c++){
					if (c == min_idx)continue;
					int f1 = cal_dist2(P[c][0], P[c][1],i, j);
					int f2 = cal_dist2(P[min_idx][0], P[min_idx][1],i, j);
					heapPush(min_idx, c, i, j, abs2(f1 - f2));
				}
			}
		}
	}

	int def_max = 67500;
	int tar;
	int src = 1;
	PQ tmp;
	while (psum[1] > def_max || psum[2] > def_max || psum[3] > def_max || psum[4] > def_max){
		int min_idx = -1;
		int min_val = 999999999;
		for (int c = 1; c < 5; c++){
			heapPop(c, &tmp);
			if (tmp.val<min_val && psum[c]>def_max && psum[tmp.tar] < def_max){
				min_val = tmp.val;
				min_idx = c;
			}
			heapPush(c, tmp.tar, tmp.y, tmp.x, tmp.val);
		}
		if (min_idx == -1){
			for (int c = 1; c < 5; c++){
				if (psum[c] > def_max){
					min_idx = c;
					break;
				}
			}
		}
		src = min_idx;
		while (psum[src] > def_max){
			heapPop(src, &tmp);
			tar = tmp.tar;
			if (MyCell[tmp.y][tmp.x] != src)
				continue;
			if (psum[tar] >= def_max)continue;
			psum[src]--;
			psum[tar]++;
			MyCell[tmp.y][tmp.x] = tar;
		}
	}

	for (int i = 0; i < 5000; i++){
		for (int j = 0; j < 5000; j++){
			ptr[i * 5000 + j] = MyCell[i][j];
		}
	}
	DONE = 1;
}
void func2(void* param){
	//DONE = 1;
}
