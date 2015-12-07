#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

void linkStuds(studs_t s) {
	if (s.length <= 0 || s.alloc_size <= 0)
		return;

	for (int i = 0; i < (int)s.length; i++) {
		s.links[i] = &s.data[i];
	}
}

void extendStuds(studs_t *s) {
	if (s->data == NULL || s->links == NULL || s->alloc_size <= 0) {
		free(s->data);
		s->data = calloc(1, sizeof(*s->data)); // one element
		free(s->links);
		s->links = calloc(1, sizeof(*s->links)); // one element

		s->length = 0;
		s->alloc_size = 1;

		return;
	}

	s->alloc_size *= 1.5;
	s->data = realloc(s->data, s->alloc_size * sizeof(*s->data));
	s->links = realloc(s->links, s->alloc_size * sizeof(*s->links));
}

void freeStuds(studs_t *s) {
	for (int i = 0; i < (int) s->length; i++) {
		freeStudent(s->data[i]);
	}

	free(s->data);
	free(s->links);
	s->length = 0;
	s->alloc_size = 0;
	s->data = NULL;
	s->links = NULL;
}

void addStud(studs_t *arr, student_t student) {
	if (arr->length <= 0 || arr->length >= arr->alloc_size) {
		extendStuds(arr);
	}

	arr->data[arr->length++] = cloneStudent(student);
	linkStuds(*arr);
}
