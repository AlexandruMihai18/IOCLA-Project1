#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_STRING_SIZE 256
#define HEADER_SIZE 5

typedef struct head {
	unsigned char type;
	unsigned int len;
} head;

typedef struct data_structure {
	head *header;
	void *data;
} data_structure;

void *initialize_array();

data_structure *read_data(char *token);

int add_last(void **arr, int *len, data_structure *data);

int add_at(void **arr, int *len, data_structure *data, int index);

int delete_at(void **arr, int *len, int index);

void find(void *arr, int len, int index);

void print(void *arr, int len);

void *get_int8(char *token, data_structure *data, int *size);

void *get_int16(char *token, data_structure *data, int *size);

void *get_int32(char *token, data_structure *data, int *size);

void print_data(void *arr, int size);

void *initialize_array()
{
	void *array = malloc(sizeof(char));
	return array;
}

data_structure *read_data(char *token)
{
	data_structure *new_data = malloc(sizeof(data_structure));
	new_data->header = malloc(sizeof(head));

	unsigned char type;
	token = strtok(NULL, " \n");
	type = token[0];

	new_data->header->type = type;
	new_data->header->len = HEADER_SIZE;

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
			first_banknote = get_int8(token, new_data, &first_size);
			break;
		case '2':
			first_banknote = get_int16(token, new_data, &first_size);
			break;
		case '3':
			first_banknote = get_int32(token, new_data, &first_size);
			break;
		default:
			break;
	}

	token = strtok(NULL, " \n");

	switch (type) {
		case '1':
			second_banknote = get_int8(token, new_data, &second_size);
			break;
		case '2':
			second_banknote = get_int32(token, new_data, &second_size);
			break;
		case '3':
			second_banknote = get_int32(token, new_data, &second_size);
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

	free(first_name);
	free(second_name);
	free(first_banknote);
	free(second_banknote);

	return new_data;
}

void *get_int8(char *token, data_structure *data, int *size)
{
	data->header->len += sizeof(int8_t);
	(*size) = sizeof(int8_t);
	int8_t *buffer = malloc(sizeof(int8_t));
	sscanf(token, "%"SCNd8, buffer);
	return buffer;
}

void *get_int16(char *token, data_structure *data, int *size)
{
	data->header->len += sizeof(int16_t);
	(*size) = sizeof(int16_t);
	int16_t *buffer = malloc(sizeof(int16_t));
	sscanf(token, "%"SCNd16, buffer);
	return buffer;
}

void *get_int32(char *token, data_structure *data, int *size)
{
	data->header->len += sizeof(int32_t);
	(*size) = sizeof(int32_t);
	int32_t *buffer = malloc(sizeof(int32_t));
	sscanf(token, "%"SCNd32, buffer);
	return buffer;
}

int add_last(void **arr, int *len, data_structure *data)
{
	int realloc_size = data->header->len;
	int offset = 0;

	int size;

	for (int i = 0; i < *len; i++ ){
		memcpy(&size, *arr + offset + 1, sizeof(int));
		offset += size;
	}

	void *cpy_arr = realloc(*arr, offset + realloc_size);
	if (!cpy_arr)
		return 1;

	*arr = cpy_arr;
	(*len)++;

	memcpy(*arr + offset, &(data->header->type), sizeof(char));
	offset += sizeof(char);
	
	memcpy(*arr + offset, &(data->header->len), sizeof(int));
	offset += sizeof(int);

	memcpy(*arr + offset, data->data, data->header->len - HEADER_SIZE);

	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	int realloc_size = data->header->len;
	int offset1 = 0, offset2 = 0;

	int size;

	for (int i = 0; i < index; i++ ) {
		memcpy(&size, *arr + offset1 + 1, sizeof(int));
		offset1 += size;
	}

	offset2 = offset1;

	for (int i = index; i < (*len); i++) {
		memcpy(&size, *arr + offset2 + 1, sizeof(int));
		offset2 += size;
	}

	void *cpy_arr = realloc(*arr, offset2 + realloc_size);
	if (!cpy_arr)
		return 1;

	*arr = cpy_arr;
	(*len)++;

	memcpy(*arr + offset1 + realloc_size, *arr + offset1, offset2 - offset1);

	memcpy(*arr + offset1, &(data->header->type), sizeof(char));
	offset1 += sizeof(char);
	
	memcpy(*arr + offset1, &(data->header->len), sizeof(int));
	offset1 += sizeof(int);

	memcpy(*arr + offset1, data->data, data->header->len - HEADER_SIZE);

	return 0;
}

int delete_at(void **arr, int *len, int index)
{
	int realloc_size;
	int offset1 = 0, offset2 = 0;

	int size;

	for (int i = 0; i < index; i++ ) {
		memcpy(&size, *arr + offset1 + 1, sizeof(int));
		offset1 += size;
	}

	memcpy(&realloc_size, *arr + offset1 + 1, sizeof(int));

	offset2 = offset1;

	for (int i = index; i < (*len); i++) {
		memcpy(&size, *arr + offset2 + 1, sizeof(int));
		offset2 += size;
	}

	memcpy(*arr + offset1, *arr + offset1 + realloc_size, offset2 - offset1 - realloc_size);

	void *cpy_arr = realloc(*arr, offset2 - realloc_size);
	if (!cpy_arr)
		return 1;

	*arr = cpy_arr;
	(*len)--;

	return 0;
}

void find(void *arr, int len, int index)
{
	int size, offset = 0;
	for (int i = 0; i < index; i++) {
		memcpy(&size, arr + offset + 1, sizeof(int));
		offset += size;
	}

	int struct_size;
	memcpy(&struct_size, arr + offset +1, sizeof(int));

	print_data(arr + offset, struct_size);
}

void print(void *arr, int len)
{
	int size, offset = 0;
	for (int i = 0; i < len; i++) {
		memcpy(&size, arr + offset + 1, sizeof(int));
		print_data(arr + offset, size);
		offset += size;
	}
}

void *find_word(void *arr)
{
	while (*(char *)arr != '\0')
		arr++;
	return ++arr;
}

void print_data(void *arr, int size)
{
	data_structure *new_data = malloc(sizeof(data_structure));
	new_data->header = malloc(sizeof(head));
	new_data->data = malloc(size - HEADER_SIZE);

	memcpy(&(new_data->header->type), arr, sizeof(char));
	memcpy(&(new_data->header->len), arr + 1, sizeof(int));
	memcpy(new_data->data, arr + HEADER_SIZE, size - HEADER_SIZE);

	printf("Tipul %c\n", new_data->header->type);

	void *token = find_word(new_data->data);
	char *first_name = (char *)new_data->data;

	int offset = 0;
	void *first_banknote, *second_banknote;
	int first_size, second_size;

	switch (new_data->header->type) {
		case '1':
			first_size = sizeof(int8_t);
			second_size = sizeof(int8_t);
			break;
		case '2':
			first_size = sizeof(int16_t);
			second_size = sizeof(int32_t);
			break;
		case '3':
			first_size = sizeof(int32_t);
			second_size = sizeof(int32_t);
			break;
		default:
			break;
	}

	first_banknote = malloc(first_size);
	second_banknote = malloc(second_size);

	memcpy(first_banknote, token + offset, first_size);
	offset += first_size;
	memcpy(second_banknote, token + offset, second_size);
	offset += second_size;

	char *second_name = token + offset;

	printf("%s pentru %s\n", first_name, second_name);

	switch (new_data->header->type) {
		case '1':
			printf("%"PRIi8"\n%"PRIi8"\n", *(int8_t *)first_banknote, *(int8_t *)second_banknote);
			break;
		case '2':
			printf("%"PRIi16"\n%"PRIi32"\n", *(int16_t *)first_banknote, *(int32_t *)second_banknote);
			break;
		case '3':
			printf("%"PRIi32"\n%"PRIi32"\n", *(int32_t *)first_banknote, *(int32_t *)second_banknote);
			break;
		default:
			break;
	}
	printf("\n");

	free(first_banknote);
	free(second_banknote);
	
	free(new_data->data);
	free(new_data->header);
	free(new_data);
}

void insert_command(char *token, void **array, int *length);

void insert_at_command(char *token, void **array, int *length);

void delete_at_command(char *token, void **array, int *length);

void find_command(char *token, void *array, int lenght);

void print_command(void *array, int length);

void insert_command(char *token, void **array, int *length)
{
	data_structure *new_data = read_data(token);

	if (add_last(array, length, new_data)) {
		fprintf(stderr, "add_last failed!\n");
		exit(1);
	}

	free(new_data->header);
	free(new_data->data);
	free(new_data);
}

void insert_at_command(char *token, void **array, int *length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);

	if (index > *length)
		index = *length;

	data_structure *new_data = read_data(token);

	if (index < 0) {
		fprintf(stderr, "Index out of bounds!\n");
	} else if (add_at(array, length, new_data, index)) {
		fprintf(stderr, "add_at failed!\n");
	}

	free(new_data->header);
	free(new_data->data);
	free(new_data);
}

void delete_at_command(char *token, void **array, int *length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);
	if (index < 0 || index > *length) {
		fprintf(stderr, "Index out of bounds!\n");
	} else if (delete_at(array, length, index)) {
		fprintf(stderr, "delete_at failed!\n");
	}
}

void find_command(char *token, void *array, int length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);

	if (index < 0 || index > length)
		return;

	find(array, length, index);
}

void print_command(void *array, int length)
{
	print(array, length);
}

int main(void){
	void *array = NULL;
	int length = 0;

	char command[MAX_STRING_SIZE];
	char *token;

	while (1) {
		fgets(command, MAX_STRING_SIZE, stdin);
		token = strtok(command, " \n");

		if (strcmp(token, "insert") == 0) {
			insert_command(token, &array, &length);
		} else if (strcmp(token, "insert_at") == 0) {
			insert_at_command(token, &array, &length);
		} else if (strcmp(token, "delete_at") == 0) {
			delete_at_command(token, &array, &length);
		} else if (strcmp(token, "find") == 0) {
			find_command(token, array, length);
		} else if (strcmp(token, "print") == 0) {
			print_command(array, length);
		} else if (strcmp(token, "exit") == 0) {
			free(array);
			break;
		}
	}

	return 0;
}
