#include <string.h>
const int user_div = 2;
int changeInt2(char c)
{
	int n;
	if (c <= '9') n = c - '0';
	else n = c - 'A' + 10;

	return n;
}
char changeChar2(int n)
{
	char c;
	if (n <= 9) c = n + '0';
	else c = n + 'A' - 10;

	return c;
}
typedef unsigned long long ull;
void mat(char ret[600], char src[256], char tar[256])
{
	int cnt = 0;
	ull max_mul = 1;
	while (cnt++ < user_div)max_mul *= 36;
	int len1 = strlen(src);
	int len2 = strlen(tar);

	ull S[256] = { 0 };
	ull T[256] = { 0 };
	ull R[600] = { 0 };
	int mul = 1;
	int nlen1, nlen2;
	for (int i = len1 - 1; i >= 0; i--)
	{
		int p = (len1 - 1 - i) / user_div;
		int q = (len1 - 1 - i) % user_div;
		mul = q == 0 ? 1 : mul * 36;

		S[p] += changeInt2(src[i]) * mul;
		nlen1 = p;
	}
	for (int i = len2 - 1; i >= 0; i--)
	{
		int p = (len2 - 1 - i) / user_div;
		int q = (len2 - 1 - i) % user_div;
		mul = q == 0 ? 1 : mul * 36;

		T[p] += changeInt2(tar[i]) * mul;
		nlen2 = p;
	}
	nlen1++, nlen2++;

	for (int i = 0; i < nlen1; i++)
	{
		for (int j = 0; j < nlen2; j++)
		{
			ull tmp = R[i + j] + S[i] * T[j];
			if (tmp < R[i + j])
			{
				ull t = R[i + j] / max_mul;
				R[i + j + 1] += t;
				R[i + j] -= t*max_mul;
			}
			R[i + j] += S[i] * T[j];
		}
	}
		
	int last_ret = 0;
	int ret_rev[600] = { 0 };
	for (int i = 0; i < nlen1 + nlen2; i++)
	{
		int r = 0;
		while (R[i] > 0)
		{
			ret_rev[i*user_div + r] += R[i] % 36;
			last_ret = i*user_div + r;
			R[i] /= 36, r++;
		}
	}

	for (int i = 0; i <= last_ret; i++)
	{
		if (ret_rev[i]/36 > 0)
			ret_rev[i + 1] += (ret_rev[i] / 36);
		ret_rev[i] %= 36;
	}

	if (ret_rev[last_ret + 1] != 0)last_ret++;
	for (int i = last_ret; i >= 0; i--)
	{
		int p1 = last_ret - i;
		ret[p1] = changeChar2(ret_rev[i]);
	}
}