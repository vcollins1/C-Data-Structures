CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic -std=c17
CPPFLAGS=-I./include

CUNIT_CPPFLAGS=-I/opt/homebrew/Cellar/cunit/2.1-3/include
CUNIT_LDLIBS=-L/opt/homebrew/Cellar/cunit/2.1-3/lib -lcunit

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o, $(SRC))

TARGET=main

TEST_SRC=$(wildcard test/*.c)
TEST=$(patsubst test/%.c,%, $(TEST_SRC))

.PHONY: print all clean

all: $(TARGET) $(TEST)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

main: main.c $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(OBJ)

list_test: test/list_test.c obj/list.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUNIT_CPPFLAGS) -o $@ $^ $(CUNIT_LDLIBS)

vector_test: test/vector_test.c obj/vector.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUNIT_CPPFLAGS) -o $@ $^ $(CUNIT_LDLIBS)

stack_test: test/stack_test.c $(OBJ) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUNIT_CPPFLAGS) -o $@ $^ $(CUNIT_LDLIBS)

queue_test: test/queue_test.c $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUNIT_CPPFLAGS) -o $@ $^ $(CUNIT_LDLIBS)

clean:
	rm -rf $(TARGET) $(TEST) $(OBJ) *.dSYM
