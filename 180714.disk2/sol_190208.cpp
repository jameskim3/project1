#include<stdio.h>

extern void _write_data(int sector, unsigned char* data, int size);
extern void _read_data(int sector, unsigned char* data);
extern void _change_disk(int disk);

typedef struct st{
	int next;
	int size;
	int sector_no;
	unsigned char data[1024];
}ST;

static unsigned char DISK2[32 * 1024 * 1024];//DISK2[16][1024][1024];
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
		if (DISK2[dn*DS + sn*SS + on] != 0 && memcmp2(fn, &DISK2[dn*DS + sn*SS + on], 10))
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
void int2char(unsigned char *c, int v){
	int t;
	int pos = 0;
	while (pos<2){
		t = v % 256;
		c[pos] = t;
		pos++;
		v /= 256;
	}
}
int char2int(unsigned char * c){
	return c[1] * 256 + c[0];
}
void resetST(ST* data){
	unsigned char tmp[1024] = { 0 };
	memcpy2(data->data, tmp, 1024);
	data->next = 0;
	data->sector_no = 0;
	data->size = 0;
}
void makeSector(ST* t){
	unsigned char conv[2];
	int2char(conv, t->size);
	memcpy2(&t->data[0], conv, 2);
	int2char(conv, t->next);
	memcpy2(&t->data[2], conv, 2);
	int2char(conv, t->sector_no);
	memcpy2(&t->data[4], conv, 2);

	memcpy2(&DISK2[1024*t->sector_no], t->data, 1024);
}
void getSector(int no, ST* p){
	memcpy2(p->data, &DISK2[no * 1024], 1024);
	p->size = char2int(&p->data[0]);
	p->next = char2int(&p->data[2]);
	p->sector_no = char2int(&p->data[4]);
}
int getNewSector(){
	int p;
	if (DPOS != 0){
		p = DPOS;
		ST tmp;
		getSector(DPOS, &tmp);
		DPOS = tmp.next;
	}
	else{
		p = NPOS++;
	}
	return p;
}
void addEmptySector(int sector){
	ST tmp;
	getSector(sector, &tmp);
	resetST(&tmp);
	tmp.size = 0;
	tmp.next = DPOS;
	tmp.sector_no = sector;
	makeSector(&tmp);
	DPOS = sector;
}
void searchSector(int fnum, int offset, ST* pre, int* next, int* pre_pos){
	int sum = 0;
	ST cur, old;
	getSector(fnum + 1, &cur);
	while (sum + cur.size < offset){
		sum += cur.size;
		old = cur;
		getSector(cur.next, &cur);
		if (cur.next == 0)
			int a234 = 234;
	}
	*pre = cur;
	*next = cur.next;
	*pre_pos = offset -sum;
}
void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size){
	int fnum = getfilenum(file_name);
	ST pre;
	ST cur;
	int next;
	int pre_pos;
	searchSector(fnum, offset, &pre, &next, &pre_pos);
	unsigned char ret[8192] = { 0 };
	memcpy2(ret, &pre.data[6+pre_pos], pre.size - pre_pos);
	memcpy2(&ret[pre.size - pre_pos], data, size);

	int total_size = pre.size - pre_pos + size;
	pre.size = pre_pos;

	int cnt = 0;
	while (cnt < total_size){
		int sn = getNewSector();
		if (total_size> cnt + 1018){
			memcpy2(&cur.data[6], &ret[cnt], 1018);
			cur.sector_no = sn;
			cur.size = 1018;
			cur.next = 0;
			makeSector(&cur);
			cnt += 1018;
		}
		else{
			int ts = total_size - cnt;
			memcpy2(&cur.data[6], &ret[cnt], ts);
			cur.sector_no = sn;
			cur.size = ts;
			cur.next = 0;
			makeSector(&cur);
			cnt += ts;
		}
		pre.next = sn;
		makeSector(&pre);
		getSector(cur.sector_no, &pre);
	}
	cur.next = next;
	makeSector(&cur);
}
void delete_file(unsigned char *file_name, int offset, int size){
	int fnum = getfilenum(file_name);
	ST pre;
	ST cur;
	resetST(&cur);
	int nsector;
	int pre_pos;
	searchSector(fnum, offset, &pre, &nsector, &pre_pos);

	unsigned char ret[8192] = { 0 };
	int cnt = 0;
	if (pre.size - pre_pos >= size){
		int r = pre.size - pre_pos - size;
		memcpy2(ret, &pre.data[6 + pre_pos + size], r);
		memcpy2(&pre.data[pre_pos], ret, r);
		pre.size = pre_pos + r;
		cnt = size;
	}
	else{
		cnt += pre.size - pre_pos;
		pre.size = pre_pos;
	}

	if(nsector>0)getSector(nsector, &cur);
	while (cnt < size){
		if (cur.size > size - cnt){
			int s = cur.size - (size - cnt);
			memcpy2(ret, &cur.data[6+size - cnt], s);
			memcpy2(&cur.data[6], ret, s);
			cur.size = s;
			cnt = size;
		}
		else{
			cnt += cur.size;
			int tmp_sector = cur.sector_no;
			if(cur.next>0)getSector(cur.next, &cur);
			addEmptySector(tmp_sector);
		}
	}
	pre.next = cur.sector_no;
	makeSector(&pre);
	if(cur.sector_no>0)makeSector(&cur);
}
void read_file(unsigned char *file_name, unsigned char *data, int offset, int size){
	int fnum = getfilenum(file_name);
	ST pre;
	int nsector;
	int pre_pos;
	searchSector(fnum, offset, &pre, &nsector, &pre_pos);

	unsigned char ret[8192] = { 0 };
	int cnt = 0;
	while (cnt < size){
		memcpy2(&ret[cnt], &pre.data[pre_pos], pre.size - pre_pos);
		cnt += pre.size - pre_pos;
		pre_pos = 0;
		if (nsector>0)getSector(pre.next, &pre);
	}
	memcpy2(data, ret, size);
}
void read_size(unsigned char *file_name, int* size){
	unsigned char t[4096];
	int fnum = getfilenum(file_name);
	ST cur;
	int sn = fnum + 1;
	getSector(sn, &cur);
	while (1){
		if (cur.size > 0){
			memcpy2(t, &cur.data[6], cur.size);
			t[cur.size] = 0;
			printf("%s", t);
		}
		
		*size += cur.size;
		if (cur.next == 0)break;
		getSector(cur.next, &cur);
	}
}
void init(){
	unsigned char ret[1024] = { 0 };
	memcpy2(&DISK2[DS * 0 + SS * 0], ret, 1024);
	int sn;
	ST tmp;
	unsigned char cont[1024 - 8] = { 0 };
	for (int i = 0; i < 101; i++){// file pos, npos, dpos
		sn = i + 1;
		resetST(&tmp);
		tmp.sector_no = sn;
		makeSector(&tmp);
	}
	DPOS = 0;
	NPOS = 101;
}
