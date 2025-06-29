#ifndef TAPE_H
#define TAPE_H

#include <stdint.h>
extern const int MAX_TAPE_DATA_LENGTH;

typedef struct {
	int data_len;
	int data_idx;
	int *data;
	int instruction_len;
	int instruction_idx;
	char *instructions;
} Tape;

Tape *T_tape_create(int);
void t_tape_destroy(Tape *);
int t_data_length(const Tape *);
int t_read_data_at(Tape *, int);
void t_tape_init_instructions(Tape *, const char *, int);
void t_print_info(Tape *);
int t_step(Tape *);

// unpub me later
void t_data_idx_increment(Tape *);
void t_data_idx_decrement(Tape *);
void t_data_minus(Tape *);
void t_data_plus(Tape *);
void t_set_data_idx(Tape *, int);

#endif
