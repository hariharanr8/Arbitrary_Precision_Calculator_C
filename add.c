#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1=tail1,*temp2=tail2;
    int carry=0,sum=0;
    while(temp1!=NULL || temp2!=NULL || carry !=0){
        sum=carry;
        if(temp1!=NULL){
            sum += temp1->data;
            temp1=temp1->prev;
        }
        if(temp2!=NULL){
            sum+=temp2->data;
            temp2=temp2->prev;
        }
        carry=sum/10;
        sum=sum%10;
        insert_first(headR,tailR,sum);
    }
    remove_pre_zeros(headR);
}
