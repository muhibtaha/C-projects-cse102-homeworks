#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 10
#define MAX_NAME_LEN 20

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
    int result = (inputs[0] == *former_out) ? 0 : 1;
    printf("[DEBUG] FLIPFLOP Gate: Former Out: %d, Input: %d, Result: %d\n", *former_out, inputs[0], result);
    *former_out = inputs[0];
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

    printf("[DEBUG] Created Gate: %s, Type: %s\n", gate->name, gate->type);
    return gate;
}

int evaluate_gate(Gate* gate) {
    if (gate->evaluated) return gate->output;

    printf("[DEBUG] Evaluating Gate: %s, Type: %s\n", gate->name, gate->type);

    if (strcmp(gate->type, "OUTPUT") == 0) {
        if (gate->num_inputs == 1) {
            gate->output = evaluate_gate(gate->input_gates[0]);
        } else {
            printf("[ERROR] OUTPUT gate %s has incorrect connections\n", gate->name);
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

    printf("[DEBUG] Gate %s Output: %d\n", gate->name, gate->output);
    gate->evaluated = 1;
    return gate->output;
}

void reset_gates(Gate** gates, int num_gates) {
    for (int i = 0; i < num_gates; i++) {
        printf("[DEBUG] Resetting Gate: %s, Former Out: %d\n", gates[i]->name, gates[i]->former_out);
        gates[i]->evaluated = 0;
    }
}

int main() {
    FILE* circuit_file = fopen("circuit.txt", "r");
    FILE* input_file = fopen("input.txt", "r");

    if (!circuit_file || !input_file) {
        printf("Unable to open files.\n");
        return 1;
    }

    Gate** gates = (Gate**)malloc(10 * sizeof(Gate*));
    int gate_count = 0;
    int gate_capacity = 10;

    char line[256];
    while (fgets(line, sizeof(line), circuit_file)) {
        char keyword[16], gate_type[16], gate_name[16];
        if (sscanf(line, "%s %s %s", keyword, gate_type, gate_name) == 3 && strcmp(keyword, "GATE") == 0) {
            if (gate_count >= gate_capacity) {
                gate_capacity *= 2;
                gates = (Gate**)realloc(gates, gate_capacity * sizeof(Gate*));
            }
            gates[gate_count++] = create_gate(gate_type, gate_name);
        } else if (sscanf(line, "%s %s %s", keyword, gate_name, gate_type) == 3 && strcmp(keyword, "CONNECTION") == 0) {
            Gate* from_gate = NULL;
            Gate* to_gate = NULL;

            for (int i = 0; i < gate_count; i++) {
                if (strcmp(gates[i]->name, gate_name) == 0) from_gate = gates[i];
                if (strcmp(gates[i]->name, gate_type) == 0) to_gate = gates[i];
            }

            if (from_gate && to_gate) {
                if (to_gate->num_inputs >= MAX_INPUTS) {
                    printf("[ERROR] Maximum inputs exceeded for gate %s.\n", to_gate->name);
                    exit(1);
                }
                to_gate->input_gates[to_gate->num_inputs++] = from_gate;
                printf("[DEBUG] Connected %s -> %s\n", from_gate->name, to_gate->name);
            } else {
                printf("[ERROR] Invalid connection from %s to %s\n", gate_name, gate_type);
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
                printf("[DEBUG] Assigned Input %d to Gate %s\n", gates[input_index]->output, gates[input_index]->name);
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
    free(gates);

    return 0;
}
