#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<time.h>
#define N 4
#define MAX_QUERYCOUNT 1000000
static int digits[N];
static int digits_c[10];

static int T;
extern void doUserImplementation(int guess[]);

static int querycount;

static const int limit_query = 2520;
typedef struct {
	int st, ball;
}Result;

static bool isValid(int guess[])
{
	int guess_c[10];
	for (int count = 0; count < 10; ++count)
		guess_c[count] = 0;
	for (int idx = 0; idx < N; ++idx)
	{
		if (guess[idx] < 0 || guess[idx] >= 10 ||
			guess_c[guess[idx]]>0)return false;
		guess_c[guess[idx]]++;
	}
	return true;
}

Result query(int guess[])
{
	Result result;
	if (querycount >= MAX_QUERYCOUNT){
		result.st = -1;
		result.ball = -1;
		return result;
	}
	querycount++;
	if (!isValid(guess)){
		result.st = -1;
		result.ball = -1;
		return result;
	}
	result.st = 0;
	result.ball = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.st++;
		else if (digits_c[guess[idx]]>0)
			result.ball++;
	return result;
}
//static void initialize(){
//	for (int count = 0; count < 10; ++count)
//		digits_c[count] = 0;
//	for (int idx = 0; idx < N; ++idx){
//		char c;
//		do scanf("%c", &c); while (c<'0' || c>'9');
//		digits[idx] = c - '0';
//		digits_c[digits[idx]]++;
//	}
//	querycount = 0;
//}
static void initialize(){
	for (int count = 0; count < 10; ++count)
		digits_c[count] = 0;
	for (int idx = 0; idx < N; ){
		int c = rand() % 10;
		if (digits_c[c] > 0)continue;
		digits[idx] = c;
		digits_c[c]++;
		++idx;
	}
	querycount = 0;
}
static bool check(int guess[]){
	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] != digits[idx])return false;
	return true;
}
int main() {
	time_t s = clock();
	int total_score = 0;
	int total_querycount = 0;
	freopen("in.txt", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (int testcase = 1; testcase <= T; ++testcase){
		initialize();
		int guess[N];
		doUserImplementation(guess);
		if (!check(guess))querycount = MAX_QUERYCOUNT;
		if (querycount <= limit_query)
			total_score++;
		printf("#%d %d\n", testcase, querycount);
		total_querycount += querycount;
	}
	if (total_querycount > MAX_QUERYCOUNT)
		total_querycount = MAX_QUERYCOUNT;
	time_t e = clock();
	int PERFORM = e - s;
	printf("Performance:%d total score=%d totla query=%d\n", PERFORM, total_score * 100 / T, total_querycount);
	return 0;
}