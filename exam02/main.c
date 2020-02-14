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

#define BUFFER_LEN	50
#define SAVED_FILE	"card_data.txt"

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
	Card* next;
};

Card* g_Cards = NULL;
int g_number = 1;

void input_business_card();
void show_all_cards();
void search_business_card(int num);
void edit_buisiness_card();
void delete_buisiness_card();
void release();
void load(char* filename);
void save(char* filename);
Card* GenCard(char* name, char* phone, char* email);
void InsertCard(char* name, char* phone, char* email);
void DeleteCard(int number);

// 메인함수
int main(void)
{
	load(SAVED_FILE);
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
			delete_buisiness_card();
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
			save(SAVED_FILE);
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

	if (check == 1)
	{
		printf("같은 정보의 명함이 있습니다\n");
		printf("수정 메뉴를 이용하세요\n");
		free(name);
		free(phone);
		free(email);
		system("pause");
	}
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

	while (current != NULL)
	{
		if (current->number == num)
		{
			target = current;
			break;
		}
	}

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

	if (target == NULL)
	{
		printf("없는 명함번호 입니다.\n");
		system("pause");
	}
	else
	{
		if (target == g_Cards)
		{
			g_Cards = target->next;
		}
		else
		{
			prev->next = target->next;
		}
		free(target->name);
		free(target->phone);
		free(target->email);
		free(target);
	}
}

void release()
{
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
	FILE* file = fopen(filename, "r");
	if (file != NULL)
	{
		fscanf(file, "%d", &g_number);
		fgetc(file);

		char buffer[BUFFER_LEN] = { 0 };
		while (!feof(file))
		{
			fgets(buffer, BUFFER_LEN - 1, file);

			char* token = strtok(buffer, "#");
			int number = atoi(token);

			token = strtok(NULL, "#");
			char* name = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(name, token);

			token = strtok(NULL, "#");
			char* phone = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(phone, token);

			token = strtok(NULL, "#");
			char* email = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(email, token);

			InsertCard(name, phone, email);
		}
		fclose(file);
	}
}

void save(char* filename)
{
	FILE* file = fopen(filename, "w");

	if (file != NULL)
	{
		fprintf(file, "%d", g_number);

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