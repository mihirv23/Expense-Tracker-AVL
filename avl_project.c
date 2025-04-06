#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NAME_LEN 50
#define CATEGORY_LEN 50

typedef struct user{
    int user_id;
    char name[NAME_LEN];
    float income;
    struct user* left ;
    struct user* right;
    struct user* next; //only tobe used when storing in family
}user_tree ;

typedef struct fam{
    int fam_id; // this will be referenced from struct user 
    int count;// keeping track of number of family members
    user_tree* next_user;// given a pointer to a node of type user, so that family members can be represented using a linked list within a fam node
    char fam_name[NAME_LEN];
    float fam_income,fam_expense;
    struct fam* left;
    struct fam* right;   
}fam_tree;

typedef struct expense{
    int expense_id;
    char expense_cat[CATEGORY_LEN];// also check for whether date will be int or string 
    float exp_amt;
    int date;
    int member_id ; // same as the user id one 
    struct expense* left ;
    struct expense* right ;
    
}expense_tree;

user_tree* makeNode_user(int mem_id ,float income_user,char name_user[] ){

    user_tree* nptr ;
    nptr = (user_tree*)malloc(sizeof(user_tree));
    if(nptr != NULL){
        nptr->income = income_user ;
        nptr->user_id = mem_id ;
        
        strcpy(nptr->name , name_user);
        nptr->left = NULL;
        nptr->right = NULL;
        nptr->next = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}

expense_tree* makeNode_expense(int exp_id ,float exp_amt,char exp_cat[],int date,int mem_id ){

    expense_tree* nptr ;
    nptr = (expense_tree*)malloc(sizeof(expense_tree));
    if(nptr != NULL){
        nptr->exp_amt = exp_amt ;
        nptr->expense_id = exp_id ;
        strcpy(nptr->expense_cat , exp_cat);
        nptr->date = date;
        nptr->member_id = mem_id ;
        nptr->left = NULL;
        nptr->right = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}

fam_tree* makeNode_fam(int fam_id ,float fam_income,float fam_expense,char fam_name[NAME_LEN],int count, user_tree* next_user ){

    fam_tree* nptr ;
    nptr = (fam_tree*)malloc(sizeof(fam_tree));
    if(nptr != NULL){
        nptr->count = count;
        nptr->fam_id = fam_id;
        nptr->fam_expense = fam_expense;
        nptr->fam_income = fam_income ;
        nptr->next_user = next_user ;
        strcpy(nptr->fam_name, fam_name);
        nptr->left = NULL;
        nptr->right = NULL;
    }
    else{
        nptr = NULL ;
        printf("Memory dosent exist \n");
    }
    return nptr ;
}



void rotateRight(user_tree** r){
    user_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->left == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->left ;
        (*r)->left = temp->right ;
        temp->right = *r ;
    }
    *r = temp;
    
}

void rotateRightExp(expense_tree** r){
    expense_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->left == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->left ;
        (*r)->left = temp->right ;
        temp->right = *r ;
    }
    *r = temp;
    
}

void rotateRightFam(fam_tree** r){
    fam_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->left == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->left ;
        (*r)->left = temp->right ;
        temp->right = *r ;
    }
    *r = temp;
    
}

void rotateRightExpDate(expense_tree** r){
    expense_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->left == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->left ;
        (*r)->left = temp->right ;
        temp->right = *r ;
    }
    *r = temp;
    
}


void rotateLeft(user_tree** r){
    user_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->right == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->right ;
        (*r)->right = temp->left ;
        temp->left = *r ;
    }
    *r = temp ;
    
}

void rotateLeftExp(expense_tree** r){
    expense_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->right == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->right ;
        (*r)->right = temp->left ;
        temp->left = *r ;
    }
    *r = temp ;
    
}

void rotateLeftFam(fam_tree** r){
    fam_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->right == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->right ;
        (*r)->right = temp->left ;
        temp->left = *r ;
    }
    *r = temp ;
    
}

void rotateLeftExpDate(expense_tree** r){
    expense_tree* temp = *r;
    if(*r == NULL){
        printf("Error\n");
    }
    else if((*r)->right == NULL){
        printf("Cannot rotate\n");
    }
    else{
        temp = (*r)->right ;
        (*r)->right = temp->left ;
        temp->left = *r ;
    }
    *r = temp ;
    
}



int heightTree(user_tree*root,user_tree** unbalanced1,int* maxDepth){
    int retval;
    if(root == NULL){
        retval = -1;
    }
    else{
        int left_ht, right_ht ;
        left_ht = heightTree(root->left,unbalanced1,maxDepth);
        right_ht = heightTree(root->right,unbalanced1,maxDepth);

        retval = 1 + ((left_ht > right_ht) ? left_ht : right_ht);
        
        if (abs(left_ht - right_ht) > 1) {
            int currentDepth = retval;
            if (*unbalanced1 == NULL || currentDepth > *maxDepth) { 
                *unbalanced1 = root;
                *maxDepth = currentDepth;  // Update maxDepth to this unbalanced node's depth
                // printf("Unbalanced node is %d at depth %d\n", (*unbalanced1)->data, *maxDepth);
                printf("Updated unbalanced1 = %d at depth %d\n", root->user_id, *maxDepth);
            }
        }
        
    }
    //yaha  initialy maxDeth ko kuch intmax rakhna 
    return retval;
}

int heightTreeExp(expense_tree*root,expense_tree** unbalanced1,int* maxDepth){
    int retval;
    if(root == NULL){
        retval = -1;
    }
    else{
        int left_ht, right_ht ;
        left_ht = heightTreeExp(root->left,unbalanced1,maxDepth);
        right_ht = heightTreeExp(root->right,unbalanced1,maxDepth);

        retval = 1 + ((left_ht > right_ht) ? left_ht : right_ht);
        
        if (abs(left_ht - right_ht) > 1) {
            int currentDepth = retval;
            if (*unbalanced1 == NULL || currentDepth > *maxDepth) { 
                *unbalanced1 = root;
                *maxDepth = currentDepth;  // Update maxDepth to this unbalanced node's depth
                // printf("Unbalanced node is %d at depth %d\n", (*unbalanced1)->data, *maxDepth);
                printf("Updated unbalanced1 = %d and %d at depth %d\n", root->member_id,root->expense_id, *maxDepth);
            }
        }
        
    }
    //yaha  initialy maxDeth ko kuch intmax rakhna 
    return retval;
}

int heightTreeFam(fam_tree*root,fam_tree** unbalanced1,int* maxDepth){
    int retval;
    if(root == NULL){
        retval = -1;
    }
    else{
        int left_ht, right_ht ;
        left_ht = heightTreeFam(root->left,unbalanced1,maxDepth);
        right_ht = heightTreeFam(root->right,unbalanced1,maxDepth);

        retval = 1 + ((left_ht > right_ht) ? left_ht : right_ht);
        
        if (abs(left_ht - right_ht) > 1) {
            int currentDepth = retval;
            if (*unbalanced1 == NULL || currentDepth > *maxDepth) { 
                *unbalanced1 = root;
                *maxDepth = currentDepth;  // Update maxDepth to this unbalanced node's depth
                // printf("Unbalanced node is %d at depth %d\n", (*unbalanced1)->data, *maxDepth);
                printf("Updated unbalanced1 = %d at depth %d\n", root->fam_id, *maxDepth);
            }
        }
        
    }
    //yaha  initialy maxDeth ko kuch intmax rakhna 
    return retval;
}

int heightTreeExpDate(expense_tree*root,expense_tree** unbalanced1,int* maxDepth){
    int retval;
    if(root == NULL){
        retval = -1;
    }
    else{
        int left_ht, right_ht ;
        left_ht = heightTreeExpDate(root->left,unbalanced1,maxDepth);
        right_ht = heightTreeExpDate(root->right,unbalanced1,maxDepth);

        retval = 1 + ((left_ht > right_ht) ? left_ht : right_ht);
        
        if (abs(left_ht - right_ht) > 1) {
            int currentDepth = retval;
            if (*unbalanced1 == NULL || currentDepth > *maxDepth) { 
                *unbalanced1 = root;
                *maxDepth = currentDepth;  // Update maxDepth to this unbalanced node's depth
                // printf("Unbalanced node is %d at depth %d\n", (*unbalanced1)->data, *maxDepth);
                printf("Updated unbalanced1 = %d  at depth %d\n", root->date, *maxDepth);
            }
        }
        
    }
    //yaha  initialy maxDeth ko kuch intmax rakhna 
    return retval;
}


user_tree* checkRotate(user_tree **root,user_tree** unbalanced1, int* maxDepth) {
    // The root being passed is unbalanced.
    // Now we need to check the LST and RST height and then accordingly move forward (4 cases).

    int leftHeight = heightTree((*root)->left, unbalanced1, maxDepth);
    int rightHeight = heightTree((*root)->right, unbalanced1, maxDepth);
    
    if (rightHeight > leftHeight) {
        user_tree* m = (*root)->right;
        int mLeftHeight = heightTree(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTree(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) == 1) {
            if (mLeftHeight > mRightHeight) {
                rotateRight(&((*root)->right));
                rotateLeft(root);
                printf("One right for bachha and one left for baap done\n");
            } else {
                rotateLeft(root);
                printf("Baap rotated left\n");
            }
        }
    } else {
        user_tree* m = (*root)->left;
        int mLeftHeight = heightTree(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTree(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) <= 1) {
            if (mLeftHeight >= mRightHeight) {
                rotateRight(root);
                printf("Baap rotated right\n");
                // printf("After rotation root is %d\n",(*root)->data);
            } else {
                rotateLeft(&((*root)->left));
                rotateRight(root);
                printf("One left for bachha and one right for baap done\n");
            }
        }
    }
    //imp step
    // (*unbalanced1) = NULL ;
    return (*root);
}

