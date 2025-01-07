#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


#define MAX_INPUTS 10 //macros
#define MAX_NAME_LEN 20


// Gate structure
typedef struct Gate {
    char type[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    struct Gate* input_gates[MAX_INPUTS];
    int num_inputs;
    int output;
    int former_out; // used for FLIPFLOP gates
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
        result = 0; // XOR , if they are same result 0
    } else if (inputs[0] != *former_out){
        result = 1; 
    }
    *former_out = inputs[0]; //update last one
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
    
    //add logical function if ther are funciton gate
    if (strcmp(type, "AND") == 0) gate->logic_function = and_function; 
    else if (strcmp(type, "OR") == 0) gate->logic_function = or_function;
    else if (strcmp(type, "NOT") == 0) gate->logic_function = not_function;
    else if (strcmp(type, "FLIPFLOP") == 0) gate->logic_function = flipflop_function;
    else gate->logic_function = NULL; //what if it is not function gate
    return gate;
}

int evaluate_gate(Gate* gate) {

    //if a gate is input gate, cause of it is evaluated (1) it return output
    if (gate->evaluated) return gate->output;

    if (strcmp(gate->type, "AND")|| strcmp(gate->type, "OR")){
        if (gate->num_inputs < 2) {printf("AND and OR have to have at least 2 input\n");
        exit(1);
        }

    }

    if (strcmp(gate->type, "OUTPUT") == 0) {
        // directly evaluate the single input gate connected to this out
        if (gate->num_inputs == 1) {
            gate->output = evaluate_gate(gate->input_gates[0]);
        } else {
            printf ("OUTPUT gate %s has incorrect connections\n", gate->name);
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
        printf("Unable to open files.\n");
        return 1;
    }

    // Dynamic memory allocation for gates
    Gate** gates = (Gate**)malloc(10 * sizeof(Gate*)); // Array of gate pointers
    int gate_count = 0;     // Number of gates created
    int gate_capacity = 10; // Current capacity of the gates array

    char line[256];
    while (fgets(line, sizeof(line), circuit_file)) {
        char keyword[16], gate_type[16], gate_name[16];
        if (sscanf(line, "%s %s %s", keyword, gate_type, gate_name) == 3 && strcmp(keyword, "GATE") == 0) {
            // Check if we need to expand the gates array
            if (gate_count >= gate_capacity) {
                gate_capacity *= 2; // Double the capacity
                gates = (Gate**)realloc(gates, gate_capacity * sizeof(Gate*)); // Resize the array
            }

            // Create a new gate and add it to the array
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
                    printf("Maximum inputs exceeded for gate %s.\n", to_gate->name);
                    exit(1);
                }
                to_gate->input_gates[to_gate->num_inputs] = from_gate;
                to_gate->num_inputs++;
            }
        }
    }

    fclose(circuit_file);

while (fgets(line, sizeof(line), input_file)) {
    reset_gates(gates, gate_count);

    // Assign inputs
    for (int i = 0, input_index = 0; line[i] != '\n' && line[i] != '\0'; i++) {
        if (strcmp(gates[input_index]->type, "INPUT") == 0) {
            gates[input_index]->output = line[i] - '0';
            gates[input_index]->evaluated = 1;
            input_index++;
        }
    }

    // Evaluate OUTPUT gates and print results
    int output_count = 0; // Track number of OUTPUT gates
    for (int i = 0; i < gate_count; i++) {
        if (strcmp(gates[i]->type, "OUTPUT") == 0) {
            if (output_count > 0) {
                printf(" "); // Separate multiple outputs with space
            }
            printf("%d", evaluate_gate(gates[i]));
            output_count++;
        }
    }
    printf("\n"); // Newline after printing all OUTPUT gates for the current input
}


    fclose(input_file);

    // Free all dynamically allocated gates
    for (int i = 0; i < gate_count; i++) {
        free(gates[i]);
    }
    free(gates); // Free the gates array itself

    return 0;
}