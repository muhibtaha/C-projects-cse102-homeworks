#include <stdio.h>
#define X 2 /* size of segments */
#define Y 13 /* number of recent segments */
#define c 1 /* small constant integer */
#define MAX_SIZE c*X*Y /* max size of our array */
#define control 230104004 /* control number which is not in input.txt */

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

/*error control*/
    if (inputFile == NULL || outputFile == NULL) {
        printf("File opening error!\n");
        return 1;
    }

    int x_count = 0; /* to count size of current segment */
    int y_count = 0; /* to count number of remembered segments */
    int print_count=0; /* to use print to determine which is oldest*/
    int found = 0;
    int nextNumber;
    int temp_array[X];
    int permanent_array[Y][X]; /* an array to keep numbers in the segment and keep segments */
    int segment_count_array[Y] = {0};

    /* initialize arrays with control value to ensure no random numbers */
    int i,p;
    for (i = 0; i < X; i++) {
        for (p = 0; p < Y; p++) {
            permanent_array[p][i] = control;
        }
    }
    while (fscanf(inputFile, "%d", &nextNumber) == 1) {
            

        
        temp_array[x_count] = nextNumber;
        x_count++;

        if (x_count == X) {
            x_count = X - 1;  /* we add x-1 new number */
            found = 0; /* let there has not any same segments ++++*/

            /* Check if this is an existing segment in memory */
            int j, k;
            for (j = 0; j < Y; j++) {
                int match = 1; /*let all numbers match*/
                for (k = 0; k < X; k++) {
                    if (temp_array[k] != permanent_array[j][k]) {
                        match = 0; /* if any number does not match skip that segment */
                        break;
                    }
                }
                if (match==1) {
                    segment_count_array[j]++;
                    found = 1;  /* we have same segment ++++*/
                    
                    /*if there is a match with any segment, we do not need to check all segments */
                    break;
                }
            }
            

            /* if it is a segment that is not in memory, add it as a new segment */
            if (found==0) {
                int t=0;
                while (t < X){    
                    permanent_array[y_count][t] = temp_array[t]; /* Write to permanent memory */
                t++;
                
                }
                segment_count_array[y_count] = 1;  /*start to count of new segment and also delete old segment data*/
                print_count++; 
                y_count = (y_count + 1) % Y; /*it have to forget except last Y, so we used for that % Y*/





            }

            /* shift elements just one */
            int m;
            for (m = 1; m < X; m++) {
                temp_array[m - 1] = temp_array[m];
            }
                    temp_array[X - 1] = nextNumber;  // Add the new value at the end
        }
    }
            


 /* for first y segments, oldest segments is 0
    but after second tour, oldest segments is [y_count]
    for example if y_count = 1, segment[0] is newest segment so segment [1] become oldest*/
int q, w;
if(print_count<= Y) {
    for (q = 0; q < Y; q++) {

        if (permanent_array[q][0] != control) {
            for (w = 0; w < X; w++) {
                fprintf(outputFile, "%d ", permanent_array[q][w]);
            }
            fprintf(outputFile, ": %d\n", segment_count_array[q]);
        }
    }
}

    else if (print_count> Y){    
        
        /*first print after read count*/
        for (q = y_count; q < Y; q++) {
        if (permanent_array[q][0] != control) {
            for (w = 0; w < X; w++) {
                fprintf(outputFile, "%d ", permanent_array[q][w]);
            }
            fprintf(outputFile, ": %d\n", segment_count_array[q]);
        }
    }
        /*then print before read count*/
    for (q = 0; q < y_count; q++) {
        if (permanent_array[q][0] != control) {
            for (w = 0; w < X; w++) {
                fprintf(outputFile, "%d ", permanent_array[q][w]);
            }
            fprintf(outputFile, ": %d\n", segment_count_array[q]);
        }
    }


    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
