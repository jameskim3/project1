#define MIN 10000
#define MAX 50000

struct PARTICIPANT
{
	int id, pre;
};

struct LinkedList
{
	PARTICIPANT pt;
	LinkedList* next;
};

int rp;
PARTICIPANT nd[MAX];
PARTICIPANT* getNew()
{
	return &nd[rp++];
}
LinkedList* heap[MAX];
int psum[MAX];

void init(int n, PARTICIPANT src[])
{
	int i, j, k;
	for (i = 0; i < 50000; i++)
	{
		psum[i] = 0;
		heap[i] = 0;
	}
	for (i = 0; i < n; i++)
	{
		PARTICIPANT* tmp = getNew();
		tmp->id = src[i].id;
		tmp->pre= src[i].pre;
		
	}
}
void remove(int pre)
{

}
void add(PARTICIPANT tar)
{

}
void totalsum(int *a, int *b)
{

}