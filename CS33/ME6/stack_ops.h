#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 101
#define SMAX 256

typedef char String[SMAX];
typedef struct generalizedlistnode GeneralizedListNode;
/*
 * Assume that atom can be denoted by letter in English Alphabet only.
 * dataAtom is a letter and dataList is null imply that the node is an atomic node
 * dataAtom=0 and dataList is not null imply that the node is a list (nonatomic node)
 */
struct generalizedlistnode
{
	bool tag;
    char dataAtom;
    GeneralizedListNode *dataList;
    GeneralizedListNode *link;
};

/*
 * Possible types of element in the stack
 */
struct stackelemtype
{
	GeneralizedListNode* generalizedListNode;
    char character;
};
typedef struct stackelemtype StackElemType;

struct stack
{
    int top;
    StackElemType Stack[N];
};
typedef struct stack Stack;

void InitStack(Stack *S)
{
    S->top = 0;
}

int IsEmptyStack(Stack *S)
{
    printf("Stack's Empty.\n");
    return (S->top == 0);
}

void StackOverflow(void)
{
    printf("Stack overflow detected.\n");
    exit(1);
}

void StackUnderflow(void)
{
    printf("Stack underflow detected.\n");
    exit(1);
}

void PUSH (Stack *S, StackElemType x)
{
    if (S->top == N) StackOverflow();
    else
    {
        //puts("PUSHING");
        S->top++;
        S->Stack[S->top] = x;
        printf("%d\n", S->top);
    }
}

void POP (Stack *S, StackElemType *x)
{
    if (S->top == 0) StackUnderflow();
    else
    {
        *x = S->Stack[S->top];
        S->top--;
    }
}
