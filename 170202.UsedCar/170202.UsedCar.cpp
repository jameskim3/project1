#include <iostream>
#include <time.h>

using namespace std;

struct CAR
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} ;

const int TS = 10;
const int MC = 10000;// 10000;
int seed = 3;
static int peuso_rand()
{
	seed = (214013 * seed + 2531011);
	return (seed >> 16) & 32767;
}
void build_car(CAR &car)
{
	car.age = peuso_rand() % 21;
	car.passenger = peuso_rand() % 11 + 2;
	car.engine = peuso_rand() % 4001 + 1000;
	car.price = peuso_rand() % 30001 + 10000;
}
extern void init();
extern void buy_car(CAR car);
extern void sort_age(int from, int to);
extern void sort_pass(int from, int to);
extern void sort_eng(int from, int to);
extern void sort_pri(int from, int to);
extern int sell_car();
extern void refund(int order_no);
extern int empty_car();

int main()
{
	//srand(3);
	CAR tmpCar;
	int order_no = 0;//�뷫 100ȸ
	int save_order_no = -1;

	time_t start = clock();
	int mod_val = 0;
	for (int tc = 1; tc <= 20; tc++)
	{
		init();
		for (int mc = 1; mc <= MC; mc++)
		{
			build_car(tmpCar);
			buy_car(tmpCar);
			
			//if (peuso_rand() % 100 == 0)
			if (peuso_rand() % 10 == 0)
			{
				sort_age(peuso_rand() % 21, peuso_rand() % 21);
				sort_pass(peuso_rand() % 11 + 2, peuso_rand() % 11 + 2);
				sort_eng(peuso_rand() % 4000 + 1000, peuso_rand() % 4000 + 1000);
				sort_pri(peuso_rand() % 30000 + 10000, peuso_rand() % 30000 + 10000);
				order_no = sell_car();

				if (peuso_rand() % 10 == 0)
					save_order_no = order_no;

				if (peuso_rand() % 100 == 0)
				{
					if (save_order_no != -1)
					{
						refund(save_order_no);
						save_order_no = -1;
					}
				}
			}
		}
		int tmp = empty_car();
		printf("TC#%d = %d\n", tc, tmp);
		mod_val += tmp;
	}
	time_t end = clock();
	int perform = end - start;
	printf("Performance = %d, Final=%d\n", perform, mod_val);
	return 0;
}

