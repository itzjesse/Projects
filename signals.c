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
    int signals, i, j, sLength, max, value, start, end;
    max = 0;
    
    Stack stack;                        // initialize stack
    stack = newStack(10);
    
    
    scanf("%d",&signals);

    for(i=0; i<signals; i++){
        scanf("%d",&sLength);
        for(j=0; j<sLength; j++){
            scanf("%d",&value);
            if(value<max){          // hier al die shit poppen
            int end = pop(&stack);
            

                while(max>=value){
                    if(pop(&stack)<end){
                        //    printf("[%d,%d)@%d,   ", .. stack[start] stack[end]);
                        

                    }
                }
                
                printf();
            }
            
            max = value;
            push(value, &stack);
            
        }
        
    }
  return 0;
}
