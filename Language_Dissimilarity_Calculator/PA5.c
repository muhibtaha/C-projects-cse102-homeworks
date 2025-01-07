#include <stdio.h>
#include <string.h>
#define N 5

float positive_maker(float x){ //absoulte function
    if(x<0) return -x;
        else return x;

};


void search_and_count(char *filename, char dias[27][27][3], int counts[27][27], int *total_counts) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char buffer[3] = "";  //start buffer
    char c;

//initilation
    c=fgetc(file);
    buffer[0]=c;  //first letter

    c=fgetc(file);
    buffer[1]=c; //second letter
        char first = buffer[0];
        char second = buffer[1];

	//there wont be unvalid character such as \n, \t or \0


	// calculate index
        if (first == ' ') first = 26; else first -= 'a';
        if (second == ' ') second = 26; else second -= 'a';

        counts[first][second]++;
        (*total_counts)++;  // +1 for total biagram 
    




    while ((c = fgetc(file)) != EOF) {

            buffer[0] = buffer[1];  // swift left
            buffer[1] = c; // get new char to right side
        

        if (strlen(buffer) != 2) {
            continue;  //calculate for just which has 2 letters
        }

        char first = buffer[0];
        char second = buffer[1];

        // for fist character unvalid character control except a-z and space
        if ((first < 'a' || first > 'z') && first != ' ') {
            continue;
        }
        
        //for second character unvalid character control except a-z and space
        if ((second < 'a' || second > 'z') && second != ' ') {
            continue;
        }

        // calculate index
        if (first == ' ') first = 26; else first -= 'a';
        if (second == ' ') second = 26; else second -= 'a';

        counts[first][second]++;
        (*total_counts)++;  // +1 for total biagram
    }

    fclose(file);
}




double calculate_dissimilarity(int counts_a[27][27], int total_a, int counts_b[27][27], int total_b) {
    double dissimilarity = 0.0;


	//dissimalityrecord calculator
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            double freq_a = (double)counts_a[i][j] / total_a;
            double freq_b = (double)counts_b[i][j] / total_b;
            dissimilarity += positive_maker(freq_a - freq_b);
        }
    }

    return dissimilarity;
}





int main(void) {
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz "; // string array for alphabeth
    char dias[27][27][3];
    int counts[N+1][27][27] = {{{0}}};  //counts array for n+1 folder
    int total_counts[N+1] = {0};  // total biagram counter for N+1 folder

 //making combinations diagrams
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            dias[i][j][0] = alphabet[i];
            dias[i][j][1] = alphabet[j];
            dias[i][j][2] = '\0';
        }
    }

    //  first -> language_x.txt
    search_and_count("language_x.txt", dias, counts[0], &total_counts[0]); // index 0 is for language_x  !!!!

    //  language_N.txt file
    char openfilename[17];
    for (int i = 1; i <= N; i++) {
        sprintf(openfilename, "language_%d.txt", i);
        search_and_count(openfilename, dias, counts[i], &total_counts[i]);
    }

	//calculate dissimalirty
    for (int i = 1; i <= N; i++) {
        double dissimilarity = calculate_dissimilarity(counts[0], total_counts[0], counts[i], total_counts[i]);
        printf("Dissimilarity between language_x.txt and language_%d.txt: %f\n", i, dissimilarity);
    }

    return 0;
}
