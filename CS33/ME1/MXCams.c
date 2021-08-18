#include <stdio.h>
#include <math.h>
#define newline printf("/n")

int main () {
    double IC, AC, M, F, i, a, b, c, fa, fb, fc, lowerlimit, higherlimit;

    printf("Input initial  construction cost: ");
    scanf("%lf", &IC);
    newline;

    printf("Input annual maintenance cost: ");
    scanf("%lf", &AC);
    newline;
    
    printf("Input average annual number of motorist: ");
    scanf("%lf", &M);
    newline;

    printf("Input interest rate: ");
    scanf("%lf", &i);
    newline;

    printf("Input annual fee per motorist: ");
    scanf("%lf", &F);
    newline;

    printf("Input initial lower limit of number of years to break-even: ");
    scanf("%lf", &lowerlimit);
    newline;

    printf("Input initial higher limit of number of years to break-even: ");
    scanf("%lf", &higherlimit);
    newline;


    for(int count = 0; count < 100; count ++){

    }
    return 0;
}