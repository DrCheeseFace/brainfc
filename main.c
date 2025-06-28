#include "lib/t_tape.h"

int main(void) {
	void *tape_handle = T_tape_create(8);
	t_print_info(tape_handle);
	t_data_idx_increment(tape_handle);
	t_data_idx_decrement(tape_handle);
	t_data_plus(tape_handle);
	t_data_minus(tape_handle);
	t_tape_destroy(tape_handle);
	return 0;
}
