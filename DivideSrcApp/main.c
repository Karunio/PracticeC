/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�, Division Compile Practice
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include "sub.h"

// �����Լ�
int main(void)
{
	int a, b;
	double avg;

	input_data(&a, &b);
	avg = average(a, b);
	printf("%d, %d�� ��հ� : %lf", a, b, avg);

	// type here.
	system("pause");
	return EXIT_SUCCESS;
}
