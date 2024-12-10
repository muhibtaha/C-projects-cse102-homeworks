#include <stdio.h>




int main() {
    Gate* input_gates[10];
    Gate* output_gates[10];
    Gate* other_gates[100];
    int num_inputs = 0, num_outputs = 0, num_others = 0;

    // Dosyaları aç
    FILE* circuit_file = fopen("circuit.txt", "r");
    FILE* input_file = fopen("input.txt", "r");
    
    // circuit.txt'yi işle
    process_circuit_file(circuit_file, input_gates, &num_inputs, 
                         output_gates, &num_outputs, other_gates, &num_others);
    fclose(circuit_file);

    // input.txt'yi işle ve simülasyonu gerçekleştir
    simulate_circuit(input_file, input_gates, num_inputs, output_gates, num_outputs);
    fclose(input_file);

    // Dinamik belleği temizle
    free_gates(input_gates, num_inputs);
    free_gates(output_gates, num_outputs);
    free_gates(other_gates, num_others);

    return 0;
}
