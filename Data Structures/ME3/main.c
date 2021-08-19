#include <stdio.h>
#include <stdlib.h>
#define newline printf("\n");

typedef struct binarytreenode BinaryTreeNode;
struct binarytreenode
{
    BinaryTreeNode *LSON;
    int DATA;
    int BF;
    BinaryTreeNode *RSON;
};


void INSERTNODE(BinaryTreeNode**, int);
void PREORDER(BinaryTreeNode*);
BinaryTreeNode* INITNODE(int);
void ROTATE_RIGHT(BinaryTreeNode**, BinaryTreeNode**, BinaryTreeNode**);
void ROTATE_LEFT(BinaryTreeNode**, BinaryTreeNode**, BinaryTreeNode**);
void ROTATE_RIGHT_LEFT(BinaryTreeNode**, BinaryTreeNode**, BinaryTreeNode**);
void ROTATE_LEFT_RIGHT(BinaryTreeNode**, BinaryTreeNode**, BinaryTreeNode**);


int main (){
    BinaryTreeNode* root = NULL;

    int input;
    scanf("%d", &input);

    while(input!=0){
        INSERTNODE(&root, input);
        PREORDER(root);
        newline;
        scanf("%d", &input);
    }
    return 0;
};

void INSERTNODE(BinaryTreeNode** root, int data){
    BinaryTreeNode *v, *gamma, *alpha, *tao, *phi, *beta, *rho;

    if(*root == NULL){
        *root = INITNODE(data);
        return;
    }

    gamma = *root; alpha = *root;

    while(1){
    //cases
    if(data == gamma->DATA) break;
    else if(data < gamma->DATA) {
        tao = gamma->LSON;
        if(tao == NULL) {
            v = INITNODE(data);
            *(&(gamma->LSON)) = v;
            //printf("\n breakout");
            break;
        }
    }
    else if(data > gamma->DATA){
        tao = gamma->RSON;
        if(tao == NULL){
            v = INITNODE(data);
            *(&(gamma->RSON)) = v;
            //printf("\n breakout");
            break;
        }
    };

    if(tao->BF != 0){
        alpha = tao; phi = gamma;
    };
    gamma = tao;
    };

    if(data < alpha->DATA){
        gamma = alpha->LSON; beta = gamma;
    } else {
        gamma = alpha->RSON; beta = gamma;
    };
    
    //printf("\n test");
    while(gamma != v){
        if(data < gamma->DATA){
            gamma->BF = -1; gamma = gamma->LSON;
        } else {
            gamma->BF = 1; gamma = gamma->RSON;
        }
    }

    int w;
    if(data < alpha->DATA){w = -1;} else {w = 1;};

    if(alpha->BF == 0) alpha->BF = w;
    else if(alpha->BF == -w) alpha->BF = 0;
    else if(alpha->BF == w) {

        //more fucking cases btch
        if(data < alpha->DATA && beta->BF == w) ROTATE_RIGHT(&*root, &alpha, &rho);
        else if(data < alpha->DATA && beta->BF == -w) ROTATE_LEFT_RIGHT(&*root, &alpha, &rho);
        else if(data > alpha->DATA && beta->BF == w) ROTATE_LEFT(&*root, &alpha, &rho);
        else if(data > alpha->DATA && beta->BF == -w) ROTATE_RIGHT_LEFT(&*root, &alpha, &rho);

        if(alpha == *root) *root = rho;
        else if(alpha == phi->LSON) phi->LSON = rho;
        else if(alpha == phi->RSON) phi->RSON = rho;
    }
};

BinaryTreeNode* INITNODE(int data){
    BinaryTreeNode* newNode = malloc(sizeof(BinaryTreeNode));
    newNode->DATA = data;
    newNode->LSON = NULL; newNode->RSON = NULL;
    newNode->BF = 0;

    return newNode;
};

void ROTATE_RIGHT(BinaryTreeNode** root, BinaryTreeNode** alpha, BinaryTreeNode** rho){
    *rho = (*alpha)->LSON; (*alpha)->LSON = (*rho)->RSON; (*rho)->RSON = *alpha;
    (*alpha)->BF = 0; (*rho)->BF = 0;
};

void ROTATE_LEFT(BinaryTreeNode** root, BinaryTreeNode** alpha, BinaryTreeNode** rho){
    *rho = (*alpha)->RSON; (*alpha)->RSON = (*rho)->LSON; (*rho)->LSON = *alpha;
    (*alpha)->BF = 0; (*rho)->BF = 0;
};
void ROTATE_RIGHT_LEFT(BinaryTreeNode** root, BinaryTreeNode** alpha, BinaryTreeNode** rho){
    BinaryTreeNode* beta = (*alpha)->RSON;
    *rho = beta->LSON;
    beta->LSON = (*rho)->RSON;
    (*rho)->RSON = beta;
    (*alpha)->RSON = (*rho)->LSON;
    (*rho)->LSON = *alpha;
    if((*rho)->BF == 0) {
        (*alpha)->BF = 0; beta->BF = 0;
    } else if ((*rho)->BF == 1){
        (*alpha)->BF = -1; beta->BF = 0;
    } else if ((*rho)->BF == -1){
        (*alpha)->BF = 0; beta->BF = 1;
    };
    (*rho)->BF = 0;
};
void ROTATE_LEFT_RIGHT(BinaryTreeNode** root, BinaryTreeNode** alpha, BinaryTreeNode** rho){
    BinaryTreeNode* beta = (*alpha)->LSON;
    *rho = beta->RSON;
    beta->RSON = (*rho)->LSON;
    (*rho)->LSON = beta;
    (*alpha)->LSON = (*rho)->RSON;
    (*rho)->RSON = *alpha;
    if((*rho)->BF == 0) {
        (*alpha)->BF = 0; beta->BF = 0;
    } else if ((*rho)->BF == 1){
        (*alpha)->BF = 0; beta->BF = -1;
    } else if ((*rho)->BF == -1){
        (*alpha)->BF = 1; beta->BF = 0;
    };

    //lacked this bitch kanina
    (*rho)->BF = 0;
};


void PREORDER(BinaryTreeNode* root){
    if (root != NULL)
    {
        printf("-%d-", root->DATA);
        PREORDER(root->LSON);
        PREORDER(root->RSON);
    }
    
};


