extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);

typedef struct st{
	int pre;
	int next;
	int off;
	int size;
	int sector_no;
}ST;

static unsigned char DISK2[16*1024*1024];//DISK2[16][1024][1024];
const int DN0 = 0;
const int SFN = 0;
const int SIN = 10;//ins2, del1~del4 18, fileheader 18~228
const int SDEL1 = 11;//del heap
const int SDEL2 = 12;
const int SDEL3 = 13;
const int SDEL4 = 14;
const int SROOT0 = 15;
int div = 65536;

const int DS = 1024 * 1024;
const int SS = 1024;
int NPOS = 101;
int DPOS = -1;

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
		if (DISK2[dn*DS+sn*SS+on] != 0 && memcmp2(fn, &DISK2[dn*DS+sn*SS+on], 10))
			break;
		else if (DISK2[dn*DS + sn*SS + on] == 0)
		{
			memcpy2(&DISK2[dn*DS + sn*SS + on], fn, 10);
			break;
		}
		fh = (fh + 1) % 100;
		cnt++;
	}
	return fh;
}
void searchSector(int fnum, int offset, unsigned char* f_remain, int* pre_sector, int *pre_off_size){

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
void makeSector(int pre, int next, int size, int off, unsigned char *cont, unsigned char *ret){
	int dn = DN0;
	int sn = 1;
	unsigned char uc_size[2] = { 0 };
	unsigned char uc_off[2] = { 0 };
	unsigned char uc_pre[2] = { 0 };
	unsigned char uc_next[2] = { 0 };

	int2char(uc_size, size);
	int2char(uc_off, off);
	int2char(uc_pre, pre);
	int2char(uc_next, next);
	memcpy2(&ret[0], uc_pre, 2);
	memcpy2(&ret[2], uc_next, 2);
	memcpy2(&ret[4], uc_off, 2);
	memcpy2(&ret[6], uc_size, 2);
	memcpy2(&ret[8], cont, 1016);
}
int getNewSector(){
	return 0;
}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size){
	int fnum = getfilenum(file_name);
	unsigned char pre_f_info[1024] = { 0 };
	int pre_sector, pre_off_size;
	searchSector(fnum, offset, pre_f_info, &pre_sector, &pre_off_size);
	unsigned char ret[2048] = { 0 };
	unsigned char cont[1024] = { 0 };
	memcpy2(ret, data, size);
	memcpy2(&ret[size], pre_f_info, pre_off_size);

	int cnt = 0;
	while (cnt < size + pre_off_size){
		int sn = getNewSector();
		if (size + pre_off_size> cnt+1024){
			makeSector(pre_sector, 0, 1024, 0, &ret[cnt], cont);
			memcpy2(&DISK2[DS * 0 + SS*sn], ret, 1024);

		}
	}
}
void delete_file(unsigned char *file_name, int offset, int size){

}
void read_file(unsigned char *file_name, unsigned char *data, int offset, int size){

}
void init(){
	unsigned char ret[1024] = { 0 };
	memcpy2(&DISK2[DS * 0 + SS * 0], ret, 1024);
	int sn;
	unsigned char cont[1024 - 8] = { 0 };
	unsigned char ret[1024] = { 0 };
	for (int i = 0; i < 100; i++){
		sn = i + 1;
		makeSector(0, 0, 0, 0, cont, ret);
		memcpy2(&DISK2[DS*0 + SS*sn], ret, 1024);
	}

	NPOS = 101;
	DPOS = -1;
}
