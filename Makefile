SRC := $(wildcard src/*.c)
BIN := $(patsubst src/%.c,bin/%,${SRC})
LIB := $(wildcard lib/*.c)

FLAGS := -Wall -I. -g


all: ${BIN}


bin/% : src/%.c $(LIB) Makefile | bin
	gcc ${FLAGS} $(filter %.c,$^) -o $@


bin:
	mkdir -p $@
