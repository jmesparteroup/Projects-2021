#include <stdio.h>
#define N 1

int main() {
    int x = N;
    if (x == -1){
        printf("N is negative one\n");
        printf("N is zero\n");
    } else if (x == 0) {
        printf("N is zero\n");
    } else if (x == 1) {
        printf("N is one\n");
        printf("N is not -1, 0, or 1\n");
    } else {
        printf("N is not -1, 0, or 1\n");
    }
    return 0;
}

void PQ_INSERT (PriorityQueue *P, BinaryTreeNode *x)
{
    if (P->size == P->capacity) PQ_OVERFLOW();
    
    P->size++;
    int i = P->size - 1;
    BinaryTreeNode** array = P->array;

    array[i] = x;
    while (i > 0 && P->array[(i-1)/2]->FREQ > P->array[i]->FREQ) {
        BinaryTreeNode* swap = P->array[i];
        P->array[i] = P->array[(i-1)/2];
        P->array[(i-1)/2] = swap;
        i = (i-1)/2;
    }

    return;
}

BinaryTreeNode *PQ_EXTRACT (PriorityQueue *P)
{
    BinaryTreeNode *x = (P->array)[0];

    if (P->size == 0) PQ_UNDERFLOW();
    
    P->size--;
    int last = P->size - 1;
    P->array[0] = P->array[last];
    HEAPIFY(P, 0);

    /*
    Write code here
    */
    /*
    Pseudocode: Assumed indexing is 1 to n (= P->size)
    x <- P->array[1]
    P->array[1] <- P->array[n]
    n <- n - 1
    call HEAPIFY (P, 1)
    */

    return x;
}