#ifndef COMMANDS_H__
#define COMMANDS_H__

#include "functions.h"

void insert_command(char *token, void **array, int *length);

void insert_at_command(char *token, void **array, int *length);

void delete_at_command(char *token, void **array, int *length);

void find_command(char *token, void *array, int lenght);

void print_command(void *array, int length);

#endif  // COMMANDS_H__
