#include <stdio.h>

int main(){

int question;
int stop;
printf("Which question you want to open? (1-2)\n");
scanf("%d", &question);

stop=0;
 while (stop==0) {
switch (question){

case 1 :

printf("\nGive positive integer: ");
int input;
int ques;
    int result=1;
//scanf("%d", &input);
int isNumber;
isNumber = scanf("%d", &input);

    if (input<=0||isNumber!=1)
       { printf("İnvalid number!!\n");
		isNumber=1;
		
		while (getchar() != '\n');
}
    

   	 else if (input <10)
    {
        int n;

            for (n = input; n>0; n--)
        {
            result= result *n;

        };
        
        printf("Factoriel of %d is %d \n", input, result);}
    
    

    		  else if (input >=10) printf("Square of %d is %d \n", input, input*input);
	

printf("\n Do you wanna continous. for YES click 1 \n");
scanf("%d", &ques);
if(ques != 1) stop = 1;	
	break;
case 2:
printf("\nGive a number\n");
int input2;
scanf("%d", &input2);
int number1=0, number2=1, result2,i;

printf("First %d terms : 0,", input2);
for (i=0; i<input2-1; i++){



result2= number1+number2;
printf("%d,", result2);
number2=number1;
number1=result2;



}
    
printf("\n Do you wanna continous. for YES click 1 \n");
scanf("%d", &ques);
if(ques != 1) stop = 1;	







}
}

printf("\n ... good bye ...\n");
return 0;
}
