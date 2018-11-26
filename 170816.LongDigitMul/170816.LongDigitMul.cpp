#include <iostream>
#include <string.h>

using namespace std;
char s1[110], s2[110];

int solve();

int main()
{
	while (1)
	{
		int sign = 0;
		scanf("%s", s1);
		if (s1[0] == '0')
			break;
		scanf("%s", s2);

		int result[250];
		for (int i = 0; i < 250; i++)
			result[i] = 0;

		int i;
		if (s1[0] == '-')
		{
			sign = 1 - sign;
			for (i = 0; i < strlen(s1) - 1; i++)
				s1[i] = s1[i + 1];
			s1[i] = '\0';
		}
		if (s2[0] == '-')
		{
			sign = 1 - sign;
			for (i = 0; i < strlen(s2) - 1; i++)
				s2[i] = s2[i + 1];
			s2[i] = '\0';
		}

		int len1 = strlen(s1);
		int len2 = strlen(s2);

		for (int i = 0; i < len1; i++)
		{
			for (int j = 0; j < len2; j++)
			{
				int a = s1[len1 - 1 - i] - '0';
				int b = s2[len2 - 1 - j] - '0';
				result[i + j] += a*b;
			}
		}

		for (int i = 0; i < len1 + len2; i++)
		{
			result[i + 1] += result[i] / 10;
			result[i] = result[i] % 10;
		}

		int idx = 0;
		for (int i = len1 + len2; i >= 0; i--)
		{
			if (result[i] != 0)
			{
				idx = i;
				break;
			}
		}

		if (sign == 1 && idx != 0)
			printf("-");

		for (int i = idx; i >= 0; i--)
		{
			printf("%d", result[i]);
		}
		printf("\n");
	}

	return 0;
}