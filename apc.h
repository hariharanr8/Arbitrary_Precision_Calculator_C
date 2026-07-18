#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS		1
#define FAILURE		0

#define SAME		0
#define OPERAND1	1
#define OPERAND2	2
//double linked list structure
typedef struct node
{
    struct node *prev;
    int data;
    struct node *next;
}node;

// Function Prototypes
void addition(node *tail1, node *tail2, node **headR, node **tailR);
void subtraction(node *tail1, node *tail2, node **headR, node **tailR);
void multiplication(node *tail1, node *tail2, node **headR, node **tailR);
void division(node *head1, node *head2, node *tail2, node **headR, node **tailR);
void modulus(node *head1, node *head2, node *tail2, node **headR, node **tailR);
void power(node *head1, node *tail1, node *head2, node **headR, node **tailR);

int cla_validation(int argc, char *argv[],int*,int*);
void create_list(char *opr, node **head, node **tail);

int insert_first(node **head, node **tail, int data);
int insert_last(node **head, node **tail, int data);
int delete_list(node **head, node **tail);
void print_list(node *head);

int compare_list(node *head1, node *head2);
int list_len(node *head);
void remove_pre_zeros(node **head);


#endif
