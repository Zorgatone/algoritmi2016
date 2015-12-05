#include <stdio.h>
#include <stdlib.h>  // For malloc, calloc, realloc, EXIT_FAILURE, EXIT_SUCCESS.

#include <ctype.h>   // For tolower() function.
#include <string.h>
#include <math.h>    // For ceil() function.

#include <stdbool.h> // Requires C99+, C11 only. Won't work with C89 and K&R.

#include <assert.h>  // Use -only- for DEBUGGING. Assertions library.

// Define MACROS

#define MAXID    7 + 1  // For the maximum allowed ID string length.
#define BUFFSIZE 35 + 1 // For the maximum name or surname string buffer size.
#define ROWLEN   7      // The exact number of element in each file row.

// Date struct data type
typedef struct date_s {
	short day;
	short month;
	int year;
} date_t;

// Single student struct data type
typedef struct student_s {
	char id[MAXID];
	char *name;
	char *surname;
	date_t birthdate;
	char sex;
} student_t;

// A struct data type represanting an array of students
typedef struct student_array {
	int allocnum;
	int size;
	student_t *students;
} stud_array;

// String facilities
char *my_strdup(char *string);
int ci_strcmp(const char *str1, const char *str2);

// Student I/O and memory management
stud_array readStudents(FILE *fp);
static inline void freeStudent(student_t stud);
void freeStudents(stud_array array);
void printStudent(student_t s);
void printStudents(stud_array s_array);

// Addition/removal of students
student_t copyStudent(student_t stud);
void addStudent(stud_array *s_array, student_t stud);
void removeStudent(stud_array *s_array, student_t *stud);

// Student comparison functions
int idcmp(const void *stud1, const void *stud2);
int firstamecmp(const void *stud1, const void *stud2);
int surnamecmp(const void *stud1, const void *stud2);
int namecmp(const void *stud1, const void *stud2);
int agecmp(const void *stud1, const void *stud2);

// Search algorithms
void *linearsearch(const void *base, const void *elem,
		size_t num, size_t size, int (*compar)(const void*, const void*));
void *binarysearch(const void *base, const void *elem,
		size_t num, size_t size, int (*compar)(const void*, const void*));

// Bubblesort sorting algorithm
void bubblesort(void* base, size_t num, size_t size,
	int (*compar)(const void*, const void*));

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: program inputfile.txt\n");

		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);

		exit(EXIT_FAILURE);
	}

	stud_array s_array = readStudents(fp); // Array of students;

	fclose(fp);

	student_t s1 = {
		id: "s184856",
		name: "Alessandra",
		surname: "Romano",
		birthdate: {
			day: 12,
			month: 4,
			year: 1991
		},
		sex: 'F'
	};
	student_t *s2;

	addStudent(&s_array, s1);

	bubblesort(s_array.students, s_array.size, sizeof(student_t), idcmp);

	printStudents(s_array);

	printf("\nSearching student \"%s %s\"...\n", s1.name, s1.surname);

	s2 = binarysearch(s_array.students,
		(void *) &s1, s_array.size, sizeof(student_t), idcmp
	);

	if (s2 != NULL) {
		printf("Found student \"%s %s\" with id: \"%s\".\n\n",
			s2->name, s2->surname, s2->id
		);
	} else {
		printf("Student \"%s %s\" not found.\n\n", s1.name, s1.surname);
	}

	removeStudent(&s_array, s2);

	printStudents(s_array);

	freeStudents(s_array);

    return 0;
}

/**
 * Allocates and duplicates a given string.
 * @param string The string to duplicate.
 * @return The newly allocated string duplicate.
 */
char *my_strdup(char *string) {
	char *str = NULL;

	if (string != NULL) {
		str = (char *) malloc(sizeof(char) * (strlen(string) + 1));
		strcpy(str, string);
	}

	return str;
}

/**
 * Read all the students from a file.
 * @param fp The file pointer.
 * @return The allocated students' array.
 */
stud_array readStudents(FILE *fp) {
	int n_read = 0, count = 0, max = 0;
	stud_array s_array = { size: 0, allocnum: 0, students: NULL };
	student_t *stud_p = NULL;

	struct {
		char name[BUFFSIZE];
		char surname[BUFFSIZE];
	} buffer;

	if (fp != NULL) {
        if (feof(fp)) rewind(fp);

        fscanf(fp, "%d", &max);
        s_array.students = (student_t *) calloc(
			max, sizeof(student_t)
		);

        if (s_array.students == NULL) {
			fprintf(stderr, "Out of memory");

			exit(EXIT_FAILURE);
        }

		s_array.size = max;
        s_array.allocnum = max;

        for (count = 0, stud_p = s_array.students;
			count < max;
			count++, stud_p++
		) {
			n_read = fscanf(
				fp,
				"%s %s %s %hd/%hd/%d%*[ \n\t]%c", // *[] Skip spaces before sex
				stud_p->id,
				buffer.name,
				buffer.surname,
				&stud_p->birthdate.day,
				&stud_p->birthdate.month,
				&stud_p->birthdate.year,
				&stud_p->sex
			);

			if (n_read < ROWLEN) {
				printf("n_read: %d. Count: %d.\n", n_read, count);
				fprintf(stderr, "Error students from the file.\n");

				exit(EXIT_FAILURE);
			}

			stud_p->name = my_strdup(buffer.name);
			stud_p->surname = my_strdup(buffer.surname);
        }
	}

	return s_array;
}

