#include <stdio.h>
#include <stdlib.h>

/* This imports the type and function declarations for the linear data
 * structures presented in the first lecture: stacks, queues and lists.
 *
 * NOTE You only need ONE of the three.
 * Please remove the other two lines.
 */
#include "LibStack.h"

\\ oefen code
\\ 1 9 1 3 3 5 5 7 7 4 0
\\ output: [5,7)@7, [5,7)@6, [3,7)@5, [3,9)@4, [1,9)@3, [1,9)@2, [0,9)@1, 

int main() {
    int signals, sLength, value, start, end;
    int max = 0;
    int pos = -1; //init position is zero
    int pos1 = 0;
    int previous = 0;
    int h = 0;
    int x = 1;
    
    Stack stack;                        // initialize stack
    stack = newStack(10);
    
    scanf("%d", &signals);

    for (int i = 0; i < signals; i++) {
        scanf("%d", &sLength);
        for (int j = 0; j < sLength; j++) {
            scanf("%d", &value);
            h = max;
            while (value < h) {
                if (x == 1) {
                    pop(&stack);
                    x++;
                }
                previous = pop(&stack);
                if (previous == h) {
                    pos--;
                    continue;
                } else if (previous < h){
                    push(previous, &stack);
                    printf("[%d,%d)@%d\n", pos, pos1, h);
                    h--;
                    continue;
                } else {
                    break;
                }
            }
            push(value, &stack);
            max = value;       //de top van de stack is het hoogste getal en als er eentje wordt toegevoegd is deze groter of gelijk dus altijd de max value
            pos++;             //When something gets added to the stack, the position moves one to the right (+1)
            pos1++;
            x = 1;
        }
    }
    return 0;
}
