#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 10
#define MAX_NAME_LEN 20

// Mantık Kapısı Yapısı
typedef struct Gate {
    char name[MAX_NAME_LEN];                  // Kapının ismi
    struct Gate* input_gates[MAX_INPUTS];    // Giriş kapılarının adresleri
    int number_of_inputs;                    // Giriş sayısı
    int output;                              // Kapının çıkışı
    int former_out;                         // Flip-Flop için önceki çıkış
    int (*characteristic_function)(int*, int);  // Fonksiyon işaretçisi
} Gate;

// Mantık Fonksiyonları
int and_function(int* inputs, int n) {
    for (int i = 0; i < n; i++) {
        if (!inputs[i]) return 0;            // Tüm girişler 1 değilse 0 döndür
    }
    return 1;                                // Tüm girişler 1 ise 1 döndür
}

int or_function(int* inputs, int n) {
    for (int i = 0; i < n; i++) {
        if (inputs[i]) return 1;            // En az bir giriş 1 ise 1 döndür
    }
    return 0;                                // Hiçbiri 1 değilse 0 döndür
}

int not_function(int* inputs, int n) {
    return !inputs[0];                       // Girişin tersini döndür
}

int flipflop_function(int* inputs, int former_out) {
    return inputs[0] ? !former_out : former_out;  // Flip-Flop mantığı
}

// Kapı Oluşturma
Gate* create_gate(const char* type, const char* name) {
    Gate* gate = (Gate*)malloc(sizeof(Gate));  // Dinamik bellek ayırma
    if (!gate) {
        printf("Bellek ayıramadı!\n");
        exit(1);
    }
    strncpy(gate->name, name, MAX_NAME_LEN);  // Kapı adını kopyala
    gate->number_of_inputs = 0;               // Başlangıçta giriş sayısı 0
    gate->output = 0;                         // Başlangıç çıkışı 0
    gate->former_out = -1;                     // Başlangıç önceki çıkışı -1

    // Fonksiyon işaretçisini ayarla
    if (strcmp(type, "AND") == 0) {
        gate->characteristic_function = and_function;
    } else if (strcmp(type, "OR") == 0) {
        gate->characteristic_function = or_function;
    } else if (strcmp(type, "NOT") == 0) {
        gate->characteristic_function = not_function;
    } else if (strcmp(type, "FLIPFLOP") == 0) {
        gate->characteristic_function = NULL;
    } else {
        gate->characteristic_function = NULL;  // Geçersiz tür
    }
    printf("Kapı oluşturuldu: Tür: %s, İsim: %s\n", type, name);
    return gate;
}

// Giriş Kapısı Ekleme
void add_input_gate(Gate* gate, Gate* input_gate) {
    if (gate->number_of_inputs >= MAX_INPUTS) {
        printf("Giriş kapısı sayısı maksimuma ulaştı!\n");
        return;
    }
    gate->input_gates[gate->number_of_inputs++] = input_gate;  // Adresi ekle
    printf("Bağlantı eklendi: %s --> %s\n", input_gate->name, gate->name);
}

// Kapı Değerlendirme
void evaluate_gate(Gate* gate) {
    if (gate->characteristic_function == NULL && gate->former_out >= 0 && gate->input_gates[0] != NULL) {
        gate->output = flipflop_function(&(gate->input_gates[0]->output), gate->former_out);
        gate->former_out = gate->output;
        return;
    }

    int inputs[MAX_INPUTS];
    for (int i = 0; i < gate->number_of_inputs; i++) {
        if (gate->input_gates[i] != NULL) {
            evaluate_gate(gate->input_gates[i]);  // Giriş kapılarını değerlendir
            inputs[i] = gate->input_gates[i]->output;  // Çıkış değerlerini al
        }
    }

    if (gate->characteristic_function != NULL) {
        gate->output = gate->characteristic_function(inputs, gate->number_of_inputs);  // Çıkışı hesapla
    }
    //printf("Kapı değerlendirildi: %s, Çıkış: %d\n", gate->name, gate->output);
}

int main() {
    FILE* circuit_file = fopen("circuit.txt", "r");  // Devre dosyasını aç
    FILE* input_file = fopen("input.txt", "r");     // Giriş dosyasını aç
    if (!circuit_file || !input_file) {
        printf("Dosya açma hatası!\n");
        return 1;
    }

    Gate* gates[100];         // Kapı adreslerini tutan dizi
    int gate_count = 0;       // Tanımlı kapı sayısı

    char type[MAX_NAME_LEN], name1[MAX_NAME_LEN], name2[MAX_NAME_LEN];

    while (fscanf(circuit_file, "%s %s %s", type, name1, name2) != EOF) {
        if (strcmp(type, "GATE") == 0) {
            gates[gate_count++] = create_gate(name1, name2);  // Yeni kapı oluştur
        } else if (strcmp(type, "CONNECTION") == 0) {
            Gate* from_gate = NULL;
            Gate* to_gate = NULL;
            for (int i = 0; i < gate_count; i++) {
                if (strcmp(gates[i]->name, name1) == 0) from_gate = gates[i];
                if (strcmp(gates[i]->name, name2) == 0) to_gate = gates[i];
            }
            if (from_gate && to_gate) {
                add_input_gate(to_gate, from_gate);  // Bağlantıyı kur
            }
        }
    }
    fclose(circuit_file);  // Dosyayı kapat

    char input_line[100];
    while (fscanf(input_file, "%s", input_line) != EOF) {
        int index = 0;
        for (int i = 0; i < gate_count; i++) {
            if (gates[i]->characteristic_function == NULL && gates[i]->former_out < 0) {
                gates[i]->output = input_line[index++] - '0';  // Giriş değerini ata
            }
        }

        for (int i = 0; i < gate_count; i++) {
            evaluate_gate(gates[i]);  // Çıkışı hesapla
        }

        for (int i = 0; i < gate_count; i++) {
            if (strcmp(gates[i]->name, "o") == 0) {
                printf("Sonuç: %d\n", gates[i]->output);  // Çıkışı yazdır
            }
        }
    }
    fclose(input_file);  // Giriş dosyasını kapat

    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);  // Belleği serbest bırak
    }
    return 0;
}

