
void encode(char TMP[100], char QRC[][100])
{
	register int i, j, k, s,t,u, y, x, cnt;
	int bit;
	cnt = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 100; j++)
		{
			QRC[i][j] = 1;
			QRC[j][i] = 1;
		}
	}
	int offx, offy;
	offx = offy = 4;
	for (i = 0; i < 100; i++)
	{
		TMP[i] -= 'A';
		for (j = 0; j < 5; j++)
		{
			bit = (TMP[i] >> j) & 1;

			y = (cnt / 16) * 3;
			x = (cnt % 16) * 6;

			for (s = 0; s < 3; s++)
			{
				for (t = 0; t < 6; t++)
				{
					QRC[y + s+offy][x + t+offx] = bit;
				}
			}
			cnt++;
		}
	}
}

void decode(char TMP[][100], char TAR[100])
{
	int i, j, k, s, t, u, y, x;

	int xp[2], yp[2], cnt1, cnt2;
	cnt1 = cnt2 = xp[0] = yp[0] = 0;
	xp[0] = yp[0] = -1;
	xp[1] = yp[1] = -1;
	k = 0;
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++)
		{
			if (TMP[i][j] == 4)
				cnt1++;
			else
				cnt1 = 0;
			if (cnt1 > 48)
			{
				cnt1 = 0;
				yp[k++] = i;
				break;
			}
		}

		if (yp[0] != -1 && yp[0] + 1 == i)
			break;
	}
	k = 0;
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++)
		{
			if (TMP[j][i] == 4)
				cnt1++;
			else
				cnt1 = 0;
			if (cnt1 > 48)
			{
				cnt1 = 0;
				xp[k++] = i;
				break;
			}
		}

		if (xp[0] != -1 && xp[0] + 1 == i)
			break;
	}

	int bit;
	int cnt = 0;
	int yy1[50],yy2[50];
	for (i = 0; cnt < 50; i++)
	{
		if (i % 3 == 1)continue;
		yy1[cnt++] = i;
	}
	cnt = 0;
	for (i = 0; cnt < 50; i++)
	{
		if (i % 3 == 2)continue;
		yy2[cnt++] = i;
	}

	cnt = 0;
	int offy, offx, optionY, optionX;
	offy = yp[0] + 2;
	optionY = yp[1] != -1 ? 0 : 1;
	offx = xp[0] + 2;
	optionX = xp[1] != -1 ? 3 : 2;

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 5; j++)
		{
			bit = 0;
			if (optionY == 0)
				y = yy1[(cnt / 16)];
			else
				y = yy2[(cnt / 16)];

			x = (cnt % 16) * 3;

			for (s = 0; s < 1; s++)
			{
				for (t = 0; t < optionX; t++)
				{
					bit += TMP[offy + y + s][offx + x + t];
				}
			}
			if (optionX ==3 && bit >= 12)TAR[i] += (1 << j);
			if (optionX == 2 && bit >= 8)TAR[i] += (1 << j);
			cnt++;
		}

		TAR[i] += 'A';
		char c1 = TAR[i];
		char c2 = TAR[i];
	}
}