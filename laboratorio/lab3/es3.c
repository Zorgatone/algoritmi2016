#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXREF 20
#define MAXLINE 80

char *getKeyword(char *string, char refs[MAXREF][MAXLINE + 1], int *pos);

int main(int argc, char *argv[]) {
	char refs[MAXREF][MAXLINE + 1] = {{'\0'}};

	if (argc < 4) {
		fprintf(stderr, "Usage textref.exe inputfile.txt ouputfile1.txt outputfile2.txt");

		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	FILE *fout1 = fopen(argv[2], "w");
	FILE *fout2 = fopen(argv[3], "w");

	if (!(fp && fout1 && fout2)) {
		fprintf(stderr, "Error: cannot open files.\n");

		return 1;
	}

	char LINE[MAXLINE+1] = {'\0'};
	char *p;
	int i;
	int max = -1;

	while(fgets(LINE, MAXLINE+1, fp) != NULL) {
		p = LINE;

		while(*p != '\0') {
			if (*p == '$') {
				p = getKeyword(p + 1, refs, &i);
				fprintf(fout1, "[%d]", i + 1);
				if (i > max) {
					max = i;
					fprintf(fout2, "[%d] %s\n", i + 1, refs[i]);
				}
			} else {
				fputc(*p, fout1);
				p++;
			}
		}
	}

	fclose(fp);
	fclose(fout1);
	fclose(fout2);

    return 0;
}

char *getKeyword(char *string, char refs[MAXREF][MAXLINE + 1], int *pos) {
	char buffer[MAXLINE + 1] = {'\0'};
	char *p = string, *q = buffer;
	int i;

	// Copia fino a '$' o '\0'
	while(*p != '$' && *p != '\0') {
		*(q++) = *(p++);
	}

	bool duplicate = false;

	for(i = 0; refs[i][0] != '\0'; i++) {
		if (strcmp(buffer, refs[i]) == 0) {
			duplicate = true;
			break;
		}
	}

	*pos = i;

	if (!duplicate) {
		strcpy(refs[i], buffer);
	}

	return p + 1;
}
