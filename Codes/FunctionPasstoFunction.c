#include <stdio.h>
void print(int a){
	printf("Hello world!");	
}

void helloworld(void (*fonksiyon)(int a)){
	fonksiyon(5);
}


int main() 
{
	helloworld(print);
	return 0; 
}
