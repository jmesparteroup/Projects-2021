
/**
For this code template, you may change the
function bodies as you see fit, except for
the main function.
**/

#include <stdio.h>
#include <stdlib.h>

#define newline printf("\n")

void EQUIVALENCE (void);
int NUM_EQUI_CLASSES(void);
int FIND(int);
void UNION(int, int);
int TEST(int, int);
/**
The following are optional functions.
The use of this functions depends on how you would like to implement EQUIVALENCE

void UNION (int, int);
int FIND (int);
**/

/**
QUIWA book suggested that the FATHER
array be declared as global for easier
implementation of the codes.
**/
// Declare global variables here
int *FATHER; //the global FATHER array
int SIZE; //the global FATHER array size
// Declare global variables here

int main()
{
    EQUIVALENCE ();
    printf("%d", NUM_EQUI_CLASSES());

    free (FATHER);
    return 0;
}

void UNION (int i, int j)
{
    int count = FATHER[i] + FATHER[j];
    if (abs(FATHER[i]) > abs(FATHER[j]))
    {
        FATHER[j] = i; FATHER[i] = count;
    }  else
    {
        FATHER[i] = j; FATHER[j] = count;
    }
}


int FIND(int i)
{
    int r = i;
    while (FATHER[r] > 0){
        r = FATHER[r];
    }
    int j = i, k;
    while(j!=r)
    {
        k = FATHER[j];
        FATHER[j] = r;
        j = k;
    }
    return r;

}

void EQUIVALENCE ()
{

    int i, j, n;

    // get size of S
    scanf("%d", &n);

    FATHER = malloc((n+1)*sizeof(int)); // init Father Array
    for(int item=0; item<=n; item++) FATHER[item]=-1;
    SIZE = n;



    scanf("%d %d", &i, &j);
    while (i != 0 && j != 0)
    {
        i = FIND(i);
        j = FIND(j);
        if(i!=j) UNION(i,j);

        scanf("%d %d", &i, &j);
    }

    return;
}


int TEST (int k, int l)
{
    k = FIND(k);
    l = FIND(l);

    if(k==l){return 1;} else {return 0;};
}

int NUM_EQUI_CLASSES()
{
	int numEquiClasses=0;

    // get 1 element then compare to ebribady
    for(int i=1; i<=SIZE; i++){
        if(FATHER[i]<0) numEquiClasses++;
    };

	/**
	Determine the number of equivalence classes.
	Store it in numEquiClasses variable.
	**/

	return numEquiClasses;
}
