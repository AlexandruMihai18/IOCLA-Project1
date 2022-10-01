#ifndef FUNCTIONS_H__
#define FUNCTIONS_H__

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

data_structure *get_type_1(char *token);

int add_last(void **arr, int *len, data_structure *data);

int add_at(void **arr, int *len, data_structure *data, int index);

int delete_at(void **arr, int *len, int index);

void find(void *arr, int len, int index);

void print(void *arr, int len);

void get_int8(void *banknote, char *token, data_structure *data, int *size);

void get_int16(void *banknote, char *token, data_structure *data, int *size);

void get_int32(void *banknote, char *token, data_structure *data, int *size);

#endif  // FUNCTIONS_H__
