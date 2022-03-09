#pragma once

typedef struct {
	unsigned int score;
	float data[3];
	char comments[16];
} ELEMENT;

typedef int _Cmpfun(const void*, const void*);

void qsort_orig(void*, size_t, size_t, _Cmpfun *);
void qsort_median_insert(void*, size_t, size_t, _Cmpfun*);
void qsort_median_insert_iter(void*, size_t, size_t, _Cmpfun*);