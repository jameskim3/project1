
unsigned char mymap[4096][4096];
void makedic(){

}
int dfs(int n){
	return 0;
}
void test(unsigned char newmap[4096][4096]){
	for (int i = 0; i < 4096; i++){
		for (int j = 0; j < 4096; j++){
			mymap[i][j] = newmap[i][j];
		}
	}
	makedic();
	dfs(0);
}
