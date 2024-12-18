#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 10
#define MAX_NAME_LEN 20

typedef struct Gate {
    char name[MAX_NAME_LEN];
    struct Gate* inputs[MAX_INPUTS];
    int input_count;
    int output;
    int previous_output;
    int evaluated;
    int (*operation)(int*, int);
} Gate;

int and_op(int* values, int n) {
    for (int i = 0; i < n; i++) {
        if (!values[i]) return 0;
    }
    return 1;
}

int or_op(int* values, int n) {
    for (int i = 0; i < n; i++) {
        if (values[i]) return 1;
    }
    return 0;
}

int not_op(int* values, int n) {
    return !values[0];
}

int flipflop_op(int* values, int prev_output) {
    return values[0] ? !prev_output : prev_output;
}

Gate* create_gate(const char* type, const char* name) {
    Gate* gate = (Gate*)malloc(sizeof(Gate));
    if (!gate) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strncpy(gate->name, name, MAX_NAME_LEN);
    gate->input_count = 0;
    gate->output = 0;
    gate->previous_output = 0;
    gate->evaluated = 0;

    if (strcmp(type, "AND") == 0) {
        gate->operation = and_op;
    } else if (strcmp(type, "OR") == 0) {
        gate->operation = or_op;
    } else if (strcmp(type, "NOT") == 0) {
        gate->operation = not_op;
    } else if (strcmp(type, "FLIPFLOP") == 0) {
        gate->operation = NULL;
    } else {
        gate->operation = NULL;
    }
    return gate;
}

void add_connection(Gate* to, Gate* from) {
    if (to->input_count < MAX_INPUTS) {
        to->inputs[to->input_count++] = from;
    } else {
        printf("Maximum input limit reached!\n");
    }
}

void evaluate(Gate* gate) {
    if (gate->evaluated) return;

    int values[MAX_INPUTS];
    for (int i = 0; i < gate->input_count; i++) {
        evaluate(gate->inputs[i]);
        values[i] = gate->inputs[i]->output;
    }

    if (gate->operation) {
        gate->output = gate->operation(values, gate->input_count);
    } else {
        gate->output = flipflop_op(values, gate->previous_output);
        gate->previous_output = gate->output;
    }
    gate->evaluated = 1;
}

void reset_gates(Gate** gates, int count) {
    for (int i = 0; i < count; i++) {
        gates[i]->evaluated = 0;
    }
}

Gate* find_gate(Gate** gates, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(gates[i]->name, name) == 0) return gates[i];
    }
    return NULL;
}

int main() {
    FILE* circuit = fopen("circuit.txt", "r");
    FILE* inputs = fopen("input.txt", "r");
    if (!circuit || !inputs) {
        printf("File opening error!\n");
        return 1;
    }

    Gate* gates[100];
    int gate_count = 0;

    char type[MAX_NAME_LEN], gate1[MAX_NAME_LEN], gate2[MAX_NAME_LEN];

    while (fscanf(circuit, "%s %s %s", type, gate1, gate2) != EOF) {
        if (strcmp(type, "GATE") == 0) {
            gates[gate_count++] = create_gate(gate1, gate2);
        } else if (strcmp(type, "CONNECTION") == 0) {
            Gate* from = find_gate(gates, gate_count, gate1);
            Gate* to = find_gate(gates, gate_count, gate2);
            if (from && to) add_connection(to, from);
        }
    }
    fclose(circuit);

    char input_line[100];
    while (fscanf(inputs, "%s", input_line) != EOF) {
        reset_gates(gates, gate_count);
        int index = 0;
        for (int i = 0; i < gate_count; i++) {
            if (!gates[i]->operation) {
                gates[i]->output = input_line[index++] - '0';
            }
        }

        for (int i = 0; i < gate_count; i++) {
            evaluate(gates[i]);
        }

        for (int i = 0; i < gate_count; i++) {
            if (strcmp(gates[i]->name, "OUTPUT") == 0) {
                printf("%d", gates[i]->output);
            }
        }
        printf("\n");
    }
    fclose(inputs);

    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);
    }
    return 0;
}

