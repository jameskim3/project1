struct MEMO
{
	char data[50][50];
	int y, x, height, width;
	int id;
	MEMO* pre;
	MEMO* next;
};
MEMO item[50000];
int rp;
MEMO* myList;

int MY_SIZE_Y, MY_SIZE_X;
void init(int sizeY, int sizeX)
{
	rp = 0;
	MY_SIZE_Y = sizeY;
	MY_SIZE_X = sizeX;
	for (int i = 0; i < 50000; i++)
	{
		for (int j = 0; j < 50; j++)
			for (int k = 0; k < 50;k++)
			item[i].data[j][k] = 0;
		item[i].pre = 0;
		item[i].next = 0;
	}
	myList = 0;
}
void makeMemo(int id, int y, int x, int height, int width, const char* data)
{
	MEMO* tmp = &item[rp++];
	int i, j, k;
	tmp->y = y; tmp->x = x; tmp->height = height; tmp->width = width;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			tmp->data[y+i][x+j] = data[i*width + j];
	tmp->id = id;
	tmp->next = myList;
	if (myList != 0) myList->pre = tmp;
	myList = tmp;
}
void chooseMemo(int id)
{
	MEMO* tmp = &item[id];
	if (tmp->pre != 0) tmp->pre->next = tmp->next;
	if (tmp->next != 0) tmp->next->pre = tmp->pre;
	tmp->pre = 0;
	tmp->next = myList;
	if (myList != 0) myList->pre = tmp;
	myList = tmp;
}
void moveMemo(int id, int y, int x)
{
	MEMO* tmp = &item[id];

	if (y + tmp->height >= MY_SIZE_Y || x + tmp->width >= MY_SIZE_X) 
		return;

	char bak[2510];
	int i, j;
	for (i = 0; i < tmp->height; i++)
		for (j = 0; j < tmp->width; j++)
			bak[i*tmp->width + j] = tmp->data[tmp->y + i][tmp->x + j];
	for (i = 0; i < tmp->height; i++)
		for (j = 0; j < tmp->width; j++)
			tmp->data[tmp->y + i][tmp->x + j] = 0;
	for (i = 0; i < tmp->height; i++)
		for (j = 0; j < tmp->width; j++)
			tmp->data[y + i][x + j] = bak[i*tmp->width + j];
	tmp->y = y; tmp->x = x;
}
void getContext(int y, int x, char* retString)
{
	int chk[5][5] = { 0 };
	int cnt = 0;
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			retString[i * 5 + j] = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			MEMO* head = myList;
			while (head != 0)
			{
				if (head->data[y + i][x + i] != 0)
				{
					retString[i * 5 + j] = head->data[y + i][x + i];
					break;
				}
				head = head->next;
			}
		}
	}
}