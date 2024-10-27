#include <stdio.h>
#define X 2 /* size of segments */
#define Y 13 /* number of recent segments */
#define c 1 /* small constant integer */
#define MAX_SIZE c * X * Y /* max size of our array */
#define control 230104004 /* control number which is not in input.txt */

int main(void) {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    /* Error control */
    if (inputFile == NULL || outputFile == NULL) {
        printf("File opening error!\n");
        return 1;
    }

    int x_count = 0; /* to count size of current segment */
    int y_count = 0; /* to count number of remembered segments */
    int found;
    int nextNumber;
    int temp_array[X];
    int permanent_array[Y][X]; /* an array to keep numbers in the segment and keep segments */
    int segment_count_array[Y] = {0};

    /* Initialize arrays with control value to ensure no random numbers */
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            permanent_array[i][j] = control;
        }
    }

    /* Reading the input file */
    while (fscanf(inputFile, "%d", &nextNumber) == 1) {
        temp_array[x_count] = nextNumber;
        x_count++;

        if (x_count == X) {
            found = 0; /* Reset found for each new segment check */

            /* Check if this segment already exists */
            for (int j = 0; j < Y; j++) {
                int match = 1; /* Assume a match */
                for (int k = 0; k < X; k++) {
                    if (temp_array[k] != permanent_array[j][k]) {
                        match = 0; /* No match */
                        break;
                    }
                }
                if (match == 1) {
                    segment_count_array[j]++;
                    found = 1; /* Segment found */
                    break;
                }
            }

            /* If it's a new segment, add it */
            if (!found) {
                for (int t = 0; t < X; t++) {
                    permanent_array[y_count][t] = temp_array[t];
                }
                segment_count_array[y_count] = 1; /* Start counting of new segment */
                y_count = (y_count + 1) % Y; /* Overwrite oldest segment if Y is exceeded */
            }

            /* Shift elements in temp_array for the next input */
            for (int m = 1; m < X; m++) {
                temp_array[m - 1] = temp_array[m];
            }
            x_count--; /* Decrement x_count since we are moving elements up */
        }
    }

    /* Write the output file */
    for (int q = 0; q < Y; q++) {
        if (permanent_array[q][0] != control) {
            for (int w = 0; w < X; w++) {
                fprintf(outputFile, "%d ", permanent_array[q][w]);
            }
            fprintf(outputFile, ": %d\n", segment_count_array[q]);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

