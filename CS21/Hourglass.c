#include <stdio.h>
#define N 10
#define newline printf("\n")

int main(){
    int left = 0;
    int right = 2*N-1;

    // head
    printf("o");
    for (int i=0; i<N*2+1; i++){
        printf("-");
    }; printf("o"); newline;

    //upper
    for(int i=0; i<N; i++){
        left += 1; right = 2*N-1-2*i;
        for(int j=0; j < left; j++){
            printf(" ");
        }; printf("\\");
        for(int j=right; j>0; j--){
            printf(" ");
        }; printf("/");
        newline;
    }

    //X in the middle
    for(int i=0; i<=N; i++){
        printf(" ");
    }; printf("X"); newline;

    //lower
    for(int i=0; i<N; i++){
        
        for(int j=0; j < left; j++){
            printf(" ");
        }; printf("/");
        for(int j=right; j>0; j--){
            printf(".");
        }; printf("\\");
        newline;
        left --; right += 2;
    }
     // head
    printf("o");
    for (int i=0; i<N*2+1; i++){
        printf("-");
    }; printf("o");

    return 0;
}
