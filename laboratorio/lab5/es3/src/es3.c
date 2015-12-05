/**
 * Trying to refactor the student crazy shit stuff of a previous exercise.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "student/student.h"

void die(const char * format, ...);

int main(int argc, char **argv) {
	if (argc < 2)
        die("Usage: %s inputfile.txt\n", argv[0]);

    puts("Ok");

    student_t student = {
        .id = "s184728",
        .firstname = "Tommaso",
        .lastname = "Ricci",
        .birthdate = {
            .day = 10,
            .month = 7,
            .year = 1992
        },
        .gender = MALE
    };

    printStudent(student);

    return EXIT_SUCCESS;
}

void die(const char *format, ...) {
	va_list args;
	va_start (args, format);

	vfprintf(stderr, format, args);

	va_end (args);
	exit(EXIT_FAILURE);
}
