#include <string>
#define MAX_N 1000

typedef struct express {
	char a[1024];
	char b[1024];
	int oper;
}EXP;
EXP myHeap[500];
EXP* myStack[500];
int rp = 0; 
int stk_rp = 0;

void sub(char* r, const char* a, const char* b);
int my_strlen(const char* a)
{
	int cnt = 0;
	while (*(a++) != 0) cnt++;
	return cnt;
}
int numcmp(const char *a, const char* b)
{
	if (a[0] != '-' && b[0] != '-')
	{
		int c = my_strlen(a);
		int d = my_strlen(b);
		if (c > d)
			return 1;
		if (c < d)
			return -1;
		do{
			if (*b < *a)
				return 1;
			if (*a < *b++)
				return -1;
		} while (*++a != 0);
	}
	else if (a[0] == '-' && b[0] == '-')
		return numcmp(&b[1], &a[1]);
	else if (a[0] == '-')
		return -1;
	else return 1;
	return 0;
}
void add(char r[1024], const char a[1024], const char b[1024])
{
	int len = 0;
	if (a[0] != '-' && b[0] != '-')
	{
		if (0 <= numcmp(a, b))
		{
			int tmp[MAX_N];
			int pos_a = my_strlen(a);
			int pos_b = my_strlen(b);
			int carry = 0;
			len = 0;
			while (0 < pos_a)
			{
				int num1 = a[--pos_a] - '0';
				int num2 = (0 < pos_b) ? b[--pos_b] - '0' : 0;
				int num3 = carry + num1 + num2;
				tmp[len++] = num3 % 10;
				carry = num3 / 10;
			}
			if (0 < carry)
				tmp[len++] = 1;
			for (int i = 0; i < len; i++)
				r[i] = tmp[len - 1 - i] +'0';
			r[len] = 0;
		}
		else
			add(r, b, a);
	}
	else if (a[0] == '-' && b[0] == '-')
	{
		add(&r[1], &a[1], &b[1]);
		r[0] = '-';
	}
	else if (a[0] == '-')
		sub(r, b, &a[1]);
	else
		sub(r, a, &b[1]);
}
void sub(char* r, const char* a, const char* b)
{
	if (a[0] != '-' && b[0] != '-')
	{
		if (0 <= numcmp(a, b))
		{
			int tmp[MAX_N];
			int pos_a = my_strlen(a);
			int pos_b = my_strlen(b);
			int carry = 0;
			int len = 0;
			while (0 < pos_a)
			{
				int num1 = a[--pos_a] - '0';
				int num2 = 0 < pos_b ? b[--pos_b] - '0' : 0;
				int num3 = 10 - carry + num1 - num2;
				tmp[len++] = num3 % 10;
				carry = 1 - (num3 / 10);
			}
			while (1 < len && tmp[len - 1] == 0)--len;
			for (int i = 0; i < len; i++)
				r[i] = tmp[len - 1 - i] + '0';
			r[len] = 0;
		}
		else
		{
			sub(&r[1], b, a);
			r[0] = '-';
		}
	}
	else if (a[0] == '-' && b[0] == '-')
		sub(r, &b[1], &a[1]);
	else if (a[0] == '-')
	{
		add(&r[1], &a[1], b);
		r[0] = '-';
	}
	else{
		add(r, a, &b[1]);
	}
}
void mul(char* r, const char * a, const char* b)
{
	if (numcmp(a, "0") == 0 || numcmp(b, "0") == 0)
		strcpy(r, "0");
	else if (a[0] != '-' && b[0] != '-')
	{
		char cpy_a[MAX_N + 1];
		strcpy(cpy_a, a);
		strcpy(r, "0");
		for (int i = my_strlen(b) - 1; i >= 0; i--)
		{
			for (int j = 0; j < b[i] - '0'; j++)
				add(r, r, cpy_a);
			strcat(cpy_a, "0");
		}
	}
	else if (a[0] == '-' && b[0] == '-')
		mul(r, &a[1], &b[1]);
	else if (a[0] == '-')
	{
		mul(&r[1], &a[1], b);
		r[0] = '-';
	}
	else
	{
		mul(&r[1], a, &b[1]);
		r[0] = '-';
	}
}
void div(char* r, const char* a, const char * b)
{
	if (numcmp(a, "0") == 0 || numcmp(b, "0") == 0)
		strcpy(r, "0");
	else if (numcmp(((a[0] != '-') ? a : &a[1]), ((b[0] != '-') ? b : &b[1])) == -1)
		strcpy(r, "0");
	else if (a[0] != '-' && b[0] != '-')
	{
		char cpy_a[MAX_N + 1];
		char cpy_b[MAX_N + 1];
		char itr[MAX_N + 1];
		strcpy(cpy_a, a);
		strcpy(r, "");
		int c = (my_strlen(a) > my_strlen(b)) ? my_strlen(a) - my_strlen(b) : 1;
		for (int i = 0; i < c; i++)
		{
			strcpy(cpy_b, b);
			for (int j = 0; j < c - i - 1; j++)
				strcat(cpy_b, "0");
			strcpy(itr, "0");
			while (0 <= numcmp(cpy_a, "0"))
			{
				add(itr, itr, "1");
				sub(cpy_a, cpy_a, cpy_b);
			}
			sub(itr, itr, "1");
			add(cpy_a, cpy_a, cpy_b);
			strcat(r, itr);
		}
	}
	else if (a[0] == '-' && b[0] == '-')
		div(r, &a[1], &b[1]);
	else
	{
		if (a[0] == '-')
			div(&r[1], &a[1], b);
		else
			div(&r[1], a, &b[1]);
		r[0] = '-';
	}
}
int isOper(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	return 0;
}
int isDigit(char c)
{
	if (c >= '0' && c <= '9')return 1;
	return 0;
}
int getVal(char* a, char* ret)
{
	int lmax = my_strlen(a);
	int cnt = 0;
	int digitOccur = 0;
	while (!digitOccur || !isOper(a[cnt]))
	{
		if (cnt >= lmax)break;
		if (isDigit(a[cnt])) digitOccur = 1;
		ret[cnt] = a[cnt++];
	}
	ret[cnt] = 0;
	return cnt;
}
int getOper(char* a,int* ret)
{
	if (a[0] == '+')*ret = 0;
	else if (a[0] == '-')*ret = 1;
	else if (a[0] == '*')*ret = 2;
	else *ret = 3;
	return 1;
}
void setExp(char* up, char* down, int oper, EXP* ret)
{
	strcpy(ret->a, up);
	strcpy(ret->b, down);
	ret->oper = oper;
}
void run(char *ret, char *query)
{
	rp = stk_rp = 0;
	int ori = my_strlen(query);
	char valStr[1024], retStr[1024];
	int oper;
	int len = getVal(query, valStr);
	EXP* ptr = &myHeap[rp++];
	setExp(valStr, "1", 0, ptr);
	myStack[stk_rp++] = ptr;

	EXP* ptr2;
	while (len<ori)
	{
		len += getOper(&query[len], &oper);
		len += getVal(&query[len], valStr);
		switch (oper)
		{
		case 0:// +
		case 1:// -
			ptr = &myHeap[rp++];
			setExp(valStr, "1", oper, ptr);
			myStack[stk_rp++] = ptr;
			break;
		case 2:// *
			ptr2 = myStack[--stk_rp];
			mul(retStr, ptr2->a, valStr);
			ptr = &myHeap[rp++];
			setExp(retStr, ptr2->b, ptr2->oper, ptr);
			myStack[stk_rp++] = ptr;
			break;
		case 3:// div
			ptr2 = myStack[--stk_rp];
			mul(retStr, ptr2->b, valStr);
			ptr = &myHeap[rp++];
			setExp(ptr2->a, retStr, ptr2->oper, ptr);
			myStack[stk_rp++] = ptr;
			break;
		}
	}

	char up1[1024], up2[1024], up[1024];
	char down[1024];
	int cnt = 0;
	ptr = myStack[cnt++];
	strcpy(up, ptr->a);
	strcpy(down, ptr->b);
	while (cnt<stk_rp)
	{
		ptr2 = myStack[cnt++];
		mul(down, ptr->b, ptr2->b);
		mul(up1, ptr->a, ptr2->b);
		mul(up2, ptr->b, ptr2->a);
		if (ptr2->oper == 0)
			add(up, up1, up2);
		else
			sub(up, up1, up2);
		setExp(up, down, ptr->oper, ptr);
	}
	char r[1024],remain[1024],vali[1024];
	div(r, up, down);
	mul(vali, r, down);
	if (r[0]!='-')
		sub(remain, up, vali);
	else
		sub(remain, vali, up);

	len = my_strlen(r);
	for (int i = 0; i < len; i++)
		ret[i] = r[i];
	if (strcmp(remain, "0") == 0)
	{
		ret[len] = 0;
		return;
	}

	ret[len] = '.';
	cnt = 0;
	int spos = len + 1;
	while (1)
	{
		if (strcmp(remain, "0") == 0)
			break;
		if (cnt >= 20)
			break;
		mul(up, remain, "10");
		div(r, up, down);
		mul(vali, r, down);
		sub(remain, up, vali);
		ret[spos + cnt++] = r[0];
	}
	ret[spos + cnt] = 0;
	return;
}