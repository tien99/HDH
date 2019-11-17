#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define FILE_NAME "numbers.txt"
#define MAX_SIZE 10

mpz_t array[MAX_SIZE];
int size = 0;

void readfile() {
	FILE *file;
	char str[80];
	mpz_t temp;
	mpz_init(temp);
	file = fopen(FILE_NAME, "r");
	if (file == NULL) {
		perror("Can't open file!\n");
		exit(1);
	}
	while (1) {
		fgets(str, 80, file);
		if (feof(file)) {
			break;
		}
		if (mpz_set_str(temp, str, 10)) {
		    perror("Error! Not a number");
		    exit(1);
		}
		mpz_set(array[size++], temp);
	}
	mpz_clear(temp);
	fclose(file);
}

void count(int n) {
	int count = 0;
	mpz_t temp;
	mpz_init(temp);
	for (int i = 0; i < size; ++i) {
	    mpz_mod_ui(temp, array[i], n);
		if (!mpz_cmp_ui(temp, 0)) {
			++count;
		}
	}
	printf("Co %d so chia het cho %d.\n", count, n);
	mpz_clear(temp);
}

int main() {
	int child1_pid = 0,
	    child2_pid = 0,
	    child3_pid = 0,
	    parrent_pid = getpid();
	readfile();
	child1_pid = fork();
	if (child1_pid < 0) {
		perror("Error at 1st pork()!\n");
		exit(1);
	} else if (child1_pid == 0) {
		count(2);
	}
	if (parrent_pid == getpid()) {
		child2_pid = fork();
		if (child2_pid < 0) {
			perror("Error at 2nd pork()!\n");
			exit(1);
		} else if (child2_pid == 0) {
			count(3);
		}
	}
	if (parrent_pid == getpid()) {
		child3_pid = fork();
		if (child3_pid < 0) {
			perror("Error at 3rd pork()!\n");
			exit(1);
		} else if (child3_pid == 0) {
			count(5);
		}
	}
	return 0;
}
