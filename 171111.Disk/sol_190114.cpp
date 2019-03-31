//RESULT: 2701239
extern void disk_read(int sector, char data[512]);
extern void disk_write(int sector, char data[512]);

const int FNAME = 0;
const int FSIZE = 7;
const int FCONT = 8;
const int FPART = 13000;
int fvisited[100];
int fcnt = 0;
int getHash(char* fn){
	int h = 5381;
	int cnt = 0;
	while (fn[cnt] && cnt<31){
		h = (h * 33 + fn[cnt]) % 32768;
		cnt++;
	}
	return h;
}
int strcmp(char* a, char* b){
	int cnt = 0;
	while (cnt<31 && *a && *a == *b){
		a++, b++, cnt++;
	}
	return *a == *b;
}
int strncmp(char* a, char* b, int n){
	int cnt = 0;
	while (cnt<n && *a == *b){
		a++, b++, cnt++;
	}
	return *a == *b;
}
void my_disk_write(int p, char d[512]){
	char dt[512] = { 0 };
	for (int i = 0; i < 512; i++)dt[i] = d[i];

	for (int i = 0; i < 4; i++){
		disk_write(p + FPART*i, d);
	}
}
//void my_disk_read(int p, char d[512]){
//	char tmp[4][512];
//	disk_read(p, d);
//	disk_read(p+FPART, tmp[1]);
//	if (strncmp(tmp[1], d, 512))
//		return;
//	for (int i = 2; i < 4; i++){
//		disk_read(p + FPART*i, tmp[i]);
//	}
//	for (int i = 0; i < 512; i++){
//		if (d[i] != tmp[1][i]){
//			char valid[512] = { 0 };
//			valid[d[i] + 128]++;
//			valid[tmp[1][i]+128]++;
//			valid[tmp[2][i]+128]++;
//			valid[tmp[3][i]+128]++;
//			if (valid[tmp[1][i] + 128]>1)
//				d[i] = tmp[1][i];
//			else if (valid[tmp[2][i] + 128]>1)
//				d[i] = tmp[2][i];
//			else if (valid[tmp[3][i] + 128]>1)
//				d[i] = tmp[3][i];
//		}
//	}
//	my_disk_write(p, d);
//}
void my_disk_read(int p, char d[512]){
	char tmp[5][512];
	for (int i = 0; i < 4; i++){
		disk_read(p + FPART*i, tmp[i]);
	}
	for (int i = 0; i < 512; i++){
		int cnt[512] = { 0 };
		int que[5] = { 0 };
		int rp = 0;
		cnt[tmp[0][i]]++, que[rp++] = tmp[0][i];
		cnt[tmp[1][i]]++, que[rp++] = tmp[1][i];
		cnt[tmp[2][i]]++, que[rp++] = tmp[2][i];
		cnt[tmp[3][i]]++, que[rp++] = tmp[3][i];
		
		int max = -1;
		int max_idx = 0;
		for (int j = 0; j < rp; j++){
			if (max < cnt[que[j]]){
				max = cnt[que[j]], max_idx = que[j];
			}
		}
		if (max == 2)
			int af3 = 1234;		
		if (max == 3)
			int af4 = 1234;
		d[i] = max_idx;
	}
	my_disk_write(p, d);
}
int getFile(char filename[32]){
	int h = getHash(filename)%100;
	char d[512];
	while (1){
		int p = h / 16;
		int o = h % 16;
		my_disk_read(p, d);
		if (d[o * 32] == 0){
			int cnt = 0;
			while (filename[cnt]&& cnt<31){
				d[o * 32 + cnt] = filename[cnt];
				cnt++;
			}
			my_disk_write(p, d);
			fcnt++;
			break;
		}
		else{
			if (strcmp(&d[o * 32], filename) == 1)
				break;
			else
				h = (h + 1) % 100;
		}
	}
	fvisited[h] = 1;
	return h;
}
int getSize(int nFile){
	char d[512];
	my_disk_read(FSIZE, d);
	int v = 0;
	int mul = 1;
	for (int i = 0; i < 3; i++){
		v += d[nFile * 3 + i] * mul;
		mul *= 128;
	}
	return v;
}
void setSize(int nFile, int size){
	char d[512];
	my_disk_read(FSIZE, d);
	int v = 0;
	int mul = 1;
	for (int i = 0; i < 3; i++){
		d[nFile * 3 + i] = size % 128;
		size /= 128;
	}
	my_disk_write(FSIZE, d);
}
void file_read(char filename[32], int pos, char data[4096], int size){
	int nFile = getFile(filename);
	int nSize = getSize(nFile);

	if (nSize < size)size = nSize;
	if (pos > nSize - size)pos = nSize - size;

	char d[512];
	int cnt = 0;
	int p = (65536 * nFile + pos) / 512 + FCONT;
	int o = (65536 * nFile + pos) % 512;
	while (cnt < size){
		my_disk_read(p, d);
		for (int i = o; i < 512; i++){
			data[cnt++] = d[i];
			if (cnt == size)break;
		}
		p++;
		o = 0;
	}
}

void file_write(char filename[32], int pos, char data[4096], int size){
	int nFile = getFile(filename);
	int nSize = getSize(nFile);

	if (pos + size > 65536)size = 65536 - pos;
	if (pos + size > nSize)nSize = pos + size;
	setSize(nFile, nSize);

	char d[512];
	int cnt = 0;
	int p = (65536 * nFile + pos) / 512 + FCONT;
	int o = (65536 * nFile + pos) % 512;
	while (cnt < size){
		my_disk_read(p, d);
		for (int i = o; i < 512; i++){
			d[i] = data[cnt++];
			if (cnt == size)break;
		}
		my_disk_write(p, d);
		p++;
		o = 0;
	}
}