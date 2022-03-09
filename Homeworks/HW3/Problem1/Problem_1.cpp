#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

#define MAX_FILE_NAME 100

void LPS(const int m, const char* X, int* LPS_length, char** LPS_string);

int max(int x, int y) { return (x > y) ? x : y; }


int L[1025][1025];

int main()
{
	char temp[100];
	int numCase;
	char inputFile[MAX_FILE_NAME];
	char outputFile[MAX_FILE_NAME];
	FILE* fpConfig = fopen("config_LPS.txt", "r");
	FILE* fpInput;
	FILE* fpOutput;
	fscanf(fpConfig, "%d", &numCase);
	fgets(temp , 3, fpConfig);
	
	
	int len = 0;
	char str[1025];
	int lenLps = 0;
	char *strLps;
	//strLps = (char*)malloc(sizeof(char) * 1024);
	for (int i = 0; i < 1025; i++)
	{
		str[i] = 0;
		
		for (int j = 0; j < 1025; j++)
		{
			L[i][j] = 0;
		}
	}
	//printf("num case : %d\n", numCase);
	for (int i = 0; i < numCase; i++)
	{
		fgets(inputFile, MAX_FILE_NAME, fpConfig);
		fgets(outputFile, MAX_FILE_NAME, fpConfig);
		if (inputFile[strlen(inputFile) - 1] == '\n')
		{
			inputFile[strlen(inputFile) - 1] = '\0';
		}
		if (outputFile[strlen(outputFile) - 1] == '\n')
		{
			outputFile[strlen(outputFile) - 1] = '\0';
		}
		//printf("file name : %s\n%s\n", inputFile, outputFile);
		fpInput = fopen(inputFile, "r");
		fpOutput = fopen(outputFile, "w");
		if (!fpInput)
		{
			printf("Error!!\n");
			break;
		}
		fread(&len, sizeof(int), 1, fpInput);
		//printf("length is %d\n", len);
		fread(str, sizeof(char), len, fpInput);
		str[len] = '\0';
		
		//printf("string is : %s\n", str); 




		LPS(len, str, &lenLps, &strLps); 
		/*printf("lenLPS : %d\n", lenLps);
		
		printf("\n\t");
		for (int i = 0; i < len; i++)
		{
			printf("%c\t", str[i]); 
		}
		printf("\n");
		for (int i = 0; i < len; i++)
		{
			printf("%c\t", str[i]); 
			for (int j = 0; j < len; j++)
			{
				printf("%d\t", L[i][j]);
			}
			printf("\n");
		}*/
		

		//File output
		fwrite(&lenLps, sizeof(int), 1, fpOutput);
		fwrite(strLps, sizeof(char), lenLps, fpOutput);
		//clear the variables
		for (int i = 0; i < 1025; i++)
		{
			str[i] = 0; 
			
			strLps[i] = 0;
			for (int j = 0; j < 1025; j++)
			{
				L[i][j] = 0;
			}
		}
		len = 0;
		fclose(fpInput); fclose(fpOutput);

		

	}
	

	return 0;
}

void LPS(const int m, const char* X, int* LPS_length, char** LPS_string)
{
	int i, j, cl;
	int count = 0;
	char *lps;
	lps = (char*)malloc(sizeof(char) * 1025);
	int temp;
	for (i = 0; i < m; i++)
	{
		L[i][i] = 1;
	}
	for (cl = 2; cl <= m; cl++)
	{
		for (i = 0; i < m - cl + 1; i++)
		{
			j = i + cl - 1;
			if (X[i] == X[j] && cl == 2)
				L[i][j] = 2;
			else if (X[i] == X[j])
				L[i][j] = L[i + 1][j - 1] + 2;
			else
				L[i][j] = max(L[i][j - 1], L[i + 1][j]);
		}
	}
	i = 0; j = m - 1;
	while (L[i + 1][j] != 0 && L[i][j - 1] != 0 && i < m - 1 && j > 0)
	{
		
		while (L[i][j] == L[i + 1][j])
		{
			i++;
		}
		while (L[i][j] == L[i][j - 1])
		{
			j--;
		}
		lps[count] = X[j];
		count++;
		
		i++; j--;
	}
	lps[count] = X[j];
	*LPS_length = L[0][m - 1];
	
	
	
	for (int k = 0; k < (*LPS_length / 2); k++)
	{
		lps[*LPS_length - k - 1] = lps[k];
	}
	lps[*LPS_length] = '\0';
	

	*LPS_string = lps;
	
	
}

