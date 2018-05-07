const int LM = 3;
const int TC = 20;
const int MAX_ROTATE = 8;

extern void copy_cube(int src[6][LM][LM], int tar[6][LM][LM]);
extern void initial_cute(int cube[6][LM][LM]);
extern void rotate(int cube[6][3][3], int face, int cw);

struct st2{
	int face, cw;
};
st2 acts[MAX_ROTATE];

int search(int start[6][LM][LM],int visited)
{
	int check = 1;
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
			{
				if (start[face][i][j] != face)
					check = 0;
			}
	if (check == 1)
		return 1;

	if (visited >= MAX_ROTATE)
	{
		return 0;
	}


	for (int face = 0; face < 6; face++)
	{
		for (int cw = 0; cw < 2; cw++)
		{
			rotate(start, face, cw);
			acts[visited].face = face;
			acts[visited].cw = cw;
			if (search(start, visited + 1) == 1)
				return 1;

			rotate(start, face, 1 - cw);
			int a = 0;
		}
	}
	return 0;
}

void runTest(int local[6][LM][LM])
{
	int visited = 0;
	search(local, visited);

	return;
}
