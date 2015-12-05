#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For uint64_t
#include <inttypes.h> // For PRIu64
#include <math.h>

#define factorial(n) fact(n, 1)

static inline uint64_t fact(uint8_t n, uint64_t inc);
static inline uint64_t binomial(uint8_t n, uint8_t k);
static inline uint64_t bell(uint8_t n);

int main(int argc, char **argv) {
	printf("Bell: %" PRIu64 ".\n", bell(21));

    return EXIT_SUCCESS;
}

static inline uint64_t fact(uint8_t n, uint64_t inc) {
	return (n == 0) ? inc : fact(n - 1, inc * (uint64_t)n);
}

static inline uint64_t binomial(uint8_t n, uint8_t k) {
	return factorial(n) / (factorial(k) * factorial(n - k));
}

// can calculate up to bell(21)
static inline uint64_t bell(uint8_t N) {
	if (N == 0) {
		return 1;
	}

	uint8_t i, n = N - 1;
	uint64_t sum = 0;

	for (i = 0; i <= n; i++) {
		sum += binomial(n, i) * bell(i);
	}

	return sum;
}
