#include "sub.h"
#include <stdio.h>

void input_data(int* pa, int* pb)
{
	printf("�� ���� �Է� : ");
	scanf("%d %d", pa, pb);
}

double average(int a, int b)
{
	int sum;
	double avg;

	sum = a + b;
	avg = sum / 2.0;
	return avg;
}