
BinaryTreeNode* ROTATE_RIGHT(BinaryTreeNode* Tree, BinaryTreeNode* alpha, BinaryTreeNode* rho){
    printf("\nCALLING ROTATE RIGHT");
    rho = alpha->LSON;
    alpha->LSON = rho->RSON;
    rho->RSON = alpha;
    rho->BF = 0; alpha->BF = 0;