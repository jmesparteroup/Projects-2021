#include <stdio.h>
#include <stdlib.h>

#define newline printf("\n")

int **matrix, *visited, *predecessor, *discovery, *finish, time=0;



void INIT_LIST(int);
void BUILD_LIST(int);
void DFS(int, int);
void print(int);

int main () {
    int n;
    scanf("%d", &n);
    INIT_LIST(n);
    BUILD_LIST(n);
    for(int i=1; i<=n; i++)
    {
        if(visited[i] != 1) DFS(i,n);
    }
    //printing
    print(n);

    return 0;
}

void INIT_LIST(int n){
    matrix = malloc((n+1)*sizeof(int*));
    discovery = malloc((n+1)*sizeof(int));
    visited = malloc((n+1)*sizeof(int));
    predecessor = malloc((n+1)*sizeof(int));
    finish = malloc((n+1)*sizeof(int));

    for(int i=1; i<=n; i++) {
        matrix[i] = malloc((n+1)*sizeof(int));
        discovery[i] = 0;
        predecessor[i] = 0;
        finish[i] = 0;
        }
    }



void BUILD_LIST(int n){
    for(int i=1; i<=n; i++) {
        for(int k=1; k<=n; k++) scanf("%d", &matrix[i][k]);
        };
}

void DFS(int node, int n){
    time++;
    visited[node] = 1;
    discovery[node] = time;

    for(int i=1; i<=n; i++){
        if (matrix[node][i] == 1){
            if(visited[i] != 1){
                predecessor[i] = node;
                DFS(i,n);

            }
        }
    }
    
    time++;
    finish[node] = time;
    
}

void print(int n){
    for(int i=1; i<=n; i++) printf("-%d-", predecessor[i]);
    newline;
    for(int i=1; i<=n; i++) printf("-%d-", discovery[i]);
    newline;
    for(int i=1; i<=n; i++) printf("-%d-", finish[i]);
}
