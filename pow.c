#include "apc.h"

void power(node *head1, node *tail1, node *head2, node **headR, node **tailR)
{
    // Condition 1: Any number to the power of 0 is 1
    if (head2->data == 0 && head2->next == NULL) {
        insert_last(headR, tailR, 1);
        return;
    }
    // Condition 2: 0 to any positive power is 0
    if (head1->data == 0 && head1->next == NULL) {
        insert_last(headR, tailR, 0);
        return;
    }
    // Step 1: Convert the exponent linked list (head2) into a standard integer counter
    long long exp_counter = 0;
    node *temp_exp = head2;
    while (temp_exp != NULL) {
        exp_counter = (exp_counter * 10) + temp_exp->data;
        temp_exp = temp_exp->next;
    }
    // Step 2: Initialize result list with the base value (head1/tail1 copy)
    node *curr = head1;
    while (curr != NULL) {
        insert_last(headR, tailR, curr->data);
        curr = curr->next;
    }
    // Step 3: Run the loop calling multiplication (exp_counter - 1) times
    // Example: 5^3 means Result = 5, then multiply by 5 two more times (5 * 5 * 5)
    for (long long i = 1; i < exp_counter; i++) {
        node *head_temp_res = NULL, *tail_temp_res = NULL;
        // Multiply current accumulated result (*tailR) with the original base (tail1)
        multiplication(*tailR, tail1, &head_temp_res, &tail_temp_res);
        // Delete the old accumulator result and replace it with the newly multiplied list
        delete_list(headR, tailR);
        *headR = head_temp_res;
        *tailR = tail_temp_res;
    }
}