CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -ffreestanding -I- -Iinclude -O2 -fno-strict-aliasing

%.o: %.c
		clang $(CFLAGS) -c $< -o $@

##### !!! ONLY TESTWISE - NOT FINAL !!! ######
