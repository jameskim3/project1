
#define MAXLength (10000)
#define MAxServer (10)

#define MAX_SIZE 10000

typedef struct {
	int id, val;
}PQ;
PQ heap1[10][MAX_SIZE];
PQ heap2[10][MAX_SIZE];

int heapSize1[10];
int heapSize2[10];

typedef struct{
	int dist[10];
	int order[10];
	int se;
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
int compare2(PQ a, PQ b){
	if (a.val < b.val || (a.val == b.val && a.id < b.id))
		return 1;
	return -1;
}
int heapPush_remain(int se, int id, int value)
{
	if (heapSize1[se] + 1 > MAX_SIZE)
		return 0;
	if (heapSize2[se] + 1 > MAX_SIZE)
		return 0;
	int size1 = heapSize2[se];
	heap2[se][size1].id = id;
	heap2[se][size1].val = value;

	int current = size1;
	while (current > 0 && compare2(heap2[se][current], heap2[se][(current - 1) / 2]) == 1)
	{
		PQ temp = heap2[se][(current - 1) / 2];
		heap2[se][(current - 1) / 2] = heap2[se][current];
		heap2[se][current] = temp;
		current = (current - 1) / 2;
	}

	heapSize2[se] = heapSize2[se] + 1;
	return 1;
}
int heapPush(int se, int id, int value, int visited)
{
	if (heapSize1[se] + 1 > MAX_SIZE)
		return 0;
	if (heapSize2[se] + 1 > MAX_SIZE)
		return 0;
	int size1 = heapSize1[se];
	heap1[se][size1].id = id;
	heap1[se][size1].val = -value;

	int current = size1;
	while (current > 0 && compare(heap1[se][current], heap1[se][(current - 1) / 2]) == 1)
	{
		PQ temp = heap1[se][(current - 1) / 2];
		heap1[se][(current - 1) / 2] = heap1[se][current];
		heap1[se][current] = temp;
		current = (current - 1) / 2;
	}
	nd[id].se = se;

	heapSize1[se] = heapSize1[se] + 1;
	if (heapSize1[se] > CL){
		PQ poped;
		heapPop(se, &poped);
		heapPush_remain(se, poped.id, -poped.val);
		int next_pos = 0;
		ND* poped_id = &nd[poped.id];
		for (int i = 0; i < 10; i++){
			int val = visited >> poped_id->order[i];
			if (val & 1)continue;
			visited += 1 << poped_id->order[i];
			int n = poped_id->order[i];
			heapPush(n, poped.id, poped_id->dist[n], visited);
			break;
		}
	}
	return 1;
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
int LE, NU, CL, AXIS[MAxServer];
void init(int L, int N, int C, int axis[MAxServer])
{
	LE = L, NU = N, CL = C;
	for (int i = 0; i < NU; i++){
		AXIS[i] = axis[i];
	}
	rp = 0;
}
int abs(int a){ return a>0 ? a : -a; }
int add_user(int uid, int axis){
	ND* tmp = &nd[rp++];
	int dist[10], order[10];
	for (int i = 0; i < NU; i++){
		int d1 = abs(AXIS[i] - axis);
		int d2 = axis + (LE - AXIS[i]);
		tmp->dist[i] = d1 > d2 ? d2 : d1;
		tmp->order[i] = i;
	}
	for (int i = 0; i < NU; i++){
		for (int j = i+1; j < NU; j++){
			if (tmp->dist[i] < tmp->dist[j]){
				int t = tmp->dist[i];
				tmp->dist[i] = tmp->dist[j]; tmp->dist[j] = t;
				t = tmp->order[i];
				tmp->order[i] = tmp->order[j]; tmp->order[j] = t;
			}
		}
	}
	int visited = 0;
	visited += 1 << tmp->order[0];
	heapPush(tmp->order[0], rp - 1, tmp->dist[0],visited);
}
int remove_user(int uid);
int get_users(int sid);

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
