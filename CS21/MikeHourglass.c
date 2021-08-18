// Online C compiler to run C program online
#include <stdio.h>
#define N 5
int main() {
    printf("o");
    for(int lines = 1 + 2*N; lines != 0; lines--){
        printf("-");
    }
    printf("o\n");
    int outside_space = 1;
    int inside_space = 2*N - 1;
    while(inside_space > 0){
        for(int temp = outside_space;temp != 0; temp--){
            printf(" ");
        }
        printf("\\");
        for(int temp = inside_space;temp != 0; temp--){
            printf(" ");
        }
        printf("/\n");
        outside_space++;
        inside_space--;
        inside_space--;
    }

    for(int temp = outside_space;temp != 0; temp--){
            printf(" ");
    }
    
    printf("X\n");
    outside_space--;
    inside_space = 1;
    while(inside_space < 2*N+1){
        for(int temp = outside_space;temp != 0; temp--){
            printf(" ");
        }
        printf("/");
        for(int temp = inside_space;temp != 0; temp--){
            printf(".");
        }
        printf("\\\n");
        outside_space--;
        inside_space++;
        inside_space++;
    }
    
    printf("o");
    for(int lines = 1 + 2*N; lines != 0; lines--){
        printf("-");
    }
    printf("o\n");
    
    return 0;
}