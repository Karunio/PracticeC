/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�, Extern Static Test
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>

int input_data();
double average();
void print_data(double avg);

int count = 0;
static int total = 0;

// �����Լ�
int main(void)
{
	double avg;

	total = input_data();
	avg = average();
	print_data(avg);

	system("pause");
	return EXIT_SUCCESS;
}

void print_data(double avg)
{
	printf("�Է��� ����� ���� : %d\n", count);
	printf("��ü �� : %d, ��� : %lf\n", total, avg);
}
