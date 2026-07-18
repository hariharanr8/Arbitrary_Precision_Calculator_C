#include "apc.h"

void modulus(node *head1, node *head2, node *tail2, node **headR, node **tailR)
{
    // Handle modulus by zero edge case
    if (head2->data == 0 && head2->next == NULL) {
        printf("ERROR: Modulus by zero is undefined!\n");
        return;
    }

    if (head2 != NULL && head2->next == NULL) {
        tail2 = head2;
    }

    node *head_sr = NULL, *tail_sr = NULL;
    node *head_opr1 = NULL, *tail_opr1 = NULL;
    node *temp_1 = head1;

    // Process dividend digit by digit from left to right
    while (temp_1 != NULL) {
        insert_last(&head_opr1, &tail_opr1, temp_1->data);
        remove_pre_zeros(&head_opr1);

        // Repeated subtraction loop to find the remainder of this chunk
        while (1) {
            int cmp = compare_list(head_opr1, head2);
            if (cmp == OPERAND1 || cmp == SAME) {
                subtraction(tail_opr1, tail2, &head_sr, &tail_sr);
                
                delete_list(&head_opr1, &tail_opr1);
                head_opr1 = head_sr;
                tail_opr1 = tail_sr;
                head_sr = tail_sr = NULL;
            } else {
                break; 
            }
        }
        temp_1 = temp_1->next;
    }

    // At the end of long division, the final working block IS the remainder!
    node *remainder_curr = head_opr1;
    while (remainder_curr != NULL) {
        insert_last(headR, tailR, remainder_curr->data);
        remainder_curr = remainder_curr->next;
    }
    // Clean up temporary tracking memory
    delete_list(&head_opr1, &tail_opr1);
    // Remove any trailing formatting leading zeros
    remove_pre_zeros(headR);
}