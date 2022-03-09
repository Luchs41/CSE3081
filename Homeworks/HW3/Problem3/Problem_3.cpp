#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable: 4996)

char* str = 0;
int len = 0;


struct node
{
    int item; //-1 if it's combine of more than 2 node, ASCII if it's just a character. 
    int freq;
    struct node* left;
    struct node* right;
    struct node* link;
};
typedef struct node* nodePointer;
nodePointer front, rear = NULL;
int numNode = 0;
int count[128];
float freqArr[128];

int stack[128];
int top = -1; // stack for edcoding
char coded[128][128];
char c;

void makePQueue();
nodePointer newNode(int item, int freq);
void addPQ(nodePointer node);
nodePointer delPQ();
void mergeNode(nodePointer node1, nodePointer node2);
void inorder(nodePointer ptr);
void push(int n);
char pop();
void show(int item);


int main()
{
    
    FILE* fpInput = fopen("P3_input_ASCII.txt", "r");
    char buffer[10];
    
    size_t cur_len = 0;
    while (fgets(buffer, sizeof(buffer), fpInput) != 0)
    {
        size_t buf_len = strlen(buffer);
        char* extra = (char*)realloc(str, buf_len + cur_len + 1);
        if (extra == 0)
            break;
        str = extra;
        strcpy(str + cur_len, buffer);
        cur_len += buf_len;
    }
    //printf("%s [%d]", str, (int)strlen(str));
    len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        count[str[i]]++;
    }
    for (int i = 0; i < 128; i++)
    {
       // printf("%c : %d\n", i, count[i]);
    }
    
    makePQueue();
    nodePointer temp = front;
    //printf("------------Queue------------\n");
    //while (temp)
    {
        //printf("%c : %d ->", temp->item, temp->freq);
        //temp = temp->link;
    }
    while (numNode > 1)
    {
        mergeNode(delPQ(), delPQ());
        //printf("node left : %d / front(%c : %d) / rear(%c : %d)\n", numNode, front->item, front->freq, rear->item, rear->freq);
    }
    temp = front;
    //printf("\n------------inorder------------\n");
    inorder(temp);
    for (int k = 0; k < 128; k++)
    {
        if (count[k] != 0)
        {
            freqArr[k] = (float)count[k] / len * 100;
        }
    }
    
    FILE* fpOutput1 = fopen("P3_output_codewords.txt", "w");
    FILE* fpOutput2 = fopen("P3_output_encoded.bin", "wb");
    for (int m = 0; m < 128; m++)
    {
        if (count[m] != 0)
        {
            fprintf(fpOutput1, "%c %s %.2f\n", m, coded[m], freqArr[m]);
        }
    }
    
    int size2;
    
    size2 = 0;
    
    fread(&size2, sizeof(int), 1, fpOutput2);
   
    int codedSize = 0;
    for (int i = 0; i < 128; i++)
    {
        codedSize += count[i] * strlen(coded[i]);
    }
    //printf("codedSize is %d\n\n", codedSize);
    int codedByte = codedSize / 8;
    if (codedSize % 8 != 0) codedByte++;
    //printf("CodedByte is %d\n\n", codedByte);
    fwrite(&codedSize, sizeof(int), 1, fpOutput2);
    fwrite(&codedByte, sizeof(int), 1, fpOutput2);
    int cIdx = 0;
    char* codedStr;
    codedStr = (char*)malloc(sizeof(char) * codedSize + 1);
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < strlen(coded[str[i]]); j++)
        {
            codedStr[cIdx] = coded[str[i]][j];
            cIdx++;
        }
    }
    codedStr[cIdx] = '\0';
    //printf("cIdx : %d\nEncoded String : %s\ncodedStr len : %d\n", cIdx, codedStr, strlen(codedStr));
    
    //paking
    int counter8 = 7;
    for (int i = 0; i < strlen(codedStr); i++)
    {

        c += (codedStr[i] - '0') * pow(2, counter8);
        counter8--;
        //printf("c = %d\n", c);
        if (counter8 == -1)
        {
            fwrite(&c, sizeof(char), 1, fpOutput2);
            counter8 = 7;
            c = 0;
        }
    }
    if (counter8 != -1)
    {
        fwrite(&c, sizeof(char), 1, fpOutput2);
    }




    fclose(fpOutput1);
    fclose(fpOutput2);
    fclose(fpInput);
    return 0;
}

void makePQueue()
{
    for (int i = 0; i < 128; i++)
    {
        if (count[i] != 0)
        {
            addPQ(newNode(i, count[i]));
        }
    }
}

nodePointer newNode(int item, int freq)
{
    nodePointer node = (nodePointer)malloc(sizeof(struct node));
    node->item = item;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    node->link = NULL;
    return node;
}

void addPQ(nodePointer node)
{
    //printf("input node : %c, %d\n", node->item, node->freq);
    nodePointer temp = front;
    nodePointer pre = temp;
    if (numNode == 0)
    {
        front = node;
        rear = node;
    }
    else
    {
        while (temp!= NULL && node->freq > temp->freq)
        {
            pre = temp;
            temp = temp->link;
        }
        if (temp == NULL)
        {
            pre->link = node;
            rear = node;
        }
        else if (pre == temp)
        {
            node->link = temp;
            front = node;
        }
        else
        {
            pre->link = node;
            node->link = temp;
        }

    }
    numNode++;
}


nodePointer delPQ()
{
    nodePointer temp;
    temp = front;
    front = front->link;
    numNode--;
    
    return temp;
}

void mergeNode(nodePointer node1, nodePointer node2)
{
    nodePointer merged = (nodePointer)malloc(sizeof(struct node));
    merged->link = NULL;
    merged->left = node2;
    merged->right = node1;
    merged->freq = node1->freq + node2->freq;
    merged->item = -1;
    //printf("\nmerging : %c : %d + %c : %d\n", node2->item, node2->freq, node1->item, node1->freq);
    addPQ(merged);
}

void inorder(nodePointer ptr)
{
    
    

    if (!ptr)
    {
        pop();
        return;
    }
    push('0');
    inorder(ptr->left);
    if (!ptr->left && !ptr->right)
    {
        //printf("top=%d, %c : ", top, ptr->item);
        show(ptr->item);
    }
    push('1');
    inorder(ptr->right);
    pop();
}

void push(int n)
{
    top++;
    stack[top] = n;
}

char pop()
{
    int n = stack[top];
    top--;
    return n;
}

void show(int item)
{
    int j = 0;
    //printf("\n------show------\n");
    for (int i = top; i >= 0; i--)
    {
        //printf("%c", stack[i]);
        coded[item][i] = stack[i];
        j++;
    }
    //printf(" / coded : ");
    //for (j = 0; j < 128; j++)
    {
        //printf("%c", coded[item][j]);
    }
    //printf("[this is string] : %s", coded[item]);
    //printf("\n");
}

