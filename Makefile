CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpointer-arith -Wcast-align \
         -Wstrict-prototypes -Wwrite-strings -Waggregate-return \
         -Wswitch-default -Wswitch-enum -Wunreachable-code \
	 -Wunused-parameter -Wuninitialized -Winit-self -Wpedantic \
 	 -fsanitize=address -O2 -std=c11 -g

MAIN_TARGET = main.out
TEST_TARGET = test.out
MAIN_SRC = main.c lib/*.c
TEST_SRC = test/test.c lib/*.c

.PHONY: all build run clean test format bear 

all: whodoyouthinkyouareiam

whodoyouthinkyouareiam: build run

build:
	$(CC) $(CFLAGS) -o $(MAIN_TARGET) $(MAIN_SRC) 

run:
	./$(MAIN_TARGET)

test:
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) && ./$(TEST_TARGET)

clean:
	-rm -f $(MAIN_TARGET) $(TEST_TARGET) -i

format: 
	find ./ -name '*.h' -o -iname '*.c' | xargs clang-format -i --verbose

bear: clean # this is for creating the compile_commands.json file
	bear -- make build 

