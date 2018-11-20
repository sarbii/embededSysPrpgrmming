#include <stdio.h>
#include "sub.h"
#include "sum.h"

int main(){
	int a=5;
	int b=6;
	
	int c =sum(a,b);
	printf("value: %d\n",c);

	int d= sub(a,b);
	printf("value: %d",d);

	
}
