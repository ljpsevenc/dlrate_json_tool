#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

cJSON *get_cjson_from_file(const char *file_name)
{
	FILE *json = NULL;
	json=fopen(file_name, "r");
	if (NULL == json)
	{
		return -1;
	}
	char *json_string = NULL;
	int i = 0;
	long json_size;
	fseek(json, 0, SEEK_END);
	json_size = ftell(json);
	fseek(json, 0, SEEK_SET);
	json_string = (char *)malloc(json_size + 1);
	memset(json_string, 0, json_size + 1);
	fread((void *)json_string, json_size, 1, json);
	fclose(json);
	json = NULL;
	cJSON *cJSON_result = cJSON_Parse(json_string)->child;
	return cJSON_result;
}

int main()
{
	int count = 0;
	char *buf = (char*)malloc(10000);
	memset(buf, 0, 10000);
	const char *file_name = "C:\\temp\\input.json";
	cJSON *temp_json = get_cjson_from_file(file_name);
	FILE *test = NULL;
	test=fopen("C:\\temp\\output.txt", "wb");
	cJSON *pointer1 = NULL;
	for(pointer1=temp_json->child;pointer1!=NULL;pointer1=pointer1->next)
	{
		double dlrate = cJSON_GetObjectItem(pointer1, "dlRate")->valuedouble;
		fprintf(test, "%18.13lf\n", dlrate);
	}
	fclose(test);
	test = NULL;
	return count;
}
