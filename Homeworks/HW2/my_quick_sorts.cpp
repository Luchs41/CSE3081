#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_quick_sorts.h"

#define MAX_BUF 256
int flag = 0;
size_t oldn = 0;

void insertion_sort(void* array, size_t n, size_t size, _Cmpfun* cmp)
{
	size_t i, j;
	char* S = (char*)array;
	char* temp = (char*)malloc(sizeof(char) * size);
	i = n - 1;
	while (i-- > 0)
	{
		memcpy(temp, S + i * size, size);
		j = i;
		while (++j < n && (*cmp)(temp, S + j * size) > 0);
		if (--j == i) continue;
		memcpy(S + i * size, S + (i + 1) * size, size * (j - i));
		memcpy(S + j * size, temp, size);
	}
	free(temp);
}
int median(size_t left, size_t right)
{
	size_t a, b, c;
	a = rand() % (right - left) + left;
	b = rand() % (right - left) + left;
	c = rand() % (right - left) + left;

	if (a >= b && a >= c) return a;
	else if (b >= a &&b >= c) return b;
	else return c;
}



void qsort_orig(void* array, size_t n, size_t size, _Cmpfun* cmp)
{
	while (1 < n)
	{
		int	i = 0;
		int	j = n - 1;
		char* qs = (char*)array;
		char* qi = (char*)array;
		char* qj = qi + size * j;
		
		{
			char	buf[MAX_BUF];
			char* q1 = qi;
			char* q2 = qj;
			size_t	m, ms;

			for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
				m = (ms < sizeof(buf)) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}
		//changed first and last value for pivot setting
		char* qp = qj;
		
		while (i < j)
		{
			
			while (i < j && (*cmp)(qi, qp) <= 0)
				++i, qi += size;
			while (i < j && (*cmp)(qp, qj) <= 0)
				--j, qj -= size;
			
			if (i < j) {
				char	buf[MAX_BUF];
				char* q1 = qi;
				char* q2 = qj;
				size_t	m, ms;

				for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
					m = (ms < sizeof(buf)) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
				++i, qi += size;
				
			}
		}
		
		if (qi != qp) {
			char	buf[MAX_BUF];
			char* q1 = qi;
			char* q2 = qp;
			size_t	m, ms;

			for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
				m = (ms < sizeof(buf)) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}
		
		
		j = n - i - 1, qi += size;
		if (j < i) {
			if (1 < j)
				qsort(qi, j, size, cmp);
			n = i;
		}
		else {
			if (1 < i)
				qsort(array, i, size, cmp);
			array = qi;
			n = j;
		}
	}
}

void qsort_median_insert(void* array, size_t n, size_t size, _Cmpfun* cmp)
{
	if (n < 30)
	{
		insertion_sort(array, n, size, cmp);
	}
	else
	{
		while (1 < n)
		{
			size_t	i = 0;
			size_t	j = n - 1;
			size_t	r = median(i, j);
			char* qi = (char*)array;
			char* qj = qi + size * j;
			char* qr = qi + size * r;
			{
				char	buf[MAX_BUF];
				char* q1 = qr;
				char* q2 = qj;
				size_t	m, ms;

				for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
					m = (ms < sizeof(buf)) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
			char* qp = qj;
			
			while (i < j)
			{
				while (i < j && (*cmp)(qi, qp) <= 0)
					++i, qi += size;
				while (i < j && (*cmp)(qp, qj) <= 0)
					--j, qj -= size;

				if (i < j) {
					char	buf[MAX_BUF];
					char* q1 = qi;
					char* q2 = qj;
					size_t	m, ms;

					for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
						m = (ms < sizeof(buf)) ? ms : sizeof(buf);
						memcpy(buf, q1, m);
						memcpy(q1, q2, m);
						memcpy(q2, buf, m);
					}
					++i, qi += size;
					
				}
			}
			if (qi != qp) {
				char	buf[MAX_BUF];
				char* q1 = qi;
				char* q2 = qp;
				size_t	m, ms;

				for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
					m = (ms < sizeof(buf)) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
			j = n - i - 1, qi += size;
			if (j < i) {
				if (1 < j)
					qsort_median_insert(qi, j, size, cmp);
				n = i;
			}
			else {
				if (1 < i)
					qsort_median_insert(array, i, size, cmp);
				array = qi;
				n = j;
			}
		}
	}
}

void qsort_median_insert_iter(void* array, size_t n, size_t size, _Cmpfun* cmp)
{
	if (flag == 1 && n > (oldn / 2))
	{
		insertion_sort(array, n, size, cmp);
	}
	else {
		
		while (1 < n)
		{

			size_t	i = 0;
			size_t	j = n - 1;
			size_t	r = median(i, j);
			char* qi = (char*)array;
			char* qj = qi + size * j;
			char* qr = qi + size * r;
			{
				char	buf[MAX_BUF];
				char* q1 = qr;
				char* q2 = qj;
				size_t	m, ms;

				for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
					m = (ms < sizeof(buf)) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
			char* qp = qj;

			while (i < j)
			{
				while (i < j && (*cmp)(qi, qp) <= 0)
					++i, qi += size;
				while (i < j && (*cmp)(qp, qj) <= 0)
					--j, qj -= size;

				if (i < j) {
					char	buf[MAX_BUF];
					char* q1 = qi;
					char* q2 = qj;
					size_t	m, ms;

					for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
						m = (ms < sizeof(buf)) ? ms : sizeof(buf);
						memcpy(buf, q1, m);
						memcpy(q1, q2, m);
						memcpy(q2, buf, m);
					}
					++i, qi += size;
				}

			}

			if (qi != qp) {
				char	buf[MAX_BUF];
				char* q1 = qi;
				char* q2 = qp;
				size_t	m, ms;

				for (ms = size; 0 < ms; ms -= m, q1 += m, q2 += m) {
					m = (ms < sizeof(buf)) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
			
			j = n - i - 1, qi += size;
			if (j < i) {
				if (1 < j)
					qsort_median_insert_iter(qi, j, size, cmp);
				
				n = i;
				
			}
			else {
				if (1 < i)
					qsort_median_insert_iter(array, i, size, cmp);
				array = qi;
				
				n = j;
			}



		}
		flag = 1; oldn = n;
	}
	
}