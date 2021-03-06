#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "treeForm.h"

int main(int argc, char *argv[]) {
    char *ar;
    int complexity;
    List tl, tl1;
    tl1 = NULL;
    printf("give a formula: ");
    ar = readInput();
    while (ar[0] != '!') {
        tl = tokenList(ar);
        printList(tl);
        tl1 = tl;
        FormTree t = NULL;
        if ( biimplication(&tl1,&t) && tl1 == NULL ) {
            printf("with parentheses: ");
            // correction factor of -1
            complexity = complexityTree(t) - 1;
            printTree(t);
            printf("\n");
            simplify(t);
            printTree(t);
            printf("\ncomplexity: %d\n", complexity);
            freeTree(t);
        } else {
            printf("this is not a formula\n");
            if (t != NULL) {
                freeTree(t);
            }
        }
        free(ar);
        freeTokenList(tl);
        printf("\ngive a formula: ");
        ar = readInput();
        complexity = 0;
    }
    free(ar);
    printf("good bye\n");
    return 0;
}
