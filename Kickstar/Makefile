TARGET  = train
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
LIBS =
TESTFILES = $(shell ls ./inputs)
CC = gcc
DBG = gdb
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g

.PHONY: clean

all: $(TARGET)

test: $(TARGET) $(TESTFILES)

debug:
	$(DBG) $(TARGET)

%.in:
	-./$(TARGET) ./inputs/$*.in


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)