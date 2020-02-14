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

// 전역변수 g_Cards이 최대 저장갯수
#define MAX_CARDS	50
// 버퍼의 최대 길이
#define BUFFER_LEN	50

// 메뉴 선택을 위한 열거체 INPUT
typedef enum _INPUT INPUT;
enum _INPUT {
	INSERT = 1,	// 명함 삽입
	EDIT,		// 명함 수정
	DELETE,		// 명함 삭제
	PRINT,		// 전체 출력
	SEARCH,		// 명함 검색
	EXIT		// 종료
};

// 명함 정보를 저장할 구조체
typedef struct _Card Card;
struct _Card {
	int number;		// 명함번호
	char* name;		// 이름
	char* phone;	// 휴대폰 번호
	char* email;	// 이메일
};

// 편한 접근을 위한 전역 명함배열
Card g_Cards[MAX_CARDS];
// 현재 저장된 카드의 갯수
int g_count = 0;

// 명함을 입력받고 배열에 추가한다
void input_business_card();
// 현재 저장된 카드들을 출력한다.
void show_all_cards();
// 명함번호로 해당 명함을 찾는다.
void search_business_card(int num);
// 명함을 수정한다
void edit_buisiness_card();
// 명함 내부의 동적할당 변수들을 해제한다
void release();

// 메인함수
int main(void)
{
	// 메뉴선택을 저장할 변수
	INPUT input;

	while (1)
	{
		printf("1: 입력, 2: 수정, 3: 삭제, 4: 전체출력, 5: 검색, 6: 종료\n");
		printf("> ");
		scanf("%d", &input);

		// 해당 메뉴 기능에 대한 함수를 호출한다
		switch (input)
		{
		case INSERT:	// 명함 삽입
			input_business_card();
			break;
		case EDIT:		// 명함 수정
			edit_buisiness_card();
			break;
		case DELETE:	// 명함 삭제
			break;
		case PRINT:		// 명함 전체 출력
			show_all_cards();
			break;
		case SEARCH:	// 명함 검색
		{
			int target_num;
			printf("찾을 명함번호를 입력하세요 : ");
			scanf("%d", &target_num);
			search_business_card(target_num);
		}
		break;
		case EXIT:
		default:	// 해당 메뉴 외의 번호는 프로그렘을 종료한다.
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
	// 새로운 명함이 추가될때마다 1씩 증가하는 정적변수
	static int number = 1;

	// 입력을 받을 버퍼
	char buffer[BUFFER_LEN] = { 0 };

	// 이름을 입력받아 동적할당을 받고 복사한다
	printf("이름 : ");
	scanf("%s", buffer);
	char* name = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(name, buffer);

	// 폰번호를 입력받아 동적할당을 받고 복사한다.
	printf("폰번호 : ");
	scanf("%s", buffer);
	char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(phone, buffer);

	// 이메일을 입력받아 동적할당을 받고 복사한다.
	printf("이메일 : ");
	scanf("%s", buffer);
	char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(email, buffer);

	// 복사한 정보를 전역변수에 저장하고 현재 갯수를 1개 늘린다.
	g_Cards[g_count].email = email;
	g_Cards[g_count].name = name;
	g_Cards[g_count].phone = phone;
	g_Cards[g_count].number = number++;
	g_count++;
}

void show_all_cards()
{
	// 현재 저장된 명함들을 돌며 정보를 출력한다.
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
	// -1일 경우 찾는 명함이 없으며 해당명함의 index를 저장
	int target_index = -1;
	for (int i = 0; i < g_count; i++)
	{
		if (g_Cards[i].number == num)
		{
			target_index = i;
			break;
		}
	}

	// 찾은 명함의 정보를 출력한다.
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
	// -1일 경우 찾는 명함이 없으며 해당명함의 index를 저장
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

	// 명함이 있을경우 정보를 새로 받고 기존의 정보를 해제한다.
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
