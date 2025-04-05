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



user_tree** Search_AVL(user_tree** root_ref, int e) {
    user_tree** retval = NULL;  
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return NULL;  
    }
    if ((*root_ref)->user_id == e) {
        retval = root_ref;  
    } 
    else if ((*root_ref)->user_id > e) {
        retval = Search_AVL(&((*root_ref)->left), e);
    } 
    else {
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
//write VisitFam code

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



int searchLinkedList(user_tree* lptr, int id, float expense, fam_tree* root) {
    int found = 0;
    user_tree* nptr = lptr;
    while (nptr != NULL && !found) {
        if (nptr->user_id == id) {
            //id has been found so this is the family
            //recalculate the total expense 
            // root->fam_expense = 0.00; //this ensures that even if i want to update it it will get reset to 0 before assigning it a new value
            root->fam_expense += expense;
            found = 1;
        }
        nptr = nptr->next;
    }
    return found;
}

int searchInFamUser(fam_tree **root, int target,float expense) {
    if (root == NULL || *root == NULL) return 0; // Base case

    // Check current node's linked list
    int c = searchLinkedList((*root)->next_user, target,expense,(*root));
    if(c == 1){
        return 1;
    }
    // if (searchLinkedList((*root)->next_user, target,expense,(*root))) return 1;

    // Search both left and right subtrees
    return searchInFamUser(&((*root)->left), target,expense) || searchInFamUser(&((*root)->right), target,expense);
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
            free(r);
            *parent_ptr = NULL;
        }
        else if(r->left == NULL){
            *parent_ptr = r->right ;
        }
        else if(r->right == NULL){
            *parent_ptr = r->left;
        }
        else{
            p=q=r->left ;
            while(q->right != NULL){
                p=q; //p is prev node
                q = q->right;
            }
            p->right = q->left ;
            q->left = r->left;
            q->right = r->right;
            *parent_ptr = q;
        }
    }
    // printf("Done with deleteAVL\n");
}

expense_tree* deleteRotCndCheckExp(expense_tree **root, expense_tree* toDel,expense_tree** unbalanced1,int* maxDepth){
    
    int left_ht = heightTreeExp((*root)->left,unbalanced1,maxDepth);
    int right_ht = heightTreeExp((*root)->right,unbalanced1,maxDepth);

    if(left_ht == right_ht){
        expense_tree **temp_del =searchInExpExpId(root,toDel->expense_id);
        if(temp_del != NULL){
            int deleted_value = (*temp_del)->expense_id;
            delete_AVLExp(temp_del);//initially it was &root
            printf("Ele %d deleted\n",deleted_value);
        }
        else{
            printf("Element not found\n");
        }
    }
    else if((left_ht-right_ht) == 1){
        // this will cover 2 cases
        if((toDel->member_id < (*root)->member_id)||((toDel->member_id == (*root)->member_id)&&(toDel->expense_id < (*root)->expense_id))){
            expense_tree **temp_del =searchInExpExpId(root,toDel->expense_id);
            if(temp_del != NULL){
                int deleted_value = (*temp_del)->expense_id;
                delete_AVLExp(temp_del);
                // printf("element deleted\n");
                printf("Ele %d deleted\n",deleted_value);
            }
            else{
                printf("Element not found\n");
            }
        }
        else{
            expense_tree **temp_del =searchInExpExpId(root,toDel->expense_id);
            if(temp_del != NULL){
                int deleted_value = (*temp_del)->expense_id;
                delete_AVLExp(temp_del);//post this it is twice left tilted
                printf("Root now is %d\n",(*root)->expense_id);
                printf("Ele %d deleted, now rotating \n",deleted_value);
                
                printf("max depth now is%d\n",*maxDepth); 
                *maxDepth = -999999;  // Reset before recalculating height
                int a = heightTreeExp(*root,unbalanced1,maxDepth);
                
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
        
                // if (abs(left_ht - right_ht) > 1) {
                //     *root = checkRotate(unbalanced1, unbalanced1, maxDepth);
                // }
                // root = checkRotate(root,unbalanced1,maxDepth); //all cases handled here 
                //here root is the true root which we are passing as the unbalanced one 
            }
        }
    }
    else if((right_ht-left_ht) == 1){
        if((toDel->member_id > (*root)->member_id)||((toDel->member_id == (*root)->member_id)&&(toDel->expense_id > (*root)->expense_id))){
            printf("checking RST \n");
            expense_tree **temp_del =searchInExpExpId(root,toDel->expense_id);
            printf("Done searching\n");
            if(temp_del != NULL){
                printf("inside delete block\n");
                int deleted_value = (*temp_del)->expense_id;
                delete_AVLExp(temp_del);
                printf("Ele %d deleted\n",deleted_value);
                //this had to be written bcos after temp_del has been deleted wecant access temp_del_>data right 
            }
            else{
                printf("Element not found\n");
            }
        }
        else {
            expense_tree **temp_del =searchInExpExpId(root,toDel->expense_id);
            if(temp_del != NULL){
                int deleted_value = (*temp_del)->expense_id;
                delete_AVLExp(temp_del);//post this it is twice right tilted
                printf("Ele %d deleted, now rotating \n",deleted_value);
                // left_ht = heightTree((*root)->left, unbalanced1, maxDepth);
                // right_ht = heightTree((*root)->right, unbalanced1, maxDepth);
                printf("max depth now is%d\n",*maxDepth); 
                *maxDepth = -999999;  // Reset before recalculating height
                int a = heightTreeExp(*root,unbalanced1,maxDepth);
                
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
                
                // if (abs(left_ht - right_ht) > 1) {
                //     *root = checkRotate(unbalanced1, unbalanced1, maxDepth);
                // }
                // *root = checkRotate(root,unbalanced1,maxDepth); //all cases handled here 
                //here root is the true root which we are passing as the unbalanced one 
            }
        }
    }

    return *root;
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
                    ptr1->next = user_input;
                    (*ptr)->fam_income += user_input->income;
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

void input_expense(expense_tree **root,fam_tree **f1, expense_tree **unbalanced1, int maxDepth) {
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
            (*root) = insertAVLExp((*root), expense_input, unbalanced1, &maxDepth);
            float expense = expense_input->exp_amt;
            int a = searchInFamUser(f1,mem_id,expense);
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
    int a = searchInFamUser(f1,id,expense);
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
                if((*ptr)->count < 4){
                    fam_id_found = 1;
                    user_tree* ptr3 = (*ptr)->next_user;
                    while((ptr3 != NULL)&&(ptr3->next != NULL)){

                        ptr3 = ptr3->next ;
                    }
                    ptr3->next = made_from_makeuser ;
                    (*ptr)->fam_income = (*ptr)->fam_income + made_from_makeuser->income;
                    (*ptr)->count += 1;
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
        
        if((foundNode != NULL)&&(*foundNode != NULL)){
            int user_id = (*foundNode)->member_id;
            int m = searchInFamUser(f1, user_id, -(*foundNode)->exp_amt);
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


            int k = searchInFamUser(f1, user_id, (*foundNode)->exp_amt);
            if(k==1){
                printf("Exp changes updated everywhere\n");
            }
        }
        else{
            printf("Expense id not found\n");
        }
        
    }
    else{
        printf("Which expense id information do u want to delete: \n");
        scanf("%d",&exp_id_del);
        
        expense_tree **foundNode = searchInExpExpId(e1,exp_id_del);
        if((foundNode != NULL)&&(*foundNode != NULL)){
            int user_id = (*foundNode)->member_id;
            int k = searchInFamUser(f1, user_id, -(*foundNode)->exp_amt);
            if(k==1){
                printf("Exp changes updated everywhere\n");
            }
            (*e1) = deleteRotCndCheckExp(e1,(*foundNode),unbalanced1,&maxDepthExp);
            printf("Expense deleted\n");
        }
        
        if(foundNode == NULL){
            //famtree me jaake uss family ke exp se subtract kardena 
            //call deleteRotCondCheckExp here 
            //this will ensure family se initially exp kam hojayega and then wo exp_tree se delete hojayega
            printf("Expense id not found\n");
            
        }
        

    }
    output_expense((*e1));
    output_fam((*f1));
}



int main(){
    user_tree* unbalanced1 = NULL;
    expense_tree* unbalanced1_exp = NULL;
    fam_tree* unbalanced1_fam = NULL;
    int maxDepth = __INT_MAX__ ;
    int maxDepth_exp = __INT_MAX__;
    int maxDepthFam = __INT_MAX__;
    user_tree* root = NULL;
    expense_tree* root_exp = NULL;
    fam_tree* f1 = NULL;
    int cj;
    int fam_id = 0;

    input_user(&root,&f1,&unbalanced1,maxDepth,&fam_id,&unbalanced1_fam,maxDepthFam);
    input_expense(&root_exp,&f1,&unbalanced1_exp,maxDepth_exp);
    //make an input function to take user inputfrom file 
    //after this call the addUser
    

    // addUser(&root,&cj,&fam_id,&f1,&unbalanced1,maxDepth,&unbalanced1_fam,maxDepthFam);
    // printf("User root is %d\n",root->user_id);// working good 
    // addExpense(&root_exp,&root,&f1,&unbalanced1_exp,maxDepth_exp);

    update_delete_expense(&f1,&root_exp,&unbalanced1_exp,maxDepth_exp);

    

}

        // printf("If exp cat has to be changed give different,else provide the same one: \n");
        // scanf("%s",upd_exp_cat);
        // printf("If u want to change the exp amt, give new exp amt else give old income: \n");
        // scanf("%f",&upd_exp_amt);
        // printf("If date has to be changed give different,else provide the same one: \n");
        // scanf("%d",&upd_date);
        
        // (*root)->date = upd_date ;
        // // ptr->exp_amt = upd_exp_amt ; this has been incorporated in the next loop
        // strcpy((*root)->expense_cat, upd_exp_cat);
        // (*root)->exp_amt = upd_exp_amt;
        
        // int user_id = (*root)->member_id;
        // int a = searchInFamUser(f1,user_id,upd_exp_amt);
        // return 1;