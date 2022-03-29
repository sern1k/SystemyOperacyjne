.SUFFIXES: .c .out

CFLAGS = -Wall -std=c99 -pedantic
CC = gcc

main.out: main.c
	$(CC) $(CFLAGS) main.c -o main.out

wypisywanie.out: wypisywanie.c
	$(CC) $(CFLAGS) wypisywanie.c -o wypisywanie.out


.PHONY: run clean tar

run: main.out wypisywanie.out
	./main.out ./wypisywanie.out

clean:
	rm -f *.out

tar: clean
	cd ..; tar cvzf zad2.tar.gz zad2
