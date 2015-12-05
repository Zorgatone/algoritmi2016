#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 10

int changeBase(char num[MAX], short base);
short charInt(char c);
short getBase(char *str);
bool isNum(char *str);
int intDigits(char *str);

int main() {
	short base;
	char num[MAX] = "+1204.00";
	int converted;

	if(isNum(num)) {
		base = getBase(num);

		if (base > 1) {
			converted = changeBase(num, base);
			printf("Input %s (base %d) is equal to %d in base 10.\n", num, base, converted);
		}
	}

	return 0;
}

int intDigits(char *str) {
	assert(str != NULL);
	char *p = str;
	int i = 0;

	if(*p == '-' || *p == '+')
		p++;

	while (*p != '\0') {
		if (*p++ == '.')
			break;
		i++;
	}

	return i;
}

int changeBase(char num[MAX], short fromBase) {
	assert(num != NULL);
	assert(fromBase > 1);
	int result = 0, i = intDigits(num) - 1, sign = 1;
	char *p = num;

	if (*p == '-') {
		sign = -1;
		p++;
	} else if (*p == '+') {
		p++;
	}

	while(*p != '\0') {
		if (*p == '.')
			break;
		result += charInt(*(p++)) * pow(fromBase, i--);
	}

	return result * sign;
}

short charInt(char c) {
	switch(c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		fprintf(stderr, "Invalid character: %c\n", c);
		assert(false);
	}
}

short getBase(char *str) {
	assert(str != NULL);
	short higher = -1;
	short i;
	char *p = str;

	if (*p == '-') {
		p++;
	} else if (*p == '+') {
		p++;
	}

	for (;*p != '\0'; p++) {
		if (*p == '.')
			continue;
		i = charInt(*p);

		if (i > higher) {
			higher = i;
		}
	}

	return higher + 1;
}

bool isNum(char *str) {
	assert(str != NULL);
	bool result = true, loop = true;
	unsigned countsign = 0, countperiod = 0, i = 0;

	for (char *p = str; loop; p++, i++) {
		switch(*p) {
		case '+': case '-':
			countsign++;
			loop = result = countsign < 2  && i == 0;
			break;
		case '.': case ',':
			countperiod++;
			loop = result = countperiod < 2;
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			// OK: is digit, continue the for loop
			break;
		case '\0':
			loop = false;
			break;
		default:
			// Not accepting exponentials and bases higher than 10 for simplicity
			loop = result = false;
		}
	}

	return result;
}
