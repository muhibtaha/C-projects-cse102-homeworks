#include <stdio.h>
#define X 2 /*size of segments*/
#define Y 3 /*number of recent segments*/
#define c 1 /*small constant integer*/
#define MAX_SIZE c*X*Y /*max size of our array*/

int areSame()



void my_function(FILE *inputFile, FILE *outputFile) {

int x_count=0, /*to count size of current segment*/
    y_count=0, /*to count number of remembered segment*/
    nextNumber;

    int x_array[MAX_SIZE], /*an array to keep numbers in the segment*/
        y_array[MAX_SIZE]; /*an array to keep needed arrays that are keeping numbers*/

int i;
for(i=0; i<MAX_SIZE; i++){  /*to sure that all arrays do not have random numbers*/
                               x_array[i]=0; 
                               y_array[i]=0;             };


                        while (fscanf(inputFile, "%d", &nextNumber) != EOF){

                                    x_array[x_count++]=nextNumber;
                                    
                                    if(x_count==X){
                                        x_count=0;

                                        /*(if that was not same segment)*/
                                        
                                        int j;
                                        for(j=0;j<X;j++){
                                            y_array[y_count] += {x_array[j]} /*hatalı x er x er sırayla yazacağız*/

                                        };
                                                y_count++;

                                    }


}





}






int 
    main (void){

 FILE *inputFile= fopen("input.txt", "r");
 FILE *outputFile= fopen("output.txt", "w");

        printf("%2d\n", MAX_SIZE);

    }