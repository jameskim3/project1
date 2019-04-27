#include <iostream>
#include <time.h>

static unsigned char DISK[16][1024][1024];
static unsigned char FILE_CONTEXT[100][600000];
static char FILE_NAME[100][16];
static int FILE_SIZE[100];
static int TOTAL_SIZE;
static int DISK_NUM;

extern void insert_file(unsigned char *file_name, unsigned char *data, int offset, int size);
extern void delete_file(unsigned char *file_name, int offset, int size);
extern void read_file(unsigned char *file_name, unsigned char *data, int offset, int size);
extern void read_size(unsigned char *file_name, int* size);
extern void init();

void _write_data(int sector, unsigned char* data, int size)
{
	if (sector < 0 || sector >= 1024)return;
	memcpy(DISK[DISK_NUM][sector], data, 1024);
}

void _read_data(int sector, unsigned char* data)
{
	if (sector < 0 || sector >= 1024)return;
	memcpy(data, DISK[DISK_NUM][sector], 1024);
}

void _change_disk(int disk)
{
	DISK_NUM = disk;
}

int PENALTY = 0;
void _build()
{
	PENALTY = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			FILE_NAME[i][j] = rand() % 26 + 'A';
		}
		FILE_SIZE[i] = 0;
	}
	TOTAL_SIZE = 0;

	init();
}

unsigned char data2[300000];
int INSERT_SIZE = 4096;
void insert_data()
{
	int file = rand() % 100;
	unsigned char fn[16];
	for (int i = 0; i < 16; i++)
		fn[i] = FILE_NAME[file][i];

	int size = rand() % INSERT_SIZE + 1;
	int offset;
	offset = FILE_SIZE[file] == 0 ? 0 : rand() % FILE_SIZE[file];

	unsigned char data[4096];
	for (int i = 0; i < size; i++)
		data[i] = rand() % 26+'A';
	int shift_size = FILE_SIZE[file] - offset;
	memcpy(data2, &FILE_CONTEXT[file][offset], shift_size);

	insert_file(fn, data, offset, size);
	FILE_SIZE[file] += size;
	TOTAL_SIZE += size;

	memcpy(&FILE_CONTEXT[file][offset], data, size);
	memcpy(&FILE_CONTEXT[file][offset + size], data2, shift_size);
}
int DELETE_SIZE = 4096;
void delete_data()
{
	int file = rand() % 100;
	if (FILE_SIZE[file] == 0)return;
	unsigned char fn[16];
	for (int i = 0; i < 16; i++)
		fn[i] = FILE_NAME[file][i];

	int size = rand() % DELETE_SIZE + 1;
	int offset = rand() % FILE_SIZE[file];

	if (size + offset > FILE_SIZE[file])
		size = FILE_SIZE[file] - offset;
	if (size <= 0)return;
	
	int shift_size = FILE_SIZE[file] - (offset+size);
	memcpy(data2, &FILE_CONTEXT[file][offset+size], shift_size);

	delete_file(fn, offset, size);
	FILE_SIZE[file] -= size;
	TOTAL_SIZE -= size;

	memcpy(&FILE_CONTEXT[file][offset], data2, shift_size);
	FILE_CONTEXT[file][FILE_SIZE[file]] = '\0';
}

void verify()
{
	int fsize[100] = { 0 };
	unsigned char fn[16];
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 16; j++)
			fn[j] = FILE_NAME[i][j];
		read_size(fn, &fsize[i]);
	}

	int file = rand() % 100;
	for (int i = 0; i < 16; i++)
		fn[i] = FILE_NAME[file][i];

	int size = rand() % 4096 + 1;
	unsigned char data[4096];
	int offset = rand() % FILE_SIZE[file];
	
	if (size + offset > FILE_SIZE[file])
		size = FILE_SIZE[file] - offset;

	read_file(fn, data, offset, size);
	if (size>0 && memcmp(data, &FILE_CONTEXT[file][offset], size) != 0)
		PENALTY += 1000000;

	for (int i = 0; i < FILE_SIZE[file]; i++){
		if (memcmp(data, &FILE_CONTEXT[file][i], 100) == 0){
			int a324 = 234;
		}
	}
}

int main()
{
	freopen("out.txt", "w", stdout);
	time_t start = clock();
	for (int tc = 0; tc < 10 ; tc++)
	{
		_build();
		while (TOTAL_SIZE < 10 * 1024 * 1024)
		{
			int c = rand() % 10;
			switch (c)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				insert_data(); break;
			case 6:
			case 7:
			case 8:
			case 9:
				//delete_data(); 
				break;
			}
		}
		for (int i = 0; i < 100; i++)
			verify();
	}
	time_t end = clock();

	printf("penalty: %d\n", PENALTY + end-start);
	return 0;
}