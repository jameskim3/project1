
typedef struct LN{
	int cnt;
	char text[20000];
	LN* pre;
	LN* next;
}SLN;

int Y;
int X;
int total_y;
LN nd[20000];
int rp;
char buff[20000];
int cnt_buff;
LN* cur;
LN* start;
void strncpy(char* tar, char* src, int len){
	for (int i = 0; i < len; i++){
		tar[i] = src[i];
	}
}
void create()
{
	for (int i = 0; i < rp; i++){
		nd[i].pre = 0;
		nd[i].next = 0;
		nd[i].cnt = 0;
	}
	Y = X = rp = 0;
	total_y = 1;
	cnt_buff = 0;
	cur = &nd[rp++];
	start = cur;
}
void putChar(char a)
{
	buff[cnt_buff++] = a;
}
void add_buff(){
	char tmp[20000] = { 0 };
	strncpy(tmp, &cur->text[X], cur->cnt - X);
	strncpy(&cur->text[X], buff, cnt_buff);
	strncpy(&cur->text[X + cnt_buff], tmp, cur->cnt - X);
	X += cnt_buff;
	cur->cnt += cnt_buff;
	cnt_buff = 0;
}
void ins_data(LN* a, LN* b, LN* c){
	if (a){
		a->next = b;
	}
	if (b){
		b->pre = a;
		b->next = c;
	}
	if (c){
		c->pre = b;
	}
}
void del_data(LN* a, LN* b, LN* c){
	if (a){
		a->next = c;
	}
	if (c){
		c->pre = a;
	}
	cur = a;
}
void putEnter()
{
	add_buff();
	LN* ins = &nd[rp++];
	ins_data(cur, ins, cur->next);

	char tmp[20000] = { 0 };
	if (cur->cnt > X){
		strncpy(tmp, &cur->text[X], cur->cnt - X);
		strncpy(cur->next->text, tmp, cur->cnt - X);
		cur->next->cnt = cur->cnt - X;
		cur->cnt = X;
		X = 0;
		cur = cur->next;
	}
	else{
		X = 0;
	}
}
void putBackSpace()
{
	add_buff();

	if (start == cur && X == 0)return;

	char tmp[20000] = { 0 };
	if (X == 0){
		strncpy(tmp, cur->text, cur->cnt);
		int prepos = cur->pre->cnt;
		strncpy(&cur->pre->text[prepos], tmp, cur->cnt);
		X = cur->pre->cnt;
		cur->pre->cnt += cur->cnt;
		del_data(cur->pre, cur, cur->next);

	}
	else{
		strncpy(tmp, &cur->text[X], cur->cnt - X);
		strncpy(&cur->text[X - 1], tmp, cur->cnt - X);
		X--;
		cur->cnt--;
	}
}
void moveUp(int n)
{
	add_buff();

	int cnt = 0;
	int pos = X;
	while (cnt < n && cur != start){
		cnt++;
		cur = cur->pre;
	}
	if (cur->cnt < pos)pos = cur->cnt;
	X = pos;
}
void moveDown(int n)
{
	add_buff();

	int cnt = 0;
	int pos = X;
	while (cnt < n && cur->next != 0){
		cnt++;
		cur = cur->next;
	}
	if (cur->cnt < pos)pos = cur->cnt;
	X = pos;
}
void moveLeft(int n)
{
	add_buff();

	int cnt = 0;
	int pos = X-n;
	if (pos<0)pos = 0;
	X = pos;
}
void moveRight(int n)
{
	add_buff();

	int cnt = 0;
	int pos = X + n;
	if (pos > cur->cnt)pos = cur->cnt;
	X = pos;
}
void close(char* document)
{
	add_buff();

	int cnt = 0;
	cur = start;
	while (cur){
		for (int i = 0; i < cur->cnt; i++){
			document[cnt++] = cur->text[i];
		}
		document[cnt++] = '\n';
		cur = cur->next;
	}

	cnt = cnt;
}