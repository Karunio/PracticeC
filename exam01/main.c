/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, exam01
  --------------------------------------------------------------------------------
  first created - 2020.02.14
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS	50
#define BUFFER_LEN	50

typedef enum _INPUT INPUT;
enum _INPUT {
	INSERT = 1,
	EDIT,
	DELETE,
	PRINT,
	SEARCH,
	EXIT
};

typedef struct _Card Card;
struct _Card {
	int number;
	char* name;
	char* phone;
	char* email;
};

Card g_Cards[MAX_CARDS];
int g_count = 0;

void input_business_card();
void show_all_cards();
void search_business_card(int num);
void edit_buisiness_card();
void release();

// 메인함수
int main(void)
{
	INPUT input;

	while (1)
	{
		printf("1: 입력, 2: 수정, 3: 삭제, 4: 전체출력, 5: 검색, 6: 종료\n");
		printf("> ");
		scanf("%d", &input);

		switch (input)
		{
		case INSERT:
			input_business_card();
			break;
		case EDIT:
			edit_buisiness_card();
			break;
		case DELETE:
			break;
		case PRINT:
			show_all_cards();
			break;
		case SEARCH:
		{
			int target_num;
			printf("찾을 명함번호를 입력하세요 : ");
			scanf("%d", &target_num);
			search_business_card(target_num);
		}
		break;
		case EXIT:
		default:
			release();
			return EXIT_SUCCESS;
		}

		printf("\n");
	}
	system("pause");
	return EXIT_SUCCESS;
}

void input_business_card()
{
	static int number = 1;

	char buffer[BUFFER_LEN] = { 0 };

	printf("이름 : ");
	scanf("%s", buffer);
	char* name = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(name, buffer);

	printf("폰번호 : ");
	scanf("%s", buffer);
	char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(phone, buffer);

	printf("이메일 : ");
	scanf("%s", buffer);
	char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(email, buffer);

	g_Cards[g_count].email = email;
	g_Cards[g_count].name = name;
	g_Cards[g_count].phone = phone;
	g_Cards[g_count].number = number++;
	g_count++;
}

void show_all_cards()
{
	for (int i = 0; i < g_count; i++)
	{
		printf("명함번호 : %d\n", g_Cards[i].number);
		printf("이름 : %s\n", g_Cards[i].name);
		printf("폰번호 : %s\n", g_Cards[i].phone);
		printf("이메일 : %s\n", g_Cards[i].email);
		printf("\n");
	}
}

void search_business_card(int num)
{
	int target_index = -1;
	for (int i = 0; i < g_count; i++)
	{
		if (g_Cards[i].number == num)
		{
			target_index = i;
			break;
		}
	}

	if (target_index == -1)
	{
		printf("찾으시는 명함이 없습니다\n");
	}
	else
	{
		printf("명함번호 : %d\n", g_Cards[target_index].number);
		printf("이름 : %s\n", g_Cards[target_index].name);
		printf("폰번호 : %s\n", g_Cards[target_index].phone);
		printf("이메일 : %s\n", g_Cards[target_index].email);
		printf("\n");
	}


	printf("\n아무 키 입력시 메뉴로 돌아갑니다.\n");
	system("pause");
}

void edit_buisiness_card()
{
	int target_index = -1, number;

	printf("수정할 명함번호를 입력해주세요 : ");
	scanf("%d", &number);

	for (int i = 0; i < g_count; i++)
	{
		if (g_Cards[i].number == number)
		{
			target_index = i;
			break;
		}
	}

	if (target_index == -1)
	{
		printf("찾으시는 명함이 없습니다\n");
	}
	else
	{
		char buffer[BUFFER_LEN] = { 0 };
		printf("수정하실 정보를 입력해주세요.\n");

		printf("폰번호 : ");
		scanf("%s", buffer);
		free(g_Cards[target_index].phone);
		char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(phone, buffer);
		g_Cards[target_index].phone = phone;

		printf("이메일 : ");
		scanf("%s", buffer);
		free(g_Cards[target_index].email);
		char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(email, buffer);
		g_Cards[target_index].email = email;
	}


	printf("\n아무 키 입력시 메뉴로 돌아갑니다.\n");
	system("pause");
}

void release()
{
	for (int i = 0; i < g_count; i++)
	{
		free(g_Cards[i].name);
		free(g_Cards[i].phone);
		free(g_Cards[i].email);
	}
}
