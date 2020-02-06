#include <stdio.h>
#include <stdlib.h>

/* This imports the type and function declarations for the linear data
 * structures presented in the first lecture: stacks, queues and lists.
 *
 * NOTE You only need ONE of the three.
 * Please remove the other two lines.
 */
#include "LibStack.h"

int main() {
    int signals, sLength, value;
    int max = 0;
    int left = -1;                                                          //(left) left starts at -1
    int right = 0;                                                          //(right) right starts
    int previous = 0;
    int h = 0;                                                              //initialize height at 0
    Stack stack;                                                            //initialize stack
    stack = newStack(10);
    
    scanf("%d", &signals);                                                  //input the amount of signals
    for (int i = 0; i < signals; i++) {                                     //input the signal lengths
        scanf("%d", &sLength);
        for (int j = 0; j < sLength; j++) {                                 //input the signals
            scanf("%d", &value);
            h = max;                                                        //the height is the maximum value of the stack
            if (value < h) {
                pop(&stack);
            }
            while (value < h) {                                             //if the next input is lower than the height, we need to pop and print
                if (left == 0) {                                            /* if the second input is lower than the first input we can not pop the                                        non-existing previous input, so we instantly print */
                    printf("[%d,%d)@%d\n", left, right, h);                 //print the position (left and right) and the height of the top value
                    break;                                                  //we are done printing, so exit the loop
                } else if (left == 1) {                                     //if the third input is lower than the second and maybe the first, we can not pop the previous input in the case of e.g. 3 3 2 to check if the second and the first inputs are the same.
                    printf("[%d,%d)@%d\n", left, right, h);
                    break;
                }
                previous = pop(&stack);                                     //we also want the previous input to check against our max
                if (previous == h) {                                        //if the previous input is equal to the maximum height
                    left--;                                                 //the starting position of the bar is one to the left
                } else if (previous < h) {                                  //if the previous input is lower than the max. height
                    push(previous, &stack);                                 //we push that input back
                    printf("[%d,%d)@%d\n", left, right, h);                 //and we print the length of the bar of the max. height
                    h--;                                                    //then we check a level lower
                }
            }
            push(value, &stack);                                            //we push the new value on the stack
            max = value;
            right++;                                                        //the stack gets higher, so the postion to the right goes further
            if (j == sLength - 1) {                                         //if that was the last value of the signal
                value = 0;                                                  //we set the next value to a zero
                if (value < h) {
                    pop(&stack);                                            //we pop the top of the stack
                }
                while (value < h) {                                         //if that is lower than h (so h is not 0)
                    if (left == 0) {                                        //if the second input is lower than the first input we can not pop, so we instantly print
                        printf("[%d,%d)@%d\n", left, right, h);
                        break;
                    } else if (left == 1) {                                 //if the third input is lower than the second and maybe the first
                        printf("[%d,%d)@%d\n", left, right, h);
                        break;
                    }
                    previous = pop(&stack);                                 //we also want the previous input to check against our h
                    if (previous == h) {                                    //if the previous input is equal to the maximum height
                        left--;                                             //the starting position of the bar is one to the left
                    } else if (previous < h){                               //if the previous input is lower than the max. height
                        push(previous, &stack);                             //we push that input back
                        printf("[%d,%d)@%d\n", left, right, h);             //and we print the length of the bar of the max. height
                        h--;                                                //then we check a level lower
                    }
                }
            }
            left++;                                                         //then we increase the left position
        }
    }
    freeStack(stack);                                                       //free the stack, because we care about our memory ;)
    return 0;
}
