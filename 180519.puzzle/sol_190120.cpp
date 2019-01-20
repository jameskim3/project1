typedef struct pz{
	unsigned char map[4][2][256];
	int rcandi[256];
	int dcnadi[256];
	int rcnt;
	int dcnt;
}PZ;
PZ ND[256];
int tmp_path[256];
int ans_path[256];
void makeDic(unsigned char newmap[4096][4096]){

}
int dfs(int n){

}
void swap_pz(int src, int tar){

}
void test(unsigned char newmap[4096][4096]){
	makeDic(newmap);

	for (int i = 0; i < 256; i++){
		if (dfs(i))break;
	}
	int ori_path[256];
	for (int i = 0; i < 256; i++){
		ori_path[i] = i;
	}
	for (int i = 0; i < 256; i++){
		int tar;
		for (int tar = i; tar < 256; tar++){
			if (ori_path[tar] == ans_path[i])break;
		}
		swap_pz(ori_path[tar], ans_path[i]);
		ori_path[tar] = ori_path[i];
	}
}