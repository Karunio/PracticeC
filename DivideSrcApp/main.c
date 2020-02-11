/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, Division Compile Practice
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include "sub.h"

// 메인함수
int main(void)
{
	int a, b;
	double avg;

	input_data(&a, &b);
	avg = average(a, b);
	printf("%d, %d의 평균값 : %lf", a, b, avg);

	// type here.
	system("pause");
	return EXIT_SUCCESS;
}
