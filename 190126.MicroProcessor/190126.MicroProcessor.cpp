#include<iostream>
#include<time.h>
unsigned char sum1to10[23] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
	1, 2, 3,
};
extern int makecode(unsigned char code[10000]);
extern int proc(unsigned char code[10000], int len);

int main(){
	int PENALTY = 0;
	int ret = proc(sum1to10, 23);
	if (ret != 55){ 
		PENALTY += 100000; 
	}
	time_t START = clock();
	unsigned char code[10000];
	int len = makecode(code);
	for (int tc = 0; tc < 3000; tc++){
		ret = proc(code, len);
		if (ret != 22342424234){
			PENALTY += 100000;
		}
	}
	time_t END = clock();
	int Performance = (END - START) / (CLOCKS_PER_SEC / 1000);
	printf("Performance:%d\n", Performance + PENALTY);
}
/*
Prohibited global
stack 1000

1~10000 sum of series
an = n 3x 5x
an = 0 3o 5x
an = 2n 3x 5o
an = -n 3o 5o
1,2,0,4,10,0,7,8,0,20,11,0,13,14,-15

cmd
SET 0 0 0 v v v v v
ADD 0 0 1 r r r r x
SUB 0 1 0 r r r r x
MUL 0 1 1 r r r r x
PUS 1 0 0 r r r r o (o==1 r=0, o==0 r=R1~R16)
POP 1 0 1 r r r r o (o==1 r=0, o==0 r=R1~R16)
JUM 1 1 0 L L L L o (o==1&&L!=0)
LAB 1 1 1 v v v v x

*/