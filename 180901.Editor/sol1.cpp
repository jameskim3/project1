
typedef struct map {
	char d[20000];
	int cnt;
}MAP;

typedef struct fs {
	fs* pre;
	fs* next;
	map* m;
}FS;

const int MAX_ENT = 1024 * 1024 / 50;
map map_heap[MAX_ENT];
fs fs_heap[MAX_ENT];
fs* head;
fs* cur;
int gX;
int rp;
char buff[20000];
int bcnt = 0;
void create()
{
	rp = 0;
	gX = 0; ;
	head = 0;
	head = &fs_heap[rp++]; 
	cur = &fs_heap[rp]; cur->pre = 0; cur->next = 0; cur->m = 0;
	head->next = cur;
	cur->m = &map_heap[rp++]; cur->m->cnt = 0;
}
void putChar(char a)
{
	buff[bcnt++] = a;
}
void ins_fs(fs* a, fs* b, fs* c)
{
	if (a){ a->next = c; }
	if (c){ c->pre = a; c->next = b; }
	if (b){ b->pre = c; }
}
void del_fs(fs* a)
{
	fs* p = 0;
	fs* n = 0;
	if (cur) p = a->pre;
	if (cur) n = a->next;
	if (p) p->next = n;
	if (n) n->pre = p;
}
void merge(char* s, char* t, int len)
{
	int c = 0;
	while (c < len)
	{
		s[c] = t[c];
		c++;
	}
}
void add_buff()
{
	int t = cur->m->cnt - gX;
	char ct[20000];
	for (int i = 0; i < t; i++)
		ct[i] = cur->m->d[i + gX];
	merge(&cur->m->d[gX], buff, bcnt);
	merge(&cur->m->d[gX + bcnt], ct, t);
	gX += bcnt;
	cur->m->cnt += bcnt;
	bcnt = 0;
	if (cur->m->cnt >= 5000)
	{
		int a = 12345;
	}
}
int getTotalChar()
{
	int cnt = 0;
	fs* tmpft = head->next;
	while (tmpft)
	{
		cnt += tmpft->m->cnt;
		tmpft = tmpft->next;
		if (tmpft)cnt++;
	}
	return cnt;
}
void putEnter()
{
	if (bcnt > 0)
		add_buff();

	map* mt = &map_heap[rp]; mt->cnt = 0;
	fs* ft = &fs_heap[rp++]; ft->pre = 0; ft->next = 0;
	ft->m = mt;
	for (int i = 0; i < cur->m->cnt - gX; i++)
	{
		mt->d[i] = cur->m->d[i + gX];
	}
	mt->cnt = cur->m->cnt - gX;
	cur->m->cnt = gX;

	ins_fs(cur, cur->next, ft);
	gX = 0;
	
	cur = cur->next;
}
char* find_end(fs* a)
{
	int c = a->m->cnt;
	return &a->m->d[c];
}
void putBackSpace()
{
	if (bcnt > 0)
	{
		bcnt--;
		return;
	}

	if (gX == 0 && cur->pre ==0)
		return;
	if (gX > 0)
	{
		int cnt = cur->m->cnt - gX;
		for (int i = 0; i < cnt; i++)
			cur->m->d[gX - 1 + i] = cur->m->d[gX + i];
		cur->m->cnt--;
		gX--;
	}
	else
	{
		char* s = find_end(cur->pre);
		merge(s, cur->m->d, cur->m->cnt);
		gX = cur->pre->m->cnt;
		cur->pre->m->cnt += cur->m->cnt;
		cur = cur->pre;
		del_fs(cur->next);
	}
}
void moveUp(int n)
{
	if (bcnt > 0)
		add_buff();

	while (cur->pre) {
		cur = cur->pre;
		if (--n == 0)break;
	}
		
	int t = cur->m->cnt; 
	if (t < gX) gX = t;
}
void moveDown(int n)
{
	if (bcnt > 0)
		add_buff();

	while (cur->next) {
		cur = cur->next;
		if (--n == 0)break;
	}

	int t = cur->m->cnt;
	if (t < gX) gX = t;
}
void moveLeft(int n)
{
	if (bcnt > 0)
		add_buff();
	gX -= n;
	if (gX < 0)gX = 0;
}
void moveRight(int n)
{
	if (bcnt > 0)
		add_buff();
	gX += n;
	if (gX > cur->m->cnt)
		gX = cur->m->cnt;
}
void close(char* document)
{
	if (bcnt > 0)
		add_buff();
	fs* st = head->next;
	int cnt = 0;
	while (st)
	{
		for (int i = 0; i < st->m->cnt; i++)
			document[cnt++] = st->m->d[i];
		st = st->next;
		if (st) document[cnt++] = '\n';
	}
	cnt = cnt;
}