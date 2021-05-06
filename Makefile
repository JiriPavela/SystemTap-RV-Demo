CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -g
SRCS = $(wildcard sources/*.c)
TARGETS = $(patsubst sources/%.c,%,$(SRCS))

CPP = g++
CPPFLAGS = -std=c++11 -Wall -Wextra -pedantic -g


all: $(TARGETS) resource_allocation

%: sources/%.c
	$(CC) $(CFLAGS) $< -o $@

resource_allocation: sources/resource_allocation.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	rm $(TARGETS) resource_allocation


