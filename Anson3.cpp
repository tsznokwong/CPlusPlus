#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	scanf("%d\n", &N);
	
	for(int i = 1; i <= N; i++) {
		
		char op, input[10000], original[10000], command[10000], str[10000], replace[10000];
		int quoteCnt = 0, mode = 0, olen = 0, clen = 0, slen = 0, rlen = 0;
		gets(input);
		memset(original, 0, sizeof(original));
		memset(command, 0, sizeof(command));
		memset(replace, 0, sizeof(replace));
		memset(str, 0, sizeof(str));
		
		int length = strlen(input);
		for(int j = 0; j < length; j++) {
			if(input[j] == 34)
				mode++;
			else if(mode == 1)
				original[olen++] = input[j];
			else if(mode == 2)
				command[clen++] = input[j];
			else if(mode == 3)
				str[slen++] = input[j];
			else if(mode == 5)
				replace[rlen++] = input[j];
		}
		for(int j = 0; j < clen; j++)
			if(command[j] != ' ') {
				op = command[j];
				break;
			}
		printf("Command #%d: ", i);
		if(op == 'A')
			printf("%c%s%s%c\n", 34, original, str, 34);
		else if(op == 'I') {
			printf("%c", 34);
			int pos = 0, loc;
			for(int j = 0; j < clen; j++)
				if(command[j] >= '0' && command[j] <= '9') {
					loc = j;
					break;
				}
			for(int j = loc; j < clen; j++)
				if(command[j] == ' ')
					break;
				else
					pos = pos*10 + command[j]-'0';
			for(int j = 0; j < olen; j++) {
				if(j == pos-1)
					printf("%s", str);
				printf("%c", original[j]);
			}
			printf("%c\n", 34);
		} else if(op == 'C') {
			printf("%c", 34);
			bool del = true;
			int inc = 1;
			for(int i = 0; i < olen; i += inc) {
				char cmp[500];
				memset(cmp, 0, sizeof(cmp));
				strncpy(cmp, original+i, slen);
				cmp[slen] = '\0';
				if(!strcmp(cmp, str) && del) {
					inc = slen;
					del = false;
				}
				else {
					inc = 1;
					printf("%c", original[i]);
				}
			}
			printf("%c\n", 34);
		} else {
			printf("%c", 34);
			bool rep = true;
			int inc = 1;
			for(int i = 0; i < olen; i += inc) {
				char cmp[500];
				memset(cmp, 0, sizeof(cmp));
				strncpy(cmp, original+i, slen);
				cmp[slen] = '\0';
				if(!strcmp(cmp, str) && rep) {
					inc = slen;
					printf("%s", replace);
					rep = false;
				}
				else {
					inc = 1;
					printf("%c", original[i]);
				}
			}
			printf("%c\n", 34);
		}
	}
	return 0;
}
