#include <iostream>
using namespace std;
#include <time.h>

int trash_map[1000][1000];
int ori_trash_map[1000][1000];
int trash_can[3];
int result;

void build_map()
{

}

void move_trash(int y, int x, int d)
{
	result++;
}

void test(int trash_map[1000][1000]);

int main()
{
	time_t start,end;

	for (int T = 0; T < 10; T++)
	{
		build_map();

		time(&start);

		test(trash_map);

		time(&end);
		result += (end - start) / (CLOCKS_PER_SEC / 1000);

		for (int i = 0; i < 1000; i++)
			for (int j = 0; j < 1000; j++)
				if (trash_map[i][j] == -1)
					result += 1000;
	}
	return  0;
}

void test(int trash_map[1000][1000])
{

}