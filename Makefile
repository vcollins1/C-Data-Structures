CC=gcc
CFLAGS=-g -Wall -Wextra -Wpedantic -std=c17
CPPFLAGS=-I./include

CUNIT_CPPFLAGS := -I/opt/homebrew/Cellar/cunit/2.1-3/include
CUNIT_LDLIBS := -L/opt/homebrew/Cellar/cunit/2.1-3/lib -lcunit

SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c,obj/%.o, $(SRC))

TARGET=main
TARGET_SRC=main.c

TEST := list_test
TEST_SRC := $(wildcard test/*.c)

.PHONY: print all clean

all: $(TARGET) $(TEST)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(TARGET_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(OBJ)

$(TEST): $(TEST_SRC) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CUNIT_CPPFLAGS) -o $@ $< $(OBJ) $(CUNIT_LDLIBS)

clean:
	rm -rf $(TARGET) $(TEST) $(OBJ) *.dSYM

print:
	@echo $(SRC)
	@echo $(OBJ)
