//SCORE: 10241211
#define NN 4096 
#define NM 256 
extern void flip(unsigned char bitmap[NM][NM / 8], int mode);
extern void rotate(unsigned char bitmap[NM][NM / 8], int angle);
void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN]){
	int cnt = 0;
	for (register int i = 0; i < NN; i++){
		int val = data[i];
		int b = 0;
		for (int j = 0; j < 4; j++){
			b = (val >> j) & 1;
			int y = i / 32;
			int x = i % 32;
			bitmap[y * 2][x] += b<<(j*2);
			bitmap[y * 2][x] += b<<(j*2+1);
			bitmap[y * 2 + 1][x] += b << (j * 2);
			bitmap[y * 2 + 1][x] += b << (j * 2+1);
		}
	}
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 16; j++){
			for (int k = 0; k < 4; k++){
				bitmap[i * 2 + 1][j] |= 1 << (k * 2 + 1);
			}
		}
	}
}
void adjmap(unsigned char bitmap[NM][NM / 8]) {
	int sum[8] = { 0 };
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 16; j++){
			for (int k = 0; k < 4; k++){
				sum[0] += (bitmap[i * 2 + 1][j] >> (k * 2 + 1)) & 1 ? 1 : 0;
				sum[1] += (bitmap[i * 2 + 1][j + 16] >> (k * 2)) & 1 ? 1 : 0;
				sum[2] += (bitmap[(127 - i) * 2][j] >> (k * 2 + 1)) & 1 ? 1 : 0;
				sum[3] += (bitmap[(127 - i) * 2][j + 16] >> (k * 2)) & 1 ? 1 : 0;
			}
		}
	}
	for (int i = 0; i < 64; i++){
		for (int j = 0; j < 4; j++){
			sum[4] += (bitmap[i*2][31] >> (j*2+1) ) & 1 ? 1 : 0;
			sum[5] += (bitmap[(i+64)*2+1][31] >> (j*2+1)) & 1 ? 1 : 0;
			sum[6] += (bitmap[i*2][0] >> j*2) & 1 ? 1 : 0;
			sum[7] += (bitmap[(i+64)*2+1][0] >>j*2) & 1 ? 1 : 0;
		}
	}
	int max_idx = 0;
	int max_val = -1;
	for (int i = 0; i < 8; i++){
		if (max_val < sum[i]){
			max_val = sum[i];
			max_idx = i;
		}
	}
	switch (max_idx){
	case 1:
		flip(bitmap, 2); break;
	case 2:
		flip(bitmap, 1); break;
	case 3:
		rotate(bitmap, 2); break;
	case 4:
		rotate(bitmap, 3); break;
	case 5:
		flip(bitmap, 1);
		rotate(bitmap, 3); break;
	case 6:
		flip(bitmap, 2);
		rotate(bitmap, 3); break;
	case 7:
		rotate(bitmap, 1); break;
	}
}
void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8]) {
	adjmap(bitmap);
	for (register int i = 0; i < NN; i++){
		int val = 0;
		for (int j = 0; j < 4; j++){
			int cnt = 0;
			int y = i / 32;
			int x = i % 32;
			if ((bitmap[y * 2][x] >> (j * 2)) & 1) cnt++;
			if ((bitmap[y * 2][x] >> (j * 2 + 1)) & 1) cnt++;
			if ((bitmap[y * 2 + 1][x] >> (j * 2)) & 1) cnt++;
			if (cnt > 1) val += 1 << j;
		}
		data[i] = val; 
	}
}
