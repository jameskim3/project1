typedef struct st
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} CAR;
struct MyCar
{
	int id;
	int age;//0~20
	int pas;//2~12
	int eng;//1000~5000
	int pri;//10000~40000
	MyCar* nextage;
	MyCar* nextpas;
	MyCar* nexteng;
	MyCar* nextpri;
};
const int max_item = 10000;
MyCar Nd[max_item];
const int max_age = 20;
const int max_pas = 12;
const int max_eng = 5000;
const int max_pri = 40000;
const int div_age = max_item / max_age;
const int div_pas = max_item / max_pas;
const int div_eng = max_item / max_eng;
const int div_pri = 1;
MyCar* myHashAge[max_age + 1][max_item / max_age];
MyCar* myHashPas[max_pas + 1][max_item / max_pas];
MyCar* myHashEng[max_eng + 1][max_item / max_eng];
MyCar* myHashPri[max_item + 1];
int rp;
void copyCar(MyCar* tar, CAR* src){
	tar->id = rp;
	tar->age = src->age;
	tar->pas = src->passenger;
	tar->eng = src->engine;
	tar->pri = src->price;
	tar->nextage = 0;
	tar->nextpas = 0;
	tar->nexteng = 0;
	tar->nextpri = 0;
}
void push(MyCar*tar, MyCar*src, int opt){
	if (tar == 0)tar = src;
	if (tar->id > src->id){
		switch (opt){
		case 0: src->nextage = pre->nextage; pre->nextage = src; break;
		case 1: tar = tar->nextpas; break;
		case 2: tar = tar->nexteng; break;
		case 3: tar = tar->nextpri; break;
		}
	}
	else{
		MyCar*pre = tar;
		while (tar->id < src->id){
			pre = tar;
			switch (opt){
			case 0: tar = tar->nextage; break;
			case 1: tar = tar->nextpas; break;
			case 2: tar = tar->nexteng; break;
			case 3: tar = tar->nextpri; break;
			}
		}
		switch (opt){
		case 0: src->nextage = pre->nextage; pre->nextage = src; break;
		}
	}
}
void addHash(MyCar* c){
	MyCar*p_age = myHashAge[c->age][c->id%div_age];
	MyCar*p_pas = myHashAge[c->pas][c->id%div_pas];
	MyCar*p_eng = myHashAge[c->eng][c->id%div_eng];
	MyCar*p_pri = myHashAge[c->pri][c->id%div_pri];
	push(p_age, c, 0);
	push(p_pas, c, 1);
	push(p_eng, c, 2);
	push(p_pri, c, 3);
}

void buy_car(CAR car)
{
	MyCar *tmp = &Nd[rp++];
	copyCar(tmp, &car);

	addHash(tmp);
}