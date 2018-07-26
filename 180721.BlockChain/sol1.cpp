#ifndef NULL
#define NULL 0
#endif // NULL

extern unsigned int hexToDeci(unsigned char*s, unsigned int len);
extern unsigned int getBlockID(unsigned char*str, int stIdx, int length);

const int LM = (int)1e6 + 5;
const int MAX_BLK = 15010;
const int HASH_KEY = 10007;
struct BLOCK
{
	unsigned int parentHash;
	unsigned int hash;
	BLOCK* list;
	BLOCK* child[20];
	int count[20];
	int n;
	int occur;
};

BLOCK item[MAX_BLK];
BLOCK* heap[HASH_KEY];
int rp;

unsigned int getID(unsigned char *arr, int len)
{
	unsigned int a= hexToDeci(arr, len);
	return a;
}
void makeChain()
{

}
BLOCK* isOccur(int h)
{
	BLOCK* tmp = heap[h%HASH_KEY];
	while (tmp != 0)
	{
		if (tmp->hash == h)
			return tmp;
		tmp = tmp->list;
	}
	return 0;
}
void processBlockImage(int serverCnt, unsigned char image[][LM])
{
	int i, j, k;
	for (i = 0; i < MAX_BLK; i++)
	{
		//
	}
	for (i = 0; i < serverCnt; i++)
	{
		int idx = 0;
		int len = getID(&image[i][idx], 8); idx += 8;
		while(idx < len)
		{
			BLOCK* tmp = &item[rp++];
			unsigned h = getBlockID(&image[i][0], idx, 0);
			tmp->parentHash = getID(&image[i][idx], 8); idx += 8;
			tmp->hash = getID(&image[i][idx], 4); idx += 4;
			int tn = getID(&image[i][idx], 2); idx += 2;
			for (j = 0; j < tn; j++)
			{
				int exid = getID(&image[i][idx], 2); idx += 2;
				int exvol = getID(&image[i][idx], 4); idx += 4;
				tmp->count[exid] += exvol;
			}
			BLOCK* tmp2 = isOccur(h);
			if (tmp2 != 0)
			{
				tmp2->occur++;
				continue;
			}
			tmp->occur++;
			tmp->list = heap[h%HASH_KEY];
			heap[h%HASH_KEY] = tmp;
		}
	}
	makeChain();
}

int getSumVolume(unsigned int ID, int exchangeID){

	return 0;
}