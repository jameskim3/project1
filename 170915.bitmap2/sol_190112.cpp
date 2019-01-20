
void encode(char TMP[100], char QRC[][100]){
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 4; j++){
			QRC[i][j] = 1;
			QRC[j][i] = 1;
		}
	}
	int off_y = 4;
	int off_x = 4;
	int cnt = 0;
	int py, px;
	for (int i = 0; i < 100; i++){
		int v = TMP[i]-'A';
		for (int j = 0; j < 5; j++){
			int b = (v >> j) & 1;
			px = (cnt * 6) % 96;
			py = (cnt * 6) / 96;
			for (int k = 0; k < 3; k++){
				for (int l = 0; l < 6; l++){
					QRC[off_y + py * 3 + k][off_x+px + l] = b;
				}
			}
			cnt++;
		}
	}
	cnt = cnt;
}
int y1, y2;
int x1, x2;
void searchBoundary(char TMP[][100]){
	y1 = y2 = x1 = x2 = -1;
	for (int i = 0; i < 100; i++){
		int cnt = 0;
		for (int j = 0; j < 100; j++){
			if (TMP[i][j] == 4){
				cnt++;
			}
			else cnt = 0;
			if (cnt > 45){
				y1 = i; break;
			}
		}
		if (y1 != -1)break;
	}
	int cnt = 0;
	for (int i = 0; i < 100; i++){
		if (TMP[y1+1][i] == 4){
			cnt++;
		}
		else cnt = 0;
		if (cnt > 45){
			y2 = y1+1; break;
		}
	}
	for (int i = 0; i < 100; i++){
		int cnt = 0;
		for (int j = 0; j < 100; j++){
			if (TMP[j][i] == 4){
				cnt++;
			}
			else cnt = 0;
			if (cnt > 45){
				x1 = i; break;
			}
		}
		if (x1 != -1)break;
	}
	cnt = 0;
	for (int i = 0; i < 100; i++){
		if (TMP[i][x1+1] == 4){
			cnt++;
		}
		else cnt = 0;
		if (cnt > 45){
			x2 = x1+1; break;
		}
	}
}

void decode(char TMP[][100], char TAR[100]){
	searchBoundary(TMP);
	int cnt = 0;
	int off_y, off_x;
	int y, x;
	int even_x = x2 != -1 ? 1 : 0;
	int even_y = y2 != -1 ? 1 : 0;
	int dummy_y = 0;
	off_x = x1 + 2;
	off_y = y1 + 2;
	for (int i = 0; i < 100; i++){
		int v = 0;
		for (int j = 0; j < 5; j++){
			int sum = 0;
			for (int k = 0; k < 3; k++){
				x = cnt % 48;
				y = cnt / 48;
				if (y>0 && x == 0 && even_y && y % 2 == 1) dummy_y++;
				if (y>0 && x == 0 && even_y == 0 && y % 2 == 0) dummy_y++;
				cnt++;
				if (even_x == 0 && k == 2)continue;
				sum += TMP[off_y+dummy_y+y][off_x+x];
			}
			if (even_x && sum == 12)v += 1 << j;
			else if (even_x == 0 && sum == 8)v += 1 << j;
		}
		TAR[i] = v+'A';
	}
}