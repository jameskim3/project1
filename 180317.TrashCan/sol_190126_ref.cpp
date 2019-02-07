//result 42869504

void move_trash(int y, int x, int d);
typedef struct{
	int y, x, cnt;
}CAN;
typedef struct{
	int y, x, value, pre;
}QUE;
typedef struct{
	int y, x, ori, aft, value;
}PQ;
CAN can[5];
QUE que[2000000];
QUE Q;
int mymap[1001][1001];
int check[1001][1001];
int sum, sum1, sum2;
int wp, rp;
int xx[] = { 0, 0, 1, -1 };
int yy[] = { 1, -1, 0, 0 };
PQ heap[1000000];
int MAX_SIZE = 100000;
int heapSize;
int abs(int a, int b){
	if (a - b > 0)return a - b;
	return b - a;
}
void heapInit(){
	heapSize = 0;
}
int heapPush(int a, int b, int c, int d){
	if (heapSize + 1 > MAX_SIZE){
		return 0;
	}
	heap[heapSize].y = a;
	heap[heapSize].x = b;
	heap[heapSize].ori = c;
	heap[heapSize].aft = d;
	heap[heapSize].value = (abs(can[d].y, a) + abs(can[d].x, b)) - (abs(can[c].y, a) + abs(can[c].x, b));
	int current = heapSize;
	while (current > 0 && heap[current].value < heap[(current - 1) / 2].value){
		PQ temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2;
	}
	heapSize = heapSize + 1;
	return 1;
}
PQ heapPop(){
	PQ value = heap[0];
	heapSize = heapSize - 1;
	heap[0] = heap[heapSize];
	int current = 0;
	while (current * 2 + 1 < heapSize){
		int child;
		if (current * 2 + 2 == heapSize){
			child = current * 2 + 1;
		}
		else{
			child = heap[current * 2 + 1].value < heap[current * 2 + 2].value ? current * 2 + 1 : current * 2 + 2;
		}
		if (heap[current].value < heap[child].value){
			break;
		}
		PQ temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;
		current = child;
	}
	return value;
}

void in_que(int a, int b, int c, int d){
	que[wp].y = a;
	que[wp].x = b;
	que[wp].value = c;
	que[wp++].pre = d;
	return;
}
int out_que(){
	if (wp <= rp)return 0;
	Q.y = que[rp].y;
	Q.x = que[rp].x;
	Q.value = que[rp].value;
	Q.pre = que[rp++].pre;
	return 1;
}
void bfs(int n){
	int i, j, x, y;
	for (i = 0; i < 1000; i++){
		for (int j = 0; j < 1000; j++){
			check[i][j] = 0;
		}
	}
	wp = rp = 0;
	in_que(can[n].y, can[n].x, -1, -1);
	check[can[n].y][can[n].x] = 1;
	while (out_que()){
		if (mymap[Q.y][Q.x] == n){
			mymap[Q.y][Q.x] = 0;
			while (Q.value >= 0){
				move_trash(Q.y, Q.x, Q.value);
				sum2++;
				Q = que[Q.pre];
			}
		}
		for (i = 0; i < 4; i++){
			y = Q.y + yy[i];
			x = Q.x + xx[i];
			if (check[y][x])continue;
			if (mymap[y][x] == -4)continue;
			if (y >= 1000 || y < 0 || x >= 1000 || x < 0)continue;
			if (mymap[y][x] == 0 || mymap[y][x] == n){
				check[y][x] = 1;
				in_que(y, x, i, rp - 1);
			}
		}
	}
	return;
}
void test(int trash_map[1000][1000]){
	register int i, j, k, z;
	int min, max, index, maxindex, minindex;
	PQ myresult;
	can[1].cnt = can[2].cnt = can[3].cnt = 0;
	sum = sum1 = sum2 = 0;
	heapInit();
	for (i = 0; i < 1000; i++){
		for (j = 0; j < 1000; j++){
			if (trash_map[i][j]>0){
				can[trash_map[i][j]].y = i;
				can[trash_map[i][j]].x = j;
				mymap[i][j] = -4;
			}
		}
	}
	for (i = 0; i < 1000; i++){
		for (j = 0; j < 1000; j++){
			if (trash_map[i][j] == -1){
				min = 100000;
				for (k = 1; k < 4; k++){
					if (min > abs(can[k].y, i) + abs(can[k].x, j)){
						min = abs(can[k].y, i) + abs(can[k].x, j);
						index = k;
					}
				}
				sum += min;
				can[index].cnt++;
				mymap[i][j] = index;
				for (k = 1; k < 4; k++){
					if (k == index)continue;
					heapPush(i, j, index, k);
				}
			}
		}
	}
	min = 100000;
	for (i = 1; i < 4; i++){
		if (min > can[i].cnt){
			min = can[i].cnt;
			minindex = i;
		}
	}
	i = 1;
	while (can[minindex].cnt < 3000){
		myresult = heapPop();
		if (myresult.aft != minindex)continue;
		if (mymap[myresult.y][myresult.x] != myresult.ori)continue;
		mymap[myresult.y][myresult.x] = myresult.aft;
		can[myresult.ori].cnt--;
		can[myresult.aft].cnt++;
	}
	heapInit();
	for (i = 0; i < 1000; i++){
		for (j = 0; j < 1000; j++){
			if (mymap[i][j] != minindex&&mymap[i][j]>0){
				for (k = 1; k < 4; k++){
					if (k == mymap[i][j] || k == minindex)continue;
					heapPush(i, j, mymap[i][j], k);
				}
			}
		}
	}
	while (can[1].cnt>3500 || can[2].cnt>3500 || can[3].cnt>3500){
		myresult = heapPop();
		if (can[myresult.ori].cnt <= 3500)continue;
		if (mymap[myresult.y][myresult.x] != myresult.ori)continue;
		mymap[myresult.y][myresult.x] = myresult.aft;
		can[myresult.ori].cnt--;
		can[myresult.aft].cnt++;
	}
	for (i = 0; i < 1000; i++){
		for (j = 0; j < 1000; j++){
			if (mymap[i][j]>0){
				sum2 += abs(can[mymap[i][j]].y, i) + abs(can[mymap[i][j]].x, j);
			}
		}
	}
	for (i = 1; i < 4; i++){
		bfs(i);
	}
	mymap[can[1].y][can[1].x] = 0;
	mymap[can[2].y][can[2].x] = 0;
	mymap[can[3].y][can[3].x] = 0;
	i = 1;
	return;
}
