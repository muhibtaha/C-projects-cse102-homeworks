#include <stdio.h>

int
    main(void){

            printf("Enter positive integer number for n\n");
            int n;
            scanf("%d", &n);

            int i , result=0;
            for (i = 1; i < n; i+=2)
            { 
                result= result+i;
                
            }
            
            printf("The sum of odd numbers between 1 and %d is %d\n", n, result);






    }