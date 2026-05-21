CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -ffreestanding -O2 -fno-strict-aliasing

ARCH_NAME := generic
OS_NAME   := generic

ifeq ($(OS),Windows_NT)
	OS_NAME := windows
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		ARCH_NAME := x86_64
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		ARCH_NAME := x86_64
	ifeq ($(PROCESSOR_ARCHITECTURE),ARM64)
		ARCH_NAME := AArch64
	endif
else
	UNAME_S := $(shell uname -s)
	UNAME_M := $(shell uname -m)

	ifeq ($(UNAME_S),Linux)
		OS_NAME := linux
	else ifeq ($(UNAME_S),Darwin)
		OS_NAME := macos
	endif

	ifeq ($(UNAME_M),x86_64)
		ARCH_NAME := x86_64
	ifeq ($(UNAME_M),arm64)
		ARCH_NAME := AArch64
	ifeq ($(UNAME_M),aarch64)
		ARCH_NAME := AArch64
	endif
endif

INCLUDE_FLAGS := -Iinclude \
				 -Iarch/$(ARCH_NAME)/$(OS_NAME) \
				 -Iarch/$(ARCH_NAME)/common

CFLAGS += $(INCLUDE_FLAGS)

SRC_C   := $(wildcard src/**/*.c)
SRC_ASM := $(wildcard arch/$(ARCH_NAME)/$(OS_NAME)/**/*.S)

OBJ := $(SRC_C:.c=.o) $(SRC_ASM:.S=.o)
TARGET := libtartarus.a

all: $(TARGET)

$(TARGET): $(OBJ)
		ar rcs $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ) $(TARGET)

.PHONY: all clean

##### !!! ONLY TESTWISE - NOT FINAL !!! ######