expense_tree* checkRotateExp(expense_tree **root,expense_tree** unbalanced1, int* maxDepth) {
    // The root being passed is unbalanced.
    // Now we need to check the LST and RST height and then accordingly move forward (4 cases).

    int leftHeight = heightTreeExp((*root)->left, unbalanced1, maxDepth);
    int rightHeight = heightTreeExp((*root)->right, unbalanced1, maxDepth);
    
    if (rightHeight > leftHeight) {
        expense_tree* m = (*root)->right;
        int mLeftHeight = heightTreeExp(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeExp(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) == 1) {
            if (mLeftHeight > mRightHeight) {
                rotateRightExp(&((*root)->right));
                rotateLeftExp(root);
                printf("One right for bachha and one left for baap done\n");
            } else {
                rotateLeftExp(root);
                printf("Baap rotated left\n");
            }
        }
    } else {
        expense_tree* m = (*root)->left;
        int mLeftHeight = heightTreeExp(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeExp(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) <= 1) {
            if (mLeftHeight >= mRightHeight) {
                rotateRightExp(root);
                printf("Baap rotated right\n");
                // printf("After rotation root is %d\n",(*root)->data);
            } else {
                rotateLeftExp(&((*root)->left));
                rotateRightExp(root);
                printf("One left for bachha and one right for baap done\n");
            }
        }
    }
    //imp step
    // (*unbalanced1) = NULL ;
    return (*root);
}

fam_tree* checkRotateFam(fam_tree **root,fam_tree** unbalanced1, int* maxDepth) {
    // The root being passed is unbalanced.
    // Now we need to check the LST and RST height and then accordingly move forward (4 cases).

    int leftHeight = heightTreeFam((*root)->left, unbalanced1, maxDepth);
    int rightHeight = heightTreeFam((*root)->right, unbalanced1, maxDepth);
    
    if (rightHeight > leftHeight) {
        fam_tree* m = (*root)->right;
        int mLeftHeight = heightTreeFam(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeFam(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) == 1) {
            if (mLeftHeight > mRightHeight) {
                rotateRightFam(&((*root)->right));
                rotateLeftFam(root);
                printf("One right for bachha and one left for baap done\n");
            } else {
                rotateLeftFam(root);
                printf("Baap rotated left\n");
            }
        }
    } else {
        fam_tree* m = (*root)->left;
        int mLeftHeight = heightTreeFam(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeFam(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) <= 1) {
            if (mLeftHeight >= mRightHeight) {
                rotateRightFam(root);
                printf("Baap rotated right\n");
                // printf("After rotation root is %d\n",(*root)->data);
            } else {
                rotateLeftFam(&((*root)->left));
                rotateRightFam(root);
                printf("One left for bachha and one right for baap done\n");
            }
        }
    }
    //imp step
    // (*unbalanced1) = NULL ;
    return (*root);
}

expense_tree* checkRotateExpDate(expense_tree **root,expense_tree** unbalanced1, int* maxDepth) {
    // The root being passed is unbalanced.
    // Now we need to check the LST and RST height and then accordingly move forward (4 cases).

    int leftHeight = heightTreeExpDate((*root)->left, unbalanced1, maxDepth);
    int rightHeight = heightTreeExpDate((*root)->right, unbalanced1, maxDepth);
    
    if (rightHeight > leftHeight) {
        expense_tree* m = (*root)->right;
        int mLeftHeight = heightTreeExpDate(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeExpDate(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) == 1) {
            if (mLeftHeight > mRightHeight) {
                rotateRightExpDate(&((*root)->right));
                rotateLeftExpDate(root);
                printf("One right for bachha and one left for baap done\n");
            } else {
                rotateLeftExpDate(root);
                printf("Baap rotated left\n");
            }
        }
    } else {
        expense_tree* m = (*root)->left;
        int mLeftHeight = heightTreeExpDate(m->left, unbalanced1, maxDepth);
        int mRightHeight = heightTreeExpDate(m->right, unbalanced1, maxDepth);

        if (abs(mLeftHeight - mRightHeight) <= 1) {
            if (mLeftHeight >= mRightHeight) {
                rotateRightExpDate(root);
                printf("Baap rotated right\n");
                // printf("After rotation root is %d\n",(*root)->data);
            } else {
                rotateLeftExpDate(&((*root)->left));
                rotateRightExpDate(root);
                printf("One left for bachha and one right for baap done\n");
            }
        }
    }
    //imp step
    // (*unbalanced1) = NULL ;
    return (*root);
}



user_tree* searchSubs(user_tree *root,int e, user_tree**unbalanced1, int* maxDepth){
    if(root==NULL){return root;}
    if(root->user_id == e){
        root = checkRotate(unbalanced1,unbalanced1,maxDepth);
        
    }
    else if((root->left != NULL)&&(root->left->user_id == e)){
        user_tree* rotatedTree = checkRotate(unbalanced1,unbalanced1,maxDepth);
        root->left = rotatedTree ;
        
        
    }
    else if((root->right != NULL)&&(root->right->user_id == e)){
        user_tree* rotatedTree = checkRotate(unbalanced1,unbalanced1,maxDepth);
        // printf("After insertion changed child root is %d\n",rotatedTree->user_id);
        root->right = rotatedTree ; //glitch statemnt 
        
        
    }
    else{
        if(root->user_id > e){
            searchSubs(root->left,e,unbalanced1,maxDepth);
        }
        else{
            searchSubs(root->right,e,unbalanced1,maxDepth);
        }
        
    }

    // printf("Final root is after searchSubs %d\n",root->user_id);
    return root;
}

expense_tree* searchSubsExp(expense_tree *root,int u,int e,expense_tree **unbalanced1, int* maxDepth){
    if(root==NULL){return root;}
    if(root->member_id == u){
        if (root->expense_id == e) {
            root = checkRotateExp(unbalanced1, unbalanced1, maxDepth);
        }
        else if ((root->left != NULL) && (root->left->member_id == u) && (root->left->expense_id == e)) {
            expense_tree* rotatedTree = checkRotateExp(unbalanced1, unbalanced1, maxDepth);
            root->left = rotatedTree;
        }
        else if ((root->right != NULL) && (root->right->member_id == u) && (root->right->expense_id == e)) {
            expense_tree* rotatedTree = checkRotateExp(unbalanced1, unbalanced1, maxDepth);
            root->right = rotatedTree;
        }
        else {
            // If same user_id but different exp_id, continue searching
            if (root->expense_id > e) {
                searchSubsExp(root->left, u, e, unbalanced1, maxDepth);
            } else {
                searchSubsExp(root->right, u, e, unbalanced1, maxDepth);
            }
        }
    }
    else{
        if (root->member_id > u) {
            searchSubsExp(root->left, u, e, unbalanced1, maxDepth);
        } 
        else {
            searchSubsExp(root->right, u, e, unbalanced1, maxDepth);
        }
    }
    return root;
}

fam_tree* searchSubsFam(fam_tree *root,int e, fam_tree**unbalanced1, int* maxDepth){
    if(root==NULL){return root;}
    if(root->fam_id == e){
        root = checkRotateFam(unbalanced1,unbalanced1,maxDepth);
        
    }
    else if((root->left != NULL)&&(root->left->fam_id == e)){
        fam_tree* rotatedTree = checkRotateFam(unbalanced1,unbalanced1,maxDepth);
        root->left = rotatedTree ;
        
        
    }
    else if((root->right != NULL)&&(root->right->fam_id == e)){
        fam_tree* rotatedTree = checkRotateFam(unbalanced1,unbalanced1,maxDepth);
        // printf("After insertion changed child root is %d\n",rotatedTree->user_id);
        root->right = rotatedTree ; //glitch statemnt 
        
        
    }
    else{
        if(root->fam_id > e){
            searchSubsFam(root->left,e,unbalanced1,maxDepth);
        }
        else{
            searchSubsFam(root->right,e,unbalanced1,maxDepth);
        }
        
    }

    // printf("Final root is after searchSubs %d\n",root->user_id);
    return root;
}

