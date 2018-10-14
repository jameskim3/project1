extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);
const int FILE = 0;
const int INS = 10;//ins2, del1~del4 18, fileheader 18~228
const int DEL1 = 11;//del heap
const int DEL2 = 12;
const int DEL3 = 13;
const int DEL4 = 14;
const int F0 = 15;//15~1015

int div = 1000;
int ins_cnt[100];
int del_cnt[100];
static unsigned char DISK2[16][1024][1024];

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
void setChar(unsigned char* tar, int val, int len)
{
	int cnt = 0;
	while (cnt < len)
	{
		tar[cnt++] = val % 256;
		val /= 256;
	}
}
int getDel(int size)
{
	int jn = (size - 1) / 1024 ;
	int pos = getInt(&DISK2[0][DEL1+jn][0], 2);
	if (pos == 0)return 0;
	setChar(&DISK2[0][DEL1 + jn][0], pos-1, 2);
	return pos;
}
int assign(int size)
{
	int pos = getInt(&DISK2[0][INS][0], 2);
	int jn = (size - 1) / 1024 +1;
	int sect = pos % 1024;
	if (sect + jn>1024)
		pos += 1024-sect;
	setChar(&DISK2[0][INS][0], pos + jn, 2);
	return pos;
}
int isEmpty(unsigned char* pos, int len)
{
	int cnt = 0;
	while (cnt < len)
	{
		if (pos[cnt++] != 0)return 0;
	}
	return 1;
}
void ins_f(unsigned char *file_name, unsigned char *data, int offset, int size)
{
	unsigned char stc[8];

	//file num
	int fnum = getfilenum(file_name);

	//del possible check
	int dn, sn;
	int pos = getDel(size);
	if (pos == 0)
		pos = assign(size);
	dn = pos / 1024;
	sn = pos % 1024;

	//write index info to file index
	setChar(&stc[0], pos, 2);
	setChar(&stc[2], offset, 2);
	setChar(&stc[4], size, 2);
	int h = offset % 1700;
	int fsect, foff;
	while (1)
	{
		fsect = (F0 + fnum) * 10 + h / 170;
		foff = (h % 170) * 6;
		if (isEmpty(&DISK2[0][fsect][foff], 6))
			break;
		h = (h + 1) % 1700;
	}
	memcpy2(&DISK2[0][fsect][foff], stc, 6);

	//write real data to disk
	int pos = 0;
	while (size > 0)
	{
		memcpy2(&DISK2[dn][sn][0], &data[pos], 1024);
		pos += (size >= 1024 ? 1024 : size);
		size -= 1024;
		dn = pos / 1024;
		sn = pos % 1024;
	}
}
int findOffsetPos(int fnum, int offset, unsigned char* stc, int *idx_pos)
{

}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size)
{
	ins_f(file_name, data, offset, size);

	//offset patch devide
	//file num
	int fnum = getfilenum(file_name);
	unsigned char stc[8];

	unsigned char tmp[4096] = { 0 };
	int idx_pos;
	findOffsetPos(fnum, offset, stc, &idx_pos);
	int f_pos = getInt(stc, 2);
	int f_offset = getInt(&stc[2], 2);
	int f_size = getInt(&stc[4], 2);
	int dn = f_pos / 1024; 
	int sn = f_pos % 1024;
	memcpy2(tmp, DISK2[dn][sn], f_size);	
	
	int diff = offset - f_offset;
	ins_f(file_name, &tmp[diff], offset + size, f_size - diff);

	f_size -= diff;
	setChar(&stc[4], f_size, 2);
	int fsect = (F0 + fnum) * 10 + idx_pos / 170;
	int foff = (idx_pos % 170) * 6;
	memcpy2(&DISK2[0][fsect][foff], stc, 6);
}
void delete_file(unsigned char *file_name, int offset, int size)
{
	unsigned char stc[8];
	int fnum = getfilenum(file_name);
	int idx_pos;
	
	while (size>0)
	{
		findOffsetPos(fnum, offset, stc, &idx_pos);
	}

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