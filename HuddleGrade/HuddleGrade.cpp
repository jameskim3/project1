#include <iostream>

typedef struct {
	char st, ball;
}Result2;
typedef struct {
	int st, ball;
}Result;
const int MC = 10 * 9 * 8 * 7;
Result2 nd[10000][10000];
int dic[10000];

int main(){
	freopen("in.txt", "r", stdin);
	int TC, N;
	scanf("%d", &TC);
	for (int i = 0; i < TC; i++){
		scanf("%d", &N);
		int diffUp, diffDown, tmp, tmp_old;
		diffUp = diffDown = 0;
		tmp_old = tmp = 0;
		for (int j = 0; j < N; j++){
			scanf("%d", &tmp);
			if (j > 0){
				if (tmp_old < tmp){
					if (diffUp < tmp - tmp_old){
						diffUp = tmp - tmp_old;
					}
				}
				if (tmp_old > tmp){
					if (diffDown < tmp_old - tmp){
						diffDown = tmp_old - tmp;
					}
				}
			}
			tmp_old = tmp;
		}
		printf("#%d %d %d\n", i + 1, diffUp, diffDown);
	}
}