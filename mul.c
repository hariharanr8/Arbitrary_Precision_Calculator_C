#include "apc.h"


void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1=tail1;
    node *temp2=tail2,*headR2=NULL,*tailR2=NULL,*head_ar=NULL,*tail_ar=NULL;
    int mul,carry=0,count=0,i;
    while(temp2!=NULL){
        i=0,carry=0;
        while(i<count){
            insert_first(&headR2,&tailR2,0);
            i++;
        }
        while(temp1!=NULL){
            mul = (temp1->data * temp2->data) + carry;
            carry = mul/10;
            if(count==0){
                insert_first(headR,tailR,(mul%10));
            }
            else{
                insert_first(&headR2,&tailR2,(mul%10));
            }
            temp1=temp1->prev;
        }
        //Capture the final carry for the row if it exists
        if(carry > 0){
            if(count == 0){
                insert_first(headR,tailR,carry);
            } else {
                insert_first(&headR2,&tailR2,carry);
            }
        }
        if(count>=1){
            addition(*tailR,tailR2,&head_ar,&tail_ar);
            delete_list(headR,tailR);
            delete_list(&headR2,&tailR2);
            *headR=head_ar;
            *tailR=tail_ar;
            head_ar=tail_ar=NULL;
        }
        count++;
        temp1=tail1;
        temp2=temp2->prev;
    }
    remove_pre_zeros(headR);
}
