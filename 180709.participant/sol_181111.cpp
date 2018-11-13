struct PARTICIPANT
{
	int id, preference;
};
struct PARTICIPANT2
{
	int id, preference;
	PARTICIPANT2* next;
};

PARTICIPANT2 nd[100000];
int rp;
PARTICIPANT2 *mid, *low, *high;
PARTICIPANT2* heap[50000 + 10];
int gTotal;
int gLowSum;
int gHighSum;
void addHeap(PARTICIPANT2* p)
{
	if (heap[p->preference] == 0 || heap[p->preference]->id > p->id)
	{
		p->next = heap[p->preference];
		heap[p->preference] = p;
	}
	else
	{
		PARTICIPANT2* iter = heap[p->preference];
		while (iter->next != 0 && iter->next->id < p->id)
			iter = iter->next;
		p->next = iter->next;
		iter->next = p;
	}
}
void removeHeap(PARTICIPANT2* p)
{
	if (heap[p->preference] == p)
		heap[p->preference] = heap[p->preference]->next;
	else
	{
		PARTICIPANT2* iter = heap[p->preference];
		while (iter->next->id != p->id)
			iter = iter->next;
		iter->next = p->next;
	}
}
int compare(PARTICIPANT2* a, PARTICIPANT2* b)
{
	if (a->preference < b->preference)return 1;
	else if (a->preference > b->preference)return -1;
	else
	{
		if (a->id < b->id)return 1;
		else if (a->id>b->id)return -1;
	}
	return 0;
}
PARTICIPANT2* getnext(PARTICIPANT2* p)
{
	PARTICIPANT2* h = heap[p->preference];
	while (h->id != p->id)
		h = h->next; 
	if (p->next != 0)return p->next;
	int cnt = 1;
	while (heap[p->preference + cnt] == 0)
		cnt++;
	return heap[p->preference + cnt];
}
PARTICIPANT2* getpre(PARTICIPANT2* p)
{
	PARTICIPANT2* h = heap[p->preference];
	PARTICIPANT2* hpre = 0;
	while (h->id != p->id)
	{
		hpre = h;
		h = h->next;
	}
	if (hpre != 0)return hpre;
	int cnt = 1;
	while (heap[p->preference - cnt] == 0)
		cnt++;
	h = heap[p->preference - cnt];
	while (h->next != 0)
		h = h->next;
	return h;
}
void addSum(PARTICIPANT2* p)
{
	if (low == 0 || compare(low,p)==-1)low = p;
	if (high == 0 || compare(high, p) == 1)high = p;
	if (gTotal == 0)
	{
		mid = p;
		gLowSum = p->preference;
	}
	else if (gTotal == 1)
	{
		if (compare(mid, p) == -1)
		{
			gLowSum -= mid->preference;
			gLowSum += p->preference;
			gHighSum += mid->preference;
			mid = p;
		}
		else
		{
			gHighSum += p->preference;
		}
	}
	else
	{
		if (gTotal % 2 == 0)
		{
			if (compare(mid, p) == -1)
			{
				gLowSum += p->preference;
			}
			else
			{
				PARTICIPANT2* newmid = getnext(mid);
				gLowSum += newmid->preference;
				gHighSum -= newmid->preference;
				gHighSum += p->preference;
				mid = newmid;
			}
		}
		else
		{
			if (compare(mid, p) == 1)
			{
				gHighSum += p->preference;
			}
			else
			{
				PARTICIPANT2* newmid = getpre(mid);
				gLowSum -= mid->preference;
				gHighSum += mid->preference;
				gLowSum += p->preference;
				mid = newmid;
			}
		}
	}
	gTotal++;
}
void init(int n, PARTICIPANT src[])
{
	register int i, j, k;
	gTotal = gLowSum = gHighSum = 0;
	for (i = 0; i < 50000 + 10; i++)
		heap[i] = 0;
	for (i = 0; i < rp; i++)
	{
		nd[i].id = 0; nd[i].preference = 0; nd[i].next = 0;
	}
	rp = 0;
	mid = 0;
	low = 0;
	high = 0;
	for (i = 0; i < n; i++)
	{
		PARTICIPANT2* p = &nd[rp++];
		p->id = src[i].id;
		p->preference = src[i].preference;
		addHeap(p);
		addSum(p);
	}
}
void remove(int pre)
{
	if (pre == 0)
	{
		PARTICIPANT2* newlow = getnext(low);
		gLowSum -= low->preference;
		removeHeap(low);
		low = newlow;
		if (gTotal % 2 == 0)
		{
			PARTICIPANT2* newmid = getnext(mid);
			gLowSum += newmid->preference;
			gHighSum -= newmid->preference;
			mid = newmid;
		}
		gTotal--;
	}
	else if (pre == 1)
	{
		PARTICIPANT2* newhigh = getpre(high);
		gHighSum -= high->preference;
		removeHeap(high);
		high = newhigh;
		if (gTotal % 2 == 1)
		{
			PARTICIPANT2* newmid = getpre(mid);
			gHighSum += mid->preference;
			gLowSum -= mid->preference;
			mid = newmid;
		}
		gTotal--;
	}
	else
	{
		if (gTotal % 2 == 0)
		{
			PARTICIPANT2* premid = getpre(mid);
			PARTICIPANT2* nextmid = getnext(mid);
			gLowSum -= mid->preference;
			gHighSum -= nextmid->preference;
			removeHeap(mid);
			removeHeap(nextmid);
			mid = premid;
			gTotal -= 2;
		}
		else
		{
			PARTICIPANT2* premid = getpre(mid);
			gLowSum -= mid->preference;
			removeHeap(mid);
			mid = premid;
			gTotal -= 1;
		}
	}
}
void add(PARTICIPANT tar)
{
	PARTICIPANT2* p = &nd[rp++];
	p->id = tar.id;
	p->preference = tar.preference;
	addHeap(p);
	addSum(p);
}
void getsum2(int *a, int *b)
{
	*a = gLowSum;
	*b = gHighSum;
}