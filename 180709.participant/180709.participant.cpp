#include <iostream>
#include <time.h>

#define MIN 40000
#define MAX 50000

struct PARTICIPANT
{
	int id, preference;
};

extern void init(int n, PARTICIPANT src[]);
extern void remove(int pre);
extern void add(PARTICIPANT tar);
extern void getsum2(int *a, int *b);

PARTICIPANT src[50000 * 2];
int N;
char chk[50000 * 2];

int setid(int t)
{
	int id;
	while (1)
	{
		id = (rand() + rand() + rand()) % (50000 * 2) + 1;
		if (chk[id] == 1) continue;
		chk[id] = 1;
		break;
	}
	return id;
}

PARTICIPANT new_participant()
{
	PARTICIPANT tmp;
	tmp.id = setid(0);
	tmp.preference = rand() % 50000 + 1;

	return tmp;
}

int main()
{
	int i, j, k, s, t, u, v;
	int result, performance;
	for (int tc = 0; tc < 10; tc++)
	{
		time_t s = clock();
		result = 0; performance = 0; u = v = 0;
		memset(chk, 0, sizeof(chk));
		N = MIN + rand() % (MAX - MIN);
		for (i = 0; i < N; i++)
			src[i] = new_participant();

		init(N, src);

		for (j = 0; j < 40000; j++)
		{
			remove(rand() % 3);//0 MIN, 1 MAX, 2 MID
			add(new_participant());

			getsum2(&u, &v);
			result = (result + u + v) % 10003;
		}

		performance = clock() - s;
		printf("#%d : %d %d\n", tc + 1, result, performance);
	}
}