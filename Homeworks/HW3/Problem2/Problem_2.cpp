#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#define MAX_HAND 1001

void clear();
int make1();
int make2();

int counter;
int left[MAX_HAND];
int right[MAX_HAND];
int case1[MAX_HAND];
int case2[MAX_HAND];
int solve1[MAX_HAND][MAX_HAND];
int solve2[MAX_HAND][MAX_HAND];
int leftNum;
int rightNum;
int caseNum;

int main()
{
	counter = 0;
	char inputFile[1000];
	FILE* fpCommand = fopen("commands_3_2.txt", "r");
	FILE* fpInput;
	char* temp;
	FILE* fpOutput = fopen("output_3_2.txt", "w");
	while (!feof(fpCommand))
	{
		if (counter == 1)
			fprintf(fpOutput, "\n");
		clear();
		fgets(inputFile, 100, fpCommand);
		if (inputFile[strlen(inputFile) - 1] == '\n')
			inputFile[strlen(inputFile) - 1] = '\0';
		fpInput = fopen(inputFile, "r");

		while (!feof(fpInput))
		{
			
			fscanf(fpInput, "%d", &leftNum);
			for (int i = 0; i < leftNum; i++)
			{
				fscanf(fpInput, "%d", &left[i]);
			}
			fscanf(fpInput, "%d", &rightNum);
			for (int i = 0; i < rightNum; i++)
			{
				fscanf(fpInput, "%d", &right[i]);
			}
			fscanf(fpInput, "%d", &caseNum);
			for (int i = 0; i < caseNum; i++)
			{
				fscanf(fpInput, "%d", &case1[i]);
			}
			fscanf(fpInput, "%d", &caseNum);
			for (int i = 0; i < caseNum; i++)
			{
				fscanf(fpInput, "%d", &case2[i]);
			}
			
		}

		fprintf(fpOutput, "%d%d", make1(), make2());
		/*for (int i = 0; i <= leftNum; i++)
		{
			for (int j = 0; j <= rightNum; j++)
			{
				printf("%d  ", solve1[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
		for (int i = 0; i <= leftNum; i++)
		{
			for (int j = 0; j <= rightNum; j++)
			{
				printf("%d  ", solve2[i][j]);
			}
			printf("\n");
		}*/
		counter = 1;
		fclose(fpInput);
	}
	fclose(fpCommand);
	fclose(fpOutput);
	return 0;
}

void clear()
{
	int i, j;
	for (i = 0; i < MAX_HAND; i++)
	{
		left[i] = 0;
		right[i] = 0;
		case1[i] = 0;
		case2[i] = 0;
		for (j = 0; j < MAX_HAND; j++)
		{
			solve1[i][j] = 0;
			solve2[i][j] = 0;
		}
	}
}

int make1()
{
	int i, j;
	solve1[0][0] = 1;
	for (i = 1; i <= leftNum; i++)
	{
		if (left[i - 1] == case1[i - 1] && solve1[i - 1][0] == 1)
		{
			solve1[i][0] = 1;
		}
	}
	for (j = 1; j <= rightNum; j++)
	{
		if (right[j - 1] == case1[j - 1] && solve1[0][j - 1] == 1)
		{
			solve1[0][j] = 1;
		}
	}
	for (i = 1; i <= leftNum; i++)
	{
		for (j = 1; j <= rightNum; j++)
		{
			if (solve1[i][j - 1] == 1 && case1[i + j - 1] == right[j - 1])
				solve1[i][j] = 1;
			else if (solve1[i - 1][j] == 1 && case1[i + j - 1] == left[i - 1])
				solve1[i][j] = 1;
		}
	}
	if (solve1[leftNum][rightNum] == 1)
		return 1;
	else return 0;
}

int make2()
{
	int i, j;
	solve2[0][0] = 1;
	for (i = 1; i <= leftNum; i++)
	{
		if (left[i - 1] == case2[i - 1])
		{
			solve2[i][0] = 1;
		}
	}
	for (j = 1; j <= rightNum; j++)
	{
		if (right[j - 1] == case2[j - 1])
		{
			solve2[0][j] = 1;
		}
	}
	for (i = 1; i <= leftNum; i++)
	{
		for (j = 1; j <= rightNum; j++)
		{
			if (solve2[i][j - 1] == 1 && case2[i + j - 1] == right[j - 1])
				solve2[i][j] = 1;
			else if (solve2[i - 1][j] == 1 && case2[i + j - 1] == left[i - 1])
				solve2[i][j] = 1;
		}
	}
	if (solve2[leftNum][rightNum] == 1)
		return 1;
	else return 0;
}