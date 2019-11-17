#include "gmp.h"
#include "factorial.h"
#include <stdio.h>
#include <stdlib.h>

char *factorial(const int aNumber) {
	int i;
	mpz_t p;
	mpz_init_set_ui(p, 1);
	for (int i = 1; i <= aNumber; ++i) {
	    mpz_mul_ui(p, p, i);
	}
	char * ret = mpz_get_str(NULL, 10, p);
	mpz_clear(p);
	return ret;
}
