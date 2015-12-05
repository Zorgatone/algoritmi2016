#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define MAXLEN 20

void die(char *message);
unsigned countVocals(char *str);

int main(int argc, char *argv[]) {
	FILE *in, *out;
	char name[MAXLEN + 1];

	if (argc < 3) {
		die("Usage: programname inputfile.txt outputfile.txt");
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (!(in && out)) {
		free(in);
		free(out);

		die("Error opening files.");
	}

    while (fgets(name, MAXLEN, in) != NULL) {
		if (countVocals(name) < 3) {
			fputs(name, out);
		}
    }

	free(in);
	free(out);

	return 0;
}

void die(char *message) {
	assert(message != NULL);
	fprintf(stderr, "%s\n", message);
}

unsigned countVocals(char *str) {
	char *p = str;
	unsigned count = 0;

	assert(str != NULL);

	while (*p != '\0') {
		switch (tolower(*(p++))) {
		case 'a': case 'e': case 'i':
		case 'o': case 'u':
			count++;
		}
	}

	return count;
}
