#include <stdio.h>
#include <stdlib.h>

int **alloca2d(int r, int c);
void alloc_2d(int ***matrix, int r, int c);
void free2d(int **matrix, int r);

int sommadiag(int **matrix, int r, int c, int anti);

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: program inputfile.txt\n");

		return EXIT_FAILURE;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		fprintf(stderr, "Cannot open file %s.\n", argv[1]);

		return EXIT_FAILURE;
	}

	int r, c, i, j;

	if(fscanf(fp, "%d %d", &r, &c) < 2) {
		fprintf(stderr, "Error reading the matrix dimensions.\n");

		return EXIT_FAILURE;
	}

	int **matrix;

	alloc_2d(&matrix, r, c);

	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			if (fscanf(fp, "%d", &matrix[i][j]) < 1) {
				fprintf(stderr, "Error reading matrix elements.\n");

				return EXIT_FAILURE;
			}

			printf("%02d ", matrix[i][j]);
		}

		putchar('\n');
	}

	int s1, s2;

	s1 = sommadiag(matrix, r, c, 0);
	s2 = sommadiag(matrix, r, c, 1);

	printf("Somma diagonale: %d.\n Somma antidiagonale: %d.\n", s1, s2);

	free2d(matrix, r);

    return EXIT_SUCCESS;
}

int **alloca2d(int r, int c) {
	int **matrix = malloc(sizeof(int) * r);
	int i;

	if (matrix == NULL) {
		fprintf(stderr, "Out of memory.\n");

		exit(EXIT_FAILURE);
	}

	for (i = 0; i < r; i++) {
		matrix[i] = malloc(sizeof(int) * c);

		if (matrix[i] == NULL) {
			fprintf(stderr, "Out of memory.\n");

			exit(EXIT_FAILURE);
		}
	}

	return matrix;
}

void alloc_2d(int ***matrix, int r, int c) {
	*matrix = malloc(sizeof(int) * r);
	int i;

	if (*matrix == NULL) {
		fprintf(stderr, "Out of memory.\n");

		exit(EXIT_FAILURE);
	}

	for (i = 0; i < r; i++) {
		(*matrix)[i] = malloc(sizeof(int) * c);

		if ((*matrix)[i] == NULL) {
			fprintf(stderr, "Out of memory.\n");

			exit(EXIT_FAILURE);
		}
	}
}

void free2d(int **matrix, int r) {
	int i;

	if (matrix == NULL)
		return;

	for (i = 0; i < r; i++) {
		free(matrix[i]);
	}

	free(matrix);
}

int sommadiag(int **matrix, int r, int c, int anti) {
	if (matrix == NULL)
		return 0;

	int somma = 0, i;

	if (anti) {
		for (i = 0; i < r && i < c; i++) {
			somma += matrix[i][c - i - 1];
		}
	} else {
		for (i = 0; i < r && i < c; i++) {
			somma += matrix[i][i];
		}
	}

	return somma;
}
