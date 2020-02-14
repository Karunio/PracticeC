/*
  filename - main.c
  version - 1.0
  description - 기본 메인 함수, Using Github Parser
  --------------------------------------------------------------------------------
  first created - 2020.02.12
  writer - Karunio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parson.h"

void read_json();
void write_json();

// 메인함수
int main(void)
{
	write_json();
	system("pause");
	return EXIT_SUCCESS;
}

void read_json()
{
	JSON_Value* rootValue;      // Json을 읽어 값을 읽어온다.
	JSON_Object* rootObject;    // 읽은 값으로 부터 오브젝트를 만든다.

	// JSON 파일을 읽어온다.
	rootValue = json_parse_file("Package.json");
	// 읽은 값으로 부터 오브젝트를 얻는다.
	rootObject = json_value_get_object(rootValue);

	// 키값으로 값을 읽어와 출력한다.
	printf("name : %s\n", json_object_get_string(rootObject, "name"));
	printf("version : %s\n", json_object_get_string(rootObject, "version"));
	printf("repo : %s\n", json_object_get_string(rootObject, "repo"));
	printf("description : %s\n", json_object_get_string(rootObject, "description"));
	printf("keywords :\n");
	{
		JSON_Array* array = json_object_get_array(rootObject, "keywords");
		for (int i = 0; i < json_array_get_count(array); i++)
		{
			printf("\t%s\n", json_array_get_string(array, i));
		}
	}
	printf("license : %s\n", json_object_get_string(rootObject, "license"));
	printf("src :\n");
	{
		JSON_Array* array = json_object_get_array(rootObject, "src");
		for (int i = 0; i < json_array_get_count(array); i++)
		{
			printf("\t%s\n", json_array_get_string(array, i));
		}
	}

	json_value_free(rootValue);
}

void write_json()
{
	JSON_Value* rootValue;
	JSON_Object* rootObject;

	rootValue = json_value_init_object();
	rootObject = json_value_get_object(rootValue);

	json_object_set_string(rootObject, "Title", "Interstellar");
	json_object_set_number(rootObject, "Year", 2014);
	json_object_set_number(rootObject, "Runtime", 169);

	json_object_set_string(rootObject, "Genre", "Sci-Fi");
	json_object_set_string(rootObject, "Director", "Christopher Nolan");

	json_object_set_value(rootObject, "Actors", json_value_init_array());

	JSON_Array* actors = json_object_get_array(rootObject, "Actors");

	json_array_append_string(actors, "Matthew McConaughey");
	json_array_append_string(actors, "Anne Hathaway");
	json_array_append_string(actors, "Michael Caine");
	json_array_append_string(actors, "Jessica Chastain");
	json_array_append_string(actors, "Casey Affleck");

	json_object_set_boolean(rootObject, "KoreaReleas", 1);


	json_serialize_to_file_pretty(rootValue, "Saved.json");
	json_value_free(rootValue);
}
