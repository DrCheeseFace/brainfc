#ifndef TAPE_H
#define TAPE_H

extern const int MAX_TAPE_DATA_LENGTH;

typedef void Tape;

Tape *T_tape_create(int);
void t_tape_destroy(Tape *);
int t_data_length(const Tape *);

void t_print_info(Tape *);

void t_data_idx_increment(Tape *);
void t_data_idx_decrement(Tape *);
void t_data_minus(Tape *);
void t_data_plus(Tape *);
void t_set_data_idx(Tape *, int);

int t_read_data_at(Tape *, int);

#endif
