#include <string>

char makeChar(int n);
int changeInt(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A' + 10;

	return n;
}
char changeChar(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A' - 10;

	return c;
}

typedef unsigned long long ULL;
int DIV = 5;
ULL N_Num = 36;
ULL ARR[12];

void cal(char* ret, const char* src, const char* tar, int d)
{
	int a = strlen(src);
	int b = strlen(tar);

	N_Num = d;
	int i, j, k;
	ARR[0] = 1;
	for (i = 1; i < 12; i++)
		ARR[i] = ARR[i - 1] * N_Num;

	ULL mySrc[256] = { 0 };
	ULL myTar[256] = { 0 };
	ULL myRet[512] = { 0 };

	char tmpSrc[256] = { 0 };
	char tmpTar[256] = { 0 };

	for (i = a - 1; i >= 0; i--)
		tmpSrc[i] = src[a - 1 - i];
	for (i = b - 1; i >= 0; i--)
		tmpTar[i] = tar[b - 1 - i];


	for (i = 0; i < a; i++)
		mySrc[i / DIV] += changeInt(tmpSrc[i]) * (ARR[i%DIV]);
	for (i = 0; i < b; i++)
		myTar[i / DIV] += changeInt(tmpTar[i]) * (ARR[i%DIV]);

	for (i = 0; i <= (a / DIV); i++)
		for (j = 0; j <= (b / DIV); j++)
			myRet[i + j] += mySrc[i] * myTar[j];

	int offset;
	int len = 0;
	int buf[600] = { 0 };
	for (i = 0; i <= (a / DIV) + (b / DIV); i++)
	{
		offset = i*DIV;
		ULL div_val = myRet[i];
		while (div_val > 0)
		{
			buf[offset++] += div_val%N_Num;
			div_val /= N_Num;
		}

		len = offset;
	}

	for (i = 0; i < len; ++i)
	{
		buf[i + 1] += buf[i] / N_Num;
		buf[i] = buf[i] % N_Num;
	}
	if (buf[len] > 0) 
		len++;
	for (i = 0; i < len; i++)
	{
		ret[i] = changeChar(buf[len - 1 - i]);
	}

}