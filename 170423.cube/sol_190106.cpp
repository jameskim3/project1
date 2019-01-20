//Performance = 3468, Final=650
const int LM = 3;
const int TC = 100;
const int MAX_ROTATE = 8;
int MyCube[6][LM][LM];

extern void rotate(int face, int cw);
extern int check_cube(int src[6][LM][LM]);
extern void initial_cute(int cube[6][LM][LM]);

struct ROT{
	int n;
	int f[10];
	int c[10];
	int cube[6][LM][LM];
	ROT* next;
};
ROT ND[3300000];
ROT* HT[1000000];
int rp;
int ans_cnt;
int ans_path[10][2];
int tmp_path[10][2];
ROT* ans_dic;

int hash_f(int cube[6][LM][LM]){
	int h = 5381;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 3; j++){
			for (int k = 0; k < 3; k++){
				h = (h * 33 + cube[i][j][k])%1000000;
			}
		}
	}
	return h;
}
int isSameCube(int a[6][LM][LM], int b[6][LM][LM]){
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				if (a[i][j][k] != b[i][j][k])
					return 0;	
	return 1;
}
void My_copy_cube(int src[6][LM][LM], int tar[6][LM][LM])
{
	for (int face = 0; face < 6; face++)
		for (int i = 0; i < LM; i++)
			for (int j = 0; j < LM; j++)
				tar[face][i][j] = src[face][i][j];
}
void MyRotate(int face, int cw)
{
	int local[6][LM][LM];
	My_copy_cube(MyCube, local);

	int i;
	switch (face)
	{
	case 0:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[2][2][i] = local[4][3 - 1 - i][2];
				MyCube[4][i][2] = local[3][0][i];
				MyCube[3][0][i] = local[5][3 - 1 - i][0];
				MyCube[5][i][0] = local[2][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[4][3 - 1 - i][2] = local[2][2][i];
				MyCube[3][0][i] = local[4][i][2];
				MyCube[5][3 - 1 - i][0] = local[3][0][i];
				MyCube[2][2][i] = local[5][i][0];
			}
		}
		break;
	case 1:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[5][i][2] = local[3][2][3 - 1 - i];
				MyCube[3][2][i] = local[4][i][0];
				MyCube[4][i][0] = local[2][0][3 - 1 - i];
				MyCube[2][0][i] = local[5][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[3][2][3 - 1 - i] = local[5][i][2];
				MyCube[4][i][0] = local[3][2][i];
				MyCube[2][0][3 - 1 - i] = local[4][i][0];
				MyCube[5][i][2] = local[2][0][i];
			}
		}
		break;
	case 2:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[0][0][i] = local[5][0][i];
				MyCube[5][0][i] = local[1][0][i];
				MyCube[1][0][i] = local[4][0][i];
				MyCube[4][0][i] = local[0][0][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[5][0][i] = local[0][0][i];
				MyCube[1][0][i] = local[5][0][i];
				MyCube[4][0][i] = local[1][0][i];
				MyCube[0][0][i] = local[4][0][i];
			}
		}
		break;
	case 3:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[0][2][i] = local[4][2][i];
				MyCube[4][2][i] = local[1][2][i];
				MyCube[1][2][i] = local[5][2][i];
				MyCube[5][2][i] = local[0][2][i];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[4][2][i] = local[0][2][i];
				MyCube[1][2][i] = local[4][2][i];
				MyCube[5][2][i] = local[1][2][i];
				MyCube[0][2][i] = local[5][2][i];
			}
		}
		break;
	case 4:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[0][i][0] = local[2][i][0];
				MyCube[2][i][0] = local[1][3 - 1 - i][2];
				MyCube[1][i][2] = local[3][3 - 1 - i][0];
				MyCube[3][i][0] = local[0][i][0];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[2][i][0] = local[0][i][0];
				MyCube[1][3 - 1 - i][2] = local[2][i][0];
				MyCube[3][3 - 1 - i][0] = local[1][i][2];
				MyCube[0][i][0] = local[3][i][0];
			}
		}
		break;
	case 5:
		if (cw == 1)
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[0][i][2] = local[3][i][2];
				MyCube[3][i][2] = local[1][3 - 1 - i][0];
				MyCube[1][i][0] = local[2][3 - 1 - i][2];
				MyCube[2][i][2] = local[0][i][2];
			}
		}
		else
		{
			for (i = 0; i < 3; i++)
			{
				MyCube[3][i][2] = local[0][i][2];
				MyCube[1][3 - 1 - i][0] = local[3][i][2];
				MyCube[2][3 - 1 - i][2] = local[1][i][0];
				MyCube[0][i][2] = local[2][i][2];
			}
		}
		break;
	}

}
void makeDic(int n){
	if (n >= 5)return;
	ROT* tmp = &ND[rp++];
	tmp->n = n;
	for (int i = 0; i < n; i++){
		tmp->f[i] = tmp_path[i][0];
		tmp->c[i] = tmp_path[i][1];
	}
	My_copy_cube(MyCube, tmp->cube);

	int hn = hash_f(MyCube);
	tmp->next = HT[hn];
	HT[hn] = tmp;
	
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 2; j++){
			MyRotate(i, j);
			tmp_path[n][0] = i;
			tmp_path[n][1] = j;
			makeDic(n + 1);
			MyRotate(i, 1 - j);
		}
	}
}
void dfs(int n){
	if (n >= ans_cnt)return;
	if (n >= 5)return;
	int hn = hash_f(MyCube);
	ROT* tmp = HT[hn];
	while (tmp != 0){
		if (isSameCube(MyCube, tmp->cube)){
			ans_cnt = n;
			for (int i = 0; i < n; i++){
				ans_path[i][0] =tmp_path[i][0];
				ans_path[i][1] =tmp_path[i][1];
			}
			ans_dic = tmp;
			return;
		}
		tmp = tmp->next;
	}
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 2; j++){
			MyRotate(i, j);
			tmp_path[n][0] = i;
			tmp_path[n][1] = j;
			dfs(n + 1);
			MyRotate(i, 1 - j);
		}
	}
}
void runTest(int local[6][LM][LM]){
	if (rp == 0){
		for (int face = 0; face < 6; face++)
			for (int i = 0; i < LM; i++)
				for (int j = 0; j < LM; j++)
					MyCube[face][i][j] = face;
		makeDic(0);
	}
	My_copy_cube(local, MyCube);
	ans_cnt = 6;
	dfs(0);
	for (int i = 0; i < ans_cnt; i++){
		int f = ans_path[i][0];
		int c = ans_path[i][1];
		rotate(f, c);
	}
	for (int i = ans_dic->n-1; i >=0; i--){
		int f = ans_dic->f[i];
		int c = ans_dic->c[i];
		rotate(f, 1-c);
	}
}

