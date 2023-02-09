#include <stdlib.h>
#define SIZE 3


struct person{
	char *name;
	int age;
};


int main() 
{
	struct person p1;
	char *names[SIZE] = {"alperen", "mert", "ahmet"};
	int ages[SIZE] = {20, 19, 20};
	int i = 0;

	struct person *p = (struct person*) malloc(SIZE*(sizeof(struct person)));

	for ( i = 0; i < SIZE; i++)
	{
		p[i].name = names[i];
		p[i].age = ages[i];
	}
	
	
	
	return 0; 
}
