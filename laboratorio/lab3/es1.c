#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAXSIZE 10

// MACRO con parametri
#define CONTAINED(x, y, size) (x >= 0 && y >= 0 && x < size && y < size)

short readMatrix(FILE *fp, int matrix[MAXSIZE][MAXSIZE]);
int calcSum(int matrix[MAXSIZE][MAXSIZE], int size, int row, int col);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: alfiere.exe inputfile.txt\n");

		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if (!fp) {
		fprintf(stderr, "Error: cannot open file %s\n", argv[1]);

		return 1;
	}

	int scacchiera[MAXSIZE][MAXSIZE];

	int size = readMatrix(fp, scacchiera);
	fclose(fp);

	// C99
	int max = 0;
	int posx = 0, posy = 0;
	bool found = false;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (scacchiera[i][j] == 0) {
				found = true;
				int tmp = calcSum(scacchiera, size, i, j);

				if(tmp > max) {
					max = tmp;
					posx = i;
					posy = j;
				}
			}
		}
	}

	if (found) {
		printf("Maximum is %d, at position (%d, %d).\n", max, posx + 1, posy + 1);
	} else {
		printf("Not found free position.\n");
	}

    return 0;
}

short readMatrix(FILE *fp, int matrix[MAXSIZE][MAXSIZE]) {
	short size;

	assert(fp != NULL);

	if (fscanf(fp, "%hd", &size) != 1) {
		fprintf(stderr, "Error: size not specified.");

		exit(1);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if(fscanf(fp, "%d", &matrix[i][j]) != 1)
				break;
		}
	}

	return size;
}

int calcSum(int matrix[MAXSIZE][MAXSIZE], int size, int row, int col) {
	int sum = 0;

	int offset[2][2][2] = {
		{ {-1, -1}, {-1, +1} },
		{ {+1, -1}, {+1, +1} }
	};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int posx = row, posy = col; CONTAINED(posx, posy, size); posx += offset[i][j][0], posy += offset[i][j][1]) {
				sum += matrix[posx][posy];
			}
		}
	}

	return sum;
}
