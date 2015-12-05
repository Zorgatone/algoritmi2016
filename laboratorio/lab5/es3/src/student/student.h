#ifndef STUDENT_H
#define STUDENT_H

#define IDSIZE 7 + 1 // 7x char + '\0' terminator

typedef enum gender {
	MALE = 'M',
	FEMALE = 'F',
	OTHER = 'O'
} gender_t;

typedef struct date {
	short day;
	short month;
	int year;
} date_t;

typedef struct student {
	char id[IDSIZE];
	char *firstname;
	char *lastname;
	date_t birthdate;
	gender_t gender;
} student_t;

void printStudent(student_t student);

#endif
