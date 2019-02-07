#include<string>
char text[13000][20000];
int cnt_line[13000];
int Y;
int X;
int total_y;
void create()
{
	Y = X = 0;
	total_y = 1;
	for (int i = 0; i < 13000; i++){
		cnt_line[i] = 0;
	}
}
void putChar(char a)
{
	if (cnt_line[Y] > X){
		char tmp[10000];
		int len = cnt_line[Y] - X;
		strncpy(tmp, &text[Y][X], len);
		strncpy(&text[Y][X+1], tmp, len);
	}
	text[Y][X] = a;
	X++;
	cnt_line[Y]++;
}
void putEnter()
{
	for (int i = total_y - 1; i >= Y + 1; i--){
		strncpy(text[i + 1], text[i], cnt_line[i]);
		cnt_line[i + 1] = cnt_line[i];
	}
	if (cnt_line[Y] > X){
		char tmp[10000];
		int len = cnt_line[Y] - X;
		strncpy(text[Y+1], &text[Y][X], len);
		cnt_line[Y + 1] = len;
		cnt_line[Y] -= len;
	}
	else{
		cnt_line[Y + 1] = 0;
	}
	total_y++;
	X = 0;
	Y++;
}
void putBackSpace()
{
	if (Y == 0 && X == 0)return;
	if (X == 0){
		strncpy(&text[Y - 1][cnt_line[Y - 1]], text[Y], cnt_line[Y]);
		cnt_line[Y - 1] += cnt_line[Y];
		for (int i = Y; i <total_y-1; i++){
			strncpy(text[i], text[i+1], cnt_line[i+1]);
			cnt_line[i] = cnt_line[i+1];
		}
		total_y--;
		X = cnt_line[Y - 1];
		Y--;
	}
	else{
		char tmp[10000];
		int len = cnt_line[Y] - X;
		strncpy(tmp, &text[Y][X], len);
		strncpy(&text[Y][X-1], tmp, len);
		X--;
		cnt_line[Y]--;
	}
}
void moveUp(int n)
{
	int tmp_y = Y;
	tmp_y -= n;
	if (tmp_y < 0)tmp_y = 0;
	if (cnt_line[tmp_y] < X)X = cnt_line[tmp_y];
	Y = tmp_y;
}
void moveDown(int n)
{
	int tmp_y = Y;
	tmp_y += n;
	if (tmp_y >= total_y)tmp_y = total_y - 1;
	if (cnt_line[tmp_y] < X)X = cnt_line[tmp_y];
	Y = tmp_y;
}
void moveLeft(int n)
{
	int tmp_x = X;
	tmp_x -= n;
	if (tmp_x < 0)tmp_x = 0;
	X = tmp_x;
}
void moveRight(int n)
{
	int tmp_x = X;
	tmp_x += n;
	if (tmp_x > cnt_line[Y])tmp_x = cnt_line[Y];
	X = tmp_x;
}
void close(char* document)
{
	int sum = 0;
	int cnt = 0;
	for (int i = 0; i < total_y; i++){
		for (int j = 0; j < cnt_line[i]; j++){
			document[cnt++] = text[i][j];
		}
		document[cnt++] = '\n';
		sum += (cnt_line[i]+1);
	}
	cnt = cnt;
}