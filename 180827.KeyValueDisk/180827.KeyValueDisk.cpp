#include<iostream>
#include <time.h>

#define MAX_N 1000
#pragma warning(disable:4996)
#define MEMORYSIZE 65536

static unsigned char mem[MEMORYSIZE];

#define CMD_PUT 100
#define CMD_DEL 200
#define CMD_GET 300
#define CMD_GETKEY 400
#define MAXLEN 12

extern bool init();
extern void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1]);
extern void del(unsigned char key_in[MAXLEN + 1]);
extern void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN+1]);
extern void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1]);
extern void my_strcpy(unsigned char* tar, unsigned char* src);

bool memread(unsigned char dest[], int pos, int len)
{
	if (pos<0 || len <= 0 || pos + len>MEMORYSIZE)
	{
		return false;
	}
	for (register int i = 0; i < len; ++i)
		dest[i] = mem[pos + i];
	return true;
}
bool memwrite(unsigned char src[], int pos, int len)
{
	if (pos < 0 || len <= 0 || pos + len>MEMORYSIZE)
		return false;
	for (register int i = 0; i < len; ++i)
		mem[pos + i] = src[i];
	return true;
}
static bool ztrcmp(unsigned char *a, unsigned char *b)
{
	while (*a != 0 && *a == *b)
		++a, ++b;
	return *a == *b;
}

const int max_key = 10000;
typedef struct key_val{
	unsigned char k[MAXLEN + 1];
	unsigned char v[MAXLEN + 1];
}KEY_VAL;
int chk[max_key];
int del_chk[max_key];
KEY_VAL map[max_key];
unsigned long hash_f(const unsigned char *a)
{
	unsigned long h = 5381;
	while (*a)
		h = (((h << 5) + h) + *a++) % max_key;
	return h % max_key;
}
void get_rand_str(unsigned char*a, unsigned char*b)
{
	register int i;
	int max_str = rand() % 8 + 5;
	for (i = 0; i < max_str; i++)
	{
		char r1 = rand() % 62;
		char r2 = rand() % 62;
		if (r1 < 26) r1 += 'a';
		else if (r1 < 52) r1 = r1-26 +'A';
		else r1 = r1-52+'0';
		if (r2 < 26) r2 += 'a';
		else if (r2 < 52) r2 = r2 - 26 + 'A';
		else r2 += r2 - 52 + '0';
		a[i] = r1; b[i] = r2;
	}
	a[max_str] = b[max_str] = 0;
}
void build_map()
{
	for (register int i = 0; i < max_key; ++i)
	{
		while (1)
		{
			get_rand_str(map[i].k, map[i].v);
			int hv = hash_f(map[i].k);
			if (chk[hv] == 0)
			{
				chk[hv] = 1;
				break;
			}
		}
	}
}
void mix_map()
{
	int s, t;
	unsigned char c1[MAXLEN + 1], c2[MAXLEN + 1];
	for (register int i = 0; i < max_key; i++)
	{
		s = rand() % max_key;
		t = rand() % max_key;
		my_strcpy(c1, map[s].k);
		my_strcpy(c2, map[s].v);
		my_strcpy(map[s].k, map[t].k);
		my_strcpy(map[s].v, map[t].v);
		my_strcpy(map[t].k, c1);
		my_strcpy(map[t].v, c2);
	}
}
int rp;
static bool run()
{
	unsigned char key[MAXLEN + 1], value[MAXLEN + 1];
	unsigned char key_u[MAXLEN + 1], value_u[MAXLEN + 1];
	mix_map();
	bool okay = init();
	for (int i = 0; i < max_key; i++)
		del_chk[i] = 0;

	srand(time(NULL));
	int ms = 0;
	int q = 0;
	while (ms<2300)
	{
		int cmd = rand()%100;
		if (75 <= cmd && cmd < 85) cmd = CMD_GET;
		else if (85 <= cmd && cmd < 95) cmd = CMD_GETKEY;
		else if (95 <= cmd && cmd < 100) cmd = CMD_DEL;
		else cmd = CMD_PUT;

		switch (cmd)
		{
		case CMD_PUT:
			if (okay) put(map[q].k, map[q].v);
			q++;
			ms++;
			break;
		case CMD_DEL:
			if (ms <= 5)break;
			rp = rand() % q;
			if (okay && del_chk[rp] == 0) {
				del(map[rp].k);
				del_chk[rp] = 1;
				ms--;
			}
			break;
		case CMD_GET:
			if (ms <= 5)break;
			rp = rand() % q;
			if (okay && del_chk[rp] == 0) {
				get(map[rp].k, value_u);
				if (!ztrcmp(map[rp].v, value_u))
					okay = false;
			}
			break;
		case CMD_GETKEY:
			if (ms <= 5)break;
			rp = rand() % q;
			if (okay && del_chk[rp] == 0) {
				getkey(map[rp].v, key_u);
				if (!ztrcmp(map[rp].k, key_u))
					okay = false;
			}	
			break;
		}
	}
	return okay;
}
int TC = 100;
int main()
{
	build_map();
	int SCORE = 0;
	for (int tc = 0; tc < TC; tc++)
	{
		int score = run() ? 100 : 0;
		SCORE += score;
		printf("#%d SCORE:%d \n", tc+1, score);
	}
	printf("SCORE:%d \n", SCORE);
	return 0;
}