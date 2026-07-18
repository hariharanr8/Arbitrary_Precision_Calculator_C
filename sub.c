#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1=tail1,*temp2=tail2;
    int borrow=0,sub=0,val1,val2;
    while(temp1!=NULL){
        sub=0;
        val1=temp1->data;
        val2=(temp2!=NULL) ? temp2->data : 0;
        if(val1<(val2+borrow)){
            val1 +=10;
            val1 -=borrow;
            borrow=1;
        }
        else{
            val1 -=borrow;
            borrow=0;
        }
        sub = val1 - val2;
        insert_first(headR,tailR,sub);
        if(temp2!=NULL){
            temp2=temp2->prev;
        }
        temp1 =temp1->prev;
    }
    remove_pre_zeros(headR);
}
