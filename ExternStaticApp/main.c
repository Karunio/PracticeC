/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, Extern Static Test
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

// 메인함수
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
	printf("입력한 양수의 갯수 : %d\n", count);
	printf("전체 합 : %d, 평균 : %lf\n", total, avg);
}
