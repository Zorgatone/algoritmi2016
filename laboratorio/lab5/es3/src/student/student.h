#ifndef STUDENT_H
#define STUDENT_H

#include <stdlib.h>
#include <string.h>

#define IDSIZE 7 + 1 // 7x char + '\0' terminator

typedef enum gender {
	MALE = 'M',
	FEMALE = 'F',
	OTHER = 'O'
} gender_t;

typedef struct date {
	unsigned short day;
	unsigned short month;
	int year;
} date_t;

typedef struct student {
	char id[IDSIZE];
	char *firstname;
	char *lastname;
	date_t birthdate;
	gender_t gender;
} student_t;

typedef struct studs {
	student_t *data;
	student_t **links;
	size_t length;
	size_t alloc_size;
} studs_t;

void addStud(studs_t *arr, student_t student);
void freeStuds(studs_t *s);
void linkStuds(studs_t s);
void extendStuds(studs_t *s);

static inline void printStudent(student_t student) {
	printf("Student: %s %s %s %02hu/%02hu/%d %c\n",
		student.id,
		student.firstname,
		student.lastname,
		student.birthdate.day,
		student.birthdate.month,
		student.birthdate.year,
		student.gender
	);
}

static inline studs_t newStuds(void) {
	studs_t students = {
		.data = NULL,
		.links = NULL,
		.length = 0,
		.alloc_size = 0
	};

	return students;
}

static inline void freeStudent(student_t student) {
	free(student.firstname);
	free(student.lastname);
	student.firstname = NULL;
	student.lastname = NULL;
}

static inline char *dupstr(char *str) {
	char *tmp = malloc(strlen(str) + 1);
	strcpy(tmp, str);

	return tmp;
}

static inline student_t cloneStudent(student_t student) {
	student_t tmp;

	strcpy(tmp.id, student.id);
	tmp.firstname = dupstr(student.firstname);
	tmp.lastname = dupstr(student.lastname);
	tmp.birthdate = student.birthdate;
	tmp.gender = student.gender;

	return tmp;
}

#endif
