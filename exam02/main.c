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

// 버퍼의 최대 길이
#define BUFFER_LEN	50
// 저장 및 불러올 파일의 이름
#define SAVED_FILE	"card_data.txt"

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
	Card* next;		// 단방향 연결리스트를 위한 변수
};

// 연결리스트의 시작점을 저장할 전역변수
Card* g_Cards = NULL;
// 새로운 명함을 만들경우 증가할 변수
int g_number = 1;


// 명함을 입력받고 연결리스트에 추가한다
void input_business_card();
// 현재 저장된 카드들을 출력한다.
void show_all_cards();
// 명함번호로 해당 명함을 찾는다.
void search_business_card(int num);
// 명함을 수정한다
void edit_buisiness_card();
// 명함 내부의 동적할당 변수들을 해제한다
void release();
// 명함번호로 해당 명함을 삭제한다.
void delete_buisiness_card();
// 저장된 정보를 불러온다
void load(char* filename);
// 연결리스트의 정보를 파일로 저장한다.
void save(char* filename);
// 연결리스트에 추가할 새로운 명함을 동적할당하여 생성한다.
Card* GenCard(char* name, char* phone, char* email);
// 해당 정보로 새로운 카드를 만들고 연결리스트에 추가한다.
void InsertCard(char* name, char* phone, char* email);

// 메인함수
int main(void)
{
	// 저장된 파일을 읽어와 연결리스트에 저장한다.
	load(SAVED_FILE);
	// 메뉴 선택을 위한 변수
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
			// 종료시 현재 정보를 저장한다
			save(SAVED_FILE);
			// 연결리스트를 해제한다.
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

	// 현재 저장된 명함들중 이름과 전화번호가 같은 명함이 있는지 확인한다.
	Card* current = g_Cards;
	int check = 0;
	while (current != NULL)
	{
		if (strcmp(name, current->name) == 0 && strcmp(phone, current->name) == 0)
		{
			check = 1;
			break;
		}
		current = current->next;
	}

	// 이름과 전화번호가 같은명함이 있을경우 복사한 정보를 해제한다.
	if (check == 1)
	{
		printf("같은 정보의 명함이 있습니다\n");
		printf("수정 메뉴를 이용하세요\n");
		free(name);
		free(phone);
		free(email);
		system("pause");
	}
	// 만약 없다면 현재 정보를 연결리스트에 추가한다.
	else
	{
		InsertCard(name, phone, email);
	}
}

void show_all_cards()
{
	Card* current = g_Cards;
	while (current != NULL)
	{
		printf("명함번호 : %d\n", current->number);
		printf("이름 : %s\n", current->name);
		printf("폰번호 : %s\n", current->phone);
		printf("이메일 : %s\n", current->email);
		printf("\n");

		current = current->next;
	}
}

void search_business_card(int num)
{
	Card* current = g_Cards, * target = NULL;

	// 해당 명함이 있는지 순회 하며 확인하고 있으면 target에 저장한다
	while (current != NULL)
	{
		if (current->number == num)
		{
			target = current;
			break;
		}
	}

	// 명함이 있을경우 내용을 출력한다.
	if (target == NULL)
	{
		printf("찾으시는 명함이 없습니다\n");
	}
	else
	{
		printf("명함번호 : %d\n", target->number);
		printf("이름 : %s\n", target->name);
		printf("폰번호 : %s\n", target->phone);
		printf("이메일 : %s\n", target->email);
		printf("\n");
	}


	printf("\n아무 키 입력시 메뉴로 돌아갑니다.\n");
	system("pause");
}

void edit_buisiness_card()
{
	int number;
	printf("수정할 명함번호를 입력해주세요 : ");
	scanf("%d", &number);

	// 해당 명함이 있는지 순회 하며 확인하고 있으면 target에 저장한다
	Card* current = g_Cards;
	Card* target = NULL;
	while (current != NULL)
	{
		if (current->number == number)
		{
			target = current;
			break;
		}
	}

	// 명함이 있을경우 정보를 새로 받고 기존의 정보를 해제한다.
	if (target == NULL)
	{
		printf("찾으시는 명함이 없습니다\n");
	}
	else
	{
		char buffer[BUFFER_LEN] = { 0 };
		printf("수정하실 정보를 입력해주세요.\n");

		printf("폰번호 : ");
		scanf("%s", buffer);
		free(target->phone);
		char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(phone, buffer);
		target->phone = phone;

		printf("이메일 : ");
		scanf("%s", buffer);
		free(target->email);
		char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(email, buffer);
		target->email = email;
	}


	printf("\n아무 키 입력시 메뉴로 돌아갑니다.\n");
	system("pause");
}

