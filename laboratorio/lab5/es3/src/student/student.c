#include <stdio.h>

#include "student.h"

void printStudent(student_t student) {
	printf("Student: %s %s %s %02d/%02d/%d %c",
		student.id,
		student.firstname,
		student.lastname,
		student.birthdate.day,
		student.birthdate.month,
		student.birthdate.year,
		student.gender
	);
}
