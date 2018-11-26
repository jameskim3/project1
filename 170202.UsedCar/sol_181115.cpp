typedef struct st
{
	int age;//0~20
	int passenger;//2~12
	int engine;//1000~5000
	int price;//10000~40000
} CAR; 
typedef struct node
{
	int id;
	int value;
	node* left;
	node* right;
}*pnode;
enum insert_opt { DEF_ID, DEF_VAL, };
typedef enum value_tree { AGE = 1, PASS, ENG, PRI, MAX_VALUE_TREE, };
pnode value_tree[MAX_VALUE_TREE] = { 0, };
int gidx = 1;
//Car 의 상태, 팔리기 전0, 팔린 후 order number
int id_list[10002] = { 0, };
int id_verify[10002];
int gfrom[5], gto[5], gorign4;


pnode insert_node(pnode p, pnode n, int opt)
{
	if (p == 0)
		return n;

	if (opt == DEF_ID)//id
	{
		if (n->id < p->id)
			p->left = insert_node(p->left, n, opt);
		else
			p->right = insert_node(p->right, n, opt);
	}
	else
	{
		if (n->value < p->value)
			p->left = insert_node(p->left, n, opt);
		else
			p->right = insert_node(p->right, n, opt);
	}

	return p;
}

pnode search_node(pnode p, int id, int opt)
{
	if (p == 0)
		return p;

	if (opt == DEF_ID)
	{
		if (p->id == id)
			return p;

		if (id < p->id)
			return search_node(p->left, id, opt);
		else
			return search_node(p->right, id, opt);
	}
	else
	{
		if (p->value == id)
			return p;

		if (id < p->value)
			return search_node(p->left, id, opt);
		else
			return search_node(p->right, id, opt);
	}
}

pnode find_min_node(pnode p)
{
	pnode cur = p;

	while (1)
	{
		if (cur->left == 0)
			break;
		cur = cur->left;
	}

	return cur;
}

pnode delete_node(pnode p, int id, int opt)
{
	if (p == 0)
		return 0;

	if (opt == DEF_ID)
	{
		if (id < p->id)
			p->left = delete_node(p->left, id, opt);
		else if (id > p->id)
			p->right = delete_node(p->right, id, opt);
		else
		{
			if (p->left == 0)
			{
				pnode tmp = p->right;
				free(p);
				return tmp;
			}
			else if (p->right == 0)
			{
				pnode tmp = p->left;
				free(p);
				return tmp;
			}
			else
			{
				pnode tmp = find_min_node(p->right);
				p->value = tmp->value;
				p->id = tmp->id;
				p->right = delete_node(p->right, tmp->id, opt);
			}
		}
	}
	else
	{
		if (id < p->value)
			p->left = delete_node(p->left, id, opt);
		else if (id > p->value)
			p->right = delete_node(p->right, id, opt);
		else
		{
			if (p->left == 0)
			{
				pnode tmp = p->right;
				free(p);
				return tmp;
			}
			else if (p->right == 0)
			{
				pnode tmp = p->left;
				free(p);
				return tmp;
			}
			else
			{
				pnode tmp = find_min_node(p->right);
				p->value = tmp->value;
				p->id = tmp->id;
				p->right = delete_node(p->right, tmp->value, opt);
			}
		}
	}

	return p;
}

void delete_all(pnode p)
{
	if (p == 0)
		return;

	delete_all(p->left);
	delete_all(p->right);
	free(p);
}

void buy_car(CAR car)
{
	pnode tmp[MAX_VALUE_TREE];
	tmp[AGE] = (pnode)malloc(sizeof(node));
	tmp[AGE]->value = car.age; tmp[AGE]->id = gidx;
	tmp[AGE]->left = 0; tmp[AGE]->right = 0;
	value_tree[AGE] = insert_node(value_tree[AGE], tmp[AGE], DEF_VAL);

	tmp[PASS] = (pnode)malloc(sizeof(node));
	tmp[PASS]->value = car.passenger; tmp[PASS]->id = gidx;
	tmp[PASS]->left = 0; tmp[PASS]->right = 0;
	value_tree[PASS] = insert_node(value_tree[PASS], tmp[PASS], DEF_VAL);

	tmp[ENG] = (pnode)malloc(sizeof(node));
	tmp[ENG]->value = car.engine; tmp[ENG]->id = gidx;
	tmp[ENG]->left = 0; tmp[ENG]->right = 0;
	value_tree[ENG] = insert_node(value_tree[ENG], tmp[ENG], DEF_VAL);

	tmp[PRI] = (pnode)malloc(sizeof(node));
	tmp[PRI]->value = car.price; tmp[PRI]->id = gidx;
	tmp[PRI]->left = 0; tmp[PRI]->right = 0;
	value_tree[PRI] = insert_node(value_tree[PRI], tmp[PRI], DEF_VAL);

	gidx++;
}


