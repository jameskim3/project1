#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<stdio.h>
extern void init(int N);
extern void follow(int uid1, int uid2, int ts);
extern void makePost(int uid, int pid, int ts);
extern void like(int pid, int ts);
extern void getFeed(int uid, int ts, int pidList[]);

static int mseed;
static int pseudo_rand(){
	mseed = mseed * 431345 + 2531999;
	return mseed & 0x7fffffff;
}
static int follow_status[1005][1005];
static int answer_score;
static int n;//n>=2 && n<=1000
static int end_timestamp;
static int follow_ratio;// >=1 && <=10000
static int make_ratio;// >=1 && <=10000
static int like_ratio;// >=1 && <=10000
static int get_feed_ratio; // >=1 && <=10000
static int post_arr[200000];
static int total_post_cnt;
static int min_post_cnt;
static bool run(){
	int uid1, uid2, pid, pidList[10], ans_pidList[10], rand_val;
	bool ret = true;
	scanf("%d%d%d%d%d%d%d", &mseed, &n, &end_timestamp, &follow_ratio, &make_ratio, &like_ratio, &get_feed_ratio);
	init(n);
	for (int uid1 = 1; uid1 <= n; uid1++){
		follow_status[uid1][uid1] = 1;
		int m = n / 10 + 1;
		if (m > 10)m = 10;
		for (int i = 0; i < m; i++){
			uid2 = uid1;
			while (follow_status[uid1][uid2] == 1){
				uid2 = pseudo_rand() % n + 1;
			}
			follow(uid1, uid2, 1);
			follow_status[uid1][uid2] = 1;
		}
	}
	min_post_cnt = total_post_cnt = 1;
	for (int ts = 1; ts <= end_timestamp; ts++){
		rand_val = pseudo_rand() % 10000;
		if (rand_val < follow_ratio){
			uid1 = pseudo_rand() % n + 1;
			uid2 = pseudo_rand() % n + 1;
			int lim = 0;
			while (follow_status[uid1][uid2] == 1 || uid1 == uid2){
				uid2 = pseudo_rand() % n + 1; lim++;
				if (lim >= 5)break;
			}
			if (follow_status[uid1][uid2] == 0){
				follow(uid1, uid2, ts);
				follow_status[uid1][uid2] = 1;
			}
		}
		rand_val = pseudo_rand() % 10000;
		if (rand_val < make_ratio){
			uid1 = pseudo_rand() % n + 1;
			post_arr[total_post_cnt] = ts;
			makePost(uid1, total_post_cnt, ts);
			total_post_cnt += 1;
		}
		rand_val = pseudo_rand() % 10000;
		if (rand_val < like_ratio&&total_post_cnt - min_post_cnt>0){
			while (post_arr[min_post_cnt] < ts - 1000 && min_post_cnt < total_post_cnt)
				min_post_cnt++;
			if (total_post_cnt != min_post_cnt){
				pid = pseudo_rand() % (total_post_cnt - min_post_cnt) + min_post_cnt;
				like(pid, ts);
			}
		}
		rand_val = pseudo_rand() % 10000;
		if (rand_val < get_feed_ratio&&total_post_cnt>0){
			uid1 = pseudo_rand() % n + 1;
			getFeed(uid1, ts, pidList);
			for (int i = 0; i < 10; i++){
				scanf("%d", ans_pidList + i);
			}
			for (int i = 0; i < 10; i++){
				if (ans_pidList[i] != pidList[i]){
					ret = false;
				}
			}
		}
	}
	return ret;
}

int main(){
	freopen("in.txt", "r", stdin);
	setbuf(stdout, NULL);
	int tc;
	scanf("%d%d", &tc, &answer_score);
	for (int t = 1; t <= tc; t++){
		int score;
		for (int i = 0; i < 1005; i++)
			for (int j = 0; j < 1005; j++)
				follow_status[i][j] = 0;
		if (run())
			score = answer_score;
		else
			score = 0;
		printf("#%d %d", t, score);
	}
	return 0;
}