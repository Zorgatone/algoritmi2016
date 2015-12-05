#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXSIZE 20
#define MAXLINE 100

#define SEPARATORS " \n"

void die(char *message);
void readMatrix(FILE *fp, int matrix[MAXSIZE][MAXSIZE], int rows, int cols);
void averageMatrix(int src[MAXSIZE][MAXSIZE], double dest[MAXSIZE][MAXSIZE], int rows, int cols);
double calcAverage(int matrix[MAXSIZE][MAXSIZE], int i, int j, int rows, int cols);

int main(int argc, char *argv[]) {
	int inmatrix[20][20] = {{0}}; // Zeroing for debug purposes
	double outmatrix[MAXSIZE][MAXSIZE] = {{0.0}}; // Zeroing for debug purposes

	int rows = 0, cols = 0;

	FILE *in = NULL;
	FILE *out = NULL;

	if (argc < 3) {
		die("Usage: programname inputfile.txt outputfile.txt");
	}

	in = fopen(argv[1], "r");

	if (in == NULL) {
		die("Error opening first file.");
	}

	out = fopen(argv[2], "w");

	if (out == NULL) {
		fclose(in);

		die("Error opening first file.");
	}

	if (fscanf(in, "%d %d", &rows, &cols) < 2 || rows > MAXSIZE || cols > MAXSIZE) {
		fclose(in);
		fclose(out);

		die("Invalid number of rows or columns.");
	}

	readMatrix(in, inmatrix, rows, cols);
	averageMatrix(inmatrix, outmatrix, rows, cols);

	fprintf(out, "%d %d\n", rows, cols);

	for(int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fprintf(out, (j == 0) ? "%.1F" : " %.1F", outmatrix[i][j]);
		}
		if (i < rows - 1)
			fputc('\n', out);
	}

	fclose(in);
	fclose(out);

	return 0;
}

double calcAverage(int matrix[MAXSIZE][MAXSIZE], int n, int m, int rows, int cols) {
	double sum = 0.0;
	unsigned count = 0;

	static const short offset[3][3][2] = {
		{
			{-1, -1}, {-1, 0}, {-1, +1}
		},
		{
			{0, -1}, {0, 0}, {0, +1}
		},
		{
			{+1, -1}, {+1, 0}, {+1, +1}
		}
	};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
            int offsetx = offset[i][j][0];
            int offsety = offset[i][j][1];

            if(offsetx == offsety && offsety == 0){
				continue;
            }

            int x = n + offsetx;
            int y = m + offsety;

            if (x >= 0 && x < rows) {
				if (y >= 0 && y < cols) {
					// (x, y) is inside the range so we can access the matrix[x][y];

					if (!(x == y && y == 0)) { // Is not in matrix[n][m];
					}
					printf("Summing number %d\n", matrix[x][y]);
					sum += (double) matrix[x][y];
					count++;
				}
            }
		}
	}

	assert(count > 0.0);
	printf("%g / %d = %.1F\n", sum, count, sum / (double) count);
	return sum / (double) count;
}

void averageMatrix(int src[MAXSIZE][MAXSIZE], double dest[MAXSIZE][MAXSIZE], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			dest[i][j] = calcAverage(src, i, j, rows, cols);
		}
	}
}

// Non-working function to debug
void readMatrix(FILE *fp, int matrix[MAXSIZE][MAXSIZE], int rows, int cols) {
	char LINE[MAXLINE + 1];
	int i = 0;

	// Assuming the parameters are valid
	assert(fp != NULL);
	assert(!feof(fp));
	assert(rows <= MAXSIZE);
	assert(cols <= MAXSIZE);

	while(i < rows && fgets(LINE, MAXLINE, fp) != NULL) {
		int j = 0;

		if (strlen(LINE) < 7) {
			continue; // Skip empty line
		}

		char *p = strtok(LINE, SEPARATORS); // Also accepts blank lines.

		if (p == NULL) {
			break; // No token found
		}

		while (j < cols && p != NULL) {
				if(matrix[i] == NULL)
					fprintf(stderr, "WTF!\n");

			assert(sscanf(p, "%d", &matrix[i][j++]) > 0); // Assuming the input file's format is correct.

			p = strtok(NULL, SEPARATORS);
		}

		i++;
	}
}

void die(char *message) {
	fprintf(stderr, "%s\n", message);

	exit(EXIT_FAILURE);
}
