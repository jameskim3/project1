
#define MAXLength (10000)
#define MAxServer (10)

#define MAX_SIZE 10000
int LE, NU, CL, AXIS[MAxServer];

typedef struct {
	int id, val, pos;
}PQ;
PQ heap1[10][MAX_SIZE];
PQ heap2[10][MAX_SIZE];

int heapSize1[10];
int heapSize2[10];

typedef struct{
	int se_dist[10];
	int se_order[10];
	int se;
	int id;
	int val;
}ND;
ND nd[10000];
int rp;

void heapInit(void)
{
	for (int i = 0; i < 10; i++){
		heapSize1[i] = heapSize2[i] = 0;
	}
}
int compare(PQ a, PQ b){
	if (a.val < b.val || (a.val == b.val && a.id > b.id))
		return 1;
	return -1;
}
int heapPop(int se, PQ *value)
{
	if (heapSize1[se] + 1 > MAX_SIZE)
		return 0;
	if (heapSize2[se] + 1 > MAX_SIZE)
		return 0;

	*value = heap1[se][0];
	heapSize1[se] = heapSize1[se] - 1;

	int size1 = heapSize1[se];
	heap1[se][0] = heap1[se][size1];

	int current = 0;
	while (current * 2 + 1 < heapSize1[se])
	{
		int child;
		if (current * 2 + 2 == heapSize1[se])
		{
			child = current * 2 + 1;
		}
		else
		{
			child = compare(heap1[se][current * 2 + 1], heap1[se][current * 2 + 2]) == 1 ? current * 2 + 1 : current * 2 + 2;
		}

		if (compare(heap1[se][current], heap1[se][child]) == 1)
		{
			break;
		}

		PQ temp = heap1[se][current];
		heap1[se][current] = heap1[se][child];
		heap1[se][child] = temp;
		current = child;
	}
	return 1;
}
int heapPop_remain(int se, PQ *value){
	if (heapSize2[se] == 0)
		return 0;

	*value = heap2[se][0];
	heapSize2[se] = heapSize2[se] - 1;

	int size1 = heapSize2[se];
	heap2[se][0] = heap2[se][size1];

	int current = 0;
	while (current * 2 + 1 < heapSize2[se])
	{
		int child;
		if (current * 2 + 2 == heapSize2[se])
		{
			child = current * 2 + 1;
		}
		else
		{
			child = compare(heap2[se][current * 2 + 1], heap2[se][current * 2 + 2]) == 1 ? current * 2 + 2 : current * 2 + 1;
		}

		if (compare(heap2[se][current], heap2[se][child]) == -1)
		{
			break;
		}

		PQ temp = heap2[se][current];
		heap2[se][current] = heap2[se][child];
		heap2[se][child] = temp;
		current = child;
	}
	return 1;
}
int heapPush_remain(int se, int id, int value, int pos)
{
	if (heapSize1[se] + 1 > MAX_SIZE)
		return 0;
	if (heapSize2[se] + 1 > MAX_SIZE)
		return 0;
	int size1 = heapSize2[se];
	heap2[se][size1].id = id;
	heap2[se][size1].val = value;
	heap2[se][size1].pos = pos;

	int current = size1;
	while (current > 0 && compare(heap2[se][current], heap2[se][(current - 1) / 2]) == -1)
	{
		PQ temp = heap2[se][(current - 1) / 2];
		heap2[se][(current - 1) / 2] = heap2[se][current];
		heap2[se][current] = temp;
		current = (current - 1) / 2;
	}

	heapSize2[se] = heapSize2[se] + 1;
	return 1;
}
int heapPush(int se, int id, int value, int pos, int visited)
{
	if (heapSize1[se] + 1 > MAX_SIZE)
		return 0;
	if (heapSize2[se] + 1 > MAX_SIZE)
		return 0;
	int size1 = heapSize1[se];
	heap1[se][size1].id = id;
	heap1[se][size1].val = value;
	heap1[se][size1].pos = pos;

	int current = size1;
	while (current > 0 && compare(heap1[se][current], heap1[se][(current - 1) / 2]) == 1)
	{
		PQ temp = heap1[se][(current - 1) / 2];
		heap1[se][(current - 1) / 2] = heap1[se][current];
		heap1[se][current] = temp;
		current = (current - 1) / 2;
	}
	nd[pos].se = se;

	heapSize1[se] = heapSize1[se] + 1;
	if (heapSize1[se] > CL && visited != -1){
		PQ poped;
		heapPop(se, &poped);
		heapPush_remain(se, poped.id, poped.val, poped.pos);
		ND* tmp = &nd[poped.pos];
		for (int i = 0; i < 10; i++){
			int val = visited >> tmp->se_order[i];
			if (val & 1)continue;
			visited += 1 << tmp->se_order[i];
			int new_se = tmp->se_order[i];
			heapPush(new_se, tmp->id, tmp->val, poped.pos, visited);
			break;
		}
	}
	return 1;
}
void init(int L, int N, int C, int axis[MAxServer])
{
	heapInit();
	LE = L, NU = N, CL = C;
	for (int i = 0; i < NU; i++){
		AXIS[i] = axis[i];
	}
	rp = 0;
}
int abs(int a){ return a>0 ? a : -a; }
int myMin(int a, int b){ return a > b ? b : a; }
int add_user(int uid, int axis){
	ND* tmp = &nd[rp++];
	int se_dist[10], se_order[10];
	for (int i = 0; i < NU; i++){
		int d1 = abs(AXIS[i] - axis);
		int d2 = axis + (LE - AXIS[i]);
		int d3 = (LE - axis) + AXIS[i];
		int min = myMin(d1, d2);
		min = myMin(min, d3);
		tmp->se_dist[i] = min;
		tmp->se_order[i] = i;
	}
	for (int i = 0; i < NU; i++){
		for (int j = i + 1; j < NU; j++){
			if (tmp->se_dist[i] > tmp->se_dist[j]){
				int t = tmp->se_dist[i];
				tmp->se_dist[i] = tmp->se_dist[j]; tmp->se_dist[j] = t;
				t = tmp->se_order[i];
				tmp->se_order[i] = tmp->se_order[j]; tmp->se_order[j] = t;
			}
		}
	}
	tmp->id = uid;
	tmp->val = tmp->se_dist[NU - 1];
	int visited = 0;
	visited += 1 << tmp->se_order[0];
	heapPush(tmp->se_order[0], tmp->id, tmp->val, rp - 1, visited);
	return nd[rp - 1].se;
}
int remove_user(int uid);
void resizeServer(int se){
	PQ pq;
	int ret = heapPop_remain(se, &pq);
	if (ret == 0)return;
	remove_user(pq.id);

	int visited = 0;
	visited += 1 << se;
	heapPush(se, pq.id, pq.val, pq.pos, visited - 1);
}
int remove_user(int uid){
	int pos = 0;
	while (nd[pos].id != uid)pos++;

	int se = nd[pos].se;
	PQ tmp;
	PQ store[10000];
	int cnt = 0;
	int hsize = heapSize1[se];
	for (int j = 0; j < hsize; j++){
		heapPop(se, &tmp);
		if (tmp.id == uid)break;
		store[cnt].id = tmp.id;
		store[cnt].val = tmp.val;
		store[cnt].pos = tmp.pos;
		cnt++;
	}
	while (cnt > 0){
		heapPush(se, store[cnt-1].id, store[cnt - 1].val, store[cnt - 1].pos, -1);
		cnt--;
	}
	resizeServer(se);
	return se;
}
int get_users(int sid){
	return heapSize1[sid];
}

/*
1
10 3 2 15
2 6 8
0 0 2 0
0 1 2 0
0 2 1 0
0 3 0 2
0 4 0 2
1 0 0
2 1 0
0 5 0 1
0 6 0 1
1 2 0
1 1 0
1 5 2
0 7 4 1
0 8 3 0
0 9 7 1
1 2
*/
