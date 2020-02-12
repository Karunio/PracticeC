/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수
  --------------------------------------------------------------------------------
  first created - 2020.02.12
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <WinSock2.h>
#include <mysql.h>

#define MYSQLUSER       "root"
#define MYSQLPASSWORD   "mysql_p@ssw0rd"
#define MYSQLIP         "localhost"

void loadmysql(char mysqlip[], MYSQL* cons);

// 메인함수
int main(void)
{
	MYSQL* cons = mysql_init(NULL);
	MYSQL_RES* res;
	MYSQL_ROW row;
	int fields;

	loadmysql(MYSQLIP, cons);
	printf("\n");
	mysql_query(cons, "use shopdb;");
	mysql_query(cons, "select * from membertbl;");
	res = mysql_store_result(cons);
	fields = mysql_num_fields(res);

	while (row = mysql_fetch_row(res))
	{
		for (int i = 0; i < fields; i++)
		{
			printf("%s", row[i]);
			if (i < fields)
			{
				printf("\t");
			}
		}
		printf("\n");
	}

	mysql_free_result(res);
	mysql_close(cons);

	system("pause");
	return EXIT_SUCCESS;
}

void loadmysql(char mysqlip[], MYSQL* cons)
{
	if (cons == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(cons));
		Sleep(1000);
		exit(EXIT_FAILURE);
	}

	if (!(mysql_real_connect(cons, mysqlip, MYSQLUSER, MYSQLPASSWORD, NULL, 0, NULL, 0) == NULL))
	{
		printf("\n성공");
		mysql_set_character_set(cons, "euckr");
	}
	else
	{
		fprintf(stderr, "연결 오류 : %s\n", mysql_error(cons));
		getchar();
	}
}
