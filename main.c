//
//  main.c
//  Test
//
//  Created by Ömer-Tarik Özyilmaz on 17/03/2020.
//  Copyright © 2020 Ömer Tarik Özyilmaz. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define N 11;
#define MAXINPUT 100;

/* The function readInput reads the input and yields a string containing this input.
 * Initially, the length of s is MAXINPUT: it is doubled when necessary.
 */

char *readInput() {
    int strLen = MAXINPUT;
    int c = getchar();
    int i = 0;
    char *s = malloc((strLen+1)*sizeof(char));
    assert( s != NULL );
    while ( c != '\n' ) {
        s[i] = c;
        i++;
        if ( i >= strLen ) { /* s is not large enough, its length is doubled */
            strLen = 2*strLen;
            s = realloc(s,(strLen+1)*sizeof(char));
            assert( s != NULL );
        }
        c = getchar();
    }
    s[i] = '\0';
    return s;
}

int** makeIntArr2D(int m, int n) {
    int i;
    int** array;
    array = malloc(m*sizeof(int *));
    assert( array != NULL );
    array[0] = calloc(m*n, sizeof(int));
    assert( array[0] != NULL );
    for ( i=1; i<m; i++ ) {
        array[i] = array[i-1] + n;
    }
    return array;
}

void freeTwoDimArray(int m, int n, int **array) { int i;
    for ( i = 0; i < m; i++ ) {
        free(array[i]);
    }
    free(array);
}

void connections (int **array) {
    array[0][1] = 51;
    array[0][2] = 26;
    array[1][3] = 89;
    array[3][4] = 63;
    array[3][5] = 55;
    array[3][2] = 47;
    array[6][7] = 50;
    array[8][9] = 34;
    array[8][10] = 50;
    array[9][10] = 40;
    array[4][5] = 111;
    array[10][7] = 15;
    array[5][7] = 77;
    array[2][7] = 51;
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            array[j][i] = array[i][j];
        }
    }
}

int matchNode (char *ar) {
    int node = 0;
    if (strcmp(ar, "Amsterdam") == 0) {
        node = 0;
    } else if (strcmp(ar, "Den Haag") == 0){
        node = 1;
    } else if (strcmp(ar, "Utrecht") == 0) {
        node = 2;
    } else if (strcmp(ar, "Eindhoven") == 0){
        node = 3;
    } else if (strcmp(ar, "Maastricht") == 0) {
        node = 4;
    } else if (strcmp(ar, "Nijmegen") == 0){
        node = 5;
    } else if (strcmp(ar, "Enschede") == 0) {
        node = 6;
    } else if (strcmp(ar, "Zwolle") == 0){
        node = 7;
    } else if (strcmp(ar, "Groningen") == 0) {
        node = 8;
    } else if (strcmp(ar, "Leeuwarden") == 0){
        node = 9;
    } else if (strcmp(ar, "Meppel") == 0) {
        node = 10;
    } else {
        node = 11;
    }
    return node;
}

int dijkstraAlgorithm (int **G, int v) {
    int d[11];
    int S[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int u = 0; u < 11; u++) {
        if (u == v) {
            d[u] = 0;
        } else {
            d[u] = 150;
        }
    }
    return d;
}

int main(int argc, const char * argv[]) {
    int **cities = makeIntArr2D(11, 11);
    char *ar;
    int v = 0;
    connections(cities);
    ar = readInput();
    while (ar[0] != '!') {
        v = matchNode(ar);
        if (v == 11) {
            return 0;
        }
        //dijkstraAlgorithm(cities, v);
        printf("%d\n", v);
        ar = readInput();
    }
    return 0;
}
