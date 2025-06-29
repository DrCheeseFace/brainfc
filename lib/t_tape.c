#include "logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAPE_DATA_LENGTH 1024
#define MAX_SCOPE_DEPTH 255

typedef struct {
	int data_len;
	int data_idx;
	int data[MAX_TAPE_DATA_LENGTH];
	int instruction_len;
	int instruction_idx;
	int scope_len;
	int scope_stack[MAX_SCOPE_DEPTH];
	const char *instructions;
} Tape;

Tape *T_tape_create(int data_length) {
	Tape *tape = malloc(sizeof(Tape));

	tape->data_len = data_length;
	tape->data_idx = 0;
	memset(tape->data, 0, MAX_TAPE_DATA_LENGTH * sizeof(*tape->data));

	tape->instruction_len = 0;
	tape->instruction_idx = 0;

	tape->scope_len = 0;
	memset(tape->scope_stack, -1, MAX_SCOPE_DEPTH * sizeof(*tape->scope_stack));

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

void t_tape_init_instructions(Tape *tape, const char *instructions, int length) {
	if (instructions == NULL) {
		LOG_ERROR("passed instructions pointer is null");
		return;
	}
	tape->instructions = instructions;
	tape->instruction_len = length;
	tape->instruction_idx = 0;
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

void t_scope_push(Tape *tape) {
	tape->scope_stack[tape->scope_len] = tape->instruction_idx;
	tape->scope_len++;
}

int t_scope_pop(Tape *tape) {
	int instruction_idx = tape->scope_stack[tape->scope_len - 1];
	tape->scope_stack[tape->scope_len - 1] = -1;
	tape->scope_len--;
	return instruction_idx;
}

int t_scope_matching_close(Tape *tape, int instruction_idx) {
	int depth = 0;
	for (int i = instruction_idx + 1; i < tape->instruction_len; i++) {
		if (tape->instructions[i] == ']') {
			if (depth == 0) {
				return i;
			} else {
				depth--;
			}
		} else if (tape->instructions[i] == '[') {
			depth++;
		}
	}
	LOG_ERROR("maching closing scope not found");
	return -1;
}

int t_read_data_at(Tape *tape, int idx) {
	if (idx >= tape->data_len) {
		LOG_ERROR("index out of bounds");
		return 0;
	}
	return tape->data[idx];
}

int t_step(Tape *tape) {
	uint8_t buf;
	//breakpoint
	switch (tape->instructions[tape->instruction_idx]) {
	case '\0':
		return 0;
	case '>':
		if (tape->data_idx == tape->data_len) {
			LOG_ERROR("pointer out of bounds");
			break;
		}
		tape->data_idx++;
		break;
	case '<':
		if (tape->data_idx == 0) {
			LOG_ERROR("pointer out of bounds");
			break;
		}
		tape->data_idx--;
		break;
	case '+':
		tape->data[tape->data_idx]++;
		break;
	case '-':
		tape->data[tape->data_idx]--;
		break;
	case '[':
		if (tape->data[tape->data_idx]) {
			tape->instruction_idx = t_scope_matching_close(tape, tape->instruction_idx);
		} else {
			t_scope_push(tape);
		}
		break;
	case ']':
		if (tape->data[tape->data_idx] != 0) {
			tape->instruction_idx = t_scope_pop(tape);
		}
		break;
	case '.':
		printf("char: %c\n", tape->data[tape->data_idx] + 104);
		break;
	case ',':
		scanf("%c", &buf);
		printf("%c", buf);
		break;
	default:
		LOG_ERROR("unhandled instruction")
		break;
	}
	tape->instruction_idx++;
	return 1;
}

void t_print_info(Tape *tape) {
	printf("tape: length %d\n", tape->data_len);
	printf("pointer pos: %d\n", tape->data_idx);
	printf("data [");
	for (int i = 0; i < tape->data_len; i++) {
		printf("%d,", tape->data[i]);
	}
	printf("]\n");
	printf("instructions [");
	for (int i = 0; i < tape->instruction_len; i++) {
		printf("%c", tape->instructions[i]);
	}
	printf("]\n\n");
}
