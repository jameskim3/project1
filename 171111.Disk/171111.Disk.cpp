#include <iostream>
#include<memory.h>
#include<time.h>

using namespace std;
static char disk[65536 * 512];
static int dummy[12];
static char filename[100][32];
static int dummy2[34];
static int filesize[100];
static int dummy3[56];
static char filedata[100][65536];

int fvisited2[100];
int fcnt2 = 0;

static int seed = 0;
void disk_read(int sector, char data[512]){
	memcpy(data, disk + sector * 512, 512);
}
void disk_write(int sector, char data[512]){
	memcpy(disk + sector * 512, data, 512);
}
static int pseudo_rand(){
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7fff;
}
static int _file_read(int file, int pos, char data[4096], int size){
	if (filesize[file] < size)size = filesize[file];
	if (pos > filesize[file] - size)pos = filesize[file] - size;
	memcpy(data, filedata[file] + pos, size);
	return size;
}
static void _file_write(int file, int pos, char data[4096], int size){
	if (pos + size > 65536)size = 65536 - pos;
	if (pos + size > filesize[file])filesize[file] = pos + size;
	memcpy(filedata[file] + pos, data, size);
}

extern void file_read(char filename[32], int pos, char data[4096], int size);
extern void file_write(char filename[32], int pos, char data[4096], int size);

int main(){
	seed = 3;
	memset(disk, 0, sizeof(disk));
	memset(filename, 0, sizeof(filename));
	memset(filedata, 0, sizeof(filedata));

	for (int c = 0; c < 100; c++){
		int len = 16 + pseudo_rand() % 16;
		for (int l = 0; l < len; l++){
			filename[c][l] = 'A' + pseudo_rand() % 26;
		}
		filename[c][len] = 0;
		filesize[c] = 0;
	}

	clock_t TIME = clock();
	int RESULT = 0;

	int wcnt = 0;
	for (int loop = 0; loop < 25000; loop++){
		int mode = (loop < 5000) ? 10 : pseudo_rand() % 10;
		int file = pseudo_rand() % 100;
		int pos = (pseudo_rand() | (pseudo_rand() << 15)) % 65536;
		int size = 1 + pseudo_rand() % 4096;
		if (fvisited2[file] == 0){
			fvisited2[file] = 1;
			fcnt2++;
		}

		char name[32];
		char data[4096];
		char _data[4096];

		if (mode < 9){
			memcpy(name, filename[file], 32);
			file_read(name, pos, data, size);
			size = _file_read(file, pos, _data, size);
			if (memcmp(data, _data, size) != 0)
				RESULT += 100000;
		}
		else{
			for (register int c = 0; c < size; c++){
				data[c] = pseudo_rand() % 128;// 256;
			}
			memcpy(name, filename[file], 32);
			_file_write(file, pos, data, size);
			file_write(name, pos, data, size);
			wcnt++;
		}

		for (int i = 0; i < 10; i++){
			int err = pseudo_rand() % 128;// 256;
			int pos = (pseudo_rand() | (pseudo_rand() << 15)) % (65536 * 512);
			disk[pos] = err;
		}
	}
	RESULT += (clock() - TIME) / (CLOCKS_PER_SEC / 1000);
	cout << "RESULT: " << RESULT << endl;
	return 0;
}


//#include <iostream>
//#include <time.h>
//#include <memory.h>
//
//char DISK_DATA[65536 * 512];//
//char FILE_DATA[100][65536];
//char FILE_NAME[100][32];
//int FILE_SIZE[100];
//
//int seed = 0;
//
//int seed = 3;
//static int pseudo_rand()
//{
//	seed = (214013 * seed + 2531011);
//	return (seed >> 16) & 32767;
//}
//
//void read_disk(int sector, char data[512])
//{
//	memcpy(data, DISK_DATA + sector * 65536, 512);
//}
//
//void write_disk(int sector, char data[512])
//{
//	memcpy(DISK_DATA + sector * 65536, data, 512);
//}
//
//void _read_file(int no, int pos, char data[4096], int size)
//{
//
//}
//
//void _write_file(int no, int pos, char data[4096], int size)
//{
//	if (pos + size > 65536)
//		size = 65536 - pos;
//	if (pos + size > FILE_SIZE[no])
//		FILE_SIZE[no] = pos + size;
//
//	memcpy(FILE_DATA[no] + pos, data, size);
//}
//
//extern void read_disk_usr(int no, int pos, char data[4096], int size);
//extern void write_disk_usr(int no, int pos, char data[4096], int size);
//
//int main()
//{
//	for (int i = 0; i < 100; i++)
//	{
//		int n = 16 + pseudo_rand() % 16;
//		for (int j = 0; j < n; j++)
//		{
//			FILE_NAME[i][j] = 'A' + pseudo_rand() % 26;
//		}
//		FILE_NAME[i][n] = 0;
//	}
//
//	int mode;
//	int pos;
//	int size;
//	char data[4096];
//	int file_no;
//	for (int i = 0; i < 25000; i++)
//	{
//		if (i < 5000)
//			mode = 10;
//		else
//			mode = rand() % 10 + 1;
//		
//		pos = rand() % 65536;
//		size = rand() % 4096;
//		file_no = rand() % 100;
//		if (mode == 10)
//		{
//			memset(data, 0, sizeof(data));
//			for (int j = 0; j < size; j++)
//				data[j] = rand() % 256;
//			_write_file(file_no, pos, data, size);
//			
//		}
//			
//	}
//}
