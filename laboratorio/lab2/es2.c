#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MIN 3

int main(int argc, char *argv[]) {
	if (argc < 3) {
		char *pch = strrchr(argv[0], '/');
		if (!pch) pch = strrchr(argv[0], '\\');

		fprintf(stderr, "Usage: %s inputfile.txt outputfile.txt\n", pch ? argv[0] : ++pch);

		exit(EXIT_FAILURE);
	}

	FILE *fin = fopen(argv[1], "r"), *fout = fopen(argv[2], "w");

	if (!(fin && fout)) {
		fprintf(stderr, "Error opening files.\n");

		fclose(fin); fclose(fout);
		exit(EXIT_FAILURE);
	}

	char new = '\0', old;
	unsigned count;

	while(!feof(fin)) {
		count = 0;
		do {
			old = new;
			new = fgetc(fin);

			count++;
		} while (new == old);

		if (old != '\0') {
			if (count >= MIN && isalnum(old)) fprintf(fout, "$%u$%c", count, old);
			else if(count > 0) for(int i = 0; i < count; i++) fputc(old, fout);
			else fputc(old, fout);
		}
	}

	printf("Hello, World!\n");

	fclose(fin); fclose(fout);
	return 0;
}
