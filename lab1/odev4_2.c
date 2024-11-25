#include <stdio.h>

int main(void){
char text[13]= "happaynewyear";

printf("Enter a char: \n");
char letter;
scanf("%c", &letter);
int count=0;

for (int i = 0; i < 12; i++)
{
    if(text[i]==letter) count++;
}

printf("The character %c appears %d times\n", letter, count);








}