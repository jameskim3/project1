#include <iostream>

int main()
{
	int TC, D, A, B, F;
	scanf("%d",&TC);
	for (int tc = 0; tc < TC; tc++)
	{
		scanf("%d %d %d %d", &D, &A, &B, &F);
		double t = D / double(A + B);
		double ret = double(F)*t;
		printf("#%d %f\n",tc+1, ret);
	}
}