
#include <string.h>
int changeInt3(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A' + 10;

	return n;
}
char changeChar3(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A' - 10;

	return c;
}

void mat2(char ret[600], char src[256], char tar[256])
{
	int len1, len2;
	len1 = strlen(src);
	len2 = strlen(tar);
	int ret2[600] = { 0 };
	for (int i = len1-1; i >= 0; i--)
	{
		for (int j = len2-1; j >=0; j--)
		{
			int p1 = len1 - 1 - i;
			int p2 = len2 - 1 - j;
			int val = changeInt3(src[i]) * changeInt3(tar[j]);
			ret2[p1 + p2] += val;
		}
	}
	int pos = 0;
	for (int i = 0; i < len1 + len2; i++)
	{
		if (ret2[i] != 0)pos = i;
		ret2[i + 1] += (ret2[i] / 36);
		ret2[i] = ret2[i] % 36;
	}
	for (int i = pos; i >=0; i--)
	{
		int p1 = pos - i;
		ret[p1] = changeChar3(ret2[i]);
	}
}

