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
	MyCar* next[4];
};
typedef enum TYPE{
	AG,
	PA,
	EN,
	PR,
};
const int max_item = 10010;
MyCar Nd[max_item];
struct BK{
	int max[4];
	int part_range[4];
	int min[4];
};
BK bk;
MyCar* myHash[4][max_item + 10];
int rp=0;

void init(){

}
void copyCar(MyCar* tar, CAR* src){
	tar->id = rp;
	tar->order = 0;
	tar->val[AG] = src->age;
	tar->val[PA] = src->passenger;
	tar->val[EN] = src->engine;
	tar->val[PR] = src->price;
	for (int i = 0; i < 4; i++){
		tar->next[i] = 0;
	}
}
int compare(MyCar*a, MyCar*b){
	if (a->val < b->val ||
		(a->val == b->val && a->id < b->id))return 1;
	return -1;
}
void push(int opt, int pos, MyCar*src){
	if (myHash[opt][pos]== 0)myHash[opt][pos] = src;
	else if (compare(myHash[opt][pos],src)==-1){
		src->next[opt] = myHash[opt][pos];
		myHash[opt][pos] = src;
	}
	else{
		MyCar *pre = myHash[opt][pos];
		MyCar *iter = myHash[opt][pos];
		while (iter != 0){
			if (compare(iter, src) == -1)break;
			pre = iter;
			iter = iter->next[opt];
		}
		src->next[opt] = pre->next[opt];
		pre->next[opt] = src;
	}
}
void addHash(MyCar* c){
	int pos[4] = { 0 };
	for (int i = 0; i < 4; i++){
		if (i == 3)
			pos[i] += (c->val[i] - bk.min[i]) * 10000 / 30001;
		else{
			pos[i] += (c->val[i] - bk.min[i]) * bk.part_range[i];
			pos[i] += c->id * bk.part_range[i] / 10000;
		}
	}
	for (int i = 0; i < 4;i++)
		push(i, pos[i], c);
}
void buy_car(CAR car){
	if (rp == 0){
		bk.max[AG] = 20;
		bk.max[PA] = 12;
		bk.max[EN] = 5000;
		bk.max[PR] = 40000;
		bk.min[AG] = 0;
		bk.min[PA] = 2;
		bk.min[EN] = 1000;
		bk.min[PR] = 10000;

		for (int i = 0; i < 4; i++){
			bk.part_range[i] = 10000 / (bk.max[i] - bk.min[i] + 1);
		}
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 10000; j++){
				myHash[i][j] = 0;
			}
		}
	}
	MyCar *tmp = &Nd[rp];
	copyCar(tmp, &car);
	rp++;
	addHash(tmp);
}
int cnt_candi;
int list_candi[10001];
void chk_sort(int opt, int pos1, int pos2){
	for (int i = pos1; i < pos2; i++){
		MyCar* h = myHash[opt][i];
		while (h != 0){
			if(Nd[h->id].order==0)
				list_candi[h->id]++;
			h = h->next[opt];
		}
	}
}
void sort_age(int from, int to){
	for (int i = 0; i <= 10000; i++)
		list_candi[i] = 0;
	int opt = 0;
	int pos1 = (from - bk.min[opt])* bk.part_range[opt];
	int pos2 = (to + 1 - bk.min[opt])*bk.part_range[opt];
	chk_sort(opt, pos1, pos2);
}
void sort_pass(int from, int to){
	int opt = 1;
	int pos1 = (from - bk.min[opt])* bk.part_range[opt];
	int pos2 = (to + 1 - bk.min[opt])*bk.part_range[opt];
	chk_sort(opt, pos1, pos2);
}
void sort_eng(int from, int to){
	int opt = 2;
	int pos1 = (from - bk.min[opt])* bk.part_range[opt];
	int pos2 = (to + 1 - bk.min[opt])*bk.part_range[opt];
	chk_sort(opt, pos1, pos2);
}
int sel_cnt = 1;
int order_cnt[2000];
int order_map[2000][4000];
void sort_pri(int from, int to){
	int opt = 3;
	int pos1 = (from - bk.min[opt]) * 10000 / 30001;
	int pos2 = (to - bk.min[opt]) * 10000 / 30001;
	chk_sort(opt, pos1, pos2);
}
int sell_car(){
	int cnt = 0;
	for (int i = 0; i <= 10000; i++){
		if (list_candi[i] == 4){
			order_map[sel_cnt][cnt++] = i;
			Nd[i].order = sel_cnt;
		}
	}
	if (cnt >= 2000 || sel_cnt>=2000)
		int a234 = 234;
	order_cnt[sel_cnt] = cnt;
	return sel_cnt++;
}
void refund(int order_no){
	for (int i = 0; i < order_cnt[order_no]; i++){
		Nd[order_map[order_no][i]].order = 0;
	}
}
int empty_car(){
	int cnt = 0;
	for (int i = 0; i < rp; i++){
		if (Nd[i].order == 0)
			cnt++;
	}
	rp = 0;
	sel_cnt = 1;
	for (int i = 0; i < 2000; i++){
		order_cnt[i] = 0;
	}
	return cnt;
}