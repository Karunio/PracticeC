/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, Selection Sort
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 메인함수
int main(void)
{
	const int LENGTH_A = 5;
	int a[] = { 3, 2, 1, 6, 5 };

	for (int i = 0; i < LENGTH_A - 1; i++)
	{
		int min_index = i;
		for (int j = i + 1; j < LENGTH_A; j++)
		{
			if (a[min_index] > a[j])
			{
				min_index = j;
			}
		}

		int tmp = a[min_index];
		a[min_index] = a[i];
		a[i] = tmp;
	}

	for (int i = 0; i < LENGTH_A; i++)
	{
		printf("%3d", a[i]);
	}

	system("pause");
	return EXIT_SUCCESS;
}