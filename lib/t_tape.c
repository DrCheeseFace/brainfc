#include "logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAPE_DATA_LENGTH 8
#define INT_MAX 256

typedef struct {
	int data_len;
	int data_idx;
	int data[MAX_TAPE_DATA_LENGTH];

	int instruction_len;
	int instruction_idx;
	char *instructions;
} Tape;

Tape *T_tape_create(int data_length) {
	Tape *tape = malloc(sizeof(Tape));

	tape->data_len = data_length;
	tape->data_idx = 0;
	memset(tape->data, 0, MAX_TAPE_DATA_LENGTH * sizeof(*tape->data));

	tape->instruction_len = 0;
	tape->instruction_idx = 0;

	tape->instructions = NULL;

	return tape;
}

void t_tape_destroy(Tape *tape) {
	if (tape == NULL) {
		LOG_ERROR("passed tape pointer is null");
		return;
	}
	free(tape);
}

int t_data_length(const Tape *tape) {
	return tape->data_len;
}

void t_set_data_idx(Tape *tape, int pointer_index) {
	if (pointer_index > tape->data_len) {
		LOG_ERROR("pointer out of bounds");
		return;
	}
	tape->data_idx = pointer_index;
}

void t_data_idx_increment(Tape *tape) {
	if (tape->data_idx == tape->data_len) {
		LOG_ERROR("pointer out of bounds");
		return;
	}
	tape->data_idx++;
}

void t_data_idx_decrement(Tape *tape) {
	if (tape->data_idx == 0) {
		LOG_ERROR("pointer out of bounds");
		return;
	}
	tape->data_idx--;
}

void t_data_plus(Tape *tape) {
	if (tape->data[tape->data_idx] == INT_MAX) {
		LOG_ERROR("byte overflow");
		return;
	}
	tape->data[tape->data_idx]++;
}

void t_data_minus(Tape *tape) {
	if (tape->data[tape->data_idx] == 0) {
		LOG_ERROR("byte underflow");
		return;
	}
	tape->data[tape->data_idx]--;
}

int t_read_data_at(Tape *tape, int idx) {
	if (idx >= tape->data_len) {
		LOG_ERROR("index out of bounds");
		return 0;
	}
	return tape->data[idx];
}

void t_print_info(Tape *tape) {
	printf("tape: length %d\n", tape->data_len);
	printf("pointer pos: %d\n", tape->data_idx);
	printf("data [");
	for (int i = 0; i < tape->data_len; i++) {
		printf("%d,", tape->data[i]);
	}
	printf("]\n\n");
}
