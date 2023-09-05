#include <stdio.h>

typedef struct {
    int freq;
    char ch;
} Node;

Node minH[96];
int arrPtr = 1;

void insertInMinHeap(Node node);

int main()
{
    char alpha[95];
    for (int i = 0; i < 95; i++) {
        alpha[i] = i + 32;
    }

    int freq[95] = {0};

    FILE *fptr;
    fptr = fopen("test.txt", "r");

    char ch;
    ch = fgetc(fptr);
    while (ch != EOF) {
        freq[ch-32]++;
        ch = fgetc(fptr);
    }

    fclose(fptr);

    for (int i = 0; i < 95; i++) {
        Node node;
        node.freq = freq[i];
        node.ch = alpha[i];
        insertInMinHeap(node);
    }

    for (int i = 1; i < arrPtr; i++) {
        printf("%d -> %c\n",minH[i].freq, minH[i].ch);
    }

    return 0;
}

void insertInMinHeap(Node node){
    if (node.freq == 0) {
        return;
    }
    
    minH[arrPtr] = node;
    int i = arrPtr;
    while(i>1 && minH[i].freq < minH[i/2].freq){
        Node temp = minH[i];
        minH[i] = minH[i/2];
        minH[i/2] = temp;
        i /= 2;
    }
    arrPtr++;
}
