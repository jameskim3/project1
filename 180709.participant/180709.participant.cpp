#include <iostream>
#include <time.h>

#define MIN 10000
#define MAX 50000

struct PARTICIPANT
{
	int id, pre;
};

extern void init(int n, PARTICIPANT src[]);
extern void remove(int pre);
extern void add(PARTICIPANT tar);
extern void totalsum(int *a, int *b);

PARTICIPANT src[MAX];
int N;
char chk[2][MAX];

int setid(int t)//0 id, 1 pre
{
	int id;
	while (1)
	{
		id = rand()+1;
		if (chk[t][id] == 1) continue;
		chk[t][id] = 1;
		break;
	}
	return id;
}

int getid(int t)//0 id, 1 pre
{
	int id;
	while (1)
	{
		id = rand();
		if (chk[t][id] == 1) break;
	}
	return id;
}

PARTICIPANT new_parti()
{
	PARTICIPANT tmp;
	tmp.id = setid(0);
	tmp.pre = rand() % MAX + 1;
	chk[1][tmp.pre] = 1;

	return tmp;
}

int main()
{
	int i, j, k, u,v;
	int result,performance;
	for (int tc = 0; tc < 10; tc++)
	{
		result = 0; performance = 0; u = v = 0;
		memset(chk, 0, sizeof(char)*MAX*2);
		N = MIN + rand() % (MAX - MIN);
		for (i = 0; i < N; i++)
			src[i] = new_parti();
		
		init(N, src);

		time_t s = clock();
		for (j = 0; j < 100; j++)
		{
			for (k = 0; k < 100; k++)
			{
				remove(getid(1));
				add(new_parti());
			}

			totalsum(&u, &v);
			result = (result + u + v) % 10003;
		}
		performance = clock() - s;
		printf("#&d : %d %d\n", tc + 1, result, performance);
	}
}