#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *strreverse(char *str) {
	char *p, *t, tmp;

	p = str;
	t = str + strlen(str) - 1;

	while (p != t) {
		tmp = *p;
		*p = *t;
		*t = tmp;

		t--; p++;
	}

	return str;
}

void gray(char *str, int size, int n, int cnt) {
	if (n == size) {
		puts(str);
		return;
	}

	if (cnt) {
		str[n] = '1';
		gray(str, size, n + 1, 0);

		str[n] = '0';
		gray(str, size, n + 1, 1);
	} else {
		str[n] = '0';
		gray(str, size, n + 1, 0);

		str[n] = '1';
		gray(str, size, n + 1, 1);
	}
}

void grayprint(int n) {
	char *str = malloc(n + 1);
	int i;

	for (i = 0; i < n; i++) {
		str[i] = '0';
	}
	str[i] = '\0';

	gray(str, n, 0 ,0);

	free(str);
}

int main(int argc, char **argv) {
	grayprint(3);

    return 0;
}
