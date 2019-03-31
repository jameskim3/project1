//Score:100 time: 3.638,
typedef unsigned long long ULL;
const int usr_div = 1;

extern int changeInt(char c);
extern char changeChar(int n);

int strlen(char* a){
	int cnt = 0;
	while (a[cnt])cnt++;
	return cnt;
}
void mat(char ret[600], char src[256], char tar[256]){
	ULL s[256] = { 0 };
	ULL t[256] = { 0 };
	ULL r[600] = { 0 };
	int len1 = strlen(src);
	int len2 = strlen(tar);
	int mul = 1;
	int max1, max2;
	for (int i = 0; i <len1; i++){
		int pos = i / usr_div;
		int off = i % usr_div;
		mul = off == 0 ? 1 : mul * 36;
		s[pos] += changeInt(src[len1 - 1 - i])*mul;
		max1 = pos;
	}
	for (int i = 0; i <len2; i++){
		int pos = i / usr_div;
		int off = i%usr_div;
		mul = off == 0 ? 1 : mul * 36;
		t[pos] += changeInt(tar[len2 - 1 - i])*mul;
		max2 = pos;
	}
	ULL max_mul = 1;
	int cnt = 0;
	int max3=0;
	while (cnt < usr_div * 2){
		max_mul *= 36;
		cnt++;
	}
	for (int i = 0; i <= max1; i++){
		for (int j = 0; j <= max2; j++){
			r[i + j] += s[i] * t[j];
			if (max3 < i + j)max3 = i + j;
			while (r[i + j] >= max_mul){
				r[i + j] -= max_mul;
				r[i + j + 2] += 1;
				if (max3 < (i + j +2))max3 = i + j+2;
			}
		}
	}
	for (int i = 0; i <= max3; i++){
		if (r[i] >= max_mul)
			int a3245 = 436;
	}
	int ret_rev[600] = { 0 };
	cnt = 0;
	int max4=0;
	for (int i = 0; i <= max3; i++){
		int pos = i*usr_div;
		int off = 0;
		while (r[i]>0||off==0){
			int p = pos + off;
			if(max4<p)max4 = p;
			ret_rev[p] += r[i] % 36;
			while (ret_rev[p] >= 36){
				ret_rev[p] -= 36;
				ret_rev[p + 1] += 1;
				if (max4<p+1)max4 = p + 1;
				p++;
			}
			r[i] /= 36;
			off++;
		}
	}
	for (int i = 0; i <= max4; i++){
		ret[i] = changeChar(ret_rev[max4 - i]);
	}
}