void delete_buisiness_card()
{
	show_all_cards();

	Card* target = NULL;
	int number;
	printf("삭제할 명함번호를 입력하세요 : ");
	scanf("%d", &number);

	// 삭제할 명함이 있는지 우선 확인한다.
	Card* current = g_Cards;
	Card* prev = NULL;
	while (current != NULL)
	{
		if (current->number == number)
		{
			target = current;
			break;
		}
		prev = current;
		current = current->next;
	}

	// 삭제할 명함이 있다면 삭제한다.
	if (target == NULL)
	{
		printf("없는 명함번호 입니다.\n");
		system("pause");
	}
	else
	{
		// 만약 명함이 연결리스트의 맨앞부분이라면 시작점은 그 다음점이다.
		if (target == g_Cards)
		{
			g_Cards = target->next;
		}
		// 중간, 꼬리의 경우 전노드의 다음이 대상의 다음노드이다.
		else
		{
			prev->next = target->next;
		}

		// 연결리스트에서 빠진 노드의 정보를 해제한다.
		free(target->name);
		free(target->phone);
		free(target->email);
		free(target);
	}
}

void release()
{
	// 연결리스트를 순회하며 정보를 지운다.
	Card* current = g_Cards;

	while (current != NULL)
	{
		Card* target = current;
		current = current->next;

		free(target->name);
		free(target->phone);
		free(target->email);
		free(target);
	}
}

void load(char* filename)
{
	// 저장된 정보가 있다면 불러온다.
	FILE* file = fopen(filename, "r");

	if (file != NULL)
	{
		// 저장된 정보의 첫줄은 현재까지 생성된 명함번호이다.
		fscanf(file, "%d", &g_number);
		// fscanf의 버퍼문제를 해결할 fgetc
		fgetc(file);

		// 읽어온 정보를 저장할 버퍼
		char buffer[BUFFER_LEN] = { 0 };
		while (!feof(file))
		{
			// 한줄씩 정보를 읽어온다 \0를 생각하여 버퍼 크기 -1
			fgets(buffer, BUFFER_LEN - 1, file);

			// 정보를 #으로 구분하므로 토크나이징한다.
			char* token = strtok(buffer, "#");
			// 명함번호는 정수 이므로 atoi를 이용한다
			int number = atoi(token);

			// 다음 토큰으로 넘어가며 정보를 동적할당을 받고 복사한다.
			token = strtok(NULL, "#");
			char* name = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(name, token);

			token = strtok(NULL, "#");
			char* phone = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(phone, token);

			token = strtok(NULL, "#");
			char* email = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(email, token);

			// 가져온 정보들로 연결리스트를 구성한다.
			InsertCard(name, phone, email);
		}
		fclose(file);
	}
}

void save(char* filename)
{
	// 외부에 정보를 덮어쓰며 저장한다.
	FILE* file = fopen(filename, "w");

	if (file != NULL)
	{
		// 첫번째 줄에는 현재까지 생성된 명함갯수 즉 새로운 명함번호를 저장
		fprintf(file, "%d", g_number);

		// 연결리스트를 순회 하며 정보를 # 을 토큰으로 저장
		Card* current = g_Cards;
		while (current != NULL)
		{
			fprintf(file, "\n%d#%s#%s#%s",
				current->number,
				current->name,
				current->phone,
				current->email);

			current = current->next;
		}
		fclose(file);
	}
}

Card* GenCard(char* name, char* phone, char* email)
{
	Card* tCard = (Card*)calloc(sizeof(Card), 1);
	tCard->number = g_number++;
	tCard->name = name;
	tCard->phone = phone;
	tCard->email = email;
	tCard->next = NULL;

	return tCard;
}

void InsertCard(char* name, char* phone, char* email)
{
	if (g_Cards == NULL)
	{
		g_Cards = GenCard(name, phone, email);
	}
	else
	{
		Card* current;
		current = g_Cards;
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = GenCard(name, phone, email);
	}
}