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
int insertPatch(int fnum, unsigned char* data, int offset, int size)
{
	int p = 0;
	unsigned char f_info[1024] = { 0 };
	memcpy2(f_info, &DISK2[DN0][SIN][0], 1024);
	int pos = getInt(f_info, 2);
	int dn = pos / 1024;
	int sn = pos % 1024;

	unsigned char header[10] = { 0 };
	setChar(&header[0], fnum, 2);
	setChar(&header[2], offset, 2);
	setChar(&header[4], size, 2);
	setChar(&header[6], 0, 2);
	setChar(&header[8], 0, 2);

	int sector_size = ((size + 10 - 1) / 1024)+1;
	if (sector_size + sn > 1024)
	{
		dn++, sn = 0;
	}
	memcpy2(&DISK2[dn][sn][0], header, 10);
	memcpy2(&DISK2[dn][sn][10], data, size);

	pos = dn * 1024 + sn + sector_size;
	return pos;
}
int getPatch(int pos, int offset)
{
	unsigned char f_info[1024] = { 0 };
	int offset2, size2, next2;
	while (1)
	{
		int dn = pos / 1024;
		int sn = pos % 1024;
		memcpy2(f_info, &DISK2[dn][sn][0], 1024);
		offset2 = getInt(&f_info[2], 2);
		size2 = getInt(&f_info[4], 2);
		if (offset2 <= offset && (offset2 + size2) > offset)
			break;
		pos = getInt(&f_info[6], 2);
	}
	return pos;
}
void split_patch(int pos, int offset, int *l_off, int *r_off, int *l_size, int *r_size, unsigned char *l_data, unsigned char *r_data)
{
	int pos2 = getPatch(pos, offset);
	unsigned char f_info[1024] = { 0 };
	int dn = pos2 / 1024;
	int sn = pos2 % 1024;
	memcpy2(f_info, &DISK2[dn][sn][0], 1024);

	int origin_size = getInt(&f_info[2], 4);
	*l_off = getInt(&f_info[2], 2);
	*r_off = offset;
	*l_size = offset - (*l_off);
	*r_size = origin_size - (*l_size);

	unsigned char raw[4096 + 100] = { 0 };
	memcpy2(raw, &DISK2[dn][sn][10], origin_size);
	memcpy2(l_data, raw, *l_size);
	memcpy2(r_data, &raw[*l_size], *r_size);
}
void delPatch(int fnum, int pos)
{

}
void insert_node(int a, int b, int c)
{

}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size)
{
	int fnum = getfilenum(file_name);
	unsigned char f_info[1024] = { 0 };
	memcpy2(f_info, &DISK2[DN0][SROOT0][0], 1024);

	int root = getInt(&f_info[fnum * 2], 2);
	if (root == 0)
	{
		int p = insertPatch(root, data, offset, size);
		setChar(&f_info[fnum * 2], p, 2);
		memcpy2(&DISK2[DN0][SROOT0][0], f_info, 1024);;
		return;
	}
	int pos = getPatch(root, offset);
	int l_off, r_off, l_size, r_size;
	unsigned char l_data[4096], r_data[4096];
	split_patch(pos, offset, &l_off, &r_off, &l_size, &r_size, l_data, r_data);
	delPatch(fnum, pos);
	int p1 = insertPatch(root, l_data, l_off, l_size);
	int p2 = insertPatch(root, r_data, r_off, r_size);
	int p = insertPatch(root, data, offset, size);
	insert_node(p1, p, p2);
}
void delete_file(unsigned char *file_name, int offset, int size)
{
	int fnum = getfilenum(file_name);
	unsigned char f_info[1024] = { 0 };
	memcpy2(f_info, &DISK2[DN0][SROOT0][0], 1024);

	int root = getInt(&f_info[fnum * 2], 2);
	if (root == 0)
		return;
	int pos = getPatch(root, offset);
	int l_off, r_off, l_size, r_size;
	unsigned char l_data[4096], r_data[4096];
	split_patch(pos, offset, &l_off, &r_off, &l_size, &r_size, l_data, r_data);
	delPatch(fnum, pos);
	int p1 = insertPatch(root, l_data, l_off, l_size);
	int p2 = insertPatch(root, r_data, r_off, r_size);

	int remain = size;
	int offset_temp = r_off;
	while (remain > 0)
	{
		if (r_size < size)
		{
			pos = getPatch(root, r_off);
			int dn = pos / 1024;
			int sn = pos % 1024;
			p2 = getInt(&DISK2[dn][sn][6], 2);
			dn = p2 / 1024;
			sn = p2 % 1024;
			r_off = getInt(&DISK2[dn][sn][2], 2);
			delPatch(fnum, pos);
			remain -= r_size;
		}
		else
		{
			split_patch(pos, r_off + r_size, &l_off, &r_off, &l_size, &r_size, l_data, r_data);
			delPatch(fnum, pos);
			p2 = insertPatch(root, r_data, r_off, r_size);
		}
	}
	insert_node(p1, 0, p2);
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
