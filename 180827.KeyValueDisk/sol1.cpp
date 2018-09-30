#define MAXLEN 12
bool memwrite(unsigned char src[], int pos, int len);
bool memread(unsigned char dest[], int pos, int len);

void my_strncpy(unsigned char* tar, unsigned char* src, int len)
{
	int p = 0;
	while (len--)
		tar[p] = src[p++];
}
int my_strncmp(unsigned char* a, unsigned char* b, int len)
{
	int ret = 1;
	while (len-- > 0)
	{
		if (*a++ != *b++)
		{
			ret = 0;  break;
		}
	}
	return ret;
}
const int max_key = 4600;
unsigned long hash_f(const unsigned char *a, int len)
{
	unsigned long h = 5381;
	while (len--)
		h = (((h << 5) + h) + *a++) % max_key;
	return h % max_key;
}
unsigned char map2[65536];
char chk2[10000];
bool init()
{
	for (int i = 0; i < 65536; i++)map2[i] = 0;
	for (int i = 0; i < 10000; i++)chk2[i] = 0;
	memwrite(map2, 0, 65536);
	return 1;
}
unsigned char gk[MAXLEN + 3];
unsigned char gv[MAXLEN + 3];
void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1])
{
	int h1 = hash_f(key_in,12);
	int h2 = hash_f(value_in,12);

	while (chk2[h1] == 1)
		h1 = (h1 + 1) % max_key;
	chk2[h1] = 1;
	while (chk2[h2] == 1)
		h2 = (h2 + 1) % max_key;
	chk2[h2] = 1;

	unsigned char p1[3] = { 0 };
	unsigned char p2[3] = { 0 };

	for (int i = 0; i<16; i++)
		p1[i / 8] |= ((0x01 << i) & h1) >> (i/8)*8;
	for (int i = 0; i<16; i++)
		p2[i / 8] |= ((0x01 << i) & h2) >> (i / 8) * 8;

	my_strncpy(gk, key_in, 12);
	my_strncpy(gv, value_in, 12);
	my_strncpy(&gk[12], p2,2);
	memwrite(gk, h1 * 14, 14);
	my_strncpy(&gv[12], p1,2);
	memwrite(gv, h2 * 14, 14);
}
int getPos(unsigned char* str)
{
	int h1 = hash_f(str,12);
	while (1)
	{
		memread(gk, h1*14, 14);
		if (my_strncmp(gk, str, 12) > 0)//true
			break;
		h1 = (h1 + 1) % max_key;
	}
	return h1;
}
void del(unsigned char key_in[MAXLEN + 1])
{
	int h1 = getPos(key_in);
	unsigned char p1[3] = { 0 };
	unsigned char p2[3] = { 0 };
	my_strncpy(p1, &gk[12], 2);
	int h2 = 0;
	for (int i = 0; i<16; i++)
		h2 |= (0x01 << i) & (p1[i / 8] << (i / 8) * 8);

	memwrite(p2, h1*14, 1);
	memwrite(p2, h2*14, 1);
	chk2[h1] = 0;
	chk2[h2] = 0;
}
void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1])
{
	int h1 = getPos(key_in);
	unsigned char p1[3] = { 0 };
	my_strncpy(p1, &gk[12],2);
	int h2 = 0;
	for (int i = 0; i<16; i++)
		h2 |= (0x01 << i) & (p1[i / 8] << (i / 8) * 8);
	memread(value_out, h2*14, 12);
	value_out[12] = 0;
}
void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1])
{
	get(value_in, key_out);
}