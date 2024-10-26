#include <stdio.h>
#define X 3 /*size of segments*/
#define Y 3 /*number of recent segments*/
#define c 1 /*small constant integer*/
#define MAX_SIZE c*X*Y /*max size of our array*/
#define control 230104004 /*control number which is not in input.txt*/




int 
    main (void){

 FILE *inputFile= fopen("input.txt", "r");
 FILE *outputFile= fopen("output.txt", "w");




int x_count=0, /*to count size of current segment*/
    y_count=0, /*to count number of remembered segment*/
    found=0, 
    nextNumber;

    int temp_array[X];
    int permanent_array[Y][X]; /*an array to keep numbers in the segment and keep segment*/
    int segment_count_array[Y]= {0};
        
int i,p;
for(i=0; i<X; i++){
    for ( p = 0; p < Y; p++)
    {
permanent_array[p][i]= control ;} }  /*to sure that all arrays do not have random numbers
                                                                          we will use it later for possibilty of the fact that
                                                                                        all given number may be remembered for all input
                                                                                                                       so out arrays may not be full  */




while (fscanf(inputFile, "%d", &nextNumber) != EOF){

                                    temp_array[x_count%X]=nextNumber;
                                    x_count++;
                                    if(x_count==X){
                                       x_count=0;
                                        found=0; /*a segment counter if all numbers match */


                                        /*(if that was not same segment)*/
                                        int j,k;
                                            for  (j = 0; j < Y; j++)
                                            {   
                                                int match=1;
                                                    for ( k = 0; k < X; k++)
                                                    {
                                                        if(temp_array[k]!=permanent_array[j][k]) {  match=0; /* if any number do not match skip that segment*/
                                                                                                    break;
                                                        }
                                                    }

                                                   if(match==1) {   segment_count_array[j]++; 
                                                                    found=1;  /*if there are match with any segment we do not need to look all segments*/
                                                                    break; } 
                                            }
                                            
         

                    /*if it is segment which is not in memory ...*/
                        if(found==0){
                            int t;
                                        for (t = 0; t < X; t++)
                                        {
                                            permanent_array[y_count][t]=temp_array[t]; /*write to permanent memory*/
                                        }
                                        segment_count_array[y_count]=1; /*start to count of new segment and also delete old segment data*/ 
                                        y_count = (y_count + 1) % Y; /*it have to forget except last Y, so we used for that % Y*/

                                        


                        }    
                                      
                               fseek(inputFile, -(X - 1) * sizeof(int), SEEK_CUR);      


}
}

 int q,w;
 for ( q = 0; q < Y; q++)
 {
    if (permanent_array[q][0]!= control){

        for (w = 0; w < X; w++)
        {
            fprintf (outputFile, "%d ", permanent_array[q][w]);
        }
        
        fprintf(outputFile, ": %d\n",segment_count_array[q]);

    }

 }
 


    fclose(inputFile);
    fclose(outputFile);

    return 0;



    }
