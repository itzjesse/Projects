//
//  main.c
//  practice7
//
//  Created by Jesse Laurens Wiers on 20-10-19.
//  Copyright © 2019 Jesse Laurens Wiers. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int n,i, length = 0;
    scanf("%d",&n);
    length = n;
    
    int * array = malloc(n*sizeof(int));
    
    for(i=0;i<length;i++){
        scanf("%d", &n);
        array[i] = n;
    }
    
    for(i=0;i<length;i++){
        //        printf("%d", array[i]);
    }
    
    // printf("The length = %d\n", length);
    
    int possible = 0;
    int reachable = 1;
    int t = 1;
    
    for(i=length-1; i>0;i--){
        for(int p=i-1; p>-1;p--){
            //            printf("p equals %d\n", p);
            //            printf("array[p] equals %d\n",array[p]);
            //            printf("t equals %d\n", t);
            if(array[p] >= t){
                possible = 1;
            }
           
            t++;
        }
    
        if(possible != 1){
            reachable = 0;
        }
        t = 1;
        possible = 0;
    }
    
    if(reachable == 0){
        printf("NO ");
    }else{
        printf("YES ");
    }

    return 0;
}
