//Performance = 4104, Final=137129
typedef struct
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} CAR;
struct MyCar
{
	int id;
	int order;
	int val[4];
};
typedef enum TYPE{
	AG,
	PA,
	EN,
	PR,
};
const int max_item = 10010;
MyCar Nd[max_item];
int rp = 0;

void init(){
}
void copyCar(MyCar* tar, CAR* src){
	tar->id = rp;
	tar->order = 0;
	tar->val[AG] = src->age;
	tar->val[PA] = src->passenger;
	tar->val[EN] = src->engine;
	tar->val[PR] = src->price;
}
void buy_car(CAR car){
	MyCar *tmp = &Nd[rp];
	copyCar(tmp, &car);
	rp++;
}
int cnt_candi;
int list_candi[10001];
void chk_sort(int opt, int pos1, int pos2){
	for (int i = 0; i < rp; i++){
		if (Nd[i].order==0 && Nd[i].val[opt] >= pos1 && Nd[i].val[opt] <= pos2)
			list_candi[i]++;
	}
}
void sort_age(int from, int to){
	for (int i = 0; i <= 10000; i++)
		list_candi[i] = 0;
	int opt = 0;
	chk_sort(opt, from, to);
}
void sort_pass(int from, int to){
	int opt = 1;
	chk_sort(opt, from, to);
}
void sort_eng(int from, int to){
	int opt = 2;
	chk_sort(opt, from, to);
}
int sel_cnt = 1;
int order_cnt[2000];
int order_map[2000][4000];
void sort_pri(int from, int to){
	int opt = 3;
	chk_sort(opt, from, to);
}
int sell_car(){
	int cnt = 0;
	for (int i = 0; i < 10000; i++){
		if (list_candi[i] == 4){
			order_map[sel_cnt][cnt++] = i;
			Nd[i].order = sel_cnt;
		}
	}
	order_cnt[sel_cnt++] = cnt;
	return sel_cnt-1;
}
void refund(int order_no){
	for (int i = 0; i < order_cnt[order_no]; i++){
		Nd[order_map[order_no][i]].order = 0;
	}
}
int empty_car(){
	int cnt = 0;
	for (int i = 0; i < rp; i++){
		if (Nd[i].order == 0)cnt++;
	}
	rp = 0;
	sel_cnt = 1;
	for (int i = 0; i < 2000; i++){
		order_cnt[i] = 0;
	}
	return cnt;
}