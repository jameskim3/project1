#include <iostream>

int getdate(int m,int d)
{
	int mon_info[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day_start = 4;
	int sm = 1;
	int sd = 1;
	int date = day_start;
	while (sm != m || sd != d)
	{
		if (mon_info[sm] == sd)
		{
			sm++;
			sd = 1;
		}
		else
		{
			sd++;
		}
		date++;
	}
	return date % 7;
}

int main()
{
#ifdef _WIN32
	freopen("in.txt", "r", stdin);
#endif
	int T, m,d;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d %d", &m, &d);
		printf("#%d %d\n", i + 1, getdate(m,d));
	}
}