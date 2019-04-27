typedef struct line{
	char d[20000];
	int size;
	line* pre;
	line* next;
}LINE;
LINE ND[20000];
int rp;
int Y, X;
int TY;
LINE* cur;

char buff[20000];
int bcnt;
void strncpy(char* tar, char* src, int n){
	int cnt = 0;
	while (cnt < n){
		tar[cnt] = src[cnt];
		cnt++;
	}
}
void create(){
	Y = X = 0;
	TY = 1;
	bcnt = 0;
	for (int i = 0; i < rp; i++){
		ND[i].size = 0;
		ND[i].pre = 0;
		ND[i].next = 0;
	}
	rp = 0;
	bcnt = 0;
	cur = &ND[rp++];
}
void putChar(char a){
	buff[bcnt++] = a;
}
void ins(){
	if (bcnt == 0)return;
	char tmp[20000];
	strncpy(tmp, &cur->d[X], cur->size - X);
	strncpy(&cur->d[X], buff, bcnt);
	strncpy(&cur->d[X+bcnt], tmp, cur->size - X);
	cur->size += bcnt;
	X += bcnt;
	bcnt = 0;
}
void insLink(LINE* pre, LINE* cur, LINE* next){
	if (pre){
		pre->next = cur;
		if(cur)cur->pre = pre;
	}
	if (cur){
		cur->next = next;
		if (next) next->pre = cur;
	}
}
void delLink(LINE* pre, LINE* cur, LINE* next){
	if (pre)
		pre->next = next;
	if (next)
		next->pre = pre;
}
void putEnter(){
	ins();

	char tmp[20000];
	strncpy(tmp, &cur->d[X], cur->size - X);

	LINE* t = &ND[rp++];
	t->size = cur->size - X;
	strncpy(t->d, tmp, t->size);
	cur->size = X;
	X = 0;
	insLink(cur, t, cur->next);
	cur = t;
}
void putBackSpace(){
	if (bcnt > 0){
		bcnt--;
		return;
	}

	if (X==0){
		if (cur->pre == 0)return;
		LINE* pre = cur->pre;
		strncpy(&pre->d[pre->size], cur->d, cur->size);
		X = pre->size;
		pre->size += cur->size;
		delLink(pre, cur, cur->next);
		cur = pre;
	}
	else{
		char tmp[20000];
		strncpy(tmp, &cur->d[X], cur->size - X);
		strncpy(&cur->d[X - 1], tmp, cur->size - X);
		X--;
		cur->size--;
	}
}
void moveUp(int n){
	ins();

	int cnt = 0;
	while (cnt++ < n){
		if (cur->pre == 0)break;
		cur = cur->pre;
	}
	if (cur->size < X)X = cur->size;
}
void moveDown(int n){
	ins();

	int cnt = 0;
	while (cnt++ < n){
		if (cur->next == 0)break;
		cur = cur->next;
	}
	if (cur->size < X)X = cur->size;
}
void moveLeft(int n){
	ins();

	int cnt = 0;
	while (cnt++ < n){
		if (X <= 0)break;
		X--;
	}
}
void moveRight(int n){
	ins();

	int cnt = 0;
	while (cnt++ < n){
		if (X >= cur->size)break;
		X++;
	}
}
void close(char* document){
	ins();

	moveUp(100000);
	int cnt = 0;
	while (cur != 0){
		strncpy(&document[cnt], cur->d, cur->size);
		cnt += cur->size;
		document[cnt++] = '\n';
		cur = cur->next;
	}
	cnt = cnt;
}