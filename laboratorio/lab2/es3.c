#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define MAXPOINTS 100
#define MAXLINE 12

char *progName(char path[]);

typedef struct pointpair {
	int x;
	int y1;
	int y2;
} pointpair;

void areaAndParallel(pointpair points[MAXPOINTS], int count, double* area, bool *parallel);
int compareDouble(const void *first, const void *second);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		char *pch = progName(argv[0]); // get the name of the program

		fprintf(stderr, "Usage: %s inputfile.txt", (pch) ? pch : argv[0]);

		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");

	if (!fp) {
		fprintf(stderr, "Error reading file %s.\n", argv[1]);

		exit(EXIT_FAILURE);
	}

	pointpair points[MAXPOINTS];

	for (int i = 0; i < MAXPOINTS; i++) {
		points[i].x = -1;
		points[i].y1 = -1;
		points[i].y2 = -1;
	}

	char LINE[MAXLINE] = {'\0'};
	int count; // Number of elements contained in the file

	for (count = 0; count < MAXPOINTS && fgets(LINE, MAXLINE, fp) != NULL; count++) {
		if (sscanf(LINE, "%d %d %d", &points[count].x, &points[count].y1, &points[count].y2) < 3) break;
	}

	bool parallel;
	double area;

	areaAndParallel(points, count, &area, &parallel);

	printf("The area is %.2lf.\n", area);

	printf("There is%s parallel line.\n", (parallel) ? " at least a" : "n't any");

	fclose(fp);

	return 0;
}

char *progName(char path[]) {
	char *pch = strrchr(path, '/'); // posix
	if (!pch) pch = strrchr(path, '\\'); // win32

	if (!pch) pch = path; // not found
	else ++pch; // remove slash/backslash

	char *p = strstr(pch, ".exe"); // win32

	if (p) {
		*p = '\0'; // remove .exe extension
	}

	return pch;
}

int compareDouble(const void *first, const void *second) {
	double a = *((double *) first), b = *((double *) second);

	if (a < b)
		return -1;
	else if (a > b)
		return 1;
	else
		return 0;
}

void areaAndParallel(pointpair points[MAXPOINTS], int count, double* area, bool *parallel) {
	assert(count > 1);
	assert(area != NULL);
	assert(parallel != NULL);

	*parallel = false;
	*area = 0;

	double angle[(MAXPOINTS - 1) * 2];

	for (int i = 0; i < (MAXPOINTS - 1) * 2; i++) {
		angle[i] = NAN;
	}

	int i = 0, j = 0;
	pointpair old;
	pointpair new = points[0];
	int b1, b2, h;

	do {
		old = new;
		new = points[++i];

		h = new.x - old.x;
		b1 = new.y2 - new.y1;
		b2 = old.y2 - old.y1;

		*area += (double) (b1 + b2) / 2.0F * h;

		if (new.x - old.x != 0) {
			angle[j++] = (double) (new.y1 - old.y1) / (new.x - old.x); // slope
			angle[j++] = (double) (new.y2 - old.y2) / (new.x - old.x); // slope
		} else {
			fprintf(stderr, "Errore: retta verticale.\n");

			exit(EXIT_FAILURE);
		}
	} while (i < count - 1);

	qsort((void *) angle, (size_t) (count - 1) * 2, sizeof(typeof (*angle)), compareDouble);

	for (int i = 1; i < (count - 1) * 2; i++) {
		if (abs(angle[i] - angle[i-1]) < 0.01F) {
			*parallel = true;
			//break;
		}
	}
}
