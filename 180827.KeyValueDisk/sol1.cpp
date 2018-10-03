#define MAXLEN 12
#define max_key 4800
#define CHK_START 4800*12

bool memwrite(unsigned char src[], int pos, int len);
bool memread(unsigned char dest[], int pos, int len);

void my_strcpy(unsigned char* tar, unsigned char* src)
{
	int p = 0;
	while (*src)
		*tar++ = *src++;
	*tar = 0;
}
int my_strcmp(unsigned char* a, unsigned char* b)
{
	while (*a>0&& *a==*b)
		a++, b++;
	return *a == *b;
}
unsigned long hash_func(const unsigned char *a)
{
	unsigned long h = 5381;
	while (*a)
		h = (((h << 5) + h) + *a++) % max_key;
	return h % max_key;
}
bool init()
{
	unsigned char map2[65536];
	for (int i = 0; i < 65536; i++)map2[i] = 0;
	memwrite(map2, 0, 65536);
	return 1;
}

void char2intArr(unsigned char*dest, unsigned char* src)
{
	int cnt = 0;
	while (*src)
	{
		if ('a' <= *src && *src <= 'z') *dest = *src - 'a'+1;
		else if ('A' <= *src && *src <= 'Z') *dest = *src - 'A' + 27;
		else *dest = *src - '0' + 53;
		src++, dest++, cnt++;
	}
	for (int i = cnt; i < MAXLEN + 1; i++)
	{
		*dest = 0;
		dest++;
	}	
}
void int2charArr(unsigned char*dest, unsigned char* src)
{
	while (*src)
	{
		if (1 <= *src && *src < 27) *dest = *src -1 + 'a';
		else if (27 <= *src && *src < 53) *dest = *src - 27 + 'A';
		else *dest = *src - 53 + '0';
		src++, dest++;
	}
	*dest = 0;
}
void add_hash(unsigned char*dest, int hash)
{
	int cnt = 0;
	while (hash)
	{
		dest[cnt / 2] |= (hash & 0x01) << (6 + cnt % 2);
		cnt++; hash >>= 1;
	}
}
void put(unsigned char key_in[MAXLEN + 1], unsigned char value_in[MAXLEN + 1])
{
	unsigned char gk[MAXLEN + 1];
	unsigned char gv[MAXLEN + 1];
	unsigned char chk2[600];
	memread(chk2, CHK_START, 600);

	int h1 = hash_func(key_in);
	int h2 = hash_func(value_in);

	while (chk2[h1 / 8] & (0x01 << (h1 % 8)))
		h1 = (h1 + 1) % max_key;
	chk2[h1/8] |= (0x01 << (h1 % 8));
	while (chk2[h2 / 8] & (0x01 << (h2 % 8)))
		h2 = (h2 + 1) % max_key;
	chk2[h2/8] |= (0x01 << (h2 % 8));
	memwrite(chk2, CHK_START, 600);
	
	unsigned char dest[MAXLEN+1] = { 0 };
	char2intArr(gk, key_in);
	add_hash(gk, h2);
	memwrite(gk, h1 * 12, 12);
	char2intArr(gv, value_in);
	add_hash(gv, h1);
	memwrite(gv, h2 * 12, 12);
}
void split(unsigned char* dest, unsigned char* src, int* hash)
{
	int cnt = 0;
	while (src[cnt])
	{
		dest[cnt] = src[cnt++] & 0x3f;
	}
	dest[cnt] = 0;
	cnt = 0;
	int h1 = 0;
	while (cnt<13)
	{
		h1 += (src[cnt / 2] & (0x01 << (6 + cnt % 2))) != 0 ? 0x01 << cnt : 0;
		cnt++;
	}
	*hash = h1;
}
void getPos(unsigned char* str, int* h1, int * h2)
{
	//get key and hash
	unsigned char dest[MAXLEN + 1];
	unsigned char dest2[MAXLEN + 1];
	unsigned char dest3[MAXLEN + 1];
	*h1 = hash_func(str);
	while (1)
	{
		memread(dest, 12 * (*h1), 12); dest[12] = 0;
		split(dest2, dest, h2);
		int2charArr(dest3, dest2);
		if (my_strcmp(dest3, str) > 0)//true
			break;
		*h1 = (*h1 + 1) % max_key;
	}
}
void del(unsigned char key_in[MAXLEN + 1])
{
	int h1, h2;
	getPos(key_in, &h1,&h2);

	unsigned char chk2[600];
	memread(chk2, CHK_START, 600);
	chk2[h1 / 8] &= (~(0x01 << (h1 % 8)));
	chk2[h2 / 8] &= (~(0x01 << (h2 % 8)));
	memwrite(chk2, CHK_START, 600);
}
void get(unsigned char key_in[MAXLEN + 1], unsigned char value_out[MAXLEN + 1])
{
	unsigned char dest[MAXLEN + 1];
	unsigned char dest2[MAXLEN + 1];
	int h1, h2;
	getPos(key_in, &h1, &h2);
	memread(dest, 12 * h2, 12); dest[12] = 0;
	split(dest2, dest, &h1);
	int2charArr(value_out, dest2);
}
void getkey(unsigned char value_in[MAXLEN + 1], unsigned char key_out[MAXLEN + 1])
{
	get(value_in, key_out);
}