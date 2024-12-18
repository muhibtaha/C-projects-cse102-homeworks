#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_INPUTS 10
#define MAX_NAME_LEN 20

// Enum for gate types
typedef enum {
    INPUT, OUTPUT, AND, OR, NOT, FLIPFLOP
} GateType;

// Struct for a gate
typedef struct Gate {
    GateType type;
    char name[MAX_NAME_LEN];
    struct Gate *input_gates[MAX_INPUTS]; // Array of pointers to input gates
    int number_of_inputs;
    int output; // Current output
    int former_out; // For FLIPFLOP
    short evaluated; // Flag to prevent re-evaluation in a simulation
    int (*characteristic_function)(int *, int); // Logic function pointer
} Gate;

// Function prototypes
Gate *create_gate(GateType type, const char *name);
void create_connection(Gate *from_gate, Gate *to_gate);
int evaluate_gate(Gate *gate);
int and_function(int *inputs, int n);
int or_function(int *inputs, int n);
int not_function(int *inputs, int n);
int flipflop_function(int *inputs, int n, int *former_out);
void reset_gates(Gate **gates, int count);
Gate *find_gate(Gate **gates, int count, const char *name);

// Gate characteristic functions
int and_function(int *inputs, int n) {
    printf("AND function called with %d inputs\n", n);
    for (int i = 0; i < n; i++) {
        if (!inputs[i]) return 0;
    }
    return 1;
}

int or_function(int *inputs, int n) {
    printf("OR function called with %d inputs\n", n);
    for (int i = 0; i < n; i++) {
        if (inputs[i]) return 1;
    }
    return 0;
}

int not_function(int *inputs, int n) {
    printf("NOT function called\n");
    return !inputs[0];
}

int flipflop_function(int *inputs, int n, int *former_out) {
    printf("FLIPFLOP function called with input: %d and former_out: %d\n", inputs[0], *former_out);
    int result = inputs[0] ^ *former_out; // Exclusive OR for FLIPFLOP
    *former_out = inputs[0];
    return result;
}

// Create a gate
Gate *create_gate(GateType type, const char *name) {
    printf("Creating gate: %s of type %d\n", name, type);
    Gate *gate = (Gate *)malloc(sizeof(Gate));
    if (!gate) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    gate->type = type;
    strncpy(gate->name, name, MAX_NAME_LEN);
    gate->name[MAX_NAME_LEN - 1] = '\0';
    gate->number_of_inputs = 0;
    gate->evaluated = 0;
    gate->former_out = 0;
    gate->output = 0;

    // Assign the characteristic function based on gate type
    switch (type) {
        case AND:
            gate->characteristic_function = and_function;
            break;
        case OR:
            gate->characteristic_function = or_function;
            break;
        case NOT:
            gate->characteristic_function = not_function;
            break;
        case FLIPFLOP:
            gate->characteristic_function = NULL; // Custom handling for FLIPFLOP
            break;
        default:
            gate->characteristic_function = NULL;
    }

    return gate;
}

// Create a connection between two gates
void create_connection(Gate *from_gate, Gate *to_gate) {
    printf("Creating connection from gate %s to gate %s\n", from_gate->name, to_gate->name);
    if (to_gate->number_of_inputs >= MAX_INPUTS) {
        fprintf(stderr, "Maximum number of inputs exceeded for gate %s\n", to_gate->name);
        exit(EXIT_FAILURE);
    }
    to_gate->input_gates[to_gate->number_of_inputs++] = from_gate;
}

// Evaluate a gate
int evaluate_gate(Gate *gate) {
    printf("Evaluating gate: %s\n", gate->name);
    if (gate->evaluated) {
        printf("Gate %s already evaluated with output: %d\n", gate->name, gate->output);
        return gate->output;
    }

    int input_values[MAX_INPUTS];
    for (int i = 0; i < gate->number_of_inputs; i++) {
        input_values[i] = evaluate_gate(gate->input_gates[i]);
    }

    if (gate->type == FLIPFLOP) {
        gate->output = flipflop_function(input_values, gate->number_of_inputs, &gate->former_out);
    } else if (gate->characteristic_function) {
        gate->output = gate->characteristic_function(input_values, gate->number_of_inputs);
    }

    gate->evaluated = 1;
    printf("Gate %s evaluated with output: %d\n", gate->name, gate->output);
    return gate->output;
}

// Reset gates before a new simulation
void reset_gates(Gate **gates, int count) {
    printf("Resetting gates\n");
    for (int i = 0; i < count; i++) {
        printf("Resetting gate: %s\n", gates[i]->name);
        gates[i]->evaluated = 0;
    }
}

// Find a gate by name
Gate *find_gate(Gate **gates, int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(gates[i]->name, name) == 0) {
            return gates[i];
        }
    }
    return NULL;
}

int main() {
    printf("Starting simulation\n");

    Gate *gates[100];
    int gate_count = 0;

    FILE *circuit_file = fopen("circuit.txt", "r");
    if (!circuit_file) {
        fprintf(stderr, "Failed to open circuit.txt\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), circuit_file)) {
        char command[20], type_or_from[20], name_or_to[20];
        sscanf(line, "%s %s %s", command, type_or_from, name_or_to);

        if (strcmp(command, "GATE") == 0) {
            GateType type;
            if (strcmp(type_or_from, "INPUT") == 0) type = INPUT;
            else if (strcmp(type_or_from, "OUTPUT") == 0) type = OUTPUT;
            else if (strcmp(type_or_from, "AND") == 0) type = AND;
            else if (strcmp(type_or_from, "OR") == 0) type = OR;
            else if (strcmp(type_or_from, "NOT") == 0) type = NOT;
            else if (strcmp(type_or_from, "FLIPFLOP") == 0) type = FLIPFLOP;
            else continue;

            gates[gate_count++] = create_gate(type, name_or_to);
        } else if (strcmp(command, "CONNECTION") == 0) {
            Gate *from_gate = find_gate(gates, gate_count, type_or_from);
            Gate *to_gate = find_gate(gates, gate_count, name_or_to);
            if (from_gate && to_gate) {
                create_connection(from_gate, to_gate);
            }
        }
    }
    fclose(circuit_file);

    FILE *input_file = fopen("input.txt", "r");
    if (!input_file) {
        fprintf(stderr, "Failed to open input.txt\n");
        return 1;
    }

    while (fgets(line, sizeof(line), input_file)) {
        reset_gates(gates, gate_count);

        // Assign inputs
        int input_index = 0;
        for (int i = 0; i < gate_count; i++) {
            if (gates[i]->type == INPUT) {
                gates[i]->output = line[input_index++] - '0';
            }
        }

        // Evaluate outputs
        for (int i = 0; i < gate_count; i++) {
            if (gates[i]->type == OUTPUT) {
                printf("%d", evaluate_gate(gates[i]));
            }
        }
        printf("\n");
    }
    fclose(input_file);

    // Free memory
    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);
    }

    return 0;
}