/**
 * Copies the content of a students, allocating its memory, and returns that.
 * @param stud The student to make a new copy of.
 * @return The new copy of the given student.
 */
student_t copyStudent(student_t stud) {
	student_t s_temp;
	int i;

	s_temp.birthdate = stud.birthdate; // Simple copy
	s_temp.sex = stud.sex; // Simple copy

	for (i = 0; i < MAXID; i++) {
		s_temp.id[i] = stud.id[i];
	}

	s_temp.name = my_strdup(stud.name);
	s_temp.surname = my_strdup(stud.surname);

	return s_temp;
}

/**
 * Adds a student to the given student array.
 * @param s_array A pointer to the student array's first element.
 * @param stud The student to be added to the student array.
 */
void addStudent(stud_array *s_array, student_t stud) {
	int newallocnum;

	assert(s_array->size <= s_array->allocnum);

	if (s_array->size == s_array->allocnum) { // If array is full
		newallocnum = ceil((double) s_array->allocnum * 1.5);

		// Reallocate space for 50% more elements.
		s_array->students = (student_t *) realloc(s_array->students,
			newallocnum * sizeof(student_t)
		);

		if (s_array->students == NULL) {
			fprintf(stderr, "Out of memory.");

			exit(EXIT_FAILURE);
		}

		s_array->allocnum = newallocnum;
	}

	s_array->students[s_array->size++] = copyStudent(stud); // Add the student
}


/**
 * Removes a student from the given student array.
 * @param s_array A pointer to the student array's first element.
 * @param stud A pointer to the student to remove. Must be part of the array.
 */
void removeStudent(stud_array *s_array, student_t *stud) {
	if (s_array == NULL || stud == NULL)
		return;

    student_t *end = s_array->students + s_array->size;

    if (stud < end && stud >= s_array->students) {
		freeStudent(*stud);

		for (int i = 1; i < s_array->size; i++) {
			stud[i - 1] = stud[i];
		}

		s_array->size--;
    }
}

/**
 * Frees a student's memory.
 */
static inline void freeStudent(student_t stud) {
	free(stud.name);
	free(stud.surname);
}

/**
 * Frees all the students' memory.
 */
void freeStudents(stud_array array) {
	student_t *students = array.students;
	int count = array.size;

	if (students != NULL) {
		for(int i = 0; i < count; i++) { // C99+
			freeStudent(students[i]);
		}
	}

	free(students);
}

/**
 * Print out a single students.
 * @param s The student to print.
 */
void printStudent(student_t s) {
	printf("%s %s %s %02d/%02d/%04d %c\n",
		s.id,
		s.name,
		s.surname,
		s.birthdate.day,
		s.birthdate.month,
		s.birthdate.year,
		s.sex
	);
}

/**
 * Print out all the students in the array.
 * @param s_array Student array
 */
void printStudents(stud_array s_array) {
	student_t *students = s_array.students;
	int count = s_array.size;

	if (students != NULL) {
		for (int i = 0; i < count; i++) {
			printStudent(students[i]);
		}
	}
}

/**
 * Compares two strings alphabetically, case-insensitive.
 * @param str1 String one.
 * @param str2 String two.
 * @return Comparison number (greater than 0 if the first precedes the second).
 */
int ci_strcmp(const char *str1, const char *str2) {
	char left, right;

	if (str1 != NULL && str2 != NULL) {
		do {
			left = tolower(*(str1++));
			right = tolower(*(str2++));
		} while (left == right && right != '\0');

		return left - right;
	}

	return str1 - str2;
}

/**
 * Order students by student id.
 * @param stud1 Student 1.
 * @param stud2 Student 2.
 * @return Comparison number (greater than 0 if the first precedes the second).
 */
int idcmp(const void *stud1, const void *stud2) {
	const student_t *s1 = (student_t *) stud1;
	const student_t *s2 = (student_t *) stud2;

	if (s1 != s2 && s1 != NULL && s2 != NULL)
		if (s1->id != s2->id && s1->id != NULL && s2->id != NULL)
			return ci_strcmp(s1->id, s2->id);

	return 0; // Possibly leave them in place
}

/**
 * Order students by surname, ascendant.
 * @param stud1 Student 1.
 * @param stud2 Student 2.
 * @return Comparison number (greater than 0 if the first precedes the second).
 */
