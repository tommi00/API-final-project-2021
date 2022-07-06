#include <stdio.h>

int main(){
	int x, y, a;
	a = scanf("%d %d", &x, &y);
	if(a == 2){
		printf("%d\n", x+y);
	}
}