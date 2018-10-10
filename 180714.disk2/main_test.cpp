#include <iostream>

int hash_f(char* fn)
{
	unsigned long seed = 5381;
	while (*fn)
		seed = (((seed << 5) + seed) + *fn++) % 4096;
	return seed;
}
int file_hash[4096];
int main()
{
	srand(1);
	int cnt = 0;
	char fn[16] = { 0 };
	while (cnt++ < 100)
	{
		for (int i = 0; i < 16; i++)
			fn[i] = rand() % 26 + 'A';
		file_hash[hash_f(fn)]++;
	}
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
			printf("%d ", file_hash[i * 64 + j]);
		printf("\n");
	}
}