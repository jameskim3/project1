#define MIN 10000
#define MAX 50000

struct PARTICIPANT
{
	int id, preference;
};
struct MyPARTICIPANT
{
	int id, preference;
	MyPARTICIPANT * left;
	MyPARTICIPANT * right;
};

int rp;
MyPARTICIPANT nd[MAX * 2];
MyPARTICIPANT* LEFT;
MyPARTICIPANT* RIGHT;
int total_sum;

int high_sum;
int low_sum;

int compare(MyPARTICIPANT* a, MyPARTICIPANT* b)
{
	if (a == 0)return 1;
	if (b == 0)return -1;
	if (a->preference < b->preference ||
		a->preference == b->preference && a->id < b->id)
		return 1;
	else if (a->id == b->id)
		return 0;
	else return -1;
}
MyPARTICIPANT* GetHigh(MyPARTICIPANT* p)
{
	if (p == 0)return 0;
	while (p->right != 0)
		p = p->right;
	return p;
}
MyPARTICIPANT* GetLow(MyPARTICIPANT* p)
{
	if (p == 0)return 0;
	while (p->left != 0)
		p = p->left;
	return p;
}

MyPARTICIPANT* addTree(MyPARTICIPANT* r, MyPARTICIPANT* p)
{
	if (r == 0) 
	{
		return p;
	}
	if (compare(r,p) == 1)
	{
		r->right = addTree(r->right, p);
		return r;
	}
	else
	{
		r->left = addTree(r->left, p);
		return r;
	}
}
MyPARTICIPANT* removeTree(MyPARTICIPANT* r, MyPARTICIPANT* p)
{
	if (r == 0) return 0;
	if (compare(r, p) == 1)
	{
		r->right = removeTree(r->right, p);
		return r;
	}
	else if (r->id != p->id)
	{
		r->left = removeTree(r->left, p);
		return r;
	}
	else //same
	{
		if (r->left == 0)
			return r->right;
		else if (r->right == 0)
			return r->left;
		else
		{
			MyPARTICIPANT* tmp_min = GetHigh(r->right);
			r->id = tmp_min->id;
			r->preference = tmp_min->preference;
			r->right = removeTree(r->right, tmp_min);
			return r;
		}
	}
}
void addSum(MyPARTICIPANT* tmp)
{
	total_sum += 1;

	if (total_sum == 1)
	{
		LEFT = tmp;
		low_sum += tmp->preference;
	}
	else if (total_sum == 2)
	{
		MyPARTICIPANT* left_max = GetHigh(LEFT);
		if (compare(left_max, tmp) == 1)
		{
			RIGHT = addTree(RIGHT, tmp);
			high_sum += tmp->preference;
		}
		else
		{
			LEFT = addTree(LEFT, tmp);
			low_sum += tmp->preference;
			MyPARTICIPANT* left_max = GetHigh(LEFT);
			MyPARTICIPANT* dup = &nd[rp++];
			dup->preference = left_max->preference;
			dup->id = left_max->id;

			RIGHT = addTree(RIGHT, dup);
			high_sum += dup->preference;
			LEFT = removeTree(LEFT, left_max);
			low_sum -= left_max->preference;
		}
	}
	else
	{
		if (total_sum % 2 == 0)
		{
			MyPARTICIPANT* right_min = GetLow(RIGHT);

			if (compare(tmp, right_min) == 1)
			{
				LEFT = addTree(LEFT, tmp);
				low_sum += tmp->preference;
				MyPARTICIPANT* left_max = GetHigh(LEFT);
				MyPARTICIPANT* dup = &nd[rp++]; 
				dup->preference = left_max->preference; 
				dup->id = left_max->id;
				
				RIGHT = addTree(RIGHT, dup);
				high_sum += dup->preference;
				LEFT = removeTree(LEFT, left_max);
				low_sum -= left_max->preference;
			}
			else
			{
				RIGHT = addTree(RIGHT, tmp);
				high_sum += tmp->preference;
			}
		}
		else
		{
			MyPARTICIPANT* right_min = GetLow(RIGHT);

			if (compare(tmp, right_min) == -1)
			{
				RIGHT = addTree(RIGHT, tmp);
				high_sum += tmp->preference;
				MyPARTICIPANT* right_min = GetLow(RIGHT);
				MyPARTICIPANT* dup = &nd[rp++];
				dup->preference = right_min->preference;
				dup->id = right_min->id;

				LEFT = addTree(LEFT, dup);
				low_sum += dup->preference;
				RIGHT = removeTree(RIGHT, right_min);
				high_sum -= right_min->preference;
			}
			else
			{
				LEFT = addTree(LEFT, tmp);
				low_sum += tmp->preference;
			}
		}
	}
}
void compareTree(MyPARTICIPANT* r)
{
	if (r == 0)return;
	if (r->left!=0 && compare(r->left, r) < 1)
		int a234 = 1234;
	if (r->right != 0 && compare(r, r->right) < 1)
		int b234 = 235;
	compareTree(r->left);
	compareTree(r->right);

}
void init(int n, PARTICIPANT src[])
{
	int i, j, k;
	total_sum = 0;
	low_sum = high_sum = 0;
	LEFT = RIGHT = 0;

	for (i = 0; i < rp; i++)
	{
		nd[i].id = 0;
		nd[i].preference = 0;
		nd[i].left = 0;
		nd[i].right = 0;
	}

	rp = 0;
	for (i = 0; i < n; i++)
	{
		MyPARTICIPANT* tmp = &nd[rp++];
		tmp->id = src[i].id;
		tmp->preference = src[i].preference;
		addSum(tmp);
	}

	compareTree(LEFT);
	compareTree(RIGHT);
}
void remove(int opt)//0 MIN, 1 MAX, 2 MID
{
	if (opt == 0)
	{
		MyPARTICIPANT* left_min = GetLow(LEFT);
		low_sum -= left_min->preference;
		LEFT = removeTree(LEFT, left_min);
		total_sum--;
		if (total_sum % 2 == 1)
		{
			MyPARTICIPANT* right_min = GetLow(RIGHT);
			MyPARTICIPANT* dup = &nd[rp++];
			dup->preference = right_min->preference;
			dup->id = right_min->id;

			LEFT = addTree(LEFT, dup);
			low_sum += dup->preference;
			RIGHT = removeTree(RIGHT, right_min);
			high_sum -= right_min->preference;
		}
	}
	else if (opt == 1)
	{
		MyPARTICIPANT* right_max = GetHigh(RIGHT);
		high_sum -= right_max->preference;
		RIGHT = removeTree(RIGHT, right_max);
		total_sum--;
		if (total_sum % 2 == 0)
		{
			MyPARTICIPANT* left_max = GetHigh(LEFT);
			MyPARTICIPANT* dup = &nd[rp++];
			dup->preference = left_max->preference;
			dup->id = left_max->id;

			RIGHT = addTree(RIGHT, dup);
			high_sum += dup->preference;
			LEFT = removeTree(LEFT, left_max);
			low_sum -= left_max->preference;
		}
	}
	else
	{
		if (total_sum % 2 == 0)
		{
			total_sum -= 2;
			MyPARTICIPANT* left_max = GetHigh(LEFT);
			MyPARTICIPANT* right_min = GetLow(RIGHT);
			low_sum -= left_max->preference;
			high_sum -= right_min->preference;
			LEFT = removeTree(LEFT, left_max);
			RIGHT = removeTree(RIGHT, right_min);
		}
		else
		{
			total_sum -= 1;
			MyPARTICIPANT* left_max = GetHigh(LEFT);
			low_sum -= left_max->preference;
			LEFT = removeTree(LEFT, left_max);
		}
	}
}
void add(PARTICIPANT tar)
{
	MyPARTICIPANT* tmp = &nd[rp++];
	tmp->id = tar.id;
	tmp->preference = tar.preference;
	addSum(tmp);
}
void getsum2(int *a, int *b)
{
	*a = low_sum;
	*b = high_sum;
}