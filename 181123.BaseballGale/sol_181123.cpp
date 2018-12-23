typedef struct {
	char st, ball;
}Result2;
typedef struct {
	int st, ball;
}Result;
const int MC = 10 * 9 * 8 * 7;
Result2 nd[10000][10000];
int dic[10000];
extern Result query(int guess[]);
Result2 query2(int src[], int qry[])
{
	Result2 result;
	result.st = 0;
	result.ball = 0;

	for (int idx = 0; idx < 4; ++idx){
		if (src[idx] == qry[idx])
			result.st++;
		else {
			for (int d = 0; d < 4; d++){
				if (d == idx)continue;
				if (src[idx] == qry[d]){
					result.ball++;
					break;
				}
			}
		}
	}
	return result;
}
int rp;
void conv4(int src, int tar[]){
	int div = 1;
	for (int k = 3; k >= 0; k--){
		tar[k] = (src / div) % 10;
		div *= 10;
	}
}
void makeDic(){
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				for (int l = 0; l < 10; l++){
					if (i == j || i == k || i == l ||
						j == k || j == l || k == l)continue;
					dic[rp++] = i * 1000 + j * 100 + k * 10 + l;
				}
			}
		}
	}
	int src[4], qry[4];
	for (int i = 0; i < MC; i++){
		for (int j = 0; j < MC; j++){
			int div = 1;
			conv4(dic[i], src);
			conv4(dic[j], qry);
			nd[dic[i]][dic[j]] = query2(src, qry);
		}
	}
}
const int max_test_qry = 7;
void doUserImplementation(int guess[]){
	if (rp == 0){
		makeDic();
	}
	int val[max_test_qry] = { 123, 4567, 8901, 2345, 6789, 3456, 7890 };
	int q[max_test_qry][4];
	int buf[10000] = { 0 };
	Result test[max_test_qry];
	int parti[100] = { 0 };
	for (int i = 0; i < max_test_qry; i++){
		conv4(val[i], q[i]);
		test[i] = query(q[i]);
		for (int j = 0; j < MC; j++){
			if (nd[val[i]][dic[j]].st == test[i].st
				&& nd[val[i]][dic[j]].ball == test[i].ball){
				buf[j]++;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < MC; i++){
		if (buf[i] == max_test_qry){
			parti[cnt] = i+1;
			cnt++;
		}
	}
	Result ret;
	int ret_digit[4];
	for (int i = 0; i < cnt; i++){
		conv4(dic[parti[i] - 1], ret_digit);
		ret = query(ret_digit);
		if (ret.st == 4)
		{
			for (int j = 0; j < 4; j++)guess[j] = ret_digit[j];
			return;
		}
	}
}