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

// �������� g_Cards�� �ִ� ���尹��
#define MAX_CARDS	50
// ������ �ִ� ����
#define BUFFER_LEN	50

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
};

// ���� ������ ���� ���� ���Թ迭
Card g_Cards[MAX_CARDS];
// ���� ����� ī���� ����
int g_count = 0;

// ������ �Է¹ް� �迭�� �߰��Ѵ�
void input_business_card();
// ���� ����� ī����� ����Ѵ�.
void show_all_cards();
// ���Թ�ȣ�� �ش� ������ ã�´�.
void search_business_card(int num);
// ������ �����Ѵ�
void edit_buisiness_card();
// ���� ������ �����Ҵ� �������� �����Ѵ�
void release();

// �����Լ�
int main(void)
{
	// �޴������� ������ ����
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
	// ���ο� ������ �߰��ɶ����� 1�� �����ϴ� ��������
	static int number = 1;

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

	// ������ ������ ���������� �����ϰ� ���� ������ 1�� �ø���.
	g_Cards[g_count].email = email;
	g_Cards[g_count].name = name;
	g_Cards[g_count].phone = phone;
	g_Cards[g_count].number = number++;
	g_count++;
}

void show_all_cards()
{
	// ���� ����� ���Ե��� ���� ������ ����Ѵ�.
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
	// -1�� ��� ã�� ������ ������ �ش������ index�� ����
	int target_index = -1;
	for (int i = 0; i < g_count; i++)
	{
		if (g_Cards[i].number == num)
		{
			target_index = i;
			break;
		}
	}

	// ã�� ������ ������ ����Ѵ�.
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
	// -1�� ��� ã�� ������ ������ �ش������ index�� ����
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

	// ������ ������� ������ ���� �ް� ������ ������ �����Ѵ�.
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

void release()
{
	for (int i = 0; i < g_count; i++)
	{
		free(g_Cards[i].name);
		free(g_Cards[i].phone);
		free(g_Cards[i].email);
	}
}
