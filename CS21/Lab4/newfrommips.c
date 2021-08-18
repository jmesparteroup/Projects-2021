#include <stdio.h>
#include <string.h>
#define CONST_ARR1_LEN 8
#define CONST_ARR2_LEN 3

int FOUND, LEN;
char ELEM1, ELEM2;

int P[8] = {0,0,-1,1,0,1,2,1};
int Q[] = {1,0,-1};

int main(){


    for(int I = 0; I<CONST_ARR1_LEN; I++){
        FOUND = 0;

        for(int K=0; K<CONST_ARR2_LEN; K++){
            
            ELEM1 = *(I + P);
            
            ELEM2 = *(K + Q);
            printf("%d %d\n", ELEM1, ELEM2);

            if(ELEM1 == ELEM2){
                FOUND = 1;
                break;
            }
        
        }
        if(FOUND == 0) break;
        LEN ++;
    }
    printf("%d\n", LEN);
}

