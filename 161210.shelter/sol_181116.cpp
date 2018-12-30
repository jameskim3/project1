//TOTAL = 1642.9515136900 , PERFORMANCE = 66326
//reference

const int max_size = 200000;
typedef struct {
	int ori, aft, set;
	double val;
}PQ;
PQ heap[3][200000];
int st[3];
int sc[3];
int heapSize[3];
int myHouse[10000];

const int FLOOR = 10000;
int abs(int a)
{
	return a > 0 ? a : -1 * a;
}
void heapInit()
{
	heapSize[0] = 0;
	heapSize[1] = 0;
	heapSize[2] = 0;
}
int heapPush(int a, int b, int c, double val)
{
	if (heapSize[a] + 1 > max_size)return 0;
	heap[a][heapSize[a]].ori = a;
	heap[a][heapSize[a]].aft = b;
	heap[a][heapSize[a]].set = c;
	heap[a][heapSize[a]].val = val;

	int current = heapSize[a];
	while (current > 0 && heap[a][current].val < heap[a][(current - 1) / 2].val)
	{
		PQ temp = heap[a][(current - 1) / 2];
		heap[a][(current - 1) / 2] = heap[a][current];
		heap[a][current] = temp;
		current = (current - 1) / 2;
	}
	heapSize[a] = heapSize[a] + 1;
	return 1;
}
int heapPop(int a, PQ* val)
{
	if (heapSize[a] <= 0)return -1;
	*val = heap[a][0];
	heapSize[a] = heapSize[a] - 1;
	heap[a][0] = heap[a][heapSize[a]];

	int current = 0;
	while (current * 2 + 1 < heapSize[a])
	{
		int child;
		if (current * 2 + 2 == heapSize[a])
			child = current * 2 + 1;
		else
			child = heap[a][current * 2 + 1].val < heap[a][current * 2 + 2].val ? current * 2 + 1 : current * 2 + 2;

		if (heap[a][current].val < heap[a][child].val)
			break;

		PQ temp = heap[a][current];
		heap[a][current] = heap[a][child];
		heap[a][child] = temp;

		current = child;
	}
	return 1;
}

void assign(int house[FLOOR][10000])
{
	register int i, j, f;
	int min, minindex, temp, sum;
	PQ val;
	for (f = 0; f < FLOOR; f++)
	{
		heapInit();
		sum = 0;
		j = 0;
		for (i = 0; i < 3; i++)
		{
			st[i] = 0;
			sc[i] = 0;
		}
		for (i = 0; i < 10000; i++)
		{
			myHouse[i] = house[f][i];
			if (!house[f][i])
				st[j++] = i;
		}
		for (i = 0; i < 10000; i++)
		{
			if (!house[f][i])continue;
			min = 20000;
			for (j = 0; j < 3; j++)
			{
				temp = abs(i - st[j]);
				if (temp < min)
				{
					min = temp; minindex = j;
				}
			}
			sum += min;
			sc[minindex] += myHouse[i];
			house[f][i] = st[minindex];

			for (j = 0; j < 3; j++)
			{
				if (j == minindex)continue;
				heapPush(minindex, j, i, ((abs(st[j] - i) - abs(st[minindex] - i)) * 1000) / (myHouse[i] * 2));
			}
		}

		i = 1;
		while (sc[0] > 20000)
		{
			heapPop(0, &val);
			if (house[f][val.set] != st[val.ori])continue;
			house[f][val.set] = st[val.aft];
			sc[val.aft] += myHouse[val.set];
			sc[val.ori] -= myHouse[val.set];
			heapPush(val.aft, 0, val.set, ((abs(st[0] - val.set) - abs(st[val.aft] - val.set)) * 1000) / (myHouse[val.set]));
			heapPush(val.aft, 2, val.set, ((abs(st[2] - val.set) - abs(st[val.aft] - val.set)) * 1000) / (myHouse[val.set]));
		}
		i = 1;
		while (sc[2] > 20000)
		{
			heapPop(2, &val);
			if (house[f][val.set] != st[val.ori])continue;
			house[f][val.set] = st[val.aft];
			sc[val.aft] += myHouse[val.set];
			sc[val.ori] -= myHouse[val.set];
			heapPush(val.aft, 0, val.set, ((abs(st[0] - val.set) - abs(st[val.aft] - val.set)) * 1000) / (myHouse[val.set]));
			heapPush(val.aft, 2, val.set, ((abs(st[2] - val.set) - abs(st[val.aft] - val.set)) * 1000) / (myHouse[val.set]));
		}
		i = 1;
		while (sc[1] > 20000)
		{
			heapPop(1, &val);
			if (sc[val.aft] + myHouse[val.set] >= 20000)continue;
			if (house[f][val.set] != st[val.ori])continue;
			house[f][val.set] = st[val.aft];
			sc[val.aft] += myHouse[val.set];
			sc[val.ori] -= myHouse[val.set];
		}
		i = 1;
	}
}