expense_tree* searchSubsExpDate(expense_tree *root,int e, expense_tree**unbalanced1, int* maxDepth){
    if(root==NULL){return root;}
    if(root->date == e){
        root = checkRotateExpDate(unbalanced1,unbalanced1,maxDepth);
        
    }
    else if((root->left != NULL)&&(root->left->date == e)){
        expense_tree* rotatedTree = checkRotateExpDate(unbalanced1,unbalanced1,maxDepth);
        root->left = rotatedTree ;
        
        
    }
    else if((root->right != NULL)&&(root->right->date == e)){
        expense_tree* rotatedTree = checkRotateExpDate(unbalanced1,unbalanced1,maxDepth);
        // printf("After insertion changed child root is %d\n",rotatedTree->user_id);
        root->right = rotatedTree ; //glitch statemnt 
        
        
    }
    else{
        if(root->date > e){
            searchSubsExpDate(root->left,e,unbalanced1,maxDepth);
        }
        else{
            searchSubsExpDate(root->right,e,unbalanced1,maxDepth);
        }
        
    }

    // printf("Final root is after searchSubs %d\n",root->user_id);
    return root;
}
//the above fn is a bit doubtful regarding searching by expid
//ig both userid and expid needs to be searched together 
//corrections made

user_tree* insertAVL(user_tree* root ,user_tree* n,user_tree** unbalanced1, int* maxDepth){
    
    if(root == NULL){
        root = n ;
        printf("Ele inserted without changes is: %d\n", n->user_id);
        return root;
    }
    
    if(root->user_id < n->user_id){
        root->right = insertAVL(root->right,n,unbalanced1,maxDepth);
        
    }
    else if(root->user_id > n->user_id){
        root->left = insertAVL(root->left,n,unbalanced1,maxDepth);
    }
    else{ 
        printf("Element already exists\n");
    }

    (*unbalanced1) = NULL;
    int a = heightTree(root,unbalanced1,maxDepth);
    if((*unbalanced1) != NULL){
        printf("Unbalanced node after height calci is %d\n",(*unbalanced1)->user_id);
    }
    
    // printf("Height of tree: %d\n",a);
    
    if(*unbalanced1 != NULL){
        printf("Data unbalanced is %d\n",(*unbalanced1)->user_id);
        //search for parent of *unbalanced1
        int e = (*unbalanced1)->user_id;
        root = searchSubs(root,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
        printf("rotations req and done, root is %d\n",root->user_id);
    }
    // else{
    //     printf("Ele inserted without changes is:%d\n",n->data);
    // }
    return root;
}

expense_tree* insertAVLExp(expense_tree* root ,expense_tree* n,expense_tree** unbalanced1, int* maxDepth){
    
    if(root == NULL){
        root = n ;
        printf("Ele inserted without changes is: %d and %d\n", n->member_id,n->expense_id);
        return root;
    }
    
    if(root->member_id < n->member_id){
        root->right = insertAVLExp(root->right,n,unbalanced1,maxDepth);
        
    }
    else if(root->member_id > n->member_id){
        root->left = insertAVLExp(root->left,n,unbalanced1,maxDepth);
    }
    else{ 
        if(root->member_id == n->member_id){
            if(root->expense_id < n->expense_id){
                root->right = insertAVLExp(root->right,n,unbalanced1,maxDepth);
            }
            else if(root->expense_id > n->expense_id){
                root->left =insertAVLExp(root->left,n,unbalanced1,maxDepth);
            }
            else{
                printf("Element already exists\n");
            }
        }
        
    }

    (*unbalanced1) = NULL;
    int a = heightTreeExp(root,unbalanced1,maxDepth);
    if((*unbalanced1) != NULL){
        printf("Unbalanced node_exp after height calci is %d and %d\n",(*unbalanced1)->member_id,(*unbalanced1)->expense_id);
    }
    
    // printf("Height of tree: %d\n",a);
    
    if(*unbalanced1 != NULL){
        printf("Data unbalanced_exp is %d & %d\n",(*unbalanced1)->member_id,(*unbalanced1)->expense_id);
        //search for parent of *unbalanced1
        int u = (*unbalanced1)->member_id;
        int e = (*unbalanced1)->expense_id;
        root = searchSubsExp(root,u,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
        printf("rotations req and done, root is %d and %d\n",root->member_id, root->expense_id);
    }
    // else{
    //     printf("Ele inserted without changes is:%d\n",n->data);
    // }
    return root;
}

fam_tree* insertAVLFam(fam_tree* root ,fam_tree* n,fam_tree** unbalanced1, int* maxDepth){
    
    if(root == NULL){
        root = n ;
        printf("Ele inserted without changes is: %d\n", n->fam_id);
        return root;
    }
    
    if(root->fam_id < n->fam_id){
        root->right = insertAVLFam(root->right,n,unbalanced1,maxDepth);
        
    }
    else if(root->fam_id > n->fam_id){
        root->left = insertAVLFam(root->left,n,unbalanced1,maxDepth);
    }
    else{ 
        printf("Element already exists\n");
    }

    (*unbalanced1) = NULL;
    int a = heightTreeFam(root,unbalanced1,maxDepth);
    if((*unbalanced1) != NULL){
        printf("Unbalanced node after height calci is %d\n",(*unbalanced1)->fam_id);
    }
    
    // printf("Height of tree: %d\n",a);
    
    if(*unbalanced1 != NULL){
        printf("Data unbalanced is %d\n",(*unbalanced1)->fam_id);
        //search for parent of *unbalanced1
        int e = (*unbalanced1)->fam_id;
        root = searchSubsFam(root,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
        printf("rotations req and done, root is %d\n",root->fam_id);
    }
    // else{
    //     printf("Ele inserted without changes is:%d\n",n->data);
    // }
    return root;
}

expense_tree* insertAVLExpDate(expense_tree* root ,expense_tree* n,expense_tree ** unbalanced1, int* maxDepth){
    
    if(root == NULL){
        root = n ;
        printf("Ele inserted without changes is: %d\n", n->date);
        return root;
    }
    
    if(root->date < n->date){
        root->right = insertAVLExpDate(root->right,n,unbalanced1,maxDepth);
        
    }
    else if(root->date > n->date){
        root->left = insertAVLExpDate(root->left,n,unbalanced1,maxDepth);
    }
    else{ 
        printf("Element already exists\n");
    }

    (*unbalanced1) = NULL;
    int a = heightTreeExpDate(root,unbalanced1,maxDepth);
    if((*unbalanced1) != NULL){
        printf("Unbalanced node after height calci is %d\n",(*unbalanced1)->date);
    }
    
    // printf("Height of tree: %d\n",a);
    
    if(*unbalanced1 != NULL){
        printf("Data unbalanced is %d\n",(*unbalanced1)->date);
        //search for parent of *unbalanced1
        int e = (*unbalanced1)->date;
        root = searchSubsExpDate(root,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
        printf("rotations req and done, root is %d\n",root->date);
    }
    // else{
    //     printf("Ele inserted without changes is:%d\n",n->data);
    // }
    return root;
}



user_tree** Search_AVL(user_tree** root_ref, int e) {
    user_tree** retval = NULL;  
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return NULL;  
    }
    if ((*root_ref)->user_id == e) {
        printf("Visiting node with user_id %d\n", (*root_ref)->user_id);
        retval = root_ref;  
    } 
    else if ((*root_ref)->user_id > e) {
        printf("Visiting node with user_id %d\n", (*root_ref)->user_id);
        retval = Search_AVL(&((*root_ref)->left), e);
    } 
    else {
        printf("Visiting node with user_id %d\n", (*root_ref)->user_id);
        retval = Search_AVL(&((*root_ref)->right), e);
    }

    return retval;  
}

expense_tree **Search_AVLExp(expense_tree **root_ref,int u, int e){
    expense_tree** retval = NULL;  
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return NULL;  
    }
    if ((*root_ref)->member_id == u) {
        if((*root_ref)->expense_id == e){
            retval = root_ref;
        }
        else if((*root_ref)->expense_id > e){
            retval = Search_AVLExp(&((*root_ref)->left),u,e);
        }
        else{
            retval = Search_AVLExp(&((*root_ref)->right),u,e);
        }
    } 
    else if ((*root_ref)->member_id > u) {
        retval = Search_AVLExp(&((*root_ref)->left),u,e);
    } 
    else {
        retval = Search_AVLExp(&((*root_ref)->right),u,e);
    }

    return retval;  
}

fam_tree** Search_AVLFam(fam_tree** root_ref, int e) {
    fam_tree** retval = NULL;  
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return NULL;  
    }
    if ((*root_ref)->fam_id == e) {
        retval = root_ref;  
    } 
    else if ((*root_ref)->fam_id > e) {
        retval = Search_AVLFam(&((*root_ref)->left), e);
    } 
    else {
        retval = Search_AVLFam(&((*root_ref)->right), e);
    }

    return retval;  
}

expense_tree** Search_AVLExpDate(expense_tree** root_ref, int e) {
    expense_tree** retval = NULL;  
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return NULL;  
    }
    if ((*root_ref)->date == e) {
        retval = root_ref;  
    } 
    else if ((*root_ref)->date > e) {
        retval = Search_AVLExpDate(&((*root_ref)->left), e);
    } 
    else {
        retval = Search_AVLExpDate(&((*root_ref)->right), e);
    }

    return retval;  
}


void Visit(user_tree* root, FILE* file){
    if (root && file) {
        fprintf(file, "%d,%s,%.2f\n", root->user_id, root->name, root->income);
    }
}

void VisitExp(expense_tree* root, FILE* file){
    if (root && file) {
        fprintf(file, "%d,%d,%s,%.2f,%d\n", root->member_id, root->expense_id, root->expense_cat, root->exp_amt, root->date);

    }
}

void VisitFam(fam_tree* root, FILE* file){
    if (root && file) {
        fprintf(file, "%d,%s,%.2f,%.2f\n", root->fam_id, root->fam_name, root->fam_income,root->fam_expense);
        
        user_tree* curr = root->next_user;
        while (curr) {
            fprintf(file, "   User: %d,%s,%.2f\n", curr->user_id, curr->name, curr->income);
            curr = curr->next;
        }
        fprintf(file, "\n");
    }    
}

void VisitExpDate(expense_tree* root, FILE* file){
    if (root && file) {
        fprintf(file, "%d,%d,%s,%.2f,%d\n", root->member_id, root->expense_id, root->expense_cat, root->exp_amt, root->date);
    }
}



void inOrderTraversal(user_tree* root, FILE* file){
    if(root != NULL){
        inOrderTraversal(root->left,file);
        Visit(root,file);
        inOrderTraversal(root->right,file);
    }
}

void inOrderTraversalExp(expense_tree*root, FILE* file){
    if(root != NULL){
        inOrderTraversalExp(root->left,file);
        VisitExp(root,file);
        inOrderTraversalExp(root->right,file);
    }
}

void inOrderTraversalFam(fam_tree* root, FILE* file){
    if(root != NULL){
        inOrderTraversalFam(root->left,file);
        VisitFam(root,file);
        inOrderTraversalFam(root->right,file);
    }
}

void inOrderTraversalExpDate(expense_tree*root, FILE* file){
    if(root != NULL){
        inOrderTraversalExpDate(root->left,file);
        VisitExpDate(root,file);
        inOrderTraversalExpDate(root->right,file);
    }
}


int searchLinkedList(user_tree* lptr, int id, float expense,float income, fam_tree* root) {
    int found = 0;
    user_tree* nptr = lptr;
    while (nptr != NULL && !found) {
        if (nptr->user_id == id) {
            //id has been found so this is the family
            //recalculate the total expense 
            // root->fam_expense = 0.00; //this ensures that even if i want to update it it will get reset to 0 before assigning it a new value
            root->fam_expense += expense;
            root->fam_income += income;
            found = 1;
        }
        nptr = nptr->next;
    }
    return found;
}

int searchLinkedListUser(user_tree *head, int target_id) {
    while (head != NULL) {
        if (head->user_id == target_id) {
            return 1; // Found
        }
        head = head->next;
    }
    return 0; // Not found
}

fam_tree* identifyUserFamily(fam_tree **f1, int id) {
    if (f1 == NULL || *f1 == NULL) return NULL; // Base case

    // Check if user exists in current family node's linked list
    if (searchLinkedListUser((*f1)->next_user, id)) {
        return *f1;
    }

    // Recur on left subtree
    fam_tree* leftSearch = identifyUserFamily(&((*f1)->left), id);
    if (leftSearch != NULL) return leftSearch;

    // Recur on right subtree
    return identifyUserFamily(&((*f1)->right), id);
}


int searchInFamUser(fam_tree **root, int target,float expense,float income) {
    if (root == NULL || *root == NULL) return 0; // Base case

    // Check current node's linked list
    int c = searchLinkedList((*root)->next_user, target,expense,income,(*root));
    if(c == 1){
        return 1;
    }
    // if (searchLinkedList((*root)->next_user, target,expense,(*root))) return 1;

    // Search both left and right subtrees
    return searchInFamUser(&((*root)->left), target,expense,income) || searchInFamUser(&((*root)->right), target,expense,income);
}

expense_tree** searchInExpExpId(expense_tree **root,int exp_id) {
    int upd_date;
    float upd_exp_amt;
    char upd_exp_cat[CATEGORY_LEN];
    if (root == NULL || *root == NULL) return NULL; // Base case

    // Check current node's linked list
    if((*root)->expense_id == exp_id){
        return root;
    }
    
    expense_tree **left = searchInExpExpId(&((*root)->left), exp_id);
    if (left != NULL) return left;

    return searchInExpExpId(&((*root)->right), exp_id);
}
///this searches for expid in exp tree updates it and also updates in fam_tree


void delete_AVLExp(expense_tree **parent_ptr){
    expense_tree* r, *q ,*p;
    r = *parent_ptr ;
    if(r == NULL){printf("ERROR\n");}
    else{
        if((r->left == NULL)&&(r->right == NULL)){
            //leaf node case 
            // free(r);
            *parent_ptr = NULL;
        }
        else if(r->left == NULL){
            *parent_ptr = r->right ;
        }
        else if(r->right == NULL){
            *parent_ptr = r->left;
        }
        else{
            p=NULL;
            q=r->left ;
            while(q->right != NULL){
                p=q; //p is prev node
                q = q->right;
            }
            if(p != NULL){
                p->right = q->left ;
                q->left = r->left;
            }
            
            q->right = r->right;
            *parent_ptr = q;
        }
        free(r);
    }
    
    // printf("Done with deleteAVL\n");
}

void delete_AVL(user_tree **parent_ptr){
    user_tree* r, *q ,*p;
    r = *parent_ptr ;
    if(r == NULL){printf("ERROR\n");}
    else{
        if((r->left == NULL)&&(r->right == NULL)){
            //leaf node case 
            // free(r);
            *parent_ptr = NULL;
        }
        else if(r->left == NULL){
            *parent_ptr = r->right ;
        }
        else if(r->right == NULL){
            *parent_ptr = r->left;
        }
        else{
            p=NULL;
            q=r->left ;
            while(q->right != NULL){
                p=q; //p is prev node
                q = q->right;
            }
            if(p != NULL){
                p->right = q->left ;
                q->left = r->left;
            }
            
            q->right = r->right;
            *parent_ptr = q;
        }
        free(r);
    }
      
}

void delete_AVLFam(fam_tree **parent_ptr){
    fam_tree* r, *q ,*p;
    r = *parent_ptr ;
    if(r == NULL){printf("ERROR\n");}
    else{
        if((r->left == NULL)&&(r->right == NULL)){
            //leaf node case 
            // free(r);
            *parent_ptr = NULL;
        }
        else if(r->left == NULL){
            *parent_ptr = r->right ;
        }
        else if(r->right == NULL){
            *parent_ptr = r->left;
        }
        else{
            p=NULL;
            q=r->left ;
            while(q->right != NULL){
                p=q; //p is prev node
                q = q->right;
            }
            if(p != NULL){
                p->right = q->left ;
                q->left = r->left;
            }
            
            q->right = r->right;
            *parent_ptr = q;
        }
        free(r);
    }
    
    // printf("Done with deleteAVL\n");
}



user_tree* deleteRotCndCheckNewUser(user_tree **root, int toDel,user_tree** unbalanced1,int* maxDepth){
    user_tree **temp_del =Search_AVL(root,toDel);
    if(temp_del != NULL){
        printf("Search found node with ID: %d\n", (*temp_del)->user_id);
        int deleted_value = (*temp_del)->user_id;
        delete_AVL(temp_del);
        printf("Root now is %d\n",(*root)->user_id);
        // printf("Root->left is %d\n",(*root)->left->user_id);
        printf("Ele %d deleted, now rotating \n",deleted_value);
        
        printf("max depth now is%d\n",*maxDepth); 
        *maxDepth = -999999;  // Reset before recalculating height
        
        int a = heightTree((*root),unbalanced1,maxDepth);

        printf("height of tree is %d\n",a);
        if (unbalanced1 == NULL || *unbalanced1 == NULL) {
            printf("Unbalanced1 is NULL, skipping rotation\n");
        } else {
            printf("Unbalanced node is %d\n", (*unbalanced1)->user_id);
            int e = (*unbalanced1)->user_id;
            *root = searchSubs(*root,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
            printf("rotations req and done, root is %d\n",(*root)->user_id);
        }
    }
    else{
        printf("Search_AVL() returned NULL for ID %d\n", toDel);
    }
    return *root;
}

expense_tree* deleteRotCndCheckNewExp(expense_tree **root, int toDel,expense_tree** unbalanced1,int* maxDepth){
    expense_tree **temp_del =searchInExpExpId(root,toDel);
    if(temp_del != NULL){
        int deleted_value = (*temp_del)->expense_id;
        delete_AVLExp(temp_del);
        printf("Root now is %d\n",(*root)->expense_id);
        // printf("Root->left is %d\n",(*root)->left->expense_id);
        printf("Ele %d deleted, now rotating \n",deleted_value);
        
        printf("max depth now is%d\n",*maxDepth); 
        *maxDepth = -999999;  // Reset before recalculating height
        
        int a = heightTreeExp((*root),unbalanced1,maxDepth);

        printf("height of tree is %d\n",a);
        if (unbalanced1 == NULL || *unbalanced1 == NULL) {
            printf("Unbalanced1 is NULL, skipping rotation\n");
        } else {
            printf("Unbalanced node is %d\n", (*unbalanced1)->expense_id);
            int e = (*unbalanced1)->expense_id;
            int u = (*unbalanced1)->member_id;
            *root = searchSubsExp(*root,u,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
            printf("rotations req and done, root is %d\n",(*root)->expense_id);
        }
    }
    return *root;
}

fam_tree* deleteRotCndCheckNewFam(fam_tree **root, int toDel,fam_tree** unbalanced1,int* maxDepth){
    fam_tree **temp_del =Search_AVLFam(root,toDel);
    if(temp_del != NULL){
        printf("fam found to be deleted\n");
        int deleted_value = (*temp_del)->fam_id;
        delete_AVLFam(temp_del);
        printf("Root now is %d\n",(*root)->fam_id);
        // printf("Root->left is %d\n",(*root)->left->fam_id);
        printf("Ele %d deleted, now rotating \n",deleted_value);
        
        printf("max depth now is%d\n",*maxDepth); 
        *maxDepth = -999999;  // Reset before recalculating height
        
        int a = heightTreeFam((*root),unbalanced1,maxDepth);

        printf("height of tree is %d\n",a);
        if (unbalanced1 == NULL || *unbalanced1 == NULL) {
            printf("Unbalanced1 is NULL, skipping rotation\n");
        } else {
            printf("Unbalanced node is %d\n", (*unbalanced1)->fam_id);
            int e = (*unbalanced1)->fam_id;
            *root = searchSubsFam(*root,e,unbalanced1,maxDepth); //copy of root me apan change karrahe hai, thats why it isnt visible outside
            printf("rotations req and done, root is %d\n",(*root)->fam_id);
        }
    }
    return *root;
}

//identifyUserFam call karna hai
//we will  get  fam ka node 
//fir we will go to e1
//if (*e1)->member_id == id 



expense_tree** recurseExpUserid(expense_tree **root_ref, int user_id) {
    if (*root_ref == NULL){
        printf("root_ref is NULL\n");
        return NULL;
    }
        

    if ((*root_ref)->member_id == user_id) {
        printf("user id found in exptree\n");
        return root_ref;  // First match
    }

    // Try left
    expense_tree** left_result = recurseExpUserid(&((*root_ref)->left), user_id);
    if (left_result != NULL) return left_result;

    // Try right
    return recurseExpUserid(&((*root_ref)->right), user_id);
}
void output_expense(expense_tree *root); //fn prototype

void deleteExpenseFromUserID(expense_tree **e1, int user_id, fam_tree **f1,
    expense_tree **unbalanced1_exp, int* maxDepthExp) {
    printf("Inside deleteexpenseFromUserID\n");
    expense_tree **toDel_ref = NULL;
    printf("Before deleting, the tree looks like:\n");
    printExpenseTree(*e1);

    while ((toDel_ref = recurseExpUserid(e1, user_id)) != NULL) {
        printf("Inside expesne deletion for userid");
        int exp_id = (*toDel_ref)->expense_id;
    
        if(searchInFamUser(f1,user_id,-(*toDel_ref)->exp_amt,0)){
            printf("Family me changes kiye hai\n");
        }
        // Optional: Update user's total expenses here using userInFam

        printf("Deleting expense_id %d for user_id %d\n", exp_id, user_id);
        *e1 = deleteRotCndCheckNewExp(e1, exp_id, unbalanced1_exp, maxDepthExp);
        
    }

    printf("All expenses deleted for user_id %d\n", user_id);
    output_expense((*e1));
}


void input_user(user_tree **root,fam_tree **f1,user_tree **unbalanced1,int maxDepth,int*fam_id, fam_tree **unbalanced1_fam,int maxDepthFam){
    char line[100];
    FILE *file = fopen("input_user.txt", "r");
    if (!file) {
        perror("Error opening input file");
        // return EXIT_FAILURE;
    }
    while (fgets(line, sizeof(line), file)) {
        int mem_id, cj_flag, fam_id_join;
        float income_user;
        char name_user[50];

        if (sscanf(line, "%d,%49[^,],%f,%d,%d", &mem_id, name_user, &income_user,&cj_flag,&fam_id_join)) {
            user_tree* user_input = makeNode_user(mem_id, income_user, name_user);
            user_tree* user_input_infam = makeNode_user(mem_id, income_user, name_user);
            (*root) = insertAVL((*root), user_input,unbalanced1, &maxDepth);
            if(cj_flag == 1){
                float expense_fam = 0.00;
                int count = 1;
                char fam_name[100];
                sprintf(fam_name, "%s's family", name_user);
                *fam_id = *fam_id + 1;
                fam_tree* fam_input = makeNode_fam(*fam_id,income_user,expense_fam,fam_name,count,user_input);
                (*f1)=insertAVLFam((*f1),fam_input,unbalanced1_fam,&maxDepthFam);
                
            }
            else{
                //take one more input in file as family_id to join
                fam_tree **ptr = Search_AVLFam(f1,fam_id_join);
                if((ptr != NULL)&&((*ptr)!=NULL)&&((*ptr)->fam_id == fam_id_join)){
                    user_tree* ptr1 = (*ptr)->next_user;
                    while(ptr1->next != NULL){
                        ptr1 = ptr1->next;
                    }
                    ptr1->next = user_input_infam;
                    (*ptr)->fam_income += user_input->income;
                    (*ptr)->count += 1;
                }
                //searh for family id by ptr =search_AVL_fam()
                //*ptr->next_user and run while loop until it is not null
                //go ad inser it 
            }
        }
    }
    fclose(file);

    if ((*root)) {
        printf("Current root is %d\n", (*root)->user_id);
    }

    FILE *outputFile = fopen("user_output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        // return EXIT_FAILURE;
    }
    inOrderTraversal((*root), outputFile);
    fclose(outputFile);
    //call inorder 

    //for family 
    FILE *outputFileFam = fopen("fam_output.txt", "w");
    if (!outputFileFam) {
        perror("Error opening output file");
        // return EXIT_FAILURE;
    }
    inOrderTraversalFam((*f1), outputFileFam);
    fclose(outputFileFam);

}

void output_fam(fam_tree *root); //fn protoype

void input_expense(expense_tree **root,expense_tree **root_date ,fam_tree **f1, expense_tree **unbalanced1, int maxDepth, expense_tree **unbalanced1_expdate, int maxDepth_expdate) {
    char line[150];  // Adjusted size to accommodate more fields
    FILE *file = fopen("input_expense.txt", "r");
    if (!file) {
        perror("Error opening input file");
        // return;
    }

    while (fgets(line, sizeof(line), file)) {
        int mem_id, exp_id, date;
        float exp_amt;
        char exp_cat[50];

        if (sscanf(line, "%d,%d,%49[^,],%f,%d", &mem_id, &exp_id, exp_cat, &exp_amt, &date) == 5) {
            expense_tree* expense_input = makeNode_expense(exp_id, exp_amt, exp_cat, date, mem_id);
            expense_tree* expense_input_date = makeNode_expense(exp_id, exp_amt, exp_cat, date, mem_id);

            (*root) = insertAVLExp((*root), expense_input, unbalanced1, &maxDepth);
            float expense = expense_input->exp_amt;
            (*root_date) = insertAVLExpDate((*root_date), expense_input_date, unbalanced1_expdate, &maxDepth_expdate);
            int a = searchInFamUser(f1,mem_id,expense,0);
            if(a==1){
                printf("Expenses default added to family\n");
            }
            //int a = searchINTree((*f1),mem_id)
            //if(a==1) printf expenses added to family

        }
    }
    fclose(file);


    FILE *outputFile = fopen("exp_output.txt", "w");
    if (!outputFile) {
        perror("Error opening output_exp file");
        // return EXIT_FAILURE;
    }
    inOrderTraversalExp((*root), outputFile);
    fclose(outputFile);
    //call inorder 

    FILE *outputFileDate = fopen("exp_output_date.txt", "w");
    if (!outputFileDate) {
        perror("Error opening output_exp_date file");
        // return EXIT_FAILURE;
    }
    inOrderTraversalExpDate((*root_date), outputFileDate);
    fclose(outputFileDate);

    output_fam((*f1));
    

}



void output_user(user_tree *root){
    FILE *outputFile = fopen("user_output.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        // return EXIT_FAILURE;
    }
    inOrderTraversal(root, outputFile);
    fclose(outputFile);
}

void output_expense(expense_tree *root){
    FILE *outputFile = fopen("exp_output.txt", "w");
    if (!outputFile) {
        perror("Error opening output_exp file");
        // return EXIT_FAILURE;
    }
    inOrderTraversalExp(root, outputFile);
    fclose(outputFile);
}

//write output_fam code 
void output_fam(fam_tree *root){
    FILE *outputFileFam = fopen("fam_output.txt", "w");
    if (!outputFileFam) {
        perror("Error opening output file");
        // return EXIT_FAILURE;
    }
    inOrderTraversalFam(root, outputFileFam);
    fclose(outputFileFam);
}



//fn prototype
void create_joinFamily(int* cj, fam_tree** f1, user_tree* made_from_makeuser,int*fam_id,fam_tree **unbalanced1_fam, int maxDepthFam);


void addUser(user_tree** root, int* cj, int* family_id, fam_tree** f1,user_tree **unbalanced1, int maxDepth, fam_tree **unbalanced1_fam,int maxDepthFam){ 
    // we are passing the head of the user linked list as an argument ;
    user_tree* nptr ;
    user_tree **ptr;
    int flag = 1;
    int id;
    float money_in ;
    char std_name[NAME_LEN];
   
    while(flag == 1){
        flag = 0 ;
        printf("Enter userId \n");
        scanf("%d",&id);

        ptr = Search_AVL(root,id);

        if((ptr != NULL)&&((*ptr)!=NULL)&&((*ptr)->user_id == id)){
            flag = 1;
            printf("Id already exists\n");
        }
        printf("Hello\n");

        if(ptr == NULL){
            printf("Enter name: \n");
            scanf("%s",std_name);

            printf("Enter income: \n");
            scanf("%f",&money_in);
        }

    }
    
    nptr = makeNode_user(id,money_in,std_name);
    (*root) = insertAVL((*root), nptr,unbalanced1, &maxDepth);
    output_user((*root));
    user_tree* kptr = makeNode_user(id,money_in,std_name);//check if req
    
    int flag_fam=1;
    
    while(flag_fam==1){
        printf("Enter 1 if you want to create a family or enter 0 if you want to join a family \n");
        scanf("%d",cj); 
        if(*cj==1){
            create_joinFamily(cj,f1,kptr,family_id,unbalanced1_fam,maxDepthFam); 
            flag_fam=0;
        }
        else if(*cj==0){
            create_joinFamily(cj,f1,kptr,family_id,unbalanced1_fam,maxDepthFam); 
            flag_fam=0;
        }
        else{
            printf("Invalid input");
            
        }
    }
    printf("User added \n");
    output_user((*root));
    output_fam((*f1));
}



void addExpense(expense_tree **e1, user_tree **u1, fam_tree **f1,expense_tree **unbalanced1, int maxDepth){

    int id, is_true_user = 1 ;
    int found = 0, found1 =1, found2 = 0;
    int exp_id, date;
    float money_out;
    char exp_cat[CATEGORY_LEN];

    
    while(is_true_user == 1){
        printf("Enter the user id of the person whose expense record is to be stored: \n");
        scanf("%d",&id);
        // try passing the head of user as an argument to the add_expense function 
        user_tree **ptr ; // check  //didnt wtie = u1;
        ptr = Search_AVL(u1,id);
        
        if((ptr != NULL)&&((*ptr)!=NULL)&&((*ptr)->user_id == id)){
            is_true_user = 0;
            printf("Id exists\n");
            while(found == 0){
                printf("Give expense id: \n");
                scanf("%d",&exp_id);
                expense_tree **ptr1 = Search_AVLExp(e1,id,exp_id);
                if(ptr1 == NULL){
                    found = 1;
                    printf("Enter expense category: \n");
                    scanf("%s",exp_cat);
                    printf("Enter expense amount: \n");
                    scanf("%f",&money_out);
                    printf("Enter date of transaction:(between 1 and 10) \n");
                    scanf("%d",&date);
                    
                }
                
            }
        
        }
        if(ptr == NULL){
            is_true_user = 1;
            printf("Given id dosent exist\n");
        }
         
    }
    expense_tree* nptr = makeNode_expense(exp_id,money_out,exp_cat,date,id);
    (*e1) = insertAVLExp((*e1), nptr,unbalanced1, &maxDepth);
    float expense = nptr->exp_amt;
    int a = searchInFamUser(f1,id,expense,0);
    if(a==1){
        printf("Expenses added to family\n");
    }
    //int a = searchINTree((*f1),mem_id)
    //if(a==1) printf expenses added to family
    //output_fam((*f1));
    output_expense((*e1));
    output_fam((*f1));
}

void create_joinFamily(int* cj, fam_tree** f1, user_tree* made_from_makeuser,int*fam_id,fam_tree **unbalanced1_fam, int maxDepthFam){

    char std_fam_name[NAME_LEN];
    float fam_income = 0.00, fam_expense = 0.00 ;
    int count = 0 ;
    
    fam_tree* fptr ;

    if(*cj == 1){

        printf("Enter name of family: ");
        scanf("%s",std_fam_name);
        fam_income += made_from_makeuser->income ;
        count += 1;
        *fam_id = *fam_id + 1;
        fptr = makeNode_fam(*fam_id,fam_income,fam_expense,std_fam_name,count,made_from_makeuser);
        // but remember ki tujhe madefrommakeuser me change lana hai , so double pointer pass karsakta hai 
        (*f1) = insertAVLFam((*f1), fptr,unbalanced1_fam, &maxDepthFam);
        output_fam((*f1));
        
        printf("Family id is : %d\n",*fam_id);  

    }
    else{
        int family_id, fam_id_found = 0;
        while(fam_id_found == 0){

            printf("Enter the family_id of the family you want to join: \n");
            scanf("%d",&family_id);

            //search if it exists 
            fam_tree **ptr = Search_AVLFam(f1,family_id);

            if(ptr == NULL){
                fam_id_found = 0;
                printf("Family dosent exist\n");
            }
            if((ptr != NULL)&&((*ptr)!=NULL)&&((*ptr)->fam_id == family_id)){
                printf("Family size is %d\n",(*ptr)->count);
                if((*ptr)->count < 4){
                    fam_id_found = 1;
                    user_tree* ptr3 = (*ptr)->next_user;
                    while((ptr3 != NULL)&&(ptr3->next != NULL)){

                        ptr3 = ptr3->next ;
                    }
                    ptr3->next = made_from_makeuser ;
                    (*ptr)->fam_income = (*ptr)->fam_income + made_from_makeuser->income;
                    (*ptr)->count = (*ptr)->count + 1;
                    //ouptut_fam((*f1));
                }
                else{
                    printf("Family limit exceeded\n");
                }
            }
            
        }
        output_fam((*f1));    
    }
           
}


void update_delete_expense(fam_tree** f1, expense_tree** e1,expense_tree **unbalanced1, int maxDepthExp){

    int flag, found=0, found1= 0, found2 = 0, found3 = 0, exp_id_upd, exp_id_del, upd_date;
    float upd_exp_amt;
    char upd_exp_cat[CATEGORY_LEN];
    

    printf("Do you want to delete or update expense? delete=1, update=0: \n");
    scanf("%d",&flag);
    if(flag == 0){
        printf("Which expense id information do u want to update: \n");
        scanf("%d",&exp_id_upd);
        //search for expense_id in expense_tree
        //do similar function as searchAVLFamUser wherein 
        //we go to lst and rst and search for expid
        expense_tree **foundNode = searchInExpExpId(e1,exp_id_upd);
        
        if(foundNode == NULL){
            printf("Expense id not found\n");
        }
        if((foundNode != NULL)&&(*foundNode != NULL)){
            int user_id = (*foundNode)->member_id;
            int m = searchInFamUser(f1, user_id, -(*foundNode)->exp_amt,0);
            if(m==1){
                printf("Initial exp changed\n");
            }
            //the negative sign is imp
            printf("If exp cat has to be changed give different, else provide the same one: \n");
            scanf("%s", (*foundNode)->expense_cat);

            printf("If u want to change the exp amt, give new exp amt else give old income: \n");
            scanf("%f", &(*foundNode)->exp_amt);

            printf("If date has to be changed give different, else provide the same one: \n");
            scanf("%d", &(*foundNode)->date);


            int k = searchInFamUser(f1, user_id, (*foundNode)->exp_amt,0);
            if(k==1){
                printf("Exp changes updated everywhere\n");
            }
        }
        
        
    }
    else{
        printf("Which expense id information do u want to delete: \n");
        scanf("%d",&exp_id_del);
        
        expense_tree **foundNode = searchInExpExpId(e1,exp_id_del);

        if(foundNode == NULL){
            //famtree me jaake uss family ke exp se subtract kardena 
            //call deleteRotCondCheckExp here 
            //this will ensure family se initially exp kam hojayega and then wo exp_tree se delete hojayega
            printf("Expense id not found\n");
            
        }

        if((foundNode != NULL)&&(*foundNode != NULL)){
            int user_id = (*foundNode)->member_id;
            int k = searchInFamUser(f1, user_id, -(*foundNode)->exp_amt,0);
            if(k==1){
                printf("Exp changes updated everywhere\n");
            }
            (*e1) = deleteRotCndCheckNewExp(e1,exp_id_del,unbalanced1,&maxDepthExp);
            printf("Expense deleted\n");
        }
        
    }
    output_expense((*e1));
    output_fam((*f1));
}

void update_individual_fam_details(user_tree **u1, fam_tree **f1,expense_tree **e1,user_tree **unbalanced1, int* maxDepth, fam_tree **unbalanced1_fam, int* maxDepthFam, expense_tree **unbalanced1_exp, int* maxDepthExp){
    int flag, flag2, flag3, id,fam_id, user_id_del,fam_id_del;
    

    printf("Do you want to delete or update records? delete=1, update=0: \n");
    scanf("%d",&flag);
    if(flag == 0){
        printf("Which information do you want to change, individual or family? (family 1/individual 0) \n");
        scanf("%d",&flag2);
        if(flag2 == 0){
            //update individual details
            printf("Which user id information do u want to change: \n");
            scanf("%d",&id);

            user_tree **foundNode = Search_AVL(u1,id);
            if(foundNode == NULL){
                printf("User id dosent exist\n");
            }
            if((foundNode != NULL)&&(*foundNode != NULL)){

                int user_id = (*foundNode)->user_id;
                int m = searchInFamUser(f1, user_id, 0,-(*foundNode)->income);
                if(m==1){
                    printf("Initial income changed\n");
                }
                printf("If name has to be changed give different name, else provide the same name: \n");
                scanf("%s",(*foundNode)->name);
                printf("If u want to change the income, give new income else give old income: \n");
                scanf("%f",&(*foundNode)->income);

                int k = searchInFamUser(f1, user_id, 0,(*foundNode)->income);
                if(k==1){
                    printf("Income changes updated everywhere\n");
                }

            }
            output_fam((*f1));
            output_user((*u1));
        }
        else{
            //update family details
            printf("Which fam id information do u want to change: \n");
            scanf("%d",&fam_id);

            fam_tree **foundNode = Search_AVLFam(f1,fam_id);
            if(foundNode == NULL){
                printf("Family id dosent exist\n");
            }
            if((foundNode != NULL)&&(*foundNode != NULL)){
                printf("If name has to be changed give different name, else provide the same name: \n");
                scanf(" %[^\n]", (*foundNode)->fam_name);

            }
            output_fam((*f1));

        }

    }

    else{
        //for deletion 
        printf("Which information do you want to delete, individual or family? (family 1/individual 0) \n");
        scanf("%d",&flag3);
        if(flag3==0){
            //need to note that heap locatin is same for user node in userlist and user node in family list since we are using the same nptr in both cases
            // therefore freeing one pointer will lead to a dangling pointer for the other and vice versa 
            // we will remove them from their rerpective lists and then free them together 

            printf("Which user id information do u want to delete: \n");
            scanf("%d",&user_id_del);

            user_tree **foundNode = Search_AVL(u1,user_id_del);
            if(foundNode == NULL){
                printf("user id dosent exist\n");
            }
            if((foundNode != NULL)&&(*foundNode != NULL)){
                
                
                fam_tree* fam_node = identifyUserFamily(f1,user_id_del);
                if(fam_node != NULL){
                    int family_id_del = fam_node->fam_id;
                    printf("Family count is %d\n",fam_node->count);
                    if(fam_node->count == 1){
                        user_tree* user_node = fam_node->next_user;
                        printf("We are going to del %d user\n",user_id_del);

                        deleteExpenseFromUserID(e1,user_id_del,f1,unbalanced1_exp,maxDepthExp);

                        (*u1) = deleteRotCndCheckNewUser(u1,user_id_del,unbalanced1,maxDepth);
                        printf("User deleted\n");
                        (*f1) = deleteRotCndCheckNewFam(f1,family_id_del,unbalanced1_fam,maxDepthFam);
                        
                        printf("Family deleted\n");
                    }
                    else{
                        
                        int del_user = user_id_del;
                        // user_tree *user_del = (user_tree*)malloc(sizeof(user_tree));
                        int flag_user = 0;
                        printf("We are going to del %d user\n",user_id_del);
                        deleteExpenseFromUserID(e1,user_id_del,f1,unbalanced1_exp,maxDepthExp);
                        printf("**delete expense from user id performed**\n");

                        (*u1) = deleteRotCndCheckNewUser(u1,user_id_del,unbalanced1,maxDepth);

                        user_tree* trav_ptr = fam_node->next_user;
                        user_tree* prev = NULL;
                        printf("After deletion, family node now points to:\n");
                        user_tree* debug = fam_node->next_user;
                        while(debug != NULL) {
                            printf("User ID: %d -> ", debug->user_id);
                            debug = debug->next;
                        }
                        printf("NULL\n");
                        while((trav_ptr != NULL)&&(flag_user == 0)){
                            if(trav_ptr->user_id == user_id_del){
                                flag_user = 1;
                                fam_node->fam_income -= trav_ptr->income;
                                 //used for deletion later
                                if(prev == NULL){
                                    fam_node->next_user = trav_ptr->next;
                                }
                                else{
                                    prev->next = trav_ptr->next;
                                }
                                free(trav_ptr);

                            }
                            else{
                                prev = trav_ptr;
                                trav_ptr = trav_ptr->next;
                            }
                            
                        }
                        printf("After deletion, family node now points to:\n");
                        user_tree* debug1 = fam_node->next_user;
                        while(debug1 != NULL) {
                            printf("User ID: %d -> ", debug1->user_id);
                            debug1 = debug1->next;
                        }
                        printf("NULL\n");
                        
                        //remove from user tree too
                        printf("User deleted from user tree too");
                    }
                }
            }
            output_fam((*f1));
            output_user((*u1));

        }
        else{
            
            printf("Which fam id information do u want to delete: \n");
            scanf("%d",&fam_id_del);

            fam_tree **foundNode = Search_AVLFam(f1,fam_id_del);
            if(foundNode == NULL){
                printf("Family id dosent exist\n");
            }
            if((foundNode != NULL)&&(*foundNode != NULL)){
                user_tree* nptr = (*foundNode)->next_user;
                while(nptr != NULL) {
                    user_tree* next_node = nptr->next;

                    
                    if (nptr != NULL) {
                        user_tree **searchNode = Search_AVL(u1, nptr->user_id);
                        int search_id = (*searchNode)->user_id;
                        if ((searchNode != NULL)&&((*searchNode)!= NULL)) {
                            deleteExpenseFromUserID(e1,search_id,f1,unbalanced1_exp,maxDepthExp);

                            (*u1) = deleteRotCndCheckNewUser(u1, search_id, unbalanced1, maxDepth);
                        } else {
                            printf("User %d not found in AVL tree\n", nptr->user_id);
                        }
                    }

                    nptr = next_node;
                }
                
                printf("** Going to delete family **\n");
                //check the above part it should work
                (*f1) = deleteRotCndCheckNewFam(f1,fam_id_del,unbalanced1_fam,maxDepthFam);
                printf("Family deleted\n");

                //before deleting family, gointo family->next_user
                //and for every node do deleterotuser(u1,index...)
                //delete rot cond check family
                

            }
            // if((u1 == NULL)||((*u1)==NULL)){
            //     printf("User_tree empty\n");
            // }
            printf("Hello guys\n");
            output_user((*u1));
            output_fam((*f1));

        }

    }
}



void get_total_expense(fam_tree **f1){
    int fam_id, flag = 0;

    printf("Enter the family id for which total expense and income is to be found: \n");
    scanf("%d",&fam_id);

    fam_tree **found = Search_AVLFam(f1,fam_id);
    if(found == NULL){
        printf("Family id dosent exist\n");
    }
    if((found != NULL)&&((*found)!= NULL)){
        printf("Family income is %f\n",(*found)->fam_income);
        printf("Family expense is %f\n",(*found)->fam_expense);
    }
}

struct ind_cat_exp {
    char category[20];
    float amount;
};
struct specific_cat_fam_exp{
    int user_ka_id;
    float user_ka_exp;
};

void collectExpensesForUser(expense_tree* root, int target_user_id,struct ind_cat_exp rec_individual[]) {
    if (root == NULL) return;

    // Traverse left subtree
    collectExpensesForUser(root->left, target_user_id, rec_individual);

    // If this node belongs to the user
    if (root->member_id == target_user_id) {
        if (strcmp(root->expense_cat, "RENT") == 0) {
            rec_individual[0].amount += root->exp_amt;
        }
        else if (strcmp(root->expense_cat, "UTILITY") == 0) {
            rec_individual[1].amount += root->exp_amt;
        }
        else if (strcmp(root->expense_cat, "GROCERY") == 0) {
            rec_individual[2].amount += root->exp_amt;
        }
        else if (strcmp(root->expense_cat, "STATIONARY") == 0) {
            rec_individual[3].amount += root->exp_amt;
        }
        else if (strcmp(root->expense_cat, "LEISURE") == 0) {
            rec_individual[4].amount += root->exp_amt;
        }
        else {
            printf("Unknown category: %s\n", root->expense_cat);
        }
    }

    // Continue only if current user_id is <= target
    if (root->member_id <= target_user_id) {
        collectExpensesForUser(root->right, target_user_id, rec_individual);
    }
}

float collectCategoryExpenseForUser(expense_tree* root, int target_user_id, const char* cat) {
    if (root == NULL) return 0.0;

    float total = 0.0;
    total += collectCategoryExpenseForUser(root->left, target_user_id, cat);

    if (root->member_id == target_user_id) {
        if (strcmp(root->expense_cat, cat) == 0) {
            total += root->exp_amt;
        }
    }

    //this ensures that when my root->id is greated than target then it wont go in and check the right part backtracking se dekh
    if (root->member_id <= target_user_id) {
        total += collectCategoryExpenseForUser(root->right, target_user_id, cat);
    }

    return total;
}

void collectDateForUser(expense_tree* root, int target_user_id,float date_arr[]) {
    if (root == NULL) return;

    // Traverse left subtree
    collectDateForUser(root->left, target_user_id, date_arr);

    // If this node belongs to the user
    if (root->member_id == target_user_id) {
        date_arr[root->date - 1] += root->exp_amt;
    }

    // Continue only if current user_id is <= target
    if (root->member_id <= target_user_id) {
        collectDateForUser(root->right, target_user_id, date_arr);
    }
}


void get_individual_expense(user_tree** u1, expense_tree** e1){
    int id, is_true_user = 1, found = 0, found1 = 0;
    float total_exp = 0.00;
    
    while(is_true_user == 1){
        printf("Enter userID for which expense is to be calculated: \n");
        scanf("%d",&id);

        user_tree **found = Search_AVL(u1,id);
        if(found == NULL){
            printf("User id dosent exist\n");
            is_true_user = 1;
        }
        if((found != NULL)&&((*found)!= NULL)){
            is_true_user = 0;
            // struct ind_cat_exp{
            //     float amount;
            //     char category[CATEGORY_LEN];
            // };
            struct ind_cat_exp rec_individual[5];
            const char cats[5][CATEGORY_LEN] = {"RENT","UTILITY","GROCERY","STATIONARY","LEISURE"};
            for(int x=0;x<5;x++){
                rec_individual[x].amount = 0.00;
                strcpy(rec_individual[x].category,cats[x]);
            }
            collectExpensesForUser((*e1),id,rec_individual);
            int sort=0;
            struct ind_cat_exp temp;

            for(int k=0;k<4 && sort==0;k++){
                sort=1;
                for(int j=0;j<4-k;j++){
                    if(rec_individual[j].amount<rec_individual[j+1].amount){
                        temp=rec_individual[j];
                        rec_individual[j]=rec_individual[j+1];
                        rec_individual[j+1]=temp;
                        sort=0;
                    }
                }
            }
            float total_expense=0.00;
            for(int l=0;l<5;l++){
                total_expense += rec_individual[l].amount;
                printf("Category: %s\n",rec_individual[l].category);
                printf("Expense amount is %f \n",rec_individual[l].amount);
            }
            printf("Total expense for this user is %f\n",total_expense);



        }
    }
}
        
void get_categorical_expense(fam_tree **f1, user_tree **u1, expense_tree **e1){
    char cat[CATEGORY_LEN];
    int fam_id;

    printf("Enter category for which expense is to be found\n");
    scanf("%s",cat);

    printf("Which fam id information do u want to retrieve: \n");
    scanf("%d",&fam_id);

    fam_tree **found = Search_AVLFam(f1,fam_id);
    if(found == NULL){
        printf("Family id dosent exist\n");
    }
    if((found != NULL)&&((*found)!= NULL)){
        
        struct specific_cat_fam_exp rec_cat_family[4];
        struct specific_cat_fam_exp temp;
        for(int i=0;i<4;i++){
            rec_cat_family[i].user_ka_exp=0.00;
            rec_cat_family[i].user_ka_id=0;
        } // intialization done

        user_tree* nptr = (*found)->next_user;
        int i = 0;
        int len_rec_cat_family = 0;
        while(nptr != NULL){
            rec_cat_family[i].user_ka_id = nptr->user_id;
            float exp_amt = collectCategoryExpenseForUser((*e1),nptr->user_id,cat);
            rec_cat_family[i].user_ka_exp = exp_amt;
            i++;
            len_rec_cat_family++;
            nptr = nptr->next;
        }
        int sort= 0;
        for(int k=0;k<len_rec_cat_family-1 && sort==0;k++){
            sort=1;
            for(int j=0;j<len_rec_cat_family-k-1;j++){
                if(rec_cat_family[j].user_ka_exp<rec_cat_family[j+1].user_ka_exp){
                    temp=rec_cat_family[j];
                    rec_cat_family[j]=rec_cat_family[j+1];
                    rec_cat_family[j+1]=temp;
                    sort=0;
                }
            }
                
        }
        float total_users_cat_exp = 0.00;
        for(int l=0;l<len_rec_cat_family;l++){
            total_users_cat_exp += rec_cat_family[l].user_ka_exp;
            printf("User id: %d \n",rec_cat_family[l].user_ka_id);
            printf("Expense amount is %f \n",rec_cat_family[l].user_ka_exp);
        }
        printf("Total expense for family in this category is: %f\n",total_users_cat_exp);


    }


}

void get_highest_expense_day(fam_tree **f1, expense_tree **e1, user_tree ** u1){
    int fam_id;
    float date_arr[10];
    for(int i = 0 ;i<10; i++){
        date_arr[i] = 0.00;
    }

    printf("For which family id do you want to calculate the highest expense day: \n");
    scanf("%d",&fam_id);

    fam_tree **found = Search_AVLFam(f1,fam_id);
    if(found == NULL){
        printf("Family id dosent exist\n");
    }
    if((found != NULL)&&((*found)!= NULL)){
        printf("Entered date check\n");
        user_tree* nptr = (*found)->next_user;
        while(nptr != NULL){
            collectDateForUser((*e1),nptr->user_id,date_arr);
            nptr = nptr->next;

        }
        float max=date_arr[0];
        int loc=0;
        for(int m=0;m<10;m++){
            if(date_arr[m]>max){
                max=date_arr[m];
                loc=m;
            }
        }

        printf("Date at which maximum family expense incurred is %d \n",loc+1);
        printf("Expense amount is %f \n",max);
        
    }
}


void printExpINRange(expense_tree **root_ref,int u, int e1,int e2){
      
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return; 
    }
    if ((*root_ref)->member_id == u) {

        if ((*root_ref)->expense_id > e1){
            printExpINRange(&((*root_ref)->left), u, e1, e2);
        }
        

        if(((*root_ref)->expense_id >= e1)&&((*root_ref)->expense_id <= e2)){
            printf("Range exp amt is %f\n",(*root_ref)->exp_amt);
        }

        if((*root_ref)->expense_id < e2){
            printExpINRange(&((*root_ref)->right),u,e1,e2);
        }
        
    } 
    else if ((*root_ref)->member_id > u) {
        printExpINRange(&((*root_ref)->left),u,e1,e2);
    } 
    else {
        printExpINRange(&((*root_ref)->right),u,e1,e2);
    }

    return; 
}


void printExpINRangeDate(expense_tree **root_ref,int date1,int date2){
    if (*root_ref == NULL) {
        return; 
    }
    if(((*root_ref)->date >= date1)&&((*root_ref)->date <= date2)){
        printf("Date range exp amt is %f\n",(*root_ref)->exp_amt);
    }
    if ((*root_ref)->date > date1){
        printExpINRangeDate(&((*root_ref)->left), date1,date2);
    }
    if ((*root_ref)->date < date2){
        printExpINRangeDate(&((*root_ref)->right), date1,date2);
    }

}

void rangeSearchExpId(expense_tree* e1){
    
    int exp_id1, exp_id2, user_id;
    printf("Enter user_id: ");
    scanf("%d",&user_id);
    printf("Enter start of rangeSearchExpID : \n");
    scanf("%d",&exp_id1);
    printf("Enter end of rangeSearchExpID : \n");
    scanf("%d",&exp_id2);

    printExpINRange(&e1,user_id,exp_id1,exp_id2);
}



void rangeSearchDate(expense_tree* e1){
    int date1,date2;
    printf("Enter start of rangeSearchExpDate : \n");
    scanf("%d",&date1);
    printf("Enter end of rangeSearchExpDate : \n");
    scanf("%d",&date2);
    printExpINRangeDate(&e1,date1,date2);

}

int main(){
    user_tree* unbalanced1 = NULL;
    expense_tree* unbalanced1_exp = NULL;
    expense_tree* unbalanced1_expdate = NULL;
    fam_tree* unbalanced1_fam = NULL;
    int maxDepth = __INT_MAX__ ;
    int maxDepth_exp = __INT_MAX__;
    int maxDepth_expdate = __INT_MAX__;
    int maxDepthFam = __INT_MAX__;
    user_tree* root = NULL;
    expense_tree* root_exp = NULL;
    expense_tree* root_exp_date = NULL;
    fam_tree* f1 = NULL;
    int cj;
    int fam_id = 0;

    input_user(&root,&f1,&unbalanced1,maxDepth,&fam_id,&unbalanced1_fam,maxDepthFam);
    input_expense(&root_exp,&root_exp_date,&f1,&unbalanced1_exp,maxDepth_exp,&unbalanced1_expdate,maxDepth_expdate);
    //make an input function to take user inputfrom file 
    //after this call the addUser
    

    // addUser(&root,&cj,&fam_id,&f1,&unbalanced1,maxDepth,&unbalanced1_fam,maxDepthFam);
    // addUser(&root,&cj,&fam_id,&f1,&unbalanced1,maxDepth,&unbalanced1_fam,maxDepthFam);

    // printf("User root is %d\n",root->user_id);// working good 
    // addExpense(&root_exp,&root,&f1,&unbalanced1_exp,maxDepth_exp);

    // update_delete_expense(&f1,&root_exp,&unbalanced1_exp,maxDepth_exp);
    update_individual_fam_details(&root,&f1,&root_exp,&unbalanced1,&maxDepth,&unbalanced1_fam,&maxDepthFam,&unbalanced1_exp,&maxDepth_exp);
    // get_total_expense(&f1);
    // get_individual_expense(&root,&root_exp);
    // get_categorical_expense(&f1,&root,&root_exp);
    // get_highest_expense_day(&f1,&root_exp,&root);
    // rangeSearchExpId(root_exp);
    // rangeSearchDate(root_exp_date);


}

        