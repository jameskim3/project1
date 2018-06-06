

struct d2 {
	int dx;
	int dy;
};

d2 path[4] = {
	0, -1,
	1, 0,
	0, 1,
	-1, 0,
};
struct d3{
	int p1, p2;
	int type;//0 cross, 1 line
	unsigned char val;
};

struct d1 {
	unsigned char line[4][266];
	int chk[4];
	int val;
	int idx[4];
	d3 info[4][100];
}d[16][16];

int ismatch(int y1, int x1, int d1, int y2, int x2, int d2)
{
	int c1 = d[y1][x1].idx[d1];
	int c2 = d[y2][x2].idx[d2];

	for 
}

void initial(unsigned char newmap[4096][4096])
{
	int idx = 0;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int t = 1; t <= 256; t++)
			{
				d[y][x].line[0][t] = newmap[y * 256][x * 256 + t];
				d[y][x].line[1][t] = newmap[y * 256+t][x * 256 + 255];
				d[y][x].line[2][t] = newmap[y * 256 + 255][x * 256 + t];
				d[y][x].line[3][t] = newmap[y * 256 + t][x * 256];
				if (newmap[y * 256][x * 256 + t] != 0)
				{
					int t1 = newmap[y * 256][x * 256 + t];
					int t2 = 0;
				}
			}
		}
	}

	//type
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				int idx = 0;
				for (int j = 1; j <= 256; j++)
				{
					if (d[y][x].line[i][j - 1] == 0 && d[y][x].line[i][j] != 0 && d[y][x].line[i][j + 1] == 0)
					{
						d[y][x].info[i][idx].type = 0;
						d[y][x].info[i][idx].p1 = j;
						d[y][x].info[i][idx].p2 = j;
						d[y][x].info[i][idx].val = d[y][x].line[i][j];
						idx++;
					}
				}
				for (int j = 1; j <= 256; j++)
				{
					if (d[y][x].line[i][j - 1] != 0 && d[y][x].line[i][j - 1] == d[y][x].line[i][j] && d[y][x].line[i][j] == d[y][x].line[i][j + 1])
					{
						unsigned char t;
						d[y][x].info[i][idx].type = 1;
						d[y][x].info[i][idx].p1 = j-1;
						while (1) 
						{
							t = d[y][x].line[i][j - 1];
							if (t != d[y][x].line[i][++j])
								break;
						}
						d[y][x].info[i][idx].p2 = j-1;
						d[y][x].info[i][idx].val = t;
						idx++;
					}
				}
				d[y][x].idx[i] = idx;
			}
		}
	}
	
	//matching
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (ismatch(y, x, i, y + path[(i + 2) % 4].dy, x + path[(i + 2) % 4].dx, (i + 2) % 4))
					d[y][x].chk[i] = 1;
			}
		}
	}
}
void test(unsigned char newmap[4096][4096])
{
	int a = 1;
	initial(newmap);
}