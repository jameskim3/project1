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
MyPARTICIPANT nd[MAX*2];
MyPARTICIPANT* heap[MAX];
int psum[MAX];
int total_sum;

int min_pos=9999999;
int max_pos=-1;
int mid_pos;

void init(int n, PARTICIPANT src[])
{
	int i, j, k;
	total_sum = 0;
	
	rp = 0;
	for (i = 0; i < MAX; i++)
	{
		heap[i] = 0;
		psum[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		MyPARTICIPANT* tmp = &nd[rp++];
		tmp->id = src[i].id;
		tmp->preference = src[i].preference;
		tmp->next = heap[tmp->preference];
		heap[tmp->preference] = tmp;

		psum[tmp->preference]++;
		total_sum += 1;

		if (min_pos > tmp->preference)min_pos = tmp->preference;
		if (max_pos < tmp->preference)max_pos = tmp->preference;
	}
}
void remove_pos(int pos)
{
	heap[pos] = 0;
	total_sum -= psum[pos];
	psum[pos] = 0;
}
void remove(int opt)//0 MIN, 1 MAX, 2 MID
{
	if (opt == 0)
	{
		remove_pos(min_pos);
		while (psum[++min_pos] == 0);
	}
	else if (opt == 1)
	{
		remove_pos(max_pos);
		while (psum[--max_pos] == 0)			;
	}
	else
	{
		int mid_count = total_sum / 2;
		int sum = 0;
		mid_pos = min_pos;
		while (1)
		{
			sum += psum[mid_pos];
			if (mid_count < sum)
				break;
			mid_pos++;
		}
		remove_pos(mid_pos);
	}
}
void add(PARTICIPANT tar)
{
	MyPARTICIPANT* tmp = &nd[rp++];
	tmp->id = tar.id;
	tmp->preference = tar.preference;
	tmp->next = heap[tmp->preference];
	heap[tmp->preference] = tmp;

	psum[tmp->preference]++;
	total_sum += 1;
}
void getsum2(int *a, int *b)
{

}