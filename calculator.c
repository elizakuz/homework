#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
	
int main(int argc, char **argv){

	FILE* input = NULL;
	
	input = freopen(argv[1], "r", stdin);

	char s;
	long_num new;
	long_num el1, el2;
	s = getchar();
	while(s != EOF){
		switch(s) {
			case '0'...'9': new = long_numCreate(s);
				new.digits = long_numReverse(new.digits);
				push(new); 
				break;
			case '+':
				if((hd != NULL) & (hd->next != NULL)){
					el1 = pop();
					el2 = pop();
					el1.digits = long_numReverse(el1.digits);
					el2.digits = long_numReverse(el2.digits);
					if (el1.sign == el2.sign){
						new = long_numAdd(el1, el2);
					} else {
						new = long_numDiv(el1, el2);
					}
					push(new);
				} else {
					printf("Not enough arguments1\n");
					stack_clean();
					return(1);
				}
				break;
			case '-': s = getchar();
				if (s == 13 || s == '\r' || s == EOF){
					if((hd != NULL) & (hd->next != NULL)){
						el1 = pop();
						el2 = pop();
						el1.digits = long_numReverse(el1.digits);
						el2.digits = long_numReverse(el2.digits);
						if (el1.sign == el2.sign){
							new = long_numSub(el1, el2);
						} else {
							new = long_numAdd(el1, el2);
						}	
						push(new);
					} else {	
						printf("Not enough arguments\n");
						stack_clean();
						return(1);
					}
				} else {
					new = long_numCreate(s);
					new.sign = -1;
					new.digits = long_numReverse(new.digits);
					push(new); 
				} 
				break;
			case '*': if((hd != NULL) & (hd->next != NULL)){
					el1 = pop();
					el2 = pop();
					el1.digits = long_numReverse(el1.digits);
					el2.digits = long_numReverse(el2.digits);
					new = long_numMult(el1, el2);
					push(new);
				} else {
					printf("Not enough arguments\n");
					stack_clean();
					return(1);
				}
				break;
			case '/':
				if((hd != NULL) & (hd->next != NULL)){
					if(hd->next->a.digits.head->v != 0){
						el1 = pop();
						el2 = pop();
						el1.digits = long_numReverse(el1.digits);
						el2.digits = long_numReverse(el2.digits);
						new = long_numDiv(el1, el2);
						new.digits = long_numReverse(new.digits);
						push(new);
					} else { 
						printf("Division by zero\n");
						stack_clean();
						return(1);
					}
				} else {
					printf("Not enough arguments\n");
					stack_clean();
					return(1);
				}
				break;
			case 61: if (hd != NULL) {
					new = pop();
					push(new);
					if (new. sign == -1) {
						printf("-");
					}
					print(new.digits.head);
					printf("\n");
					break;
				} else {
					printf("Not enough arguments\n");
					return(1);
				}
				break;
			case 13: break;
			case '\n': break;
			case ' ' : break;
			default: 
				stack_clean();
				printf("Unknown command\n");
				return(1);
				break;
		}
		s = getchar();
	}
	print_stack();			
	stack_clean();	
}
