#include <stdio.h>    // Giriş/çıkış işlemleri için.
#include <stdlib.h>   // Bellek tahsisi ve diğer yardımcı fonksiyonlar için.
#include <string.h>   // Karakter dizisi işlemleri için.

#define MAX_INPUTS 10    // Bir kapının maksimum giriş sayısını tanımlar.
#define MAX_NAME_LEN 20  // Kapı ve tip isimlerinin maksimum uzunluğunu tanımlar.

// Gate (Kapı) yapısını tanımlıyoruz.
typedef struct Gate {
    char type[MAX_NAME_LEN]; // Kapının türü (ör. INPUT, OUTPUT, AND).
    char name[MAX_NAME_LEN]; // Kapının adı.
    struct Gate* input_gates[MAX_INPUTS]; // Giriş kapıları için işaretçiler.
    int num_inputs;         // Giriş kapılarının sayısı.
    int output;             // Kapının çıktısı.
    int former_out;         // FLIPFLOP kapıları için önceki durum.
    int evaluated;          // Kapının değerlendirilip değerlendirilmediği (0: false, 1: true).
    int (*logic_function)(int*, int, int*); // Mantık fonksiyonu işaretçisi.
} Gate;

// Mantık fonksiyonları:
int and_function(int* inputs, int n, int* former_out) {
    // AND kapısı: tüm girişler 1 ise 1 döndürür.
    for (int i = 0; i < n; i++) {
        if (!inputs[i]) return 0;
    }
    return 1;
}

int or_function(int* inputs, int n, int* former_out) {
    // OR kapısı: herhangi bir giriş 1 ise 1 döndürür.
    for (int i = 0; i < n; i++) {
        if (inputs[i]) return 1;
    }
    return 0;
}

int not_function(int* inputs, int n, int* former_out) {
    // NOT kapısı: girişin tersini döndürür.
    return !inputs[0];
}

int flipflop_function(int* inputs, int n, int* former_out) {
    // FLIPFLOP kapısı: giriş XOR önceki durum.
    int result = inputs[0] ^ (*former_out);
    *former_out = inputs[0]; // Önceki durumu güncelle.
    return result;
}

// Yeni bir kapı oluşturma fonksiyonu.
Gate* create_gate(const char* type, const char* name) {
    Gate* gate = (Gate*)malloc(sizeof(Gate)); // Kapı için dinamik bellek tahsisi.
    strncpy(gate->type, type, MAX_NAME_LEN); // Kapı tipini ayarla.
    strncpy(gate->name, name, MAX_NAME_LEN); // Kapı adını ayarla.
    gate->num_inputs = 0;      // Başlangıçta giriş yok.
    gate->output = 0;          // Çıktı başlangıçta 0.
    gate->former_out = 0;      // FLIPFLOP için önceki durum başlangıçta 0.
    gate->evaluated = 0;       // Kapı başlangıçta değerlendirilmemiş.

    // Mantık fonksiyonunu türüne göre bağla.
    if (strcmp(type, "AND") == 0) gate->logic_function = and_function;
    else if (strcmp(type, "OR") == 0) gate->logic_function = or_function;
    else if (strcmp(type, "NOT") == 0) gate->logic_function = not_function;
    else if (strcmp(type, "FLIPFLOP") == 0) gate->logic_function = flipflop_function;
    else gate->logic_function = NULL; // Geçersiz tür için NULL.

    return gate; // Oluşturulan kapıyı döndür.
}

// Kapının değerini hesaplama fonksiyonu.
int evaluate_gate(Gate* gate) {
    if (gate->evaluated) return gate->output; // Kapı zaten değerlendirildiyse çıktıyı döndür.

    if (strcmp(gate->type, "OUTPUT") == 0) {
        // Çıktı kapısı, sadece bağlı olduğu tek bir kapıyı değerlendirir.
        if (gate->num_inputs == 1) {
            gate->output = evaluate_gate(gate->input_gates[0]);
        } else {
            fprintf(stderr, "Error: OUTPUT gate %s has incorrect connections\n", gate->name);
        }
    } else {
        // Diğer kapılar için girişleri değerlendir.
        int inputs[MAX_INPUTS];
        for (int i = 0; i < gate->num_inputs; i++) {
            inputs[i] = evaluate_gate(gate->input_gates[i]);
        }

        // Mantık fonksiyonunu çağırarak çıktıyı hesapla.
        if (gate->logic_function) {
            gate->output = gate->logic_function(inputs, gate->num_inputs, &gate->former_out);
        }
    }

    gate->evaluated = 1; // Kapı değerlendirildi olarak işaretle.
    return gate->output; // Çıktıyı döndür.
}

// Tüm kapıları sıfırla (yeniden değerlendirme için).
void reset_gates(Gate** gates, int num_gates) {
    for (int i = 0; i < num_gates; i++) {
        gates[i]->evaluated = 0;
    }
}

// Ana fonksiyon: Dosyaları okur, kapıları oluşturur ve simülasyonu çalıştırır.
int main() {
    FILE* circuit_file = fopen("circuit.txt", "r"); // circuit.txt dosyasını aç.
    FILE* input_file = fopen("input.txt", "r");    // input.txt dosyasını aç.

    if (!circuit_file || !input_file) {
        fprintf(stderr, "Error: Unable to open files.\n");
        return 1;
    }

    Gate* gates[100]; // Tüm kapıları tutacak bir dizi.
    int gate_count = 0; // Kapı sayacı.

    char line[256];
    // circuit.txt dosyasını satır satır oku.
    while (fgets(line, sizeof(line), circuit_file)) {
        char keyword[16], gate_type[16], gate_name[16];
        if (sscanf(line, "%s %s %s", keyword, gate_type, gate_name) == 3 && strcmp(keyword, "GATE") == 0) {
            // Yeni bir kapı oluştur ve diziye ekle.
            gates[gate_count++] = create_gate(gate_type, gate_name);
        } else if (sscanf(line, "%s %s %s", keyword, gate_name, gate_type) == 3 && strcmp(keyword, "CONNECTION") == 0) {
            // Bağlantı ekle.
            Gate* from_gate = NULL;
            Gate* to_gate = NULL;

            for (int i = 0; i < gate_count; i++) {
                if (strcmp(gates[i]->name, gate_name) == 0) from_gate = gates[i];
                if (strcmp(gates[i]->name, gate_type) == 0) to_gate = gates[i];
            }

            if (from_gate && to_gate) {
                to_gate->input_gates[to_gate->num_inputs++] = from_gate;
            }
        }
    }

    fclose(circuit_file); // circuit.txt dosyasını kapat.

    // input.txt dosyasındaki her giriş satırını işle.
    while (fgets(line, sizeof(line), input_file)) {
        reset_gates(gates, gate_count); // Kapıları sıfırla.

        // INPUT kapılarına değer atama.
        for (int i = 0, input_index = 0; line[i] != '\n' && line[i] != '\0'; i++) {
            if (strcmp(gates[input_index]->type, "INPUT") == 0) {
                gates[input_index]->output = line[i] - '0'; // INPUT değerini ata.
                gates[input_index]->evaluated = 1;
                input_index++;
            }
        }

        // OUTPUT kapılarını değerlendir ve çıktıyı yazdır.
        for (int i = 0; i < gate_count; i++) {
            if (strcmp(gates[i]->type, "OUTPUT") == 0) {
                printf("%d\n", evaluate_gate(gates[i]));
            }
        }
    }

    fclose(input_file); // input.txt dosyasını kapat.

    // Bellek temizliği (tüm kapıları serbest bırak).
    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);
    }

    return 0; // Program sonlanır.
}
