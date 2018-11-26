#include <iostream>

using namespace std;

typedef struct st
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} CAR;

const int TS = 10;
const int MC = 10000;// 10000;

void build_car(CAR &car)
{
	car.age = rand() % 21;
	car.passenger = rand() % 11 + 2;
	car.engine = rand() % 4000 + 1000;
	car.price = rand() % 30000 + 10000;
}
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
	srand(3);
	CAR tmpCar;
	int order_no = 0;//�뷫 100ȸ
	int save_order_no = -1;

	for (int tc = 1; tc <= 10; tc++)
	{
		for (int mc = 1; mc <= MC; mc++)
		{
			build_car(tmpCar);
			buy_car(tmpCar);

			if (rand() % 100 == 0)
			{
				sort_age(rand() % 21, rand() % 21);
				sort_pass(rand() % 11 + 2, rand() % 11 + 2);
				sort_eng(rand() % 4000 + 1000, rand() % 4000 + 1000);
				sort_pri(rand() % 30000 + 10000, rand() % 30000 + 10000);
				order_no = sell_car();

				if (rand() % 10 == 0)
					save_order_no = order_no;

				if (rand() % 100 == 0)
				{
					if (save_order_no != -1)
					{
						refund(save_order_no);
						save_order_no = -1;
					}
				}
			}
		}

		printf("TC#%d = %d\n", tc, empty_car());
	}

	return 0;
}

