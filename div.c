#include "apc.h"

void division(node *head1, node *head2, node *tail2, node **headR, node **tailR)
{
    // Handle division by zero
    if (head2->data == 0 && head2->next == NULL) {
        printf("ERROR: Division by zero is infinite!\n");
        return;
    }
    node *head_sr=NULL,*tail_sr=NULL,*head_opr1=NULL,*tail_opr1=NULL,*temp_1=head1;
    int sub_count=0;
    // Process dividend digit by digit from left to right
    while (temp_1 != NULL) {
        // Bring down the next digit to our working block
        insert_last(&head_opr1, &tail_opr1, temp_1->data);
        // Strip any leading zeros inside the working block to ensure correct comparison lengths
        remove_pre_zeros(&head_opr1);
        sub_count = 0;
        // Repeated subtraction loop
        while (1) {
            int cmp = compare_list(head_opr1, head2);
            if (cmp == OPERAND1 || cmp == SAME) {
                subtraction(tail_opr1, tail2, &head_sr, &tail_sr);
                
                // Clear out the old working block
                delete_list(&head_opr1, &tail_opr1);
                
                // Assign subtraction result as the new working block
                head_opr1 = head_sr;
                tail_opr1 = tail_sr; 
                // Reset temporary pointers for the next iteration
                head_sr = tail_sr = NULL;
                sub_count++;
            } else {
                break; // Working block is now smaller than the divisor
            }
        }
        // Append this digit's quotient count to our final result list
        insert_last(headR, tailR, sub_count);
        // Move to the next digit of the dividend
        temp_1 = temp_1->next;
    }
    // Clean up remaining memory used by working block
    delete_list(&head_opr1, &tail_opr1);
    // CRITICAL: Remove leading zeros from final quotient (converts "001" into "1")
    remove_pre_zeros(headR);
}
