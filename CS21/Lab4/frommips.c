#include <stdio.h>
#include <string.h>
#define CONST_ARR1_LEN 16 //.eqv CONST_ARR1_LEN 16
#define CONST_ARR2_LEN 4 //.eqv  CONST_ARR2_LEN 4

int FOUND, LEN; // stating lines
char ELEM1, ELEM2;


int main(){
    char *P = "bababacabaatest!"; // arr1 is directly stored into P
    char *Q = "abcd"; // arr2 is directly stored into Q
    
    for(int I = 0; I<CONST_ARR1_LEN; I++){ // (outer loop)outer__init, outer__cond, and outer__incr equivalent
        FOUND = 0;  // li FOUND, 0

        for(int K=0; K<CONST_ARR2_LEN; K++){ // (inner loop)inner__init, inner_cond, and inner__incr equivalent
            
            ELEM1 = *(I + P); // equivalent to the pointer arithmetic in the first 4 lines of inner__body
            ELEM2 = *(K + Q); // equivalent to the pointer arithmetic in the 5-8th lines of  

            if(ELEM1 == ELEM2){ // inverse of bne ELEM1, ELEM2, inner__incr
                FOUND = 1; // equivalent to li FOUND, 1
                break; // equivalent to j inner__end
            }
        }
        if(FOUND == 0) break; // beqz FOUND, outer__end
        LEN ++; // addiu LEN, LEN, 1
    }
    printf("%d\n", LEN); // equivalent to move $a0, LEN; do_syscall(1)

}