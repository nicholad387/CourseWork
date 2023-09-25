CC = gcc
CFLAGS = -c -Wall

all: main.o functions.o display.o
	@echo "* Linking all objects..."
	$(CC) main.o functions.o display.o -o a.out

main.o: main.c
	@echo "* Compiling main.c..."
	$(CC) main.c $(CFLAGS)

display.o: display.c
	@echo "* Compiling display.c..."
	gcc display.c -c

functions.o: functions.c
	@echo "* Compiling functions.c..."
	gcc functions.c -c

clean:
	@echo "Cleaning up..."
	rm *.o
