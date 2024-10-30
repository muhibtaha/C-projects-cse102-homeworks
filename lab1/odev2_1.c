#include <stdio.h>

int 
    main(void){
        while(1) {
        printf("Enter two integers: ");
        int number1, number2, choise;

        scanf("%d %d", &number1, &number2);

        printf("\n1 for addition \n2 for substraction \n3 for multipclation \n4 for division\n ");
        scanf("%d", &choise);

        switch (choise)
        {
        case 1:
                printf(" Addition of %d and %d is %d\n", number1, number2, number1+number2);
            break;
        
        case 2:
                printf(" Substraction of %d and %d is %d\n", number1, number2, number1-number2);
            break;

        case 3:
                printf(" Multipclication of %d and %d is %d\n", number1, number2, number1*number2);
            break;

       case 4: 
                if(number2==0) printf("Error : Dividion by zero does not allowed\n");
                else 
                printf(" Division of %d and %d is %.3f\n", number1, number2, (float)number1/number2); 

            break;         
        default:
            printf("Invalid option please choice between number 1 and 4. \n");
            break;
        }
        }





    return(0);



    }