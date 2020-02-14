/*
  filename - main.c
  version - 1.0
  description - �⺻ ���� �Լ�, exam01
  --------------------------------------------------------------------------------
  first created - 2020.02.14
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ������ �ִ� ����
#define BUFFER_LEN	50
// ���� �� �ҷ��� ������ �̸�
#define SAVED_FILE	"card_data.txt"

// �޴� ������ ���� ����ü INPUT
typedef enum _INPUT INPUT;
enum _INPUT {
	INSERT = 1,	// ���� ����
	EDIT,		// ���� ����
	DELETE,		// ���� ����
	PRINT,		// ��ü ���
	SEARCH,		// ���� �˻�
	EXIT		// ����
};

// ���� ������ ������ ����ü
typedef struct _Card Card;
struct _Card {
	int number;		// ���Թ�ȣ
	char* name;		// �̸�
	char* phone;	// �޴��� ��ȣ
	char* email;	// �̸���
	Card* next;		// �ܹ��� ���Ḯ��Ʈ�� ���� ����
};

// ���Ḯ��Ʈ�� �������� ������ ��������
Card* g_Cards = NULL;
// ���ο� ������ ������ ������ ����
int g_number = 1;


// ������ �Է¹ް� ���Ḯ��Ʈ�� �߰��Ѵ�
void input_business_card();
// ���� ����� ī����� ����Ѵ�.
void show_all_cards();
// ���Թ�ȣ�� �ش� ������ ã�´�.
void search_business_card(int num);
// ������ �����Ѵ�
void edit_buisiness_card();
// ���� ������ �����Ҵ� �������� �����Ѵ�
void release();
// ���Թ�ȣ�� �ش� ������ �����Ѵ�.
void delete_buisiness_card();
// ����� ������ �ҷ��´�
void load(char* filename);
// ���Ḯ��Ʈ�� ������ ���Ϸ� �����Ѵ�.
void save(char* filename);
// ���Ḯ��Ʈ�� �߰��� ���ο� ������ �����Ҵ��Ͽ� �����Ѵ�.
Card* GenCard(char* name, char* phone, char* email);
// �ش� ������ ���ο� ī�带 ����� ���Ḯ��Ʈ�� �߰��Ѵ�.
void InsertCard(char* name, char* phone, char* email);

// �����Լ�
int main(void)
{
	// ����� ������ �о�� ���Ḯ��Ʈ�� �����Ѵ�.
	load(SAVED_FILE);
	// �޴� ������ ���� ����
	INPUT input;

	while (1)
	{
		printf("1: �Է�, 2: ����, 3: ����, 4: ��ü���, 5: �˻�, 6: ����\n");
		printf("> ");
		scanf("%d", &input);

		// �ش� �޴� ��ɿ� ���� �Լ��� ȣ���Ѵ�
		switch (input)
		{
		case INSERT:	// ���� ����
			input_business_card();
			break;
		case EDIT:		// ���� ����
			edit_buisiness_card();
			break;
		case DELETE:	// ���� ����
			break;
		case PRINT:		// ���� ��ü ���
			show_all_cards();
			break;
		case SEARCH:	// ���� �˻�
		{
			int target_num;
			printf("ã�� ���Թ�ȣ�� �Է��ϼ��� : ");
			scanf("%d", &target_num);
			search_business_card(target_num);
		}
		break;
		case EXIT:
		default:	// �ش� �޴� ���� ��ȣ�� ���α׷��� �����Ѵ�.
			// ����� ���� ������ �����Ѵ�
			save(SAVED_FILE);
			// ���Ḯ��Ʈ�� �����Ѵ�.
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
	// �Է��� ���� ����
	char buffer[BUFFER_LEN] = { 0 };

	// �̸��� �Է¹޾� �����Ҵ��� �ް� �����Ѵ�
	printf("�̸� : ");
	scanf("%s", buffer);
	char* name = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(name, buffer);

	// ����ȣ�� �Է¹޾� �����Ҵ��� �ް� �����Ѵ�.
	printf("����ȣ : ");
	scanf("%s", buffer);
	char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(phone, buffer);

	// �̸����� �Է¹޾� �����Ҵ��� �ް� �����Ѵ�.
	printf("�̸��� : ");
	scanf("%s", buffer);
	char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(email, buffer);

	// ���� ����� ���Ե��� �̸��� ��ȭ��ȣ�� ���� ������ �ִ��� Ȯ���Ѵ�.
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

	// �̸��� ��ȭ��ȣ�� ���������� ������� ������ ������ �����Ѵ�.
	if (check == 1)
	{
		printf("���� ������ ������ �ֽ��ϴ�\n");
		printf("���� �޴��� �̿��ϼ���\n");
		free(name);
		free(phone);
		free(email);
		system("pause");
	}
	// ���� ���ٸ� ���� ������ ���Ḯ��Ʈ�� �߰��Ѵ�.
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
		printf("���Թ�ȣ : %d\n", current->number);
		printf("�̸� : %s\n", current->name);
		printf("����ȣ : %s\n", current->phone);
		printf("�̸��� : %s\n", current->email);
		printf("\n");

		current = current->next;
	}
}

void search_business_card(int num)
{
	Card* current = g_Cards, * target = NULL;

	// �ش� ������ �ִ��� ��ȸ �ϸ� Ȯ���ϰ� ������ target�� �����Ѵ�
	while (current != NULL)
	{
		if (current->number == num)
		{
			target = current;
			break;
		}
	}

	// ������ ������� ������ ����Ѵ�.
	if (target == NULL)
	{
		printf("ã���ô� ������ �����ϴ�\n");
	}
	else
	{
		printf("���Թ�ȣ : %d\n", target->number);
		printf("�̸� : %s\n", target->name);
		printf("����ȣ : %s\n", target->phone);
		printf("�̸��� : %s\n", target->email);
		printf("\n");
	}


	printf("\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�.\n");
	system("pause");
}

void edit_buisiness_card()
{
	int number;
	printf("������ ���Թ�ȣ�� �Է����ּ��� : ");
	scanf("%d", &number);

	// �ش� ������ �ִ��� ��ȸ �ϸ� Ȯ���ϰ� ������ target�� �����Ѵ�
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

	// ������ ������� ������ ���� �ް� ������ ������ �����Ѵ�.
	if (target == NULL)
	{
		printf("ã���ô� ������ �����ϴ�\n");
	}
	else
	{
		char buffer[BUFFER_LEN] = { 0 };
		printf("�����Ͻ� ������ �Է����ּ���.\n");

		printf("����ȣ : ");
		scanf("%s", buffer);
		free(target->phone);
		char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(phone, buffer);
		target->phone = phone;

		printf("�̸��� : ");
		scanf("%s", buffer);
		free(target->email);
		char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(email, buffer);
		target->email = email;
	}


	printf("\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�.\n");
	system("pause");
}

void delete_buisiness_card()
{
	show_all_cards();

	Card* target = NULL;
	int number;
	printf("������ ���Թ�ȣ�� �Է��ϼ��� : ");
	scanf("%d", &number);

	// ������ ������ �ִ��� �켱 Ȯ���Ѵ�.
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

	// ������ ������ �ִٸ� �����Ѵ�.
	if (target == NULL)
	{
		printf("���� ���Թ�ȣ �Դϴ�.\n");
		system("pause");
	}
	else
	{
		// ���� ������ ���Ḯ��Ʈ�� �Ǿպκ��̶�� �������� �� �������̴�.
		if (target == g_Cards)
		{
			g_Cards = target->next;
		}
		// �߰�, ������ ��� ������� ������ ����� ��������̴�.
		else
		{
			prev->next = target->next;
		}

		// ���Ḯ��Ʈ���� ���� ����� ������ �����Ѵ�.
		free(target->name);
		free(target->phone);
		free(target->email);
		free(target);
	}
}

void release()
{
	// ���Ḯ��Ʈ�� ��ȸ�ϸ� ������ �����.
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
	// ����� ������ �ִٸ� �ҷ��´�.
	FILE* file = fopen(filename, "r");

	if (file != NULL)
	{
		// ����� ������ ù���� ������� ������ ���Թ�ȣ�̴�.
		fscanf(file, "%d", &g_number);
		// fscanf�� ���۹����� �ذ��� fgetc
		fgetc(file);

		// �о�� ������ ������ ����
		char buffer[BUFFER_LEN] = { 0 };
		while (!feof(file))
		{
			// ���پ� ������ �о�´� \0�� �����Ͽ� ���� ũ�� -1
			fgets(buffer, BUFFER_LEN - 1, file);

			// ������ #���� �����ϹǷ� ��ũ����¡�Ѵ�.
			char* token = strtok(buffer, "#");
			// ���Թ�ȣ�� ���� �̹Ƿ� atoi�� �̿��Ѵ�
			int number = atoi(token);

			// ���� ��ū���� �Ѿ�� ������ �����Ҵ��� �ް� �����Ѵ�.
			token = strtok(NULL, "#");
			char* name = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(name, token);

			token = strtok(NULL, "#");
			char* phone = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(phone, token);

			token = strtok(NULL, "#");
			char* email = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(email, token);

			// ������ ������� ���Ḯ��Ʈ�� �����Ѵ�.
			InsertCard(name, phone, email);
		}
		fclose(file);
	}
}

void save(char* filename)
{
	// �ܺο� ������ ����� �����Ѵ�.
	FILE* file = fopen(filename, "w");

	if (file != NULL)
	{
		// ù��° �ٿ��� ������� ������ ���԰��� �� ���ο� ���Թ�ȣ�� ����
		fprintf(file, "%d", g_number);

		// ���Ḯ��Ʈ�� ��ȸ �ϸ� ������ # �� ��ū���� ����
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