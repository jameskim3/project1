//TOTAL = 1642.5065114800 , PERFORMANCE = 54314
const int FLOOR = 10000; 

#define MAX_SIZE 80000
int heapSize[3];
typedef struct pq{
	int src, tar, pos;
	double val;
}PQ;
PQ heap[3][MAX_SIZE];

void heapInit(void)
{
	for (int i = 0; i < 3;i++)
		heapSize[i] = 0;
}
int heapPush(int src,int tar, int pos, double val)
{
	if (heapSize[src] + 1 > MAX_SIZE)
		return 0;
	PQ tmp;
	tmp.src = src, tmp.tar = tar, tmp.pos = pos, tmp.val = val;
	heap[src][heapSize[src]] = tmp;

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
int abs(int a){ return a > 0 ? a : -a; }

void assign(int house[FLOOR][10000]){
	for (int f = 0; f < FLOOR; f++){
		heapInit();
		int MyHouse[10000];
		int s_pos[3];
		int s_sum[3] = { 0 };
		int idx = 0;
		for (int i = 0; i < 10000; i++){
			MyHouse[i] = house[f][i];
			if (house[f][i] == 0)
				s_pos[idx++] = i;
		}
		for (int i = 0; i < 10000; i++){
			if (MyHouse[i] == 0)continue;
			int min_idx = -1;
			int min_val = 1000000;
			for (int j = 0; j < 3; j++){
				if (abs(s_pos[j] - i) < min_val){
					min_val = abs(s_pos[j] - i);
					min_idx = j;
				}
			}
			house[f][i] = min_idx;
			s_sum[min_idx] += MyHouse[i];
			for (int j = 0; j < 3; j++){
				if (j == min_idx)continue;
				double v = abs(abs(i - s_pos[min_idx]) - abs(i - s_pos[j]))*1000. / MyHouse[i];
				heapPush(min_idx, j, i, v);
			}
		}
		PQ tmp;
		while (s_sum[0] > 20000){
			heapPop(0, &tmp);
			if (tmp.src != house[f][tmp.pos]) continue;
			house[f][tmp.pos] = tmp.tar;
			s_sum[tmp.tar] += MyHouse[tmp.pos];
			s_sum[0] -= MyHouse[tmp.pos];
			//double v1 = abs(abs(tmp.pos - s_pos[0]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
			//heapPush(tmp.tar, 0, tmp.pos, v1);
			//double v2 = abs(abs(tmp.pos - s_pos[2]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
			//heapPush(tmp.tar, 2, tmp.pos, v2);
			for (int j = 0; j < 3; j++){
				if (j == tmp.tar)continue;
				double v1 = abs(abs(tmp.pos - s_pos[j]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
				heapPush(tmp.tar, j, tmp.pos, v1);
			}
		}
		while (s_sum[2] > 20000){
			heapPop(2, &tmp);
			if (tmp.src != house[f][tmp.pos])continue;
			house[f][tmp.pos] = tmp.tar;
			s_sum[tmp.tar] += MyHouse[tmp.pos];
			s_sum[2] -= MyHouse[tmp.pos];
			//double v1 = abs(abs(tmp.pos - s_pos[0]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
			//heapPush(tmp.tar, 0, tmp.pos, v1);
			//double v2 = abs(abs(tmp.pos - s_pos[2]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
			//heapPush(tmp.tar, 2, tmp.pos, v2);
			for (int j = 0; j < 3; j++){
				if (j == tmp.tar)continue;
				double v1 = abs(abs(tmp.pos - s_pos[j]) - abs(tmp.pos - s_pos[tmp.tar]))*1000. / MyHouse[tmp.pos];
				heapPush(tmp.tar, j, tmp.pos, v1);
			}
		}
		while (s_sum[1] > 20000){
			heapPop(1, &tmp);
			if (s_sum[tmp.tar] + MyHouse[tmp.pos] > 20000)continue;
			if (tmp.src != house[f][tmp.pos])continue;
			house[f][tmp.pos] = tmp.tar;
			s_sum[tmp.tar] += MyHouse[tmp.pos];
			s_sum[1] -= MyHouse[tmp.pos];
		}
		for (int i = 0; i < 10000; i++)
			house[f][i] = s_pos[house[f][i]];
	}
}