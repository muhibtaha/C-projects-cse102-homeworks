#include <stdio.h>
#include <string.h>

// Yapı tanımı
typedef struct {
    char main_module_name[31];
    int coef_submodules[100];   // Alt modül katsayıları
    char sub_module_names[100][31];  // Alt modül isimleri
    int integers[100];          // Modüllerin tam sayı değerleri
    char temp_string_array[1000];   // Giriş stringi
} built;

// Yardımcı fonksiyonlar
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// String'i integer'a dönüştürme (atoi kullanmadan)
int stringToInt(char *str) {
    int result = 0;
    while (*str) {
        if (isDigit(*str)) {
            result = result * 10 + (*str - '0');
        } else {
            return -1; // Eğer sayı değilse hatalı durum
        }
        str++;
    }
    return result;
}

// Hesaplama fonksiyonu
int calculate(built module1, int submodule_count) {
    int result = 0;
    printf("[DEBUG] Starting calculation:\n");
    for (int i = 0; i < submodule_count; i++) {
        printf("coef[%d] = %d, integer[%d] = %d, sub_module_name: %s\n", 
               i, module1.coef_submodules[i], i, module1.integers[i], module1.sub_module_names[i]);
        result += module1.coef_submodules[i] * module1.integers[i]; // Katsayılı hesaplama
    }
    printf("[DEBUG] Final calculated result: %d\n", result);
    return result;
}

// Rekürsif işleme fonksiyonu
built my_function(built module1) {
    char *ptr = module1.temp_string_array;
    int submodule_count = 0;

    printf("Define %s: ", module1.main_module_name);
    getchar(); // \n karakterini temizlemek için
    scanf("%[^\n]", module1.temp_string_array);

    while (*ptr != '\0') {
        // Katsayıyı ayrıştır
        module1.coef_submodules[submodule_count] = 1; // Varsayılan katsayı
        if (isDigit(*ptr)) {
            module1.coef_submodules[submodule_count] = 0;
            while (isDigit(*ptr)) {
                module1.coef_submodules[submodule_count] = 
                    module1.coef_submodules[submodule_count] * 10 + (*ptr - '0');
                ptr++;
            }
        }
        if (*ptr == '*') ptr++; // '*' işaretini atla

        // Alt modül adını ayrıştır
        int len = 0;
        while (*ptr != '+' && *ptr != '\0') {
            module1.sub_module_names[submodule_count][len++] = *ptr;
            ptr++;
        }
        module1.sub_module_names[submodule_count][len] = '\0'; // Alt modül ismini sonlandır
        if (*ptr == '+') ptr++; // '+' işaretini atla

        // Eğer alt modül bir integer değilse
        int potentialInt = stringToInt(module1.sub_module_names[submodule_count]);
        if (potentialInt == -1) { // Alt modül bir integer değil, başka bir modül ismi
            printf("[DEBUG] Submodule '%s' is not an integer.\n", module1.sub_module_names[submodule_count]);
            built submodule; // Yeni bir alt modül yapısı oluştur
            strcpy(submodule.main_module_name, module1.sub_module_names[submodule_count]);
            submodule = my_function(submodule); // Alt modül işleme
            module1.integers[submodule_count] = submodule.integers[0]; // Hesaplanmış alt modül değeri al
            printf("[DEBUG] Calculated submodule '%s' result: %d\n", 
                   module1.sub_module_names[submodule_count], 
                   submodule.integers[0]);
        } else {
            // Eğer direkt bir integer ise
            module1.integers[submodule_count] = potentialInt;
            printf("[DEBUG] Integer at submodule_count %d: %d (sub_module_name: %s)\n", 
                   submodule_count, 
                   module1.integers[submodule_count], 
                   module1.sub_module_names[submodule_count]);
        }
        submodule_count++; // Bir sonraki alt modüle geç
    }

    // Tüm alt modüller tamamlandıktan sonra hesaplama
    printf("[DEBUG] Calculating result for %s with %d submodules.\n", 
           module1.main_module_name, submodule_count);
    module1.integers[0] = calculate(module1, submodule_count);
    printf("[DEBUG] Final result for module '%s': %d\n", 
           module1.main_module_name, 
           module1.integers[0]);
    return module1;
}

int main(void) {
    built module1 = {0}; // Tüm yapıyı sıfırla
    printf("Module name? ");
    scanf("%s", module1.main_module_name);
    module1 = my_function(module1); // Ana modül işleme
    
    printf("Final result for %s: %d\n", module1.main_module_name, module1.integers[0]);
    return 0;
}
