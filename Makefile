all: farewell
	@./farewell

farewell: farewell.o
	@gcc -o farewell farewell.o -lm

farewell.o: farewell.c
	@gcc -O2 -c farewell.c

clean:
	@rm -f farewell farewell.o

.PHONY: all clean

