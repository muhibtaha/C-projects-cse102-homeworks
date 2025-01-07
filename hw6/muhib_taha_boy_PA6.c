#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_INPUTS 10 //macros
#define MAX_NAME_LEN 20

// node structure input gates
typedef struct Node {
    struct Gate* gate; // to the connected gate
    struct Node* next; // to the next node
} Node;

// gate structure
typedef struct Gate {
    char type[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    Node* input_gates; // linked list of input gates
    int num_inputs;
    int output;
    int former_out; // used for FLIPFLOP gates
    int evaluated; // 0 for false, 1 for true
    int (*logic_function)(int*, int, int*);
} Gate;

// logic functions
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

// add a connection from input to funcyion
void add_input_gate(Gate* gate, Gate* input_gate) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->gate = input_gate;
    new_node->next = gate->input_gates;
    gate->input_gates = new_node;
    gate->num_inputs++;
}

// functions to create and evaluate gates
Gate* create_gate(const char* type, const char* name) {
    Gate* gate = (Gate*)malloc(sizeof(Gate));
    strncpy(gate->type, type, MAX_NAME_LEN);
    strncpy(gate->name, name, MAX_NAME_LEN);
    gate->input_gates = NULL; // initialize linklist 
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

    if ((strcmp(gate->type, "AND") == 0 || strcmp(gate->type, "OR") == 0) && gate->num_inputs < 2) {
        printf("AND and OR have to have at least 2 input\n");
        exit(1);
    }

    if (strcmp(gate->type, "OUTPUT") == 0) {
        // directly evaluate the single input gate connected to this out
        if (gate->num_inputs == 1) {
            gate->output = evaluate_gate(gate->input_gates->gate);
        } else {
            printf ("OUTPUT gate %s has incorrect connections\n", gate->name);
        }
    } else {
        int inputs[MAX_INPUTS];
        int i = 0;
        Node* current = gate->input_gates;
        while (current != NULL) {
            inputs[i++] = evaluate_gate(current->gate);
            current = current->next;
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

    
    Gate** gates = (Gate**)malloc(10 * sizeof(Gate*)); // array of gate pointers
    int gate_count = 0;     // number of gates created
    int gate_capacity = 10; // current capacity

    char line[256];
    while (fgets(line, sizeof(line), circuit_file)) {
        char keyword[16], gate_type[16], gate_name[16];
        if (sscanf(line, "%s %s %s", keyword, gate_type, gate_name) == 3 && strcmp(keyword, "GATE") == 0) {
            // check if we need to expand the gates array
            if (gate_count >= gate_capacity) {
                gate_capacity *= 2; // double the capacity
                gates = (Gate**)realloc(gates, gate_capacity * sizeof(Gate*)); // resize the array
            }

            // create a new gate and addto the array
            gates[gate_count++] = create_gate(gate_type, gate_name);
        } else if (sscanf(line, "%s %s %s", keyword, gate_name, gate_type) == 3 && strcmp(keyword, "CONNECTION") == 0) {
            Gate* from_gate = NULL;
            Gate* to_gate = NULL;

            for (int i = 0; i < gate_count; i++) {
                if (strcmp(gates[i]->name, gate_name) == 0) from_gate = gates[i];
                if (strcmp(gates[i]->name, gate_type) == 0) to_gate = gates[i];
            }

            if (from_gate && to_gate) {
                add_input_gate(to_gate, from_gate);
            }
        }
    }

    fclose(circuit_file);

while (fgets(line, sizeof(line), input_file)) {
    reset_gates(gates, gate_count);

    // assign inputs
    for (int i = 0, input_index = 0; line[i] != '\n' && line[i] != '\0'; i++) {
        if (strcmp(gates[input_index]->type, "INPUT") == 0) {
            gates[input_index]->output = line[i] - '0';
            gates[input_index]->evaluated = 1;
            input_index++;
        }
    }

    // evaluate OUTPUT
    int output_count = 0; // count number outpust gates
    for (int i = 0; i < gate_count; i++) {
        if (strcmp(gates[i]->type, "OUTPUT") == 0) {
  
            printf("%d", evaluate_gate(gates[i]));
            output_count++;
        }
    }
    printf("\n"); 
}


    fclose(input_file);

    // free gates
    for (int i = 0; i < gate_count; i++) {
        // free linked list nodes for input gates
        Node* current = gates[i]->input_gates;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
        free(gates[i]);
    }
    free(gates); //gates array itself

    return 0;
}