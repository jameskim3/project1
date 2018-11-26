#define MAX_N 1000
#ifndef _CRT_SECURE_NO_NO_WARNINGS
#define _CRT_SECURE_NO_NO_WARNINGS
#endif
#include<iostream>
#define MAXLength (10000)
#define MAxServer (10)
extern void init(int L, int N, int C, int axis[MAxServer]);
extern int remove_user(int uid);
extern int add_user(int uid, int axis);
extern int get_users(int sid);
static void init_(int L, int N, int C);
static bool run(int l, int n, int c, int r){
	init_(l, n, c);
	bool accepted = true;
	int op, sid, uid, axis, ans, ret;
	while (r--){
		scanf("%d", &op);
		switch (op){
		case 0:
			scanf("%d %d %d", &uid, &axis, &ans);
			ret = add_user(uid, axis);
			if (ret != ans)accepted = false;
			break;
		case 1:
			scanf("%d %d", &uid, &ans);
			ret = remove_user(uid);
			if (ret != ans)accepted = false;
			break;
		case 2:
			scanf("%d %d", &sid, &ans);
			ret = get_users(sid);
			if (ret != ans)accepted = false;
			break;
		default:break;
		}
	}
	scanf("%d %d", &sid, &ans);
	ret = get_users(sid);
	if (ret != ans)accepted = false;
	return accepted;
}
static void init_(int L, int N, int C){
	int axis[10];
	for (int i = 0; i < N; i++)
		scanf("%d", &axis[i]);
	init(L, N, C, axis);
}
int main(){
	int test, T;
	setbuf(stdout, NULL);
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	for (test = 0; test < T; test++){
		int L, N, C, R, tp;
		scanf("%d %d %d %d ", &L, &N, &C, &R);
		bool ret = run(L, N, C, R);
		printf("#%d %d\n", test, ret == true ? 100 : 0);
	}
	return 0;
}