#include "apc.h"
#include<ctype.h>

// Function definitions

int cla_validation(int argc, char *argv[],int *opr1_sign,int *opr2_sign){
    //check only 4 arguments presented (./a.out operand1 operator operand2)
    if(argc!=4){
        printf("ERROR: Only present four argument\n");
        printf("INFO: give args like (output_file operand1 operator operand2)\n");
        return FAILURE;
    }
    //check argument 1 and 3 only contains digit
    int i=0;
    if(argv[1][0]=='+' || argv[1][0]=='-'){
        if(argv[1][0]=='-'){
            *opr1_sign=1;
        }
        i=1;
        if(argv[1][1]=='\0'){
            return FAILURE;
        }
    }
    while(argv[1][i]){
        if(!isdigit(argv[1][i])){
            printf("ERROR: only digits is allowed in argument1\n");
            printf("INFO: arg1-->\"12345\"\n");
            return FAILURE;
        }
        i++;
    }

    int j=0;
    if(argv[3][0]=='+' || argv[3][0]=='-'){
        if(argv[3][0]=='-'){
            *opr2_sign=1;
        }
        j=1;
        if(argv[3][1]=='\0'){
            return FAILURE;
        }
    }
    while(argv[3][j]){
        if(!isdigit(argv[3][j])){
            printf("ERROR: only digits is allowed in argument3\n");
            printf("INFO: arg1-->\"12345\"\n");
            return FAILURE;
        }
        j++;
    }
    //check argument 2 only one character presenst.
    if(argv[2][1]!='\0'){
        return FAILURE;
    }
    //check argument 2 only contains any one opertors (+,-,X,x,/)
    else{
        if(argv[2][0]=='+' || argv[2][0]=='-' || argv[2][0]=='X'
            || argv[2][0]=='x' || argv[2][0]=='/' || argv[2][0]=='^' || argv[2][0]=='%'){
                return SUCCESS;
        }
        else{
            printf("ERROR: Invalid Operator!\n");
            printf("INFO: Oper--> + (Addition)\n");
            printf("INFO: Oper--> - (Subtraction)\n");
            printf("INFO: Oper--> x or X (Multiplication)\n");
            printf("INFO: Oper--> / (Division)\n");
            printf("INFO: Oper--> %% (Modulus)\n");
            printf("INFO: Oper--> ^ (Power)\n");
            return FAILURE;
        }
    }
}

//create list Function
void create_list(char *opr, node **head, node **tail){
    int i=0,data=0;
    node *temp=*tail;
    while(opr[i]){
        data=opr[i]-'0';
        node *new=malloc(sizeof(node));
        temp=*tail;
        if(new==NULL){
            printf("Memory not allocated properly!");
            return;
        }
        new->data=data;
        //list empty
        if(*head==NULL){
            new->prev=NULL;
            new->next=NULL;
            *head=*tail=new;
        }
        else{
            new->prev=temp;
            new->next=NULL;
            temp->next=new;
            *tail=new;
        }
        i++;
    }
}

//insert first function
int insert_first(node **head, node **tail, int data){
    node *new=malloc(sizeof(node));
    if(new==NULL){
        return FAILURE;
    }
    new->data=data;
    new->prev=NULL;
    if(*head==NULL){
        new->next=NULL;
        *head=new;
        *tail=new;
    }
    else{
        new->next=*head;
        (*head)->prev=new;
        *head=new;
    }
    return SUCCESS;
}

//insert last function
int insert_last(node **head, node **tail, int data){
    node *new=malloc(sizeof(node));
    if(new==NULL){
        return FAILURE;
    }
    new->data=data;
    new->next=NULL;
    if(*head==NULL){
        new->prev=NULL;
        *head=*tail=new;
    }
    else{
        new->prev=*tail;
        (*tail)->next=new;
        *tail=new;
    }
    return SUCCESS;
}

//delete list or free the memory in list
int delete_list(node **head, node **tail){
    if(*head==NULL){
        return FAILURE;
    }
    node *temp=*head;
    while(temp->next!= NULL){
        temp->next->prev=NULL;
        *head=temp->next;
        free(temp);
        temp=*head;
    }
    free(temp);
    *head=NULL;
    *tail=NULL;
    return SUCCESS;
}

//print list function
void print_list(node *head){
    while(head!=NULL){
        printf("%d",head->data);
        head=head->next;
    }
    printf("\n");
}

//find list length function
int list_len(node *head){
    int count=0;
    while(head!=NULL){
        count++;
        head=head->next;
    }
    return count;
}

//list compare function
int compare_list(node *head1, node *head2){
    
    int oper1=list_len(head1);
    int oper2=list_len(head2);
    if(oper1 > oper2){
        return OPERAND1;
    }
    if(oper2 > oper1){
        return OPERAND2;
    }

    node *temp1 = head1;
    node *temp2 = head2;
    
    while(temp1 !=NULL && temp2 !=NULL) {
        //if true operand 1 is big
        if(temp1->data > temp2->data) {
            return OPERAND1;
        }
        //if true operand 2 is big
        if(temp2->data > temp1->data) {
            return OPERAND2;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    // If every single digit matched exactly (e.g., 123 - 123)
    return SAME;
}

//remove prezeros in a list (e.g., 000012 + 00000021--> 12 + 21)
void remove_pre_zeros(node **head){
    node *temp=*head;
    while(temp->next!=NULL && temp->data==0){
        temp->next->prev=NULL;
        *head=temp->next;
        free(temp);
        temp=*head;
    }
}