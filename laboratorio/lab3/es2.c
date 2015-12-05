#include <stdio.h>
#include <stdlib.h>

#define N 3

// This is the function I'm asked to implement
void mul(int *v1, int *v2, int n, int *v3);

int main(void) {
	// Example 32 x 243 = 7776;
	int v1[N] = {0, 3, 2};
	int v2[N] = {2, 4, 3};
	int v3[2 * N] = {0};

	mul(v1, v2, N, v3);

	int i;

	for (i = 0; i < 2 * N; i++)
		if (v3[i] != 0)
			break;

	printf("The result is: ");
    for (; i < 2 * N; i++)
		printf("%d", v3[i]);

    putchar('\n');

    return 0;
}

void mul(int *v1, int *v2, int n, int *v3) {
	// Pointer to last element of the result array
	int *vdue = v2 + n - 1, i = 1;

	// Initialize the v3 number array
	for (int i = 0; i < 2 * n; i++) {
		v3[i] = 0;
	}

	// Loop until multiplied all the digits of v2
	while (vdue >= v2) {
		int *vuno = v1 + n - 1;
		int *vtre = v3 + 2 * n - (i++); // Skip each time one more right digit

		int remain = 0;

		// Loop for each digit of v1 from right
		while (vuno >= v1) {
			*vtre += ((*vdue) * (*vuno)) + remain;

			remain = *vtre / 10; // Integer division
			*vtre = *vtre % 10; // Keep 1 digit

			vuno--;
			vtre--;
		}

		vdue--;
	}
}
