#include <iostream>
#include <stdlib.h>
#define N 30000
using namespace std;

extern int makeTree(int tree[][4][4]);

int main(void)
{
	static int tree[N][4][4];

	srand(5);

	for (int tc = 1; tc <= 20; tc++)
	{
		for (int c = 0; c < N; c++)
		{
			int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					tree[c][y][x] = base + (rand() % 3);
				}
			}
		}
		cout << "#" << tc << " " << makeTree(tree) << endl;
	}

	return 0;
}