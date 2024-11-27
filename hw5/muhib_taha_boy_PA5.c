#include <stdio.h>
#include <string.h>
#define N 5

float positive_maker(float x){
    if(x<0) return -x;
        else return x;

};


void search_and_count(char *filename, char dias[27][27][3], int counts[27][27], int *total_counts) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char buffer[3] = "";  // Buffer başlatma
    char c;

//initilasion
    c=fgetc(file);
    buffer[0]=c;  //first letter

    c=fgetc(file);
    buffer[1]=c; //second letter
        char first = buffer[0];
        char second = buffer[1];



        // İndis hesaplama
        if (first == ' ') first = 26; else first -= 'a';
        if (second == ' ') second = 26; else second -= 'a';

        counts[first][second]++;
        (*total_counts)++;  // Toplam bigram sayısını artır
    




    while ((c = fgetc(file)) != EOF) {

            buffer[0] = buffer[1];  // Sola kaydır
            buffer[1] = c;
        

        if (strlen(buffer) != 2) {
            continue;  // Sadece iki harfli ifadeleri kontrol ediyoruz
        }

        char first = buffer[0];
        char second = buffer[1];

        // Geçersiz karakter kontrolü
        if ((first < 'a' || first > 'z') && first != ' ') {
            continue;
        }
        if ((second < 'a' || second > 'z') && second != ' ') {
            continue;
        }

        // İndis hesaplama
        if (first == ' ') first = 26; else first -= 'a';
        if (second == ' ') second = 26; else second -= 'a';

        counts[first][second]++;
        (*total_counts)++;  // Toplam bigram sayısını artır
    }

    fclose(file);
}

double calculate_dissimilarity(int counts_a[27][27], int total_a, int counts_b[27][27], int total_b) {
    double dissimilarity = 0.0;

    // Dissimilarity skorunu hesapla
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
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz ";
    char dias[27][27][3];
    int counts[N+1][27][27] = {{{0}}};  // N+1 dosya için sayaç tablosu
    int total_counts[N+1] = {0};  // N+1 dosya için toplam bigram sayısı

    // Tüm kombinasyonları oluştur
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 27; j++) {
            dias[i][j][0] = alphabet[i];
            dias[i][j][1] = alphabet[j];
            dias[i][j][2] = '\0';
        }
    }

    // `language_x.txt` dosyasını işleme
    search_and_count("language_x.txt", dias, counts[0], &total_counts[0]);

    // `language_1.txt`, `language_2.txt` ... dosyalarını işleme
    char openfilename[17];
    for (int i = 1; i <= N; i++) {
        sprintf(openfilename, "language_%d.txt", i);
        search_and_count(openfilename, dias, counts[i], &total_counts[i]);
    }

    // Benzerlik oranlarını hesapla ve yazdır
    for (int i = 1; i <= N; i++) {
        double dissimilarity = calculate_dissimilarity(counts[0], total_counts[0], counts[i], total_counts[i]);
        printf("Dissimilarity between language_x.txt and language_%d.txt: %f\n", i, dissimilarity);
    }

    return 0;
}
