#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <Windows.h>
__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my_quick_sorts.h"



int cmp(const void* a, const void* b)
{
	ELEMENT* ele_a, * ele_b;

	ele_a = (ELEMENT*)a;
	ele_b = (ELEMENT*)b;

	if (ele_a->score == ele_b->score)
		return 0;
	else if (ele_a->score < ele_b->score)
		return -1;
	else return 1;
}
void init_array(ELEMENT* array, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (int o = 0; o < 10; o++)
		{
			array[i].comments[o] = 1;
		}
		array[i].score = i;
		for (int k = 0; k < 3; k++)
		{
			array[i].data[k] = (float)k;
		}
	}
	//Shuffle by Fisher-Yates shuffle algorithm.
	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; i--)
	{
		j = rand() % (i + 1);
		{
			char buf[256];
			char* r_i = (char*)(array + i);
			char* r_j = (char*)(array + j);
			
			size_t m, ms;

			for (ms = sizeof(ELEMENT); ms > 0; ms -= m, r_i += m, r_j += m)
			{
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, r_i, m);
				memcpy(r_i, r_j, m);
				memcpy(r_j, buf, m);
			}
		}
	}
}

FILE* fpinput;
FILE* fpunsorted;
FILE* fpsorted;
int funcNum = -1;
int n = 0;
char unsortedFile[1024];
char sortedFile[1024];
ELEMENT* array;
float sum = 0;
int main()
{
	fpinput = fopen("HW2_commands.txt", "r");
	if (!fpinput)
	{
		printf("File Open Error.\n");
		return -1;
	}
	fscanf(fpinput, "%d%d%s%s", &funcNum, &n, unsortedFile, sortedFile);

	fpunsorted = fopen(unsortedFile, "wb");
	fpsorted = fopen(sortedFile, "wb");
	array = (ELEMENT*)malloc(sizeof(ELEMENT) * n);
	//init_array(array, n);
	
	
	
	fwrite(array, sizeof(ELEMENT), n, fpunsorted);
	{
		init_array(array, n);
		CHECK_TIME_START;
		switch (funcNum)
		{
		case 23:
			qsort_median_insert_iter(array, n, sizeof(ELEMENT), cmp);
			break;
		case 22:
			qsort_median_insert(array, n, sizeof(ELEMENT), cmp);
			break;
		case 21:
			qsort_orig(array, n, sizeof(ELEMENT), cmp);
			break;
		case 1:
			qsort(array, n, sizeof(ELEMENT), cmp);
			break;
		default:
			break;
		}
		CHECK_TIME_END(compute_time);
	}
	printf("<Function Number = %d, input size = %d>\n ELEMENT type of size %d: Time taken = %.3fms\n", funcNum, n, sizeof(ELEMENT), compute_time);
	for (int q = 0; q < n; q++)
	{
		//printf("(%d) ", array[q].score);
	}
	printf("\n");
	fwrite(array, sizeof(ELEMENT), n, fpsorted);
	

	ELEMENT*temp = array;
	free(temp);
	return 0;
}