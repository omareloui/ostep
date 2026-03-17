CC = gcc
CFLAGS = -Wall -Werror -pthread

SRCS = $(shell find . -name '*.c')
BINS = $(patsubst ./%.c, build/%, $(SRCS))

all: $(BINS)

build/%: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf build

.PHONY: all clean
