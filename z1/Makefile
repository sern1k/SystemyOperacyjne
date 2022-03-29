.SUFFIXES: .c .out

z1a = z1a.c
z1b = z1b.c
z1c = z1c.c
z1d = z1d.c
z1e = z1e.c

ao = z1a.out
bo = z1b.out
co = z1c.out
do = z1d.out
eo = z1e.out

CFLAGS = -Wall -std=c99 -pedantic -O
CO = gcc

all: $(z1a) $(z1b) $(z1c) $(z1d) $(z1e)
	$(CO) $(CFLAGS) $(z1a) -o $(ao)
	$(CO) $(CFLAGS) $(z1b) -o $(bo)
	$(CO) $(CFLAGS) $(z1c) -o $(co)
	$(CO) $(CFLAGS) $(z1d) -o $(do)
	$(CO) $(CFLAGS) $(z1e) -o $(eo)

z1a: $(ao)
	./$(ao)
z1b: $(bo)
	./$(bo)
z1c: $(co)
	./$(co)
z1d: $(do)
	./$(do)
z1e: $(eo)
	./$(eo)

clean:
	rm -f *.out
tar:
	cd ..; tar cvzf z1.tar.gz z1


