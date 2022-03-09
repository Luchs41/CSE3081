#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <direct.h>
#pragma warning(disable: 4996)
#define MAX_VERTICES 50000000
#define MAX_EDGES 50000000

typedef struct {
    int u;
    int v;
    int weight;
} edge;

//Global Variables
edge minHeap[MAX_EDGES];
int sizeH = 0;
int numV;
int numE;
int maxWeight;
int parent[MAX_VERTICES];
long long int weightSum[MAX_VERTICES];
FILE* fpOutput;

//Functions
void insertMinHeap(edge newEdge);
edge deleteMinHeap();
void kruskal();
void Union(int i, int j, int weight);
int Find(int i);


int main()
{

    FILE* fpCommand = fopen("./Graphs_HW4/commands.txt", "r");
    FILE* fpInput;
    
    char inputFile[1000];
    char outputFile[1000];
    while (!feof(fpCommand))
    {
        fgets(inputFile, 100, fpCommand);
        if (inputFile[strlen(inputFile) - 1] == '\n')
            inputFile[strlen(inputFile) - 1] = '\0';
        fgets(outputFile, 100, fpCommand);
        if (inputFile[strlen(outputFile) - 1] == '\n')
            inputFile[strlen(outputFile) - 1] = '\0';
    }
    
    chdir("./Graphs_HW4");
    fpInput = fopen(inputFile, "r");
    fscanf(fpInput, "%d", &numV);
    fscanf(fpInput, "%d", &numE);
    fscanf(fpInput, "%d", &maxWeight);
    //load inputs
    fpOutput = fopen(outputFile, "w");
    //output file open
    
    //printf("v e weight : %d %d %d\n", numV, numE, maxWeight);
    //read the number of vertices and edges
    for (int i = 0; i < numV; i++)
    {
        parent[i] = -1;
        weightSum[i] = 0;
    }
    double time = clock();
    edge tempEdge;
    for (int i = 0; i < numE; i++)
    {
        fscanf(fpInput, "%d %d %d", &tempEdge.u, &tempEdge.v, &tempEdge.weight);
        insertMinHeap(tempEdge);
    }
    //printf("size H : %d\n", sizeH);
    
    kruskal();
    

    printf("output written. \nrunning time: %.6f seconds\n", (clock() - time) / CLOCKS_PER_SEC);
    fclose(fpInput);
    fclose(fpOutput);
    return 0;
}

void insertMinHeap(edge newEdge)
{
    if (sizeH == MAX_EDGES - 1)
    {
        printf("Heap is FULL\n");
        return;
    }
    int i = ++sizeH;
    while ((i != 1) && (newEdge.weight < minHeap[i / 2].weight))
    {
        minHeap[i] = minHeap[i / 2];
        i /= 2;
    }
    minHeap[i] = newEdge;
}

edge deleteMinHeap()
{
    int parent, child;
    edge item = minHeap[1];
    edge temp;
    temp = minHeap[sizeH--];
    parent = 1; child = 2;
    while (child <= sizeH)
    {
        if ((child < sizeH) && (minHeap[child].weight > minHeap[child + 1].weight)) child++;
        if (temp.weight <= minHeap[child].weight) break;
        minHeap[parent] = minHeap[child];
        parent = child;
        child *= 2;
    }
    minHeap[parent] = temp;
    return item;
}

void kruskal()
{
    int Kscanned = 0;
    edge temp;
    long long int weightSumz = 0;
    int u, v;
    int just = 0;
    int countE = numE;
    int count = 0;
    while (sizeH > 0 && count < numV - 1)//(count < numV - 1 && countE > 0)
    {
        Kscanned++;
        //printf("numV : %d\ncount ; %d\n", numV, count);
        temp = deleteMinHeap();
        just++;
        //printf("deleteheap done\n");
        u = Find(temp.u);
        
        //printf("find u done\n");
        v = Find(temp.v);
        
        if (u != v)
        {
            
            //fprintf(fpOutput, "%d %d %d\n", temp.u, temp.v, temp.weight);
            weightSumz += temp.weight;
            
            count++;
            countE--;
            Union(u, v, temp.weight);
            
            
        }
    }
    
    //fprintf(fpOutput, "----------\n");
    printf("Kscanned : %d\n", Kscanned);
    int countSet = 0;
    for (int i = 0; i < numV; i++)
    {
        if (parent[i] < 0) countSet++;
    }
    fprintf(fpOutput, "%d\n", countSet);
    for (int i = 0; i < numV; i++)
    {
        if (parent[i] < 0)
        {
            fprintf(fpOutput, "%d %d %lld\n", i, parent[i] * (-1), weightSum[i]);
        }
    }
    for (int i = 0; i < numV; i++)
    {
        //printf("%d : %d\n", i, weightSum[i]);
    }
}

void Union(int i, int j, int weight)
{
    int temp = parent[i] + parent[j];
    if (parent[i] > parent[j])
    {
        parent[i] = j;
        parent[j] = temp;
        weightSum[j] = weightSum[j] + weight + weightSum[i];
        
    }
    else
    {
        parent[j] = i;
        parent[i] = temp;
        weightSum[i] = weightSum[i] + weight + weightSum[j];
    }
}

int Find(int i)
{
    int temp = i;
    for (; parent[i] >= 0; i = parent[i])
        ;
    
    return i;
}