int surnamecmp(const void *stud1, const void *stud2) {
	const student_t *s1 = (student_t *) stud1;
	const student_t *s2 = (student_t *) stud2;

	if (s1 != s2 && s1 != NULL && s2 != NULL)
		if (s1->surname != s2->surname &&
			s1->surname != NULL && s2->surname != NULL
		)
			return ci_strcmp(s1->surname, s2->surname);

	return 0; // Possibly leave them in place
}

/**
 * Order students by firstname, ascendant.
 * @param stud1 Student 1.
 * @param stud2 Student 2.
 * @return Comparison number (greater than 0 if the first precedes the second).
 */
int firstamecmp(const void *stud1, const void *stud2) {
	const student_t *s1 = (student_t *) stud1;
	const student_t *s2 = (student_t *) stud2;

	if (s1 != s2 && s1 != NULL && s2 != NULL)
		if (s1->name != s2->name && s1->name != NULL && s2->name != NULL)
			return ci_strcmp(s1->name, s2->name);

	return 0; // Possibly leave them in place
}

/**
 * Order students by surname/firstname, ascendant.
 * @param stud1 Student 1.
 * @param stud2 Student 2.
 * @return Comparison number (greater than 0 if the first precedes the second).
 */
int namecmp(const void *stud1, const void *stud2) {
	int sur_cmp;

	if (stud1 != stud2 && stud1 != NULL && stud2 != NULL) {
		if ((sur_cmp = surnamecmp(stud1, stud2)) == 0) {
			return firstamecmp(stud1, stud2);
		}

		return sur_cmp;
	}

	return 0; // Possibly leave them in place
}

/**
 * Order students by age, ascendant (from younger to older).
 * @param stud1 Student 1.
 * @param stud2 Student 2.
 * @return Comparison number (greater than 0 if the first is younger).
 */
int agecmp(const void *stud1, const void *stud2) {
	const student_t *s1 = (student_t *) stud1;
	const student_t *s2 = (student_t *) stud2;
	int ret = 0;

	if (s1 != s2 && s1 != NULL && s2 != NULL) {
		ret = s2->birthdate.year - s1->birthdate.year;

		if (ret == 0) {
			ret = s2->birthdate.month - s1->birthdate.month;

			if (ret == 0) {
				ret = s2->birthdate.day - s1->birthdate.day;
			}
		}
	}

	return ret; // Possibly leave them in place
}

/**
 * Linear Search. Complexity: N (linear).
 * @param base A void pointer to the array's first element.
 * @param elem A void pointer to the element being searched.
 * @param num The number of elements in the array.
 * @param size The size of each array element.
 * @param compar A pointer to the comparison function.
 */
void *linearsearch(const void *base, const void *elem,
	size_t num, size_t size, int (*compar)(const void*, const void*)
) {
    char *p = (char *) base;
    char *end = p + num * size;

    while (p < end) {
		if (compar(p, elem) == 0)
			return p;

		p += size;
    }

	// Not found.
    return NULL;
}

// Can be written with recursion.
/**
 * Binary Search (dichotomic). Complexity: N*log(N).
 * @param base A void pointer to the ordered-array's first element.
 * @param elem A void pointer to the element being searched.
 * @param num The number of elements in the array.
 * @param size The size of each array element.
 * @param compar A pointer to the comparison function.
 */
void *binarysearch(const void *base, const void *elem,
	size_t num, size_t size, int (*compar)(const void*, const void*)
) {
	char *left = (char *) base;
	char *right = (char *) base + (num - 1) * size;
	char *middle;
	int cmp;

	while (left <= right) {
		middle = left + ((right - left) / size) / 2 * size;

		cmp = compar(middle, elem);

		if (cmp == 0) {
			return middle;
		}

		if (cmp > 0) {
			right = middle - size;
		} else {
			left = middle + size;
		}
	}

	// Not found.
	return NULL;
}

/**
 * Bubblesort algorithm.
 * @param base A void pointer to the array's first element.
 * @param num The number of elements in the array.
 * @param size The size of each array element.
 * @param compar A pointer to the comparison function.
 */
void bubblesort(void* base, size_t num, size_t size,
	int (*compar)(const void*, const void*)
) {
	const char *arr = (const char *) base;
	char *buffer, *left, *current, *right;

	if (arr != NULL && size > 0 && num > 1) {
		buffer = (char *) malloc(size);

		if (buffer == NULL) {
			fprintf(stderr, "Out of memory.");

			exit(EXIT_FAILURE);
		}

		right = (char *) arr + num * size;
		while (right > arr) {
			left = (char *) arr;
			current = left + size;

			while (current < right) {
				// Compare the two elements and move the bigger to the right
				if (compar(left, current) > 0) {
					memcpy(buffer, left, size); // Temporary variable
					memcpy(left, current, size); // Swap pt.1
					memcpy(current, buffer, size); // Swap pt.2
				}

				left += size;
				current += size;
			}

			right -= size;
		}

		free(buffer);
	}
}
