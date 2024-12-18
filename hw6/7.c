#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_INPUTS 10
#define MAX_NAME_LEN 20

// Gate types enumeration


// Gate structure
typedef struct Gate {
    char type[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    struct Gate* input_gates[MAX_INPUTS];
    int num_inputs;
    int output;
    int former_out; // Used for FLIPFLOP gates
    int evaluated; // 0 for false, 1 for true
    int (*logic_function)(int*, int, int*);
} Gate;

// Logic functions
int and_function(int* inputs, int n, int* former_out) {
    for (int i = 0; i < n; i++) {
        if (!inputs[i]) return 0;
    }
    return 1;
}

int or_function(int* inputs, int n, int* former_out) {
    for (int i = 0; i < n; i++) {
        if (inputs[i]) return 1;
    }
    return 0;
}

int not_function(int* inputs, int n, int* former_out) {
    return !inputs[0];
}

int flipflop_function(int* inputs, int n, int* former_out) {
    int result;
    if (inputs[0] == *former_out) {
        result = 0; // XOR işlemi: aynıysa sonuç 0
    } else {
        result = 1; // XOR işlemi: farklıysa sonuç 1
    }
    *former_out = inputs[0]; // Önceki durumu güncelle.
    return result;
}

// Functions to create and evaluate gates
Gate* create_gate(const char* type, const char* name) {
    Gate* gate = (Gate*)malloc(sizeof(Gate));
    strncpy(gate->type, type, MAX_NAME_LEN);
    strncpy(gate->name, name, MAX_NAME_LEN);
    gate->num_inputs = 0;
    gate->output = 0;
    gate->former_out = 0;
    gate->evaluated = 0;
    
    if (strcmp(type, "AND") == 0) gate->logic_function = and_function;
    else if (strcmp(type, "OR") == 0) gate->logic_function = or_function;
    else if (strcmp(type, "NOT") == 0) gate->logic_function = not_function;
    else if (strcmp(type, "FLIPFLOP") == 0) gate->logic_function = flipflop_function;
    else gate->logic_function = NULL;
    return gate;
}

int evaluate_gate(Gate* gate) {
    if (gate->evaluated) return gate->output;

    if (strcmp(gate->type, "OUTPUT") == 0) {
        // Directly evaluate the single input gate connected to this OUTPUT
        if (gate->num_inputs == 1) {
            gate->output = evaluate_gate(gate->input_gates[0]);
        } else {
            printf ("[ERROR]:  OUTPUT gate %s has incorrect connections\n", gate->name);
        }
    } else {
        int inputs[MAX_INPUTS];
        for (int i = 0; i < gate->num_inputs; i++) {
            inputs[i] = evaluate_gate(gate->input_gates[i]);
        }

        if (gate->logic_function) {
            gate->output = gate->logic_function(inputs, gate->num_inputs, &gate->former_out);
        }
    }

    gate->evaluated = 1;
    return gate->output;
}

void reset_gates(Gate** gates, int num_gates) {
    for (int i = 0; i < num_gates; i++) {
        gates[i]->evaluated = 0;
    }
}

int main() {
    FILE* circuit_file = fopen("circuit.txt", "r");
    FILE* input_file = fopen("input.txt", "r");

    if (!circuit_file || !input_file) {
        fprintf(stderr, "Error: Unable to open files.\n");
        return 1;
    }

    Gate* gates[100];
    int gate_count = 0;

    char line[256];
    while (fgets(line, sizeof(line), circuit_file)) {
        char keyword[16], gate_type[16], gate_name[16];
        if (sscanf(line, "%s %s %s", keyword, gate_type, gate_name) == 3 && strcmp(keyword, "GATE") == 0) {
            
            

            gates[gate_count++] = create_gate(gate_type, gate_name);
        } else if (sscanf(line, "%s %s %s", keyword, gate_name, gate_type) == 3 && strcmp(keyword, "CONNECTION") == 0) {
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

    fclose(circuit_file);

    while (fgets(line, sizeof(line), input_file)) {
        reset_gates(gates, gate_count);

        for (int i = 0, input_index = 0; line[i] != '\n' && line[i] != '\0'; i++) {
            if (strcmp(gates[input_index]->type, "INPUT") == 0) {
                gates[input_index]->output = line[i] - '0';
                gates[input_index]->evaluated = 1;
                input_index++;
            }
        }

        for (int i = 0; i < gate_count; i++) {
            if (strcmp(gates[i]->type, "OUTPUT") == 0) {
                printf("%d\n", evaluate_gate(gates[i]));
            }
        }
    }

    fclose(input_file);

    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);
    }

    return 0;
}
