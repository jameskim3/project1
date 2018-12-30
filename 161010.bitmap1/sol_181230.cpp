#define NN 4096 
#define NM 256 

void encode(unsigned char bitmap[NM][NM / 8], unsigned char data[NN]){
	int cnt = 0;
	for (int i = 0; i < NN; i++){
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
			int y = i * 2;
			int x = 31;
			int k = j*2+1;
			sum[4] += (bitmap[y][x] >> k) & 1 ? 1 : 0;
			
			sum[5] += (bitmap[(127 - i) * 2][31] >> ((4 - j - 1) * 2)) & 1 ? 1 : 0;
			sum[6] += (bitmap[i * 2 + 1][0] >> (j * 2 + 1)) & 1 ? 1 : 0;
			y = (64+i) * 2 +1;
			x = 0;
			k = j * 2;
			sum[7] += (bitmap[y][x] >> k) & 1 ? 1 : 0;
		}
	}
	int a = 123;
}
void decode(unsigned char data[NN], unsigned char bitmap[NM][NM / 8]) {
	adjmap(bitmap);
	for (int i = 0; i < NN; i++){
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
