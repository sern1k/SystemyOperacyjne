CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

z3a.out: z3a.c
	$(CC) $(CFLAGS) z3a.c -o z3a.out
z3b.out: z3b.c
	$(CC) $(CFLAGS) z3b.c -o z3b.out
z3c.out: z3c.c
	$(CC) $(CFLAGS) z3c.c -o z3c.out
z3c2.out: z3c2.c
	$(CC) $(CFLAGS) z3c2.c -o z3c2.out

.PHONY: runA runB runC clean tar

runA: z3a.out
	clear
	./z3a.out $(SYGNAL) $(OPCJA)
runB: z3b.out $(PROG3A)
	clear
	./z3b.out $(SYGNAL) $(OPCJA) $(PROG3A)
runC: z3c.out $(PROG3A) $(PROG3C2)
	clear
	./z3c.out $(SYGNAL) $(OPCJA) $(PROG3C2) $(PROG3A)

clean:
	clear
	rm -f *.out
tar: clean
	clear
	cd ..; tar cvzf z3.tar.gz z3
