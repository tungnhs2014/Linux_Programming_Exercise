#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;
	
	// In ra so luong command-line truyen vao
	printf("Number of arguments: %d\n", argc);
	
	// In ra noi dung cua cac command-line
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i + 1, argv[i]);
	}
	
	return 0;
}
