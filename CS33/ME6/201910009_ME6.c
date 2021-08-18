/*
 * GeneralizedList.c
 * Sample Pseudocode/Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "stack_ops.h"

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
        //printf("%d\n", S->top);
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


/*
 * Returns true if the input symbol is an atom which is by assumtion a letter in the English Alphabet
 */
int isAtom(char symbol){
	return (symbol >= 97 && symbol <= 122) || (symbol >= 65 && symbol <= 90);
}

/*
 * Reads the input pure list and builds a tag-data-link representation of the pure list
 * Returns a pointer to the first tag-data-link node
 */
GeneralizedListNode * readInput()
{
	char symbol;
	Stack *S = malloc(sizeof(Stack));
	InitStack(S);

	while(scanf("%c", &symbol) != EOF)
	{
		//printf("%c\n", symbol);
		StackElemType* Temp = malloc(sizeof(StackElemType));
		
		GeneralizedListNode* PrevNode = malloc(sizeof(GeneralizedListNode));
		Temp->generalizedListNode = malloc(sizeof(GeneralizedListNode));
		Temp->character = 0;

		PrevNode = NULL;

		
		if (symbol == '('){
			//("is ( outside");
			Temp->character = symbol;
			PUSH(S, *Temp);}
		else if(isAtom(symbol)){
			//puts("isAtom outside");
			Temp->character = symbol;
			PUSH(S, *Temp);}		
		else if(symbol == ')'){
			//puts("is ) outside");
			
			StackElemType* top = malloc(sizeof(StackElemType));
			if(S->top == 0) break; 
			POP(S, top);
			
			PrevNode = NULL;
			while(S->top != 0){
				if(isAtom(top->character)){
					//puts("isAtom");
					GeneralizedListNode *node = malloc(sizeof(GeneralizedListNode));
					node->tag = 0;
					node->dataAtom = top->character;
					node->dataList = NULL;
					node->link = PrevNode;
					PrevNode = node;

				} else if (top->character == '(') {
					//puts("Closing the ) with (");
					GeneralizedListNode *node = malloc(sizeof(GeneralizedListNode));
					node->tag = 1;																													
					node->dataAtom = 0;
					node->dataList = PrevNode;
					node->link = NULL;
					PrevNode = node;
					Temp->character = 0;
					Temp->generalizedListNode = node;
					PUSH(S, *Temp);
					break;																								
				} else if (top->generalizedListNode != NULL){
					//puts("is Node");
					top->generalizedListNode->link = PrevNode;
					PrevNode = top->generalizedListNode;
				}
	
				POP(S, top);
				
		}
		if(S->top == 0) return PrevNode;		
	}

}
}

void VISIT(GeneralizedListNode *T)
{
	printf("-%c-", T->dataAtom);
}

void traversePureList(GeneralizedListNode *L){
	//puts("TRAVERSE PURE LIST");
	if (L == NULL) return;

	Stack* S = malloc(sizeof(Stack));
	InitStack(S);

	GeneralizedListNode *alpha = L;
	StackElemType *Temp = malloc(sizeof(StackElemType));

	while(1){
		One:
		if(alpha->tag == 0) VISIT(alpha);
		else {
			if(alpha->dataList == NULL) goto Two;
			else{
				
				Temp->generalizedListNode = alpha;
				Temp->character = 0;
				PUSH(S, *Temp);
				alpha = alpha->dataList;
				goto One;
			}
		}

		Two:
		alpha = alpha->link;
		if(alpha == NULL){
			if (S->top==0) return;
			else {
				POP(S, Temp);
				alpha = Temp->generalizedListNode;
				goto Two;
			}
		}

	}

}

// Driver program to test above functions
int main()
{
	GeneralizedListNode *L;
	L = readInput();
	traversePureList(L);
    return 0;
}