/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�, ��� �ߺ� ����
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "line.h"

// �����Լ�
int main(void)
{
	Line a = { {1, 2}, {5, 6} };
	Point b = { (a.first.x + a.second.x) / 2, (a.first.y + a.second.y) / 2 };

	printf("���� ��� �� ��ǥ : (%d, %d)\n", b.x, b.y);

	system("pause");
	return EXIT_SUCCESS;
}