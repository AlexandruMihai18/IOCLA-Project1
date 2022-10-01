#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void *initiliaze_array()
{
	void *array = malloc(sizeof(char));
	return array;
}

data_structure *read_data(char *token)
{
	data_structure *new_data = malloc(sizeof(data_structure));
	new_data->header = malloc(sizeof(header));

	unsigned char type;
	token = strtok(NULL, " \n");
	type = (unsigned char)(atoi(token));

	new_data->header->type = type;
	new_data->header->len = 0;

	char *first_name, *second_name;
	void *first_banknote, *second_banknote;
	int first_size, second_size;

	token = strtok(NULL, " \n");
	first_name = malloc(strlen(token) + 1);
	memcpy(first_name, token, strlen(token) + 1);
	new_data->header->len += strlen(token) + 1;

	token = strtok(NULL, " \n");

	switch (type) {
		case '1':
			get_int8(first_banknote, token, new_data, &first_size);
			break;
		case '2':
			get_int16(first_banknote, token, new_data, &first_size);
			break;
		case '3':
			get_int32(first_banknote, token, new_data, &first_size);
			break;
		default:
			break;
	}

	token = strtok(NULL, " \n");

	switch (type) {
		case '1':
			get_int8(second_banknote, token, new_data, &second_size);
			break;
		case '2':
			get_int16(second_banknote, token, new_data, &second_size);
			break;
		case '3':
			get_int32(second_banknote, token, new_data, &second_size);
			break;
		default:
			break;
	}

	token = strtok(NULL, " \n");
	second_name = malloc(strlen(token) + 1);
	memcpy(second_name, token, strlen(token) + 1);
	new_data->header->len += strlen(token) + 1;

	new_data->data = malloc(new_data->header->len);
	int offset = 0;

	memcpy(new_data->data + offset, first_name, strlen(first_name) + 1);
	offset += strlen(first_name) + 1;

	memcpy(new_data->data + offset, first_banknote, first_size);
	offset += first_size;

	memcpy(new_data->data + offset, second_banknote, second_size);
	offset += second_size;

	memcpy(new_data->data + offset, second_name, strlen(second_name) + 1);

	return new_data;
}

void get_int8(void *banknote, char *token, data_structure *data, int *size)
{
	int8_t buffer = (int8_t)(atoi(token));
	data->header->len += sizeof(int8_t);
	(*size) = sizeof(int);
	memcpy(banknote, &buffer, (*size));
}

void get_int16(void *banknote, char *token, data_structure *data, int *size)
{
	int8_t buffer = (int16_t)(atoi(token));
	data->header->len += sizeof(int16_t);
	(*size) = sizeof(int);
	memcpy(banknote, &buffer, (*size));
}

void get_int32(void *banknote, char *token, data_structure *data, int *size)
{
	int8_t buffer = (int32_t)(atoi(token));
	data->header->len += sizeof(int32_t);
	(*size) = sizeof(int);
	memcpy(banknote, &buffer, (*size));
}
