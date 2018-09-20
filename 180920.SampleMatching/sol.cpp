typedef struct pz {
	int d[8];
	int id;
	pz* next;
}PZ;
const int RAND_MAX = 32767;
const int HALF = RAND_MAX / 2;
pz map[10000 * 248];
pz* heap[RAND_MAX+100];
int rp = 0;
int id_cnt[RAND_MAX + 100];
void addHeap(int d[8], int id)
{
	pz* tmp = &map[rp++];
	tmp->id = id;
	for (int i = 0; i < 8; i++)
	{
		tmp->d[i] = d[i];
	}
	tmp->next = heap[d[0]];
	heap[d[0]] = tmp;

	id_cnt[d[0]]++;
	if (rp == 10000 * 248)
	{
		int a = 1;
		return;
	}
}

void init(int a[][256], int y)
{
	rp = 0;
	for (int i = 0; i < RAND_MAX; i++)
	{
		heap[i] = 0;
		id_cnt[i] = 0;
	}
	int d[8];
	for (int i = 0; i < y; i++)
	{
		for (int j = 255; j >= 7; j--)
		{
			if (a[i][j] == RAND_MAX)continue;
			for (int k = 0; k < 8; k++)
				d[k] = a[i][j - 7 + k] + HALF;
			addHeap(d, i);
		}
	}
}
int noise_chk(int noise[8], int stored[8])
{
	for (int i = 0; i < 8; i++)
	{
		if (stored[i] - 128 > noise[i] || stored[i] + 127 < noise[i])
			return 0;
	}
	return 1;
}
int matching(int arr[8])
{
	int a[8];
	for (int i = 0; i < 8; i++)
		a[i] = arr[i] + HALF;
	for (int off = -128; off <= 128; off++)
	{
		if (a[0] + off < 0)continue;
		pz* head = heap[a[0]+off];
		int cnt = 0;
		while (head)
		{
			if (noise_chk(a, head->d) == 1)
				return head->id;
			head = head->next;
			cnt++;
		}
	}
	return -1;
}