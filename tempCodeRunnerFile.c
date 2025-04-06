void printExpINRange(expense_tree **root_ref,int u, int e1,int e2){
      
    //modified my code so that it woud return a double pointer or a pointer to a
    //parent reference

    if (*root_ref == NULL) {
        return; 
    }
    if ((*root_ref)->member_id == u) {
        if(((*root_ref)->expense_id >= e1)&&((*root_ref)->expense_id <= e2)){
            printf("Range exp amt is %f\n",(*root_ref)->exp_amt);
        }
        else if((*root_ref)->expense_id > e2){
            printExpINRange(&((*root_ref)->left),u,e1,e2);
        }
        else{
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