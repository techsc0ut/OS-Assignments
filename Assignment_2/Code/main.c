#include <stdio.h>
extern void Add(long long int a, long long int b); // Prototype of the function to be called from Assembly object code file.
int main()
{ 
	long long a,b;
	scanf("%lld", &a);
	scanf("%lld", &b);
    	Add(a,b); //Invoking the Add function .
	return 0;
}

