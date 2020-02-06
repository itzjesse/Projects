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
    int pos = -1; //init position is zero
    int pos1 = 0;
    int previous = 0;
    int h = 0;
    int x = 1;
    int diff = 0;
    Stack stack;                        // initialize stack
    stack = newStack(10);
    
    scanf("%d", &signals);

    for (int i = 0; i < signals; i++) {
        scanf("%d", &sLength);
        for (int j = 0; j < sLength; j++) {
            scanf("%d", &value);
            h = max;
            while (value < h && (pos == 0 || pos == 1)) {
                if (pos == 0) {
                    printf("[%d,%d)@%d\n", pos, pos1, h);
                    break;
                } else if (pos == 1) {      //bijv 3 3 2 werkt nog niet
                    //hier nog
                }
            }
            while (value < h && pos > 1) {
                if (x == 1) {
                    pop(&stack);
                    x++;
                }
                previous = pop(&stack);
                if (previous == h) {
                    pos--;
                    diff++;
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
            pos += diff;
            diff = 0;
            max = value;       //de top van de stack is het hoogste getal en als er eentje wordt toegevoegd is deze groter of gelijk dus altijd de max value
            pos++;             //When something gets added to the stack, the position moves one to the right (+1)
            pos1++;
            x = 1;
            if (j == sLength - 1) {
                //en hier nog
            }
        }
    }
    freeStack(stack);
    return 0;
}
