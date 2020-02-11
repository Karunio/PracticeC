/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수
  --------------------------------------------------------------------------------
  first created - 2020.02.03
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>

// 메인함수
int main(void)
{
    register int i;
    int sum = 0;

    for (i = 0; i <= 10000; i++)
    {
        sum += i;
    }

    printf("sum is %d\n", sum);
	// type here.
	system("pause");
	return EXIT_SUCCESS;
}