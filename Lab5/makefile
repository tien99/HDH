all: pi_serial.o pi_multi-thread.o code.o
	gcc -o pi_serial pi_serial.o
	gcc -o pi_multi-thread pi_multi-thread.o -lpthread
	gcc -o code code.o -lpthread
pi: pi_serial.o pi_multi-thread.o
	gcc -o pi_serial pi_serial.o
	gcc -o pi_multi-thread pi_multi-thread.o -lpthread
pi_serial: pi_serial.o
	gcc -o pi_serial pi_serial.o
pi_multi-thread: pi_multi-thread.o
	gcc -o pi_multi-thread pi_multi-thread.o -lpthread
code: code.o
	gcc -o code code.o -lpthread
pi_serial.o: pi_serial.c
	gcc -c pi_serial.c
pi_multi-thread.o: pi_multi-thread.c
	gcc -c pi_multi-thread.c
code.o: code.c
	gcc -c code.c
clean:
	rm -rf *.o pi_serial pi_multi-thread code
