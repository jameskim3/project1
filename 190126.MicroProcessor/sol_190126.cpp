
extern int makecode(unsigned char code[10000]);
extern int proc(unsigned char code[10000], int len);

void parsing(unsigned char code, int *cmd, int *opt, int *val, int *val2){

}
int proc(unsigned char code[10000], int len){
	for (int i = 0; i < len; i++){
		int cmd, opt, val, val2;
		parsing(code[i], &cmd, &opt, &val, &val2);
	}
}
0
129 push r0
160 r1 = 0
11
162 r2 = 11
1
164 pop r3
224 label 0
130 push r1
161 pop r0
36 r0 += r3
1
161 r0 = 1
36 r0 += r3
129 push r0
164 pop r3
193 jump 0








