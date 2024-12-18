#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 10
#define MAX_NAME_LEN 20
#define MAX_GATES 100

// Mantık Kapısı Yapısı
typedef struct Gate {
    char name[MAX_NAME_LEN];                  // Kapının ismi
    struct Gate* input_gates[MAX_INPUTS];    // Giriş kapılarının adresleri
    int number_of_inputs;                    // Giriş sayısı
    int output;                              // Kapının çıkışı
    int former_out;                         // Flip-Flop için önceki çıkış
    int (*operation)(struct Gate* gate);    // Operasyon fonksiyonu
    struct Gate* next;                      // Bağlantı için sonraki kapı
} Gate;

// Mantık Kapısı Fonksiyonları
int and_operation(Gate* gate) {
    int result = 1;
    for (int i = 0; i < gate->number_of_inputs; i++) {
        result &= gate->input_gates[i]->output;
    }
    return result;
}

int or_operation(Gate* gate) {
    int result = 0;
    for (int i = 0; i < gate->number_of_inputs; i++) {
        result |= gate->input_gates[i]->output;
    }
    return result;
}

int not_operation(Gate* gate) {
    return !(gate->input_gates[0]->output);
}

int flipflop_operation(Gate* gate) {
    int input = gate->input_gates[0]->output;
    int output = (gate->former_out == 0 && input == 1) ? 1 : 0;
    gate->former_out = input;
    return output;
}

int input_operation(Gate* gate) {
    return gate->output;
}

// Kapıyı Oluştur ve Bağla
Gate* create_gate(const char* name, int (*operation)(Gate*)) {
    Gate* new_gate = (Gate*)malloc(sizeof(Gate));
    strcpy(new_gate->name, name);
    new_gate->number_of_inputs = 0;
    new_gate->operation = operation;
    new_gate->former_out = 0;
    new_gate->next = NULL;
    return new_gate;
}

void connect_gate(Gate* output_gate, Gate* input_gate) {
    input_gate->input_gates[input_gate->number_of_inputs++] = output_gate;
}

// Kapıyı Adına Göre Bul
Gate* find_gate_by_name(Gate* head, const char* name) {
    Gate* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Devreyi Yükle
Gate* load_circuit(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open circuit file");
        return NULL;
    }

    Gate* head = NULL;
    Gate* tail = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char type[MAX_NAME_LEN], name1[MAX_NAME_LEN], name2[MAX_NAME_LEN];
        if (sscanf(line, "%s %s %s", type, name1, name2) >= 2) {
            if (strcmp(type, "GATE") == 0) {
                int (*operation)(Gate*) = NULL;
                if (strcmp(name1, "AND") == 0) operation = and_operation;
                else if (strcmp(name1, "OR") == 0) operation = or_operation;
                else if (strcmp(name1, "NOT") == 0) operation = not_operation;
                else if (strcmp(name1, "FLIPFLOP") == 0) operation = flipflop_operation;
                else if (strcmp(name1, "INPUT") == 0) operation = input_operation;
                else if (strcmp(name1, "OUTPUT") == 0) operation = input_operation;

                if (operation) {
                    Gate* new_gate = create_gate(name2, operation);
                    if (!head) head = new_gate;
                    else tail->next = new_gate;
                    tail = new_gate;
                }
            } else if (strcmp(type, "CONNECTION") == 0) {
                Gate* output_gate = find_gate_by_name(head, name1);
                Gate* input_gate = find_gate_by_name(head, name2);
                if (output_gate && input_gate) {
                    connect_gate(output_gate, input_gate);
                }
            }
        }
    }

    fclose(file);
    return head;
}

// Devre Simülasyonu
void simulate_circuit(Gate* head, const char* inputs[], int num_inputs) {
    for (int i = 0; i < num_inputs; i++) {
        // Girişleri ayarla
        Gate* current = head;
        int index = 0;
        while (current) {
            if (current->operation == input_operation) {
                current->output = inputs[i][index++] - '0';
            }
            current = current->next;
        }

        // Kapıları çalıştır
        current = head;
        while (current) {
            if (current->operation != input_operation) {
                current->output = current->operation(current);
            }
            current = current->next;
        }

        // Çıkışı yazdır
        Gate* output_gate = find_gate_by_name(head, "o");
        if (output_gate) {
            printf("Output %d: %d\n", i + 1, output_gate->output);
        }
    }
}

int main() {
    // Devreyi yükle
    Gate* circuit = load_circuit("circuit.txt");
    if (!circuit) {
        return 1;
    }

    // Girişleri tanımla
    const char* inputs[] = {"1101", "1010", "1110"};
    int num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    // Simüle et
    simulate_circuit(circuit, inputs, num_inputs);

    // Hafızayı temizle
    Gate* current = circuit;
    while (current) {
        Gate* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
