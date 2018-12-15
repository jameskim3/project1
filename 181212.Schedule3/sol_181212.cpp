
struct SC{
	int uid, gid, nid;
	SC* mtnext;
	SC* idnext;
};
SC* MTREE[101][1001];//group,name
int rp;
SC nd[10010];
const int max_val = 1001;
char NAME[max_val][17];
SC* IDLIST[10010];

int deleteEvent2(int uid, char ename[]);

void init(){
}
int strlen(char ename[]){
	int cnt = 0;
	while (ename[cnt] > 0)cnt++;
	return cnt;
}
int strcmp(char* src, char* tar){
	int len1 = strlen(src);
	int len2 = strlen(tar);
	if (len1 != len2)return -1;
	int cnt = len1;
	while (cnt > 0){
		cnt--;
		if (src[cnt] != tar[cnt])return -1;
	}
	return 1;
}
int hashf(char ename[]){
	unsigned long h = 5381;
	int len = strlen(ename);
	for (int i = 0; i < len; i++){
		h = (h * 33 + ename[i]) % max_val;
	}
	return h%max_val;
}
int getNameID(char ename[]){
	int h = hashf(ename);
	while (1){
		if (NAME[h][0] == 0){
			int len = strlen(ename);
			for (int i = 0; i < len; i++){
				NAME[h][i] = ename[i];
			}
			NAME[h][len] = 0;
			break;
		}
		else if (strcmp(NAME[h], ename) == 1)break;
		else
			h = (h + 1) % max_val;
	}

	return h;
}
void push(SC* tmp, int opt){
	SC* head;
	if (opt==0) 
		head = MTREE[tmp->gid][tmp->nid];
	else
		head = IDLIST[tmp->uid];
	if (head == 0)	{
		if (opt == 0)
			MTREE[tmp->gid][tmp->nid]=tmp;
		else
			IDLIST[tmp->uid]=tmp;
	}
	else {
		SC*pre = head;
		SC*iter = head;
		while (iter > 0){
			pre = iter;
			if (opt == 0)
				iter = iter->mtnext;
			else
				iter = iter->idnext;
		}
		if (opt == 0)
			pre->mtnext = tmp;
		else
			pre->idnext = tmp;
	}
}
void addEvent(int uid, char ename[], int groupid){
	SC* tmp = &nd[rp++];
	tmp->gid = groupid;
	tmp->uid = uid;
	tmp->nid = getNameID(ename);
	tmp->mtnext = 0;
	tmp->idnext = 0;
	push(tmp,0);
	push(tmp, 1);
}
void deleteMTree(int uid, int gid, int nid){
	SC* head = MTREE[gid][nid];
	if (head->uid == uid){
		SC* iter = head->mtnext;
		while (iter > 0){
			deleteEvent2(iter->uid, NAME[iter->nid]);
			iter = iter->mtnext;
		}
	}
	SC* pre = head;
	SC* iter = head;
	if (head->uid == uid){
		head = 0;
	}
	else{
		while (iter > 0){
			if (iter->uid == uid){
				pre->mtnext = iter->mtnext;
				break;
			}
			pre = iter;
			iter = iter->mtnext;
		}
	}
}
int delCount;
int deleteEvent2(int uid, char ename[]){
	SC* iter = IDLIST[uid];
	SC* pre = IDLIST[uid];
	int nid = getNameID(ename);
	while (iter > 0){
		if (iter->uid == uid && iter->nid == nid){
			if (IDLIST[uid] == iter){
				IDLIST[uid] = iter->idnext;
				pre = IDLIST[uid];
				delCount++;
			}
			else{
				pre->idnext = iter->idnext;
				delCount++;
			}
			deleteMTree(iter->uid, iter->gid, iter->nid);
			iter = iter->idnext;
		}
		else{
			pre = iter;
			iter = iter->idnext;
		}
	}
	return 0;
}
int deleteEvent(int uid, char ename[]){
	delCount = 0;
	deleteEvent2(uid, ename);
	return delCount;
}
int changeCount;
void dupMTree(int uid, int gid, int nid, int tar_nid){
	SC* head = MTREE[gid][nid];
	SC* new_head = MTREE[gid][tar_nid];

	if (head->uid == uid){
		SC* iter = head;
		while (iter > 0){
			changeCount++;
			addEvent(iter->uid, NAME[tar_nid], gid);
			iter = iter->mtnext;
		}
	}
	else{
		SC* iter = head;
		while (iter>0&&iter->uid !=uid){
			iter = iter->mtnext;
		}
		if (iter > 0){
			changeCount++;
			addEvent(iter->uid, NAME[tar_nid], gid);
		}
	}
}
int changeEvent(int uid, char ename[], char cname[]){
	changeCount = 0;
	int src_nid = getNameID(ename);
	int tar_nid = getNameID(cname);

	SC* iter = IDLIST[uid];
	SC* pre = IDLIST[uid];
	int nid = getNameID(ename);
	while (iter > 0){
		if (iter->uid == uid && iter->nid == nid){
			dupMTree(iter->uid, iter->gid, src_nid, tar_nid);
			deleteEvent2(iter->uid, NAME[iter->nid]);
			iter = IDLIST[uid];
			pre = IDLIST[uid];
		}
		else{
			pre = iter;
			iter = iter->idnext;
		}
	}
	return changeCount;
}
int getCount(int uid){
	int cnt = 0;
	SC* iter = IDLIST[uid];
	while (iter > 0){
		cnt++;
		iter = iter->idnext;
	}
	return cnt;
}
