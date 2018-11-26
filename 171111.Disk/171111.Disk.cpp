#include <iostream>
#include <time.h>
#include <memory.h>

char DISK_DATA[65536 * 512];//
char FILE_DATA[100][65536];
char FILE_NAME[100][32];
int FILE_SIZE[100];

int seed = 0;

int pseudo_rand()
{
	return rand()%0x7fff;
}

void read_disk(int sector, char data[512])
{
	memcpy(data, DISK_DATA + sector * 65536, 512);
}

void write_disk(int sector, char data[512])
{
	memcpy(DISK_DATA + sector * 65536, data, 512);
}

void _read_file(int no, int pos, char data[4096], int size)
{

}

void _write_file(int no, int pos, char data[4096], int size)
{
	if (pos + size > 65536)
		size = 65536 - pos;
	if (pos + size > FILE_SIZE[no])
		FILE_SIZE[no] = pos + size;

	memcpy(FILE_DATA[no] + pos, data, size);
}

extern void read_disk_usr(int no, int pos, char data[4096], int size);
extern void write_disk_usr(int no, int pos, char data[4096], int size);

int main()
{
	for (int i = 0; i < 100; i++)
	{
		int n = 16 + pseudo_rand() % 16;
		for (int j = 0; j < n; j++)
		{
			FILE_NAME[i][j] = 'A' + pseudo_rand() % 26;
		}
		FILE_NAME[i][n] = 0;
	}

	int mode;
	int pos;
	int size;
	char data[4096];
	int file_no;
	for (int i = 0; i < 25000; i++)
	{
		if (i < 5000)
			mode = 10;
		else
			mode = rand() % 10 + 1;
		
		pos = rand() % 65536;
		size = rand() % 4096;
		file_no = rand() % 100;
		if (mode == 10)
		{
			memset(data, 0, sizeof(data));
			for (int j = 0; j < size; j++)
				data[j] = rand() % 256;
			_write_file(file_no, pos, data, size);
			
		}
			
	}
}
