extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);
const int DN0 = 0;
const int SFN = 0;
const int SIN = 10;//ins2, del1~del4 18, fileheader 18~228
const int SDEL1 = 11;//del heap
const int SDEL2 = 12;
const int SDEL3 = 13;
const int SDEL4 = 14;
const int SROOT0 = 15;

int div = 1000;
int ins_cnt[100];
int del_cnt[100];
static unsigned char DISK2[16][1024][1024];
void delete_file(unsigned char *file_name, int offset, int size);

int hash_f(unsigned char* fn, int len)
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
int memcmp2(unsigned char* a, unsigned char* b, int len)
{
	int cnt = 0;
	while (cnt<len)
	{
		if (*a != *b)break;
		a++, b++; cnt++;
	}
	return cnt == len ? 1 : 0;
}
void memcpy2(unsigned char* tar, unsigned char* src, int len)
{
	int cnt = 0;
	while (cnt < len)
		tar[cnt] = src[cnt++];
}
int getfilenum(unsigned char* fn)
{
	int dn = DN0;
	int sn = 0;
	int on = 0;
	int fh = hash_f(fn, 16) % div;
	int cnt = 0;
	while (1)
	{
		dn = DN0;
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
void setChar(unsigned char* tar, int val, int len)
{
	int cnt = 0;
	while (cnt < len)
	{
		tar[cnt++] = val % 256;
		val /= 256;
	}
}
int insertPatch(int root, unsigned char data, int offset, int size)
{
	int p = 0;
	memcpy2(f_info, &DISK2[DN0][SROOT0][0], 1024);
}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size)
{
	int fnum = getfilenum(file_name);
	unsigned char f_info[1024] = { 0 };
	memcpy2(f_info, &DISK2[DN0][SROOT0][0], 1024);

	int root = getInt(&f_info[fnum*2], 2);
	if (root == 0)
	{
		int p = insertPatch(root, data, offset, size);
		insert_node(root, p, 0);
		return;
	}
	int pos = getPatch(root, offset);
	int l_off, r_off, l_size, r_size;
	unsigned char l_data[4096], r_data[4096];
	split_patch(pos, &l_off, &r_off, &l_size, &r_size, l_data, r_data);
	int p1 = insertPatch(root, l_data, l_off, l_size);
	int p2 = insertPatch(root, r_data, r_off, r_size);
	delPatch(fnum, pos);
	int p = insertPatch(root, data, offset, size);
	insert_node(p1, p, p2);
}
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