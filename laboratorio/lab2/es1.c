#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define MAX 10

unsigned short askSize();
void readMatrix(int matrix[MAX][MAX], unsigned short size);
int ncontained(int matrix1[MAX][MAX], int matrix2[MAX][MAX], unsigned short size1, unsigned short size2);
bool mequals(int matrix1[MAX][MAX], int matrix2[MAX][MAX], unsigned short size2, unsigned short row, unsigned short col);

int main(void) {
	int matrix1[MAX][MAX] = { {0} };
	int matrix2[MAX][MAX] = { {0} };

	int n = 0;

	unsigned short size1, size2;

	printf("Insert first matrix size (MAX %d): ", MAX);
	size1 = askSize();
	readMatrix(matrix1, size1);

	printf("Insert second matrix size (MAX %d): ", MAX);
	size2 = askSize();
	while (size2 >= size1) {
		printf("Size must be < %d: ", size1);
		size2 = askSize();
	}

	readMatrix(matrix2, size2);

	n = ncontained(matrix1, matrix2, size1, size2);

	if (n > 0) {
		printf("Contained %d times.\n", n);
	} else {
		printf("Matrix2 is not contained in matrix1.\n");
	}

	return 0;
}

unsigned short askSize() {
	short size = 0;

	while (scanf("%hd", &size) < 1 || size < 1 || size > MAX) {
		printf("Invalid size.\nTry again: ");
		while(getchar() != '\n');
	}

	return size;
}

void readMatrix(int matrix[MAX][MAX], unsigned short size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("Enter matrix[%d][%d]: ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
}

bool mequals(int matrix1[MAX][MAX], int matrix2[MAX][MAX], unsigned short size2, unsigned short row, unsigned short col) {
	for (int i = 0; i < size2; i++)
		for (int j = 0; j < size2; j++)
			if (matrix1[row+i][col+j] != matrix2[i][j])
				return false;

	printf("Matrix1 equals matrix2.\n");

	return true;
}

int ncontained(int matrix1[MAX][MAX], int matrix2[MAX][MAX], unsigned short size1, unsigned short size2) {
	assert(size2 < size1);

	int num = matrix2[0][0], count = 0, k = size1 - size2 + 1;

	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			if (matrix1[i][j] == num && mequals(matrix1, matrix2, size2, i, j))
				count++;

	return count;
}
