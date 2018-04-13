#include <iostream>

using namespace std;
typedef unsigned long long ULL;

ULL convert_ull(char str[11])
{
	ULL a = 0;
	for (int i = 0; i < 10; i++)
	{
		if (str[i] == 0)
			break;
		ULL b = str[i] - 'a'+1;
		ULL c = b << (i * 5);
		a += c;
	}
	return a;
}

void convert_str(char str2[11], ULL a)
{
	for (int i = 0; i < 10; i++)
	{
		int b = a >> (i * 5);
		str2[i] = b & 31;
		if (str2[i] == 0)
			break;
		str2[i] += 'a'-1;
	}
}

int main()
{
	//make string
	for (int tc = 0; tc < 100; tc++)
	{
		char str[11] = { 0, };

		str[0] = rand() % 26 + 'a';
		for (int i = 1; i < 10; i++)
		{
			if (rand() % 10 == 0)
				break;
			str[i] = rand() % 26 + 'a';
		}

		//change to ULL
		ULL a = convert_ull(str);

		//convert to string
		char str2[11] = { 0, };
		convert_str(str2, a);
		printf("%s %s\n", str, str2);
	}


	//string comparez
	return 0;
}