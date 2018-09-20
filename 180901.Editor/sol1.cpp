
typedef struct fs {
	fs* pre;
	fs* next;

};

const int MAX_ENT = 1024 * 1024 / 50;
char map[MAX_ENT][5000];
int row_cnt[MAX_ENT];
int gY, gX;
void create()
{
	gY = 0; gX = 0;
	for (int i = 0; i < MAX_ENT; i++)
	{
		row_cnt[i] = 0;
		for (int j = 0; j < 5000; j++)
			map[i][j] = 0;
	}
}
void putChar(char a)
{
	map[gY][gX++] = a;
}
void putEnter()
{
}
void merge(int y)
{

}
void putBackSpace()
{
	if (gX > 0)
	{
		map[gY][gX] = 0;
		gX--;
	}
	else
	{
		if (gY > 0)
		{
			merge(gY);
			gY--;
		}
	}
}
void moveUp(int n)
{
	if ()
}
void moveDown(int n)
{

}
void moveLeft(int n)
{

}
void moveRight(int n)
{

}
void close(char* document)
{

}