/*181224
old solution is greedy algorithm
it changes no->1match->2match->3match
now i try to solve it in dfs
*/
const int BLOCK = 32;
const int MX = 2048;
const int MY = 2048;
const int MN = 100;

struct BL{
	int chk[4];
	int left[100];
	int down[100];
	int info[4][64];
};
BL ND[33][33];
void test(char bitmap[][MX]){

}