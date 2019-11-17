all: ex1.o ex2.o
	gcc ex1.o -o ex1 -lgmp
	gcc ex2.o -o ex2
ex1.o: ex1.c
	gcc -c ex1.c
ex2.o: ex2.c
	gcc -c ex2.c
clean:
	rm -f *.o ex1 ex2