void swap(int& from, int& to)
{
	if (from > to)
	{
		int tmp = from;
		from = to;
		to = tmp;
	}
}
enum tra_type
{
	DEF_CREATE,
	DEF_MODIFY,
};

pnode new_order = 0;
pnode order_list[MC];
int gorder_idx = 1;
void traverse_value_tree(pnode p, int from, int to, int opt)
{
	if (p == 0)
		return;

	if (from < p->value)
	{
		traverse_value_tree(p->left, from, to, opt);
	}

	if (from <= p->value && p->value <= to && id_list[p->id] == 0)
	{
		if (opt == DEF_CREATE)
		{
			pnode tmp;
			tmp = (pnode)malloc(sizeof(node));
			tmp->value = 1; tmp->id = p->id;
			tmp->left = 0; tmp->right = 0;
			new_order = insert_node(new_order, tmp, DEF_ID);
		}
		else
		{
			pnode tmp = search_node(new_order, p->id, DEF_ID);
			if (tmp != 0)
			{
				tmp->value += 1;
				if (tmp->value == 4)
					gorign4++;
			}
		}
	}

	if (to >= p->value)
	{
		traverse_value_tree(p->right, from, to, opt);
	}
}

void sort_age(int from, int to)
{
	swap(from, to); gfrom[AGE] = from; gto[AGE] = to;
	int type = AGE;

	pnode tmp;
	tmp = (pnode)malloc(sizeof(node));
	tmp->value = -1; tmp->id = 0;
	tmp->left = 0; tmp->right = 0;
	new_order = tmp;
	gorign4 = 0;

	//id가 value인 order list를 만든다.
	traverse_value_tree(value_tree[type], from, to, DEF_CREATE);
}

void sort_pass(int from, int to)
{
	swap(from, to); gfrom[PASS] = from; gto[PASS] = to;
	int type = PASS;

	//id가 value인 order list를 만든다.
	traverse_value_tree(value_tree[type], from, to, DEF_MODIFY);
}
void sort_eng(int from, int to)
{
	swap(from, to); gfrom[ENG] = from; gto[ENG] = to;
	int type = ENG;

	//id가 value인 order list를 만든다.
	traverse_value_tree(value_tree[type], from, to, DEF_MODIFY);
}
void sort_pri(int from, int to)
{
	swap(from, to); gfrom[PRI] = from; gto[PRI] = to;
	int type = PRI;

	//id가 value인 order list를 만든다.
	traverse_value_tree(value_tree[type], from, to, DEF_MODIFY);
}

void sell_car_node(pnode p)
{
	if (p == 0)
		return;
	sell_car_node(p->left);

	if (p->value == 4)
		id_list[p->id] = gorder_idx;

	sell_car_node(p->right);
}

void verify(pnode p, int n)
{
	if (p == 0)
		return;

	if (p->left != 0)
		_ASSERT(p->left->value < p->value);
	if (p->right != 0)
		_ASSERT(p->right->value >= p->value);

	verify(p->left, n);

	if (p->value >= gfrom[n] && p->value <= gto[n] && id_list[p->id] == 0)
		id_verify[p->id] += 1;

	verify(p->right, n);
}

int sell_car()
{
	memset(id_verify, 0, sizeof(id_verify));
	verify(value_tree[AGE], AGE);
	verify(value_tree[PASS], PASS);
	verify(value_tree[ENG], ENG);
	verify(value_tree[PRI], PRI);

	sell_car_node(new_order);
	order_list[gorder_idx] = new_order;

	int cnt = 0;
	for (int i = 0; i <= MC; i++)
	{
		if (id_verify[i] == 4)
			cnt++;
	}


	return gorder_idx++;
}

void refund_node(pnode p)
{
	if (p == 0)
		return;
	refund_node(p->left);

	if (p->value == 4)
		id_list[p->id] = 0;

	refund_node(p->right);
}

void delete_all_node(pnode p)
{
	if (p == 0)
		return;

	delete_all_node(p->left);
	delete_all_node(p->right);
	free(p);
}

void refund(int order_no)
{
	pnode p = order_list[order_no];
	//refund_node(p);
}

int empty_car()
{
	delete_all_node(value_tree[AGE]);
	delete_all_node(value_tree[PASS]);
	delete_all_node(value_tree[ENG]);
	delete_all_node(value_tree[PRI]);

	value_tree[AGE] = 0;
	value_tree[PASS] = 0;
	value_tree[ENG] = 0;
	value_tree[PRI] = 0;

	for (int i = 1; i < gorder_idx; i++)
	{
		delete_all_node(order_list[i]);
		order_list[i] = 0;
	}

	gorder_idx = 1;

	int cnt = 0;
	for (int i = 1; i < gidx; i++)
	{
		if (id_list[i] == 0)
			cnt++;
		id_list[i] = 0;
	}
	gidx = 1;

	return cnt;
}