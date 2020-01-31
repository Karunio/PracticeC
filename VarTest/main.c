#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char fruit[20];
	strcpy(fruit, "banana");

	printf("%s\n", fruit);
	// type here

	system("pause");
	return 0;
}