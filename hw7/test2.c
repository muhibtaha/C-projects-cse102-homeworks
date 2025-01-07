buradaki *labels i nerede tanımladık. içine sadece 1 leri mi yazdıkyoksa 0 ları da kendini etiketledik mi? statik bir tanımlama mı yaptık. eğer bunu da dinamik olarak oluştursaydık nasıl oluştururduk. renumer labels te nasıl yaptıgımızı da şema çizecerek anlat. tüm bu sorularımı tek tek ccevapla.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int label;
} piece;

// Fonksiyonlar
int find(int *labels, int x) {
    while (labels[x] != x) {
        x = labels[x];
    }
    return x;
}

void unite(int *labels, int x, int y) {
    int root_x = find(labels, x);
    int root_y = find(labels, y);
    if (root_x != root_y) {
        labels[root_y] = root_x;
    }
}

void hoshen_kopelman(piece **grid, int width, int height) {
    int *labels = malloc(width * height * sizeof(int));
    int next_label = 1;

    // Tüm etiketler kendi kökleri olarak başlar
    for (int i = 0; i < width * height; i++) {
        labels[i] = i;
    }

    // 1. Geçiş: Geçici etiketleme
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].value == 1) {
                int left = (x > 0) ? grid[y][x - 1].label : 0;
                int up = (y > 0) ? grid[y - 1][x].label : 0;

                if (left == 0 && up == 0) {
                    grid[y][x].label = next_label;
                    next_label++;
                } else if (left != 0 && up == 0) {
                    grid[y][x].label = left;
                } else if (left == 0 && up != 0) {
                    grid[y][x].label = up;
                } else {
                    grid[y][x].label = left;
                    unite(labels, left, up);
                }
            } else {
                grid[y][x].label = 0;
            }
        }
    }

    // 2. Geçiş: Nihai etiketleme
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].label != 0) {
                grid[y][x].label = find(labels, grid[y][x].label);
            }
        }
    }

    free(labels);
}

void print_grid(piece **grid, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%d ", grid[y][x].label);
        }
        printf("\n");
    }
}

int main(void) {
    int width, height;
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (!input || !output) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(input, "%d", &height);
    fscanf(input, "%d", &width);

    if (width > 1024 || height > 1024 || width < 1 || height < 1) {
        printf("M x N must be between 1 - 1024\n");
        return 1;
    }

    piece **grid = malloc(height * sizeof(piece *));
    for (int i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(piece));
        for (int j = 0; j < width; j++) {
            fscanf(input, "%d", &grid[i][j].value);
            grid[i][j].label = 0;
        }
    }

    hoshen_kopelman(grid, width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(output, "%d ", grid[i][j].label);
        }
        fprintf(output, "\n");
    }

    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }
    free(grid);

    fclose(input);
    fclose(output);

    return 0;
}
