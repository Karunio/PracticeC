/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, 헤더 중복 제거
  --------------------------------------------------------------------------------
  first created - 2020.02.11
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "line.h"

// 메인함수
int main(void)
{
	Line a = { {1, 2}, {5, 6} };
	Point b = { (a.first.x + a.second.x) / 2, (a.first.y + a.second.y) / 2 };

	printf("선의 가운데 점 좌표 : (%d, %d)\n", b.x, b.y);

	system("pause");
	return EXIT_SUCCESS;
}