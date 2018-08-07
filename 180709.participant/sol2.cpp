#define MIN 10000
#define MAX 50000

struct PARTICIPANT
{
	int id, preference;
};
struct MyPARTICIPANT
{
	int id, preference;
	MyPARTICIPANT * left;
	MyPARTICIPANT * right;
};

int rp;
MyPARTICIPANT nd[MAX * 2];
MyPARTICIPANT* LEFT;
MyPARTICIPANT* RIGHT;
int total_sum;

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
int compare(MyPARTICIPANT* a, MyPARTICIPANT* b)
{
	if (a->preference < b->preference ||
		a->preference == b->preference && a->id < b->id)
		return 1;
	else if (a->id == b->id)
		return 0;
	else return -1;
}
MyPARTICIPANT* GetHigh(MyPARTICIPANT* p)
{
	if (p == 0)return 0;
	while (p->right != 0)
		p = p->right;
	return p;
}
MyPARTICIPANT* GetLow(MyPARTICIPANT* p)
{
	if (p == 0)return 0;
	while (p->left != 0)
		p = p->left;
	return p;
}

MyPARTICIPANT* addTree(MyPARTICIPANT* r, MyPARTICIPANT* p)
{
	if (r == 0) 
	{
		return p;
	}
	if (compare(r,p) == 1)
	{
		r->right = addTree(r->right, p);
		return r;
	}
	else
	{
		r->left = addTree(r->left, p);
		return r;
	}
}
MyPARTICIPANT* removeTree(MyPARTICIPANT* r, MyPARTICIPANT* p)
{
	if (r == 0) return 0;
	if (r->preference < p->preference ||
		r->preference == p->preference && r->id < p->id)
	{
		r->right = removeTree(r->right, p);
		return r;
	}
	else if (r->id != p->id)
	{
		r->left = removeTree(r->left, p);
		return r;
	}
	else //same
	{
		if (r->left == 0)
			return r->right;
		else if (r->right == 0)
			return r->left;
		else
		{
			MyPARTICIPANT* tmp_min = GetHigh(r->right);
			removeTree(r->right, tmp_min);
			tmp_min->left = r->left;
			tmp_min->right = r->right;
			return tmp_min;
		}
	}
}
void addSum(MyPARTICIPANT* tmp)
{
	total_sum += 1;

	if (total_sum == 1)
	{
		LEFT = tmp;
	}
	else
	{
		if (total_sum % 2 == 0)
		{
			MyPARTICIPANT* right_min = GetLow(RIGHT);

			if (compare(tmp, right_min) == 1)
			{
				LEFT = addTree(LEFT, tmp);
				MyPARTICIPANT* left_max = GetHigh(LEFT);
				RIGHT = addTree(RIGHT, left_max);
				LEFT = removeTree(LEFT, left_max);
			}
			else
			{
				RIGHT = addTree(RIGHT, tmp);
			}
		}
		else
		{
			MyPARTICIPANT* right_min = GetLow(RIGHT);

			if (compare(tmp, right_min) == -1)
			{
				RIGHT = addTree(RIGHT, tmp);
				MyPARTICIPANT* right_min = GetLow(RIGHT);
				LEFT = addTree(LEFT, right_min);
				RIGHT = removeTree(RIGHT, right_min);
			}
			else
			{
				LEFT = addTree(LEFT, tmp);
			}
		}
	}
}
void init(int n, PARTICIPANT src[])
{
	int i, j, k;
	total_sum = 0;
	low_sum = high_sum = 0;

	rp = 0;
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
		min_pos = getnext(min_pos);
		total_sum--;
	}
	else if (opt == 1)
	{
		high_sum -= max_pos->preference;
		max_pos = getpre(max_pos);
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