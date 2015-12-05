#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAXS 20
#define N 4

typedef struct item_s {
	int a, b;
	char c;
	float d;
	char s[MAXS];
} Item;

int main(void) {
	char *file = "input.txt";
	Item M[N][N];
	int i, j, k;

	// Initialize all to zero.
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			Item *it = &M[i][j];

			it->a = 0;
			it->b = 0;
			it->c = '\0';
			it->d = 0.0;

			for (k = 0; k < MAXS; k++) {
				it->s[k] = '\0';
			}
		}
	}

	FILE *fp;

	assert(fp = fopen(file, "r"));

	bool loop = true;

	for (i = 0; loop && i < N; i++) {
		for (j = 0; loop && j < N; j++) {
			Item *it = &M[i][j];

			if (fscanf(fp, "%d %d %c %f %s",
					&it->a, &it->b, &it->c,
					&it->d, it->s) != 5) {
				loop = false;
			}
		}
	}

	fclose(fp);

	int one, two;

	printf("Insert two integers (max %d): ", N);
	if (scanf("%d %d", &one, &two) == 2 &&
		one >= 0 && two >= 0 && one < N && two < N) {
		Item it = M[one][two];
		printf("%d %d %c %f %s\n", it.a, it.b, it.c, it.d, it.s);
		printf("%p %p %p %p %p\n", &it.a, &it.b, &it.c, &it.d, &it.s);
	}

    return 0;
}
