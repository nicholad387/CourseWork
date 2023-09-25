# Nicholas Mohamed
# I pledge my honor that i have abided by the stevens honor pledge

CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

SRCS=insertion.c main.c utils.c
OBJS=$(SRCS:.c=.o)
HEADERS=insertion.h utils.h

TARGET=a.out

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
