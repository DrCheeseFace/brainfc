#include "lib/t_tape.h"
#include <string.h>

int main(void) {
	char instructions[] =
		"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
	// char instructions[] = "+++++[-]";
	void *tape_handle = T_tape_create(512);
	t_tape_init_instructions(tape_handle, instructions, strlen(instructions));
	t_print_info(tape_handle);
	while (t_step(tape_handle)) {
		continue;
	}
	t_tape_destroy(tape_handle);
	return 0;
}
