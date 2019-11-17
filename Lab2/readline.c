#include "readline.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int read_line(char *str) {
	fgets(str, 51, stdin);
	fputs(str, stdout);
	int i = 0;
	while (str[i] != '\n') {
		if (!isdigit(str[i])) {
			return 0;
		}
		++i;
	}
	return 1;
}
