

int myMax(int a, int b)
{
	return a > b ? a : b;
}

void encode(char TMP[100], char QRC[][100])
{
	int i, j, k,u,v,w;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 100; j++)
		{
			QRC[i][j] = 1;
			QRC[j][i] = 1;
		}
	}

	int x, y;
	for (i = 0; i < 100; i++)
	{
		int b;
		int a = TMP[i] - 'A';
		for (j = 0; j < 5; j++)
		{
			b = a >> j & 0x01;
			x = (i * 6 * 5 + j * 6) % 96;
			y = (i * 6 * 5 + j * 6) / 96;
			y *= 3;

			for (k = 0; k < 3; k++)
				for (u = 0; u < 6; u++)
					QRC[y + k][x + u] = b;
		}
	}
	int sdfasdf = 1324125;
}
void decode(char TMP[][100], char TAR[100])
{

}