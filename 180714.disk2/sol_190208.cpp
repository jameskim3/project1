extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);

static unsigned char DISK2[16][1024][1024];
const int DN0 = 0;
const int SFN = 0;
const int SIN = 10;//ins2, del1~del4 18, fileheader 18~228
const int SDEL1 = 11;//del heap
const int SDEL2 = 12;
const int SDEL3 = 13;
const int SDEL4 = 14;
const int SROOT0 = 15;
int div = 65536;

int hash_f(unsigned char* fn, int len)
{
	int cnt = 0;
	unsigned long seed = 5381;
	while (cnt < len)
	{
		seed = (((seed << 5) + seed) + *fn++) % 0xffff;
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
	int fh = hash_f(fn, 16) % 100;
	int cnt = 0;
	while (1)
	{
		dn = DN0;
		sn = 0;
		on = fh * 10;
		if (DISK2[dn][sn][on] != 0 && memcmp2(fn, &DISK2[dn][sn][on], 10))
			break;
		else if (DISK2[dn][sn][on] == 0)
		{
			memcpy2(&DISK2[dn][sn][on], fn, 10);
			break;
		}
		fh = (fh + 1) % 100;
		cnt++;
	}
	return fh;
}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size){
	int fnum = getfilenum(file_name);
	unsigned char f_info[1024] = { 0 };
	memcpy2(f_info, &DISK2[DN0][SROOT0][0], 1024);
}
void makeSector(unsigned char *pre, unsigned char *next, unsigned char *size, unsigned char *off, unsigned char *cont, unsigned char *ret){

}
void int2char(unsigned char *c, int v){
	int t;
	int pos = 0;
	while (pos<1){
		t = v % 256;
		c[pos] = t;
		pos++;
		v /= 256;
	}
}
void delete_file(unsigned char *file_name, int offset, int size){

}
void read_file(unsigned char *file_name, unsigned char *data, int offset, int size){

}
void init(){
	int dn = DN0;
	int sn = 1;
	int on = 0;
	unsigned char size[2] = { 0 };
	unsigned char off[2] = { 0 };
	unsigned char pre[2] = { 0 };
	unsigned char next[2] = { 0 };
	unsigned char cont[1024 - 8] = { 0 };
	unsigned char ret[1024] = { 0 };
	for (int i = 0; i < 100; i++){
		makeSector(pre, next, size, off, cont, ret);
		memcpy2(DISK2[dn][sn+i], ret, 1024);
	}
	memcpy2(DISK2[dn][101], ret, 1024);//removed
	int2char(cont, dn * 1024 + 103);
	memcpy2(DISK2[dn][102], ret, 1024);//removed

}
