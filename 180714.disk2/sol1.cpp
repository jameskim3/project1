extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);
const int DEF_FILE = 0;
const int DEF_INS = 20;
const int DEF_DEL1 = 21;
const int DEF_DEL2 = 22;
const int DEF_DEL3 = 23;
const int DEF_DEL4 = 24;
const int DEF_FILE0 = 25;

int div = 100;
int ins_cnt[100];
int del_cnt[100];
static unsigned char DISK2[16][1024][1024];

int hash_f(const char* fn, int len)
{
	int cnt = 0;
	unsigned long seed = 5381;
	while (cnt < len)
	{
		seed = (((seed << 5) + seed) + *fn++) % 0x7fff;
		cnt++;
	}
	return seed;
}
int memcmp2(const char* a, unsigned char* b, int len)
{
	int cnt = 0;
	while (cnt<len)
	{
		if (*a != *b)break;
		a++, b++; cnt++;
	}
	return cnt == len ? 1 : 0;
}
void memcpy2(unsigned char* tar, const char* src, int len)
{
	int cnt = 0;
	while (cnt < len)
		tar[cnt] = src[cnt++];
}
int getfilenum(const char* fn)
{
	int dn = 0;
	int sn = 0;
	int on = 0;
	int fh = hash_f(fn,16)%div;
	int cnt = 0;
	while (1)
	{
		dn = 0;
		sn = fh / 100;
		on = fh % 100;
		if (DISK2[dn][sn][on * 10] != 0 && memcmp2(fn, &DISK2[dn][sn][on * 10], 10))
			break;
		else if (DISK2[dn][sn][on * 10] == 0)
		{
			memcpy2(&DISK2[dn][sn][on * 10], fn, 10);
			break;
		}
		fh = (fh + 1) % div;
		cnt++;
	}
	return fh;
}
int getInt(unsigned char* p, int len)
{
	int ret = 0;
	if (len == 3)
		ret = p[2] * 256 * 256 + p[1] * 256 + p[0];
	else if (len == 2)
		ret = p[1] * 256 + p[0];
	else
		ret = p[0];
	return ret;
}
void setChar(unsigned char* tar, int val)
{
	while (val)
	{
		*tar = val % 256;
		val /= 256;
		tar++;
	}
}
void insert_file(const char *file_name, const unsigned char *data, int offset, int size)
{
	unsigned char stc[8];
	int fnum = getfilenum(file_name);
	int pos = getInt(&DISK2[0][DEF_INS][0],2);
	int dn = pos / 1024;
	int sn = pos % 1024;
	if ((sn + (size-1) / 1024) >= 1024)
	{
		dn++; sn = 0;
	}
	setChar(&stc[0], dn);
	setChar(&stc[1], sn);
	setChar(&stc[3], offset);
	setChar(&stc[6], size);
}
void delete_file(const char *file_name, int offset, int size)
{
	int fnum = getfilenum(file_name);
}
void read_file(const char *file_name, const unsigned char *data, int offset, int size)
{}
void init()
{
	for (int dn = 0; dn < 16; ++dn)
		for (int sn = 0; sn < 1024; ++sn)
			for (int pn = 0; pn < 1024; ++pn)
				DISK2[dn][sn][pn] = 0;
	for (int i = 0; i < 100; ++i)
	{
		ins_cnt[i] = 0;//150
		del_cnt[i] = 0;//100
	}
}