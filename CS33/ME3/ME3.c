#include <stdio.h>
#include <stdlib.h>
#define newline printf("\n")

typedef struct binarytreenode BinaryTreeNode;
    struct binarytreenode
    {
        BinaryTreeNode *LSON;
        int DATA;
        int BF;
        BinaryTreeNode *RSON;

    };

void BUILD_TREE(BinaryTreeNode*);
void PREORDER_TRAVERSAL(BinaryTreeNode*);
void INSERT(BinaryTreeNode*, int); 
BinaryTreeNode* ROTATE_RIGHT(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);
BinaryTreeNode* ROTATE_RIGHT_LEFT(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);
BinaryTreeNode* ROTATE_LEFT(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);
BinaryTreeNode* ROTATE_LEFT_RIGHT(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);


BinaryTreeNode* alpha, *y, *tao, *phi, *v ,*beta, *rho, *HEAD;

int main () {

    //accept inputs
    int input, size = 0;

    HEAD = malloc(sizeof(BinaryTreeNode));
    HEAD->DATA = 0;

    scanf("%d", &input); 
    
    while(input != 0){
        //printf("\nInserting: %d \n", input);
        INSERT(HEAD, input);
        newline;
        //printf("\nHEAD->DATA: %d\n", HEAD->DATA);
        PREORDER_TRAVERSAL(HEAD);
        newline;
        //accept again
        //printf("\nInserted: %d \n", input);
        scanf("%d",&input);
    }

    printf("Done");

};

void INSERT(BinaryTreeNode* Tree, int data){
    //check if empty
    if(Tree->DATA == 0){
        //printf("\nInit Tree:");
        Tree->DATA = data; Tree->LSON = NULL; Tree->RSON = NULL; Tree->BF=0; 
        //printf("\nInitializing Tree done");
        return;//initialize head
    };
    y = Tree; alpha = Tree;

    while(1){
        if(data == y->DATA){
            printf("Duplicate Key");
            return;
        };

        if(data < y->DATA){
            tao = y->LSON;
            if(tao == NULL){
                v = malloc(sizeof(BinaryTreeNode));
                y->LSON = v;
                v->DATA = data; v->LSON = NULL; v->RSON = NULL; v->BF = 0;
                break;
            }
        }

        if(data > y->DATA){
            tao = y->RSON;
            if(tao == NULL){
                v = malloc(sizeof(BinaryTreeNode));
                y->RSON = v;
                v->DATA = data; v->LSON = NULL; v->RSON = NULL; v->BF = 0;
                break;
            };
        }

        if(tao->BF != 0) {alpha = tao; phi = y;};
        y = tao;
        //printf("\nLoopin here in data != y->DATA \n");
    }   
    
    if(data < alpha->DATA){
        y = alpha->LSON; beta = alpha->LSON;
    } else{
        y = alpha->RSON; beta = alpha->RSON;
    }

    while(y->DATA != v->DATA){
        //printf("\nLoopin here in y != v \n");
        if(data < y->DATA){ 
            y->BF += -1; y = y->LSON;
        } else {
            y->BF += 1; y = y->RSON;
        };
    }

    //printf("Root BF: %d", Tree->BF);

    int w=0;
    if(data < alpha->DATA) {w=-1;} else {w=1;}; 
    //printf("\nif(data < alpha->DATA) w=-1; else w =1;");

    if(alpha->BF == 0) alpha->BF = w;
    else if(alpha->BF == -1*w) alpha->BF =0;
    else if(alpha->BF == w){
            //call cases for rotation
        rho = alpha; // default
            //printf("\ncall cases for rotation");
        //printf("\n data = %d | Data(a) = %d | BF(b) = %d", data, alpha->DATA, beta->BF);
        if(data<alpha->DATA && beta->BF == -1){
            rho = alpha->LSON;
            alpha->LSON = rho->RSON;
            rho->RSON = alpha;
            rho->BF = 0; alpha->BF = 0;
            }
        else if(data<alpha->DATA && beta->BF == 1){
            BinaryTreeNode *b = alpha->LSON;
            rho = b->RSON;
            b->RSON = rho->LSON;
            rho->LSON = b;
            alpha->LSON = rho->RSON;
            rho->RSON = alpha;

            if(rho->BF == 0) {alpha->BF = 0; b->BF = 0;};
            if(rho->BF == 1) {alpha->BF = 0; b->BF += -1;};
            if(rho->BF ==-1) {alpha->BF += 1; b->BF = 0;};

            rho->BF = 0;
            }
        else if(data>alpha->DATA && beta->BF == -1){
            rho = alpha->RSON;
            alpha->RSON = rho->LSON;
            rho->LSON = alpha;
            rho->BF = 0; alpha->BF = 0;
            }
        else if(data>alpha->DATA && beta->BF == 1) {
            BinaryTreeNode* b = alpha->RSON;
            rho = b->LSON;
            b->LSON = rho->RSON;
            rho->RSON = b;
            alpha->RSON = rho->LSON;
            rho->LSON = alpha;

            //cases again wtf???
            if(rho->BF == 0) {alpha->BF = 0; b->BF = 0;};
            if(rho->BF == 1) {alpha->BF += -1; b->BF = 0;};
            if(rho->BF == -1) {alpha->BF = 0; b->BF += 1;};

            rho->BF = 0;
            };

        //printf("\nnew cases because sabi sa pseudocode");
            //new cases because sabi sa pseudocode

        //printf("\n Tree->data = %d | Data(a) = %d | rho->Data = %d", Tree->DATA, alpha->DATA, rho->DATA);
        if(alpha->DATA == Tree->DATA){
            Tree = rho;}
        else if(alpha->DATA == phi->LSON->DATA){phi->LSON = rho;}
        else if(alpha->DATA == phi->RSON->DATA){phi->RSON = rho;};
            //printf("\ndone with the case yow");
        };
    return;
};


/*
BinaryTreeNode* ROTATE_RIGHT(BinaryTreeNode* Tree, BinaryTreeNode* alpha, BinaryTreeNode* rho){
    printf("\nCALLING ROTATE RIGHT");
    rho = alpha->LSON;
    alpha->LSON = rho->RSON;
    rho->RSON = alpha;
    rho->BF = 0; alpha->BF = 0;
    return rho;
};

BinaryTreeNode* ROTATE_LEFT(BinaryTreeNode* Tree, BinaryTreeNode* alpha, BinaryTreeNode* rho){
    printf("\nCALLING ROTATE LEFT");
    rho = alpha->RSON;
    alpha->RSON = rho->LSON;
    rho->LSON = alpha;
    rho->BF = 0; alpha->BF = 0;
    return;

};

BinaryTreeNode* ROTATE_LEFT_RIGHT(BinaryTreeNode* Tree, BinaryTreeNode* alpha, BinaryTreeNode* rho){
    printf("\nCALLING ROTATE LEFT_RIGHT");
    BinaryTreeNode* beta = alpha->LSON;
    rho = beta->RSON;
    beta->RSON = rho->LSON;
    rho->LSON = beta;
    alpha->LSON = rho->RSON;
    rho->RSON = alpha;

    if(rho->BF == 0) {alpha->BF = 0; beta->BF = 0;};
    if(rho->BF == 1) {alpha->BF = 0; beta->BF += -1;};
    if(rho->BF ==-1) {alpha->BF += 1; beta->BF = 0;};

    rho->BF = 0;
    return;
}

BinaryTreeNode* ROTATE_RIGHT_LEFT(BinaryTreeNode* Tree, BinaryTreeNode* alpha, BinaryTreeNode* rho){
    printf("\nCALLING ROTATE RIGHT_LEFT");
    BinaryTreeNode* beta = alpha->RSON;
    rho = beta->LSON;
    beta->LSON = rho->RSON;
    rho->RSON = beta;
    alpha->RSON = rho->LSON;
    rho->LSON = alpha;

    //cases again wtf???
    if(rho->BF == 0) {alpha->BF = 0; beta->BF = 0;};
    if(rho->BF == 1) {alpha->BF += -1; beta->BF = 0;};
    if(rho->BF == -1) {alpha->BF = 0; beta->BF += 1;};

    rho->BF = 0;
    return;
};
*/
void PREORDER_TRAVERSAL(BinaryTreeNode* alpha){
    if(alpha != NULL){
        printf("-%d-",alpha->DATA);
        PREORDER_TRAVERSAL(alpha->LSON); PREORDER_TRAVERSAL(alpha->RSON);
    }
};