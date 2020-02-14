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

#define MAX_CARDS	50
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
};

Card g_Cards[MAX_CARDS];
int g_count = 0, g_number = 1;

void input_business_card();
void show_all_cards();
void search_business_card(int num);
void edit_buisiness_card();
void delete_buisiness_card();
void release();
void load(char* filename);
void save(char* filename);

// �����Լ�
int main(void)
{
	load(SAVED_FILE);
	INPUT input;

	while (1)
	{
		printf("1: �Է�, 2: ����, 3: ����, 4: ��ü���, 5: �˻�, 6: ����\n");
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
			printf("ã�� ���Թ�ȣ�� �Է��ϼ��� : ");
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

	printf("�̸� : ");
	scanf("%s", buffer);
	char* name = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(name, buffer);

	printf("����ȣ : ");
	scanf("%s", buffer);
	char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(phone, buffer);

	printf("�̸��� : ");
	scanf("%s", buffer);
	char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
	strcpy(email, buffer);

	int check = 0;
	for (int i = 0; i < g_count; i++)
	{
		if (strcmp(g_Cards[i].name, name) == 0 && strcmp(g_Cards[i].phone, phone) == 0)
		{
			check = 1;
			break;
		}
	}

	if (check == 1)
	{
		printf("���� ������ ������ �ֽ��ϴ�\n");
		printf("���� �޴��� �̿��ϼ���\n");
		free(name);
		free(phone);
		free(email);
		system("pause");
	}
	else
	{
		g_Cards[g_count].email = email;
		g_Cards[g_count].name = name;
		g_Cards[g_count].phone = phone;
		g_Cards[g_count].number = g_number++;
		g_count++;
	}
}

void show_all_cards()
{
	for (int i = 0; i < g_count; i++)
	{
		printf("���Թ�ȣ : %d\n", g_Cards[i].number);
		printf("�̸� : %s\n", g_Cards[i].name);
		printf("����ȣ : %s\n", g_Cards[i].phone);
		printf("�̸��� : %s\n", g_Cards[i].email);
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
		printf("ã���ô� ������ �����ϴ�\n");
	}
	else
	{
		printf("���Թ�ȣ : %d\n", g_Cards[target_index].number);
		printf("�̸� : %s\n", g_Cards[target_index].name);
		printf("����ȣ : %s\n", g_Cards[target_index].phone);
		printf("�̸��� : %s\n", g_Cards[target_index].email);
		printf("\n");
	}


	printf("\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�.\n");
	system("pause");
}

void edit_buisiness_card()
{
	int target_index = -1, number;

	printf("������ ���Թ�ȣ�� �Է����ּ��� : ");
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
		printf("ã���ô� ������ �����ϴ�\n");
	}
	else
	{
		char buffer[BUFFER_LEN] = { 0 };
		printf("�����Ͻ� ������ �Է����ּ���.\n");

		printf("����ȣ : ");
		scanf("%s", buffer);
		free(g_Cards[target_index].phone);
		char* phone = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(phone, buffer);
		g_Cards[target_index].phone = phone;

		printf("�̸��� : ");
		scanf("%s", buffer);
		free(g_Cards[target_index].email);
		char* email = (char*)calloc(sizeof(char), strlen(buffer) + 1);
		strcpy(email, buffer);
		g_Cards[target_index].email = email;
	}


	printf("\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�.\n");
	system("pause");
}

void delete_buisiness_card()
{
	show_all_cards();

	int number, index = -1;
	printf("������ ���Թ�ȣ�� �Է��ϼ��� : ");
	scanf("%d", &number);

	for (int i = 0; i < g_count; i++)
	{
		if (g_Cards[i].number == number)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		printf("���� ���Թ�ȣ �Դϴ�.\n");
		system("pause");
	}
	else
	{
		free(g_Cards[index].name);
		free(g_Cards[index].phone);
		free(g_Cards[index].email);

		for (int i = index; i < g_count - 1; i++)
		{
			g_Cards[i].number = g_Cards[i + 1].number;
			g_Cards[i].name = g_Cards[i + 1].name;
			g_Cards[i].phone = g_Cards[i + 1].phone;
			g_Cards[i].email = g_Cards[i + 1].email;
		}
		g_count--;
	}
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
			g_Cards[g_count].number = atoi(token);

			token = strtok(NULL, "#");
			char* name = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(name, token);
			g_Cards[g_count].name = name;

			token = strtok(NULL, "#");
			char* phone = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(phone, token);
			g_Cards[g_count].phone = phone;

			token = strtok(NULL, "#");
			char* email = (char*)calloc(sizeof(char), strlen(token) + 1);
			strcpy(email, token);
			g_Cards[g_count].email = email;

			g_count++;
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
		for (int i = 0; i < g_count; i++)
		{
			fprintf(file, "\n%d#%s#%s#%s",
				g_Cards[i].number,
				g_Cards[i].name,
				g_Cards[i].phone,
				g_Cards[i].email);
		}
		fclose(file);
	}
}
