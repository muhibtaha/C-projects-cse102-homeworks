#include <stdio.h>

int mean_function(int arranged[27]){
int total=0;

for (int i = 0; i < 27; i++)
{
    total+=arranged[i];

}

return total/27;}


int main(void){


int cube[3][3][3]={{{5,5,12},{13,15,7}, {10,5,13}},
                     {{18,10,15},{7,10,15},{12,12,10}},
                     {{12,7,15},{10,12,15},{10,10,12}}};

int arranged[27];
int count=0;

for (int i = 0; i < 3; i++)
{
    for (int j= 0; j < 3; j++)
    {

        for (int k = 0; k < 3; k++)
        {

            arranged[count++] =cube[i][j][k];
        }
        
    }
    
}

//sort
for (int i = 26; i >0; i--)
{
    for (int j = i; j < 26 ; j++)
    {
        if(arranged[j]>arranged[j+1]){
                                        int temp = arranged[j];
                                        arranged[j]= arranged[j+1];
                                        arranged[j+1]=temp;
        }
    }
    
}





for (int i = 0; i < 27; i++)
{
    printf("%d, ", arranged[i]);
}


int mean = mean_function(arranged);
printf("\nmean :%d\n", mean);


int median = (27/2);
printf("median: %d\n", arranged[median]);



int min=10000, max=0;

for (int i = 0; i <27; i++)
{
    if(arranged[i]<min) min=arranged[i];
    if(arranged[i>max]) max=arranged[i];

}

printf("Range : [%d,%d]", min, max);



    int mode_array[27];
    for (int i = 0; i < 27; i++)
    {
        mode_array[i]=0;
    }
    
for (int i = 0; i < 27; i++)
{
   for (int j = 0; j < 27; j++)
   {
  if (arranged[j]==i){   mode_array[i]++;
}   }
    }


int mode=-1;
for (int i = 0; i < 27; i++)
{
if(mode_array[i]>mode) mode= i;}

printf("\nmode: %d\n", mode);


printf("Enter a number to chech frequency: \n");
int number;
scanf("%d", &number);

printf("The weigh value of %d, occurs %d time in the cube\n",number, mode_array[number]);

return(0);



}
