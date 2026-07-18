/*
    NAME   :    HARIHARAN R
    DATE   :    01/07/2026
DESCRIPTION:    This project implements an Arbitrary Precision Calculator (APC) in C,
                designed to overcome the standard integer data type limits (like long long int)
                by processing numbers of virtually infinite size. Using a custom doubly linked 
                list architecture, the system stores and manipulates massive numbers 
                digit-by-digit as individual nodes, ensuring complete structural memory 
                safety through dynamic allocation. The arithmetic engine fully supports 
                signed operations for Addition, Subtraction, Multiplication, Division, Modulus, 
                and Power, accurately tracking and applying sign rules based on mathematical 
                precedence. To optimize calculation speed and accuracy, a custom data-cleaning
                layer strips formatting abnormalities like leading zeros directly from the 
                memory stream. Ultimately, this project showcases core computer science 
                principles, including low-level memory management, algorithmic optimization, 
                and precise data-structure tracking.
 */
#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL;
	int opr1_sign=0,opr2_sign=0;
    // Validation
	if((cla_validation(argc,argv,&opr1_sign,&opr2_sign))==SUCCESS){
		// Create 2 lists of operands
		char *num1 = (argv[1][0] == '+' || argv[1][0] == '-') ? argv[1] + 1 : argv[1];
        char *num2 = (argv[3][0] == '+' || argv[3][0] == '-') ? argv[3] + 1 : argv[3];
		create_list(num1,&head1,&tail1);
		create_list(num2,&head2,&tail2);
        // clean up leading zeros
        remove_pre_zeros(&head1);
        remove_pre_zeros(&head2);
	}
	else{
		return FAILURE;
	}
    //print style:
    printf("operand 1 : ");
    if (opr1_sign && !(head1->data == 0 && head1->next == NULL)) {
        printf("-");
    }
    print_list(head1);
    // 2. Print Operator
    printf("operator  : %c\n", argv[2][0]);
    // 3. Print Operand 2 with its sign
    printf("operand 2 : ");
    if (opr2_sign && !(head2->data == 0 && head2->next == NULL)) {
        printf("-");
    }
    print_list(head2);
    printf("Result    : ");

    char oper = argv[2][0];
	int res_sign=0,ret;
    switch(oper)
    {
	case '+':
		//Both are positive
		if(!opr1_sign && !opr2_sign){
			addition(tail1, tail2, &headR, &tailR);
            res_sign = 0;
		}
		//Both are negative
		else if(opr1_sign && opr2_sign){
			addition(tail1, tail2, &headR, &tailR);
            res_sign = 1;
		}
		else{
			ret = compare_list(head1, head2);
            if (ret == OPERAND1) {
                subtraction(tail1, tail2, &headR, &tailR);
                // Result takes the sign of the larger magnitude (Operand 1)
				res_sign=opr1_sign;
            } 
            else if (ret == OPERAND2) {
                subtraction(tail2, tail1, &headR, &tailR);
                // Result takes the sign of the larger magnitude (Operand 2)
                res_sign=opr2_sign;
            } 
            else {
                // same values with different sign
                printf("0\n");
				break;
            }
		}
		if (res_sign && !(headR->data == 0 && headR->next == NULL)) {
            printf("-");
        }
        print_list(headR);
	    break;
	case '-':
		//Both are positive
        if (!opr1_sign && !opr2_sign) {
            ret = compare_list(head1, head2);
            if (ret == OPERAND1) {
                subtraction(tail1, tail2, &headR, &tailR);
                print_list(headR);
            } 
            else if (ret == OPERAND2) {
                subtraction(tail2, tail1, &headR, &tailR);
                printf("-");
                print_list(headR);
            } 
            else {
                printf("0\n");
            }
        }
        //Both are negative
        else if (opr1_sign && opr2_sign) {
            ret = compare_list(head1, head2);
            if (ret == OPERAND1) {
                subtraction(tail1, tail2, &headR, &tailR);
                if (opr1_sign && !(headR->data == 0 && headR->next == NULL)) {
                    printf("-");
                }
                print_list(headR);
            } 
            else if (ret == OPERAND2) {
                subtraction(tail2, tail1, &headR, &tailR);
                print_list(headR); // Operand 2 is larger, becomes positive
            } 
            else {
                printf("0\n");
            }
        }
        // Mixed signs -> This turns into ADDITION!
        else {
            addition(tail1, tail2, &headR, &tailR);
            if (opr1_sign && !(headR->data == 0 && headR->next == NULL)) {
                printf("-");
            }
            print_list(headR);
        }
	    break;
	case 'x':
	case 'X':
		if((opr1_sign && !opr2_sign) || (opr2_sign && !opr1_sign)){
			res_sign=1;
		}
		multiplication(tail1,tail2,&headR,&tailR);
		if(res_sign && !(headR->data == 0 && headR->next == NULL)){
			printf("-");
		}
		print_list(headR);
	    break;
	case '/':
		// If one is negative and the other is positive, the result sign is negative
        if ((opr1_sign && !opr2_sign) || (opr2_sign && !opr1_sign)) {
            res_sign = 1;
        }
        // Call division (Note: passing tail2 as required by your prototype)
        division(head1, head2, tail2, &headR, &tailR);
        // Print minus sign only if the result is negative and NOT zero
        if (res_sign && !(headR->data == 0 && headR->next == NULL)) {
            printf("-");
        }
        print_list(headR);
	    break;
    case '%':
        res_sign = opr1_sign;
        modulus(head1, head2, tail2, &headR, &tailR);
        if (res_sign && !(headR->data == 0 && headR->next == NULL)) {
            printf("-");
        }
        print_list(headR);
        break;
    case '^':
        // If the exponent is negative, the integer result is always 0
        if (opr2_sign) {
            printf("0\n");
            break;
        }
        // Result is negative ONLY if the base is negative AND the exponent is odd
        res_sign = (opr1_sign && (tail2->data % 2 != 0));
        power(head1, tail1, head2, &headR, &tailR);
        if (res_sign && !(headR->data == 0 && headR->next == NULL)) {
            printf("-");
        }
        print_list(headR);
        break; 
	default:
	    printf("Invalid operator\n");
    }
    // free the memory and exit
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);
    return SUCCESS;
}

