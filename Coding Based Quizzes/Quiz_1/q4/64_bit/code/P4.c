#include<stdio.h>
#include <stdint.h>

//extern int32_t long_add(int32_t a,int32_t b,int32_t c,int32_t d);
extern int64_t extended_add(int64_t a,int64_t b,int64_t c,int64_t d);

int main()
{	
	//int32_t A=100;
	//int32_t B=-100;
	//int32_t C=100;
	//int32_t D=-100;
	//int32_t result=long_add(A,B,C,D);

	int64_t a=1000000000000000;
	int64_t b=1000;
	int64_t c=5000;
	int64_t d=1000;
	int64_t result2=extended_add(a,b,c,d);

	
	//printf("%d \n",result);
	printf("%ld \n",result2);

	return 0;
}
