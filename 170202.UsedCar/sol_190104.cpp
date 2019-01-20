//Performance = 2902, Final=137129
struct CAR
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
}; struct MyCAR
{
	int order_no;
	int id;
	int val[4];
	MyCAR* next[4];
};
MyCAR nd[10000 + 10];
int rp;
MyCAR* ht[4][10000 + 10];
int min[4], max[4], range[4], part[4];
int order_hist[2000][10000];
int order_cnt[2000];
int order_rp = 0;

void pushLink(MyCAR* p, int pos, int opt){
	if (ht[opt][pos] == 0){
		ht[opt][pos] = p;
	}
	else if (ht[opt][pos]->id >= p->id){
		p->next[opt]= ht[opt][pos];
		ht[opt][pos] = p;
	}
	else{
		MyCAR* pre = ht[opt][pos];
		while (ht[opt][pos]!=0 && ht[opt][pos]->id < p->id){
			pre = ht[opt][pos];
			ht[opt][pos] = ht[opt][pos]->next[opt];
		}
		p->next[opt] = pre->next[opt];
		pre->next[opt] = p;
	}
}
void addHash(MyCAR* p){
	if (max[0] == 0){
		min[0] = 0, min[1] = 2, min[2] = 1000, min[3] = 10000;
		max[0] = 20, max[1] = 12, max[2] = 5000, max[3] = 40000;
		for (int i = 0; i < 4; i++){
			range[i] = (max[i] + 1 - min[i]);
			part[i] = 10000 / range[i];
		}
	}
	for (int i = 0; i < 4; i++){
		int pos = 0;
		pos = p->val[i];
		if (i == 3) pos = (pos-min[3]) / 3;
		if (pos < 0 || pos >= 10010)
			int a234 = 234;
		//pushLink(p, pos, i);
		p->next[i] = ht[i][pos];
		ht[i][pos] = p;
	}
}
void init(){
	rp=0;
	for (int i = 0; i < 2000; i++){
		order_cnt[i] = 0;
	}
	for (int i = 0; i < 10000; i++){
		for (int j = 0; j < 4; j++){
			nd[i].next[j] = 0;
			nd[i].val[j] = 0;
			ht[j][i] = 0;
		}
	}
	order_rp = 0;
}
void buy_car(CAR car){
	MyCAR* tmp = &nd[rp];
	tmp->val[0] = car.age;
	tmp->val[1] = car.passenger;
	tmp->val[2] = car.engine;
	tmp->val[3] = car.price;
	tmp->id = rp;
	tmp->order_no = -1;
	
	addHash(tmp);
	rp++;
}
int tmp_order[10010];
void join_chk(int from, int to, int opt){
	int idx = opt;
	for (int i = from; i <= to; i++){
		if (opt < 3){
			MyCAR* tmp = ht[idx][i];
			while (tmp != 0){
				if (tmp->order_no == -1)					
					tmp_order[tmp->id]++;
				tmp = tmp->next[idx];
			}
		}
		else{
			int pos = (i - min[3]) / 3;
			MyCAR* tmp = ht[idx][pos];
			while (tmp != 0){
				if (tmp->val[3] == i && tmp->order_no == -1)
					tmp_order[tmp->id]++;
				tmp = tmp->next[idx];
			}
		}
	}
}
int sell_condi[4][2];
void sort_age(int from, int to){
	for (int i = 0; i < 10000; i++){
		tmp_order[i] = 0;
	}
	join_chk(from, to, 0);
	sell_condi[0][0] = from, sell_condi[0][1] = to;
}
void sort_pass(int from, int to){
	join_chk(from, to, 1);
	sell_condi[1][0] = from, sell_condi[1][1] = to;
}
void sort_eng(int from, int to){
	join_chk(from, to, 2);
	sell_condi[2][0] = from, sell_condi[2][1] = to;
}
void sort_pri(int from, int to){
	join_chk(from, to, 3);
	sell_condi[3][0] = from, sell_condi[3][1] = to;
}
int sell_car(){
	order_rp++;
	int cnt = 0;
	for (int i = 0; i < 10000; i++){
		if (tmp_order[i] == 4){
			order_hist[order_rp][cnt++] = i;
			nd[i].order_no = order_rp;
		}
	}
	order_cnt[order_rp] = cnt;
	return order_rp;
}
void refund(int order_no){
	int tmp_rp = order_no;
	int tmp_cnt = order_cnt[tmp_rp];
	for (int i = 0; i < tmp_cnt; i++){
		int t = order_hist[tmp_rp][i];
		nd[t].order_no = -1;
	}
}
int empty_car(){
	int sum = 0;
	for (int i = 0; i < rp; i++){
		if (nd[i].order_no == -1)
			sum++;
	}
	return sum;
}
