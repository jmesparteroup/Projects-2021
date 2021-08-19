    #include <stdio.h>
    #include <stdlib.h>
    #define INF 69696969

    typedef struct node Node;
        struct node
        {
            int VRTX;
            int COST;
            Node *NEXT;
            };

    typedef struct tree
        {
            int size;
            Node **LIST;
            int *pred;
            } Tree;

    typedef struct priorityqueue
            {
            int size;
            int *heap;
            int *key;
            int *index;
            } PriorityQueue;

    int EXTRACT_MIN (PriorityQueue*);
    PriorityQueue *DECREASE_KEY (PriorityQueue*, int, int);
    PriorityQueue *INIT_PQ(Tree*, int);
    PriorityQueue *HEAPIFY(PriorityQueue*, int);
    void INIT_TREE(Tree*, int);
    Tree *PRIM(Tree*, int);
    void DISPLAY_MST(Tree*);
    void PQ_UNDERFLOW();

    int main() 
    {
        int n;
        // initialize G
        scanf("%d", &n);
        if(n == 0) printf("0");
        Tree *G = malloc(sizeof(Tree));
        INIT_TREE(G, n);
        G = PRIM(G,1);
        DISPLAY_MST(G);
    }

    void INIT_TREE(Tree* G, int size){
        G->size = size;
        G->LIST = malloc((size+1)*sizeof(Node*));
        G->pred = malloc((size+1)*sizeof(int));

        for (int i = 1; i <= size; i++)
        {
            G->LIST[i] = malloc(sizeof(Node));
            G->LIST[i]->NEXT = NULL;
            G->LIST[i]->VRTX = 0;
            G->LIST[i]->COST = 0;
            G->pred[i] = 0;
        }

        int cost;

        //ACCEPT INPUT IN A 2D MATRIX;
        int **matrix = malloc((size+1)*sizeof(int*));
        for(int i = 1; i<= size; i++) matrix[i] = malloc((size+1)*sizeof(int));
        for (int i = 1; i<= size; i++) for(int j=1; j<= size; j++) scanf("%d", &matrix[i][j]);

        //SETUP A LIST REPRESENTATION OF A WEIGHTED GRAPH.
        for (int i=1; i<= size; i++){
            //printf("LIST REPRESENTATION [%d] \n", i);
            
            for(int j=size; j>=1; j--){

                if(matrix[i][j] > 0){
                    Node* alpha = malloc(sizeof(Node)), *beta;
                    alpha->VRTX = j;
                    alpha->COST = matrix[i][j];
                    beta = G->LIST[i]->NEXT;
                    alpha->NEXT = beta;
                    G->LIST[i]->NEXT = alpha;
                    
                }
            }

        }

        return;
    }

    Tree *PRIM (Tree *G, int s){

        int j, l;
        Node* alpha = malloc(sizeof(Node));

        PriorityQueue *PQ = INIT_PQ(G, s);
        G->pred[s] = 0;

        while (PQ->size != 0){
            j = EXTRACT_MIN(PQ);

            PQ->key[j] = -INF;
            alpha = G->LIST[j]->NEXT;

            while (alpha != NULL){

                l = alpha->VRTX;


                if(alpha->COST < PQ->key[l]){
                    G->pred[l] = j;
                    PQ = DECREASE_KEY(PQ, l, alpha->COST);
                };
                alpha = alpha->NEXT;
            }
        }

        return G;
    }

    PriorityQueue *INIT_PQ(Tree *G, int s) {
        int i = 1, size = G->size;
        PriorityQueue* PQ = malloc(sizeof(PriorityQueue));
        PQ->heap = malloc((size+1)*sizeof(int));
        PQ->index = malloc((size+1)*sizeof(int));
        PQ->key = malloc((size+1)*sizeof(int));
        
        for(int l = 1; l <= G->size; l++){
        if (l == s) {
            PQ->heap[1] = s; PQ->index[s] = 1; PQ->key[s] = -INF;
        } else {
            i++; PQ->heap[i] = l; PQ->index[l] = i; PQ->key[l] = INF;
        }

        PQ->size = size;
        }
        
        return PQ;
    }

    int EXTRACT_MIN (PriorityQueue* PQ){

        int j;
        if(PQ->size == 0) PQ_UNDERFLOW();
        else {
            j = PQ->heap[1]; 
            PQ->heap[1] = PQ->heap[PQ->size];
            PQ->index[PQ->heap[1]] = 1;
            PQ->size --;
            PQ = HEAPIFY(PQ, 1);
        }
        return j;
    }

    void PQ_UNDERFLOW(){
        puts("Priority Queue underflow.");
        return;
    }

    PriorityQueue *DECREASE_KEY (PriorityQueue* PQ, int l, int newkey){
        PQ->key[l] = newkey;
        int i = PQ->index[l],
        j = i/2;

        while (i>1 && PQ->key[PQ->heap[j]] > newkey) {
            PQ->heap[i] = PQ->heap[j];
            PQ->index[PQ->heap[j]] = i;
            i = j; j = i/2;
        }
        PQ->heap[i] = l;
        PQ->index[l] = i;

        return PQ;
    }

    PriorityQueue *HEAPIFY(PriorityQueue* PQ, int r){
        int k = PQ->key[PQ->heap[r]], l = PQ->heap[r], i = r, j = 2*i;

        //printf("%d %d\n", j, PQ->size);
        while (j <= PQ->size){
            if(j < PQ->size && PQ->key[PQ->heap[j+1]] < PQ->key[PQ->heap[j]]) j++;
            if(PQ->key[PQ->heap[j]] < k) {
                PQ->heap[i] = PQ->heap[j];
                PQ->index[PQ->heap[j]] = i;
                i = j;
                j = 2*i;
            } else break;
        }

        PQ->heap[i] = l;
        PQ->index[l] = i;

        return PQ;
    }

    void DISPLAY_MST(Tree* G){
        Node* alpha;

        int TCost = 0, j;
        for (int l = 1; l <= G->size; l++){
            if(G->pred[l] != 0 ){
                alpha = G->LIST[l];
                while(alpha != NULL){
                    j = alpha->VRTX;
                    if(G->pred[l] == j){
                        printf("(%d, %d) -- %d\n", l, j, alpha->COST);
                        TCost += alpha->COST;
                    }
                    alpha = alpha->NEXT;
                }
            }
        }
        printf("%d", TCost);
    }