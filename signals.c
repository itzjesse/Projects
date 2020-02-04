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
    int signals, sLength, value, start, end;
    int max = 0;
    int pos = 0; //init position is zero
    int pos1 = 0;
    int previous = 0;
    int h = 0;
    
    Stack stack;                        // initialize stack
    stack = newStack(10);
    
    scanf("%d", &signals);

    for (int i = 0; i < signals; i++) {
        scanf("%d", &sLength);
        for (int j = 0; j < sLength; j++) {
            scanf("%d", &value);
            if (value < max) {          // hier al die shit poppen
                end = pop(&stack);
                previous = pop(&stack);
                pos--;
                h = end;
                while (previous <= end) {
                    if (previous < end) {
                        printf("[%d,%d)@%d\n", pos, pos1, h);
                        break;
                    } else if (previous == end) {
                        while (previous == end) {
                            pos--;
                            previous = pop(&stack);
                        }
                        printf("[%d,%d)@%d\n", pos, pos1, h);
                    }
                    h--;
                }
                push(value, &stack);
                pos++;
            } else {  //stack the value
                max = value;
                push(value, &stack);
                //printf("%d\n", pos);
                pos++;  //When something gets added to the stack, the position moves one to the right (+1)
                pos1++;
            }
            
            if (j == (sLength-1)) {
                //
            }
        }
    }
    
  return 0;
}
