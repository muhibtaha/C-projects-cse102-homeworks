#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 800
#define COLS 1000

int main() {
    FILE *file = fopen("grid.txt", "w");
    
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }

    // Rastgele sayı üreticiye başlangıç değeri verelim
    srand(time(NULL));

    // 800 satır, 1000 sütunlu grid oluşturma
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Rastgele 0 veya 1 yazdır
            fprintf(file, "%d", rand() % 2); 
            if (j < COLS - 1) {
                fprintf(file, " "); // Sütunlar arasında boşluk bırak
            }
        }
        fprintf(file, "\n"); // Her satırdan sonra yeni satıra geç
    }

    fclose(file);
    printf("Grid dosyaya yazıldı: grid.txt\n");
    
    return 0;
}
