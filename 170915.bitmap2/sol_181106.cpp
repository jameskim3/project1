//Performance : 30047
void encode(char TMP[100], char QRC[][100])
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 4; j++)
		{
			QRC[i][j] = 1;
			QRC[j][i] = 1;
		}

	int off_x = 4;
	int off_y = 4;
	int b, x, y;
	int tmp, cnt;
	cnt = 0;
	for (int i = 0; i < 100; i++)
	{
		tmp = TMP[i] - 'A';
		for (int j = 0; j < 5; j++)
		{
			b = (tmp >> j) & 1;
			x = (cnt * 6) % 96;
			y = (cnt * 6) / 96;
			y *= 3;
			x += off_x;
			y += off_y;
			for (int s = 0; s < 3; s++)
			{
				for (int t = 0; t < 6; t++)
				{
					QRC[y + s][x + t] = b;
				}
			}
			cnt++;
		}
	}

	int a3453 = 2345;
	return;
}
void decode(char TMP[][100], char TAR[100])
{
	int rsum[100] = { 0 };
	int csum[100] = { 0 };

	int cnt_1 = 0;
	int off_y[2];
	int off_x[2];
	for (int i = 0; i < 2; i++)
	{
		off_y[i] = -1;
		off_x[i] = -1;
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (TMP[i][j] == 4)
				cnt_1++;
			else
				cnt_1 = 0;

			if (cnt_1 > 45)
			{
				off_y[0] = i; cnt_1 = 0;
				break;
			}
		}
		if (off_y[0] != -1)
		{
			for (int j = 0; j < 100; j++)
			{
				if (TMP[off_y[0] + 1][j] == 4)
					cnt_1++;
				else
					cnt_1 = 0;
				if (cnt_1 > 45)
				{
					off_y[1] = off_y[0] + 1;
					break;
				}
			}
			break;
		}
	}
	cnt_1 = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (TMP[j][i] == 4)
				cnt_1++;
			else
				cnt_1 = 0;

			if (cnt_1 > 45)
			{
				off_x[0] = i; cnt_1 = 0;
				break;
			}
		}
		if (off_x[0] != -1)
		{
			for (int j = 0; j < 100; j++)
			{
				if (TMP[j][off_x[0] + 1] == 4)
					cnt_1++;
				else
					cnt_1 = 0;
				if (cnt_1 > 45)
				{
					off_x[1] = off_x[0] + 1;
					break;
				}
			}
			break;
		}
	}

	int even_x = off_x[1] == -1 ? 0 : 1;
	int even_y = off_y[1] == -1 ? 0 : 1;
	int ox = even_x ? off_x[0] + 2 : off_x[0] + 1;
	int oy = off_y[0] + 2;
	int b, x, y, r, c;
	int tmp, cnt;
	cnt = 0;
	int jy = 0;
	int sy = 0;
	for (int i = 0; i < 100; i++)
	{
		b = 0;
		for (int j = 0; j < 5; j++)
		{
			int local = 0;
			for (int k = 0; k < 3; k++, cnt++)
			{
				y = cnt / 48;
				x = cnt % 48;

				if (y > 0 && x == 0)
				{
					if (even_y == 1 && y % 2 == 1)
						jy++;
					if (even_y == 0 && y % 2 == 0)
						jy++;
				}

				if (even_x == 0 && k == 0)continue;
				local += TMP[oy + y + jy][ox + x];
			}
			int bit = 0;
			if (even_x == 1 && local >= 12)
				bit = 1;
			else if (even_x == 0 && local >= 8)
				bit = 1;
			if (bit) b += 0x01 << j;
		}
		TAR[i] = 'A' + b;
	}
	int as = 8967;
}