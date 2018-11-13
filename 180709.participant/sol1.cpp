#define MIN 10000
#define MAX 50000

struct PARTICIPANT
{
	int id, preference;
};
struct MyPARTICIPANT
{
	int id, preference;
	MyPARTICIPANT * next;
};

int rp;
MyPARTICIPANT nd[MAX * 2];
MyPARTICIPANT* heap[MAX];
MyPARTICIPANT* mid;
int total_sum;

MyPARTICIPANT* min_pos;
MyPARTICIPANT* max_pos;
int high_sum;
int low_sum;

MyPARTICIPANT* getnext(MyPARTICIPANT* p)
{
	if (p->next != 0) return p->next;
	else
	{
		int n = 0;
		MyPARTICIPANT* tmp = heap[p->preference + ++n];
		while (tmp == 0)
			tmp = heap[p->preference + ++n];
		return tmp;
	}
}
MyPARTICIPANT* getpre(MyPARTICIPANT* p)
{
	if (heap[p->preference] != p)
	{
		MyPARTICIPANT* tmp = heap[p->preference];
		while (tmp->next != p)
			tmp = tmp->next;
		return tmp;
	}
	else
	{
		int n = 0;
		MyPARTICIPANT* tmp = heap[p->preference - ++n];
		while (tmp == 0)
			tmp = heap[p->preference - ++n];
		while (tmp->next != 0)
			tmp = tmp->next;
		return tmp;
	}
}

void addheap(MyPARTICIPANT* p)
{
	if (heap[p->preference] == 0 || heap[p->preference]->id > p->id)
	{
		p->next = heap[p->preference];
		heap[p->preference] = p;
	}
	else
	{
		MyPARTICIPANT* tmp = heap[p->preference];
		while (tmp->next != 0 && tmp->next->id < p->id)
			tmp = tmp->next;
		p->next = tmp->next;
		tmp->next = p;
	}
}

int compare(MyPARTICIPANT* a, MyPARTICIPANT *b)
{
	if (a->preference < b->preference ||
		(a->preference == b->preference && a->id < b->id))
		return 1;
	else if (a->id == b->id)return 0;
	
	return -1;
}

void addSum(MyPARTICIPANT* tmp)
{
	addheap(tmp);

	total_sum += 1;

	if (min_pos != 0)
	{
		if (min_pos->preference > tmp->preference
			|| (min_pos->preference == tmp->preference && min_pos->id > tmp->id))
			min_pos = tmp;
	}
	if (max_pos != 0)
	{
		if (max_pos->preference < tmp->preference
			|| (max_pos->preference == tmp->preference && max_pos->id < tmp->id))
			max_pos = tmp;
	}
	if (total_sum == 1)
	{
		low_sum += tmp->preference;
		mid = tmp;
		min_pos = tmp;
		max_pos = tmp;
	}
	else if (total_sum == 2)
	{
		if (compare(min_pos, tmp)==0)
		{
			low_sum -= mid->preference;
			high_sum += mid->preference;
			low_sum += tmp->preference;
			mid = tmp;
		}
		else
		{
			high_sum += tmp->preference;
		}
	}
	else
	{
		if (total_sum % 2 == 0)
		{
			if (tmp->preference < mid->preference ||
				(tmp->preference == mid->preference && tmp->id < mid->id))
			{
				low_sum -= mid->preference;
				high_sum += mid->preference;
				low_sum += tmp->preference;
				mid = getpre(mid);
			}
			else
			{
				high_sum += tmp->preference;
			}
		}
		else
		{
			if (tmp->preference > mid->preference ||
				(tmp->preference == mid->preference && tmp->id > mid->id))
			{
				mid = getnext(mid);
				low_sum += mid->preference;
				high_sum -= mid->preference;
				high_sum += tmp->preference;
			}
			else
			{
				low_sum += tmp->preference;
			}
		}
	}
}
void init(int n, PARTICIPANT src[])
{
	int i, j, k;
	total_sum = 0;
	low_sum = high_sum = 0;
	min_pos = 0;
	max_pos = 0;
	rp = 0;
	for (i = 0; i < MAX; i++)
	{
		heap[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		MyPARTICIPANT* tmp = &nd[rp++];
		tmp->id = src[i].id;
		tmp->preference = src[i].preference;
		addSum(tmp);
	}
}
void removeHeap(MyPARTICIPANT* p)
{
	if (heap[p->preference] != p)
	{
		MyPARTICIPANT* tmp = heap[p->preference];
		while (tmp->next != p)
			tmp = tmp->next;
		tmp->next = p->next;
	}
	else
	{
		heap[p->preference] = p->next;
	}
}
void remove(int opt)//0 MIN, 1 MAX, 2 MID
{
	if (opt == 0)
	{
		low_sum -= min_pos->preference;
		MyPARTICIPANT* next_min_pos = getnext(min_pos);
		removeHeap(min_pos);
		min_pos = next_min_pos;
		if (total_sum % 2 == 0)
		{
			MyPARTICIPANT* newmid = getnext(mid);
			low_sum += newmid->preference;
			high_sum -= newmid->preference;
			mid = newmid;
		}
		total_sum--;
	}
	else if (opt == 1)
	{
		high_sum -= max_pos->preference;
		MyPARTICIPANT* pre_max_pos = getpre(max_pos);
		removeHeap(max_pos);
		max_pos = pre_max_pos;
		if (total_sum % 2 == 1)
		{
			MyPARTICIPANT* newmid = getpre(mid);
			high_sum += mid->preference;
			low_sum -= mid->preference;
			mid = newmid;
		}
		total_sum--;
	}
	else
	{
		if (total_sum % 2 == 0)
		{
			MyPARTICIPANT* newMid = getpre(mid);
			MyPARTICIPANT* nextmid = getnext(mid);
			low_sum -= mid->preference;
			high_sum -= nextmid->preference;
			mid = newMid;
			removeHeap(nextmid);
			removeHeap(mid);
			total_sum -= 2;
		}
		else
		{
			MyPARTICIPANT* newMid = getpre(mid);
			low_sum -= mid->preference;
			removeHeap(mid);
			mid = newMid;
			total_sum--;
		}
	}
}
void add(PARTICIPANT tar)
{
	MyPARTICIPANT* tmp = &nd[rp++];
	tmp->id = tar.id;
	tmp->preference = tar.preference;
	addSum(tmp);
}
void getsum2(int *a, int *b)
{
	*a = low_sum;
	*b = high_sum;
}