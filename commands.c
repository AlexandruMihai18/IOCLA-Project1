#include <stdio.h>
#include <string.h>

#include "commands.h"

void insert_command(char *token, void **array, int *length)
{
	data_structure *new_data = read_data(token);

	if (add_last(array, length, new_data)) {
		fprintf(stderr, "add_last failed!\n");
		exit(1);
	}
}

void insert_at_command(char *token, void **array, int *length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);

	data_structure *new_data = read_data(token);

	if (add_at(array, length, new_data, index)) {
		fprintf(stderr, "add_at failed!\n");
		exit(1);
	}
}

void delete_at_command(char *token, void **array, int *length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);

	if (delete_at(array, length, index)) {
		fprintf(stderr, "delete_at failed!\n", );
		exit(1);
	}
}

void find_command(char *token, void *array, int length)
{
	token = strtok(NULL, " \n");
	int index = atoi(token);

	find(array, length, index);
}

void print_command(void *array, int length)
{
	print(array, length);
}
