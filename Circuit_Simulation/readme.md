Circuit Simulation Program

Overview

This program simulates a logical circuit consisting of gates such as AND, OR, NOT, and FLIPFLOP. It evaluates the output of the circuit based on given input values. The circuit structure and inputs are read from external files.

Features

Gate Structures: Each gate is defined with properties like type, name, input connections, and logic functions.

Supported Logic Gates: Implements AND, OR, NOT, and FLIPFLOP gates.

Dynamic Memory Management: Handles circuits of varying complexity by dynamically allocating and resizing memory.

Input and Output Handling: Reads circuit structure from circuit.txt and evaluates outputs for inputs provided in input.txt.

Modular Design: Logic functions and gate creation are modular for easy extension.

File Structure

1. circuit.txt

This file defines the circuit structure. Each line specifies either a gate definition or a connection:

Gate definition: GATE <gate_type> <gate_name>

<gate_type>: One of AND, OR, NOT, FLIPFLOP, INPUT, or OUTPUT.

<gate_name>: A unique name for the gate.

Connection: CONNECTION <from_gate_name> <to_gate_name>

Defines a connection from the output of <from_gate_name> to the input of <to_gate_name>.

2. input.txt

This file contains the input values for the circuit. Each line represents a set of input values (0 or 1) for gates defined as INPUT in circuit.txt.

Program Flow

Read Circuit Structure:

Parse circuit.txt to create gate objects and establish connections.

Read Inputs:

Read input.txt to assign values to gates of type INPUT.

Evaluate Circuit:

Traverse the circuit and evaluate outputs for gates of type OUTPUT.

Print Results:

Print the evaluated outputs for each input set.

Logic Functions

AND Gate: Outputs 1 if all inputs are 1, otherwise 0.

OR Gate: Outputs 1 if any input is 1, otherwise 0.

NOT Gate: Outputs the inverse of its single input.

FLIPFLOP Gate: Implements a flip-flop mechanism based on the input and the previous output.

How to Use

Step 1: Prepare Files

Create circuit.txt to define the circuit structure.

Create input.txt to define input values.

Step 2: Compile the Program

gcc -o circuit_simulator circuit_simulator.c

Step 3: Run the Program

./circuit_simulator

Step 4: View Outputs

The program prints the outputs corresponding to each line of inputs in input.txt.

Example

circuit.txt

GATE INPUT A
GATE INPUT B
GATE AND G1
GATE OUTPUT O1
CONNECTION A G1
CONNECTION B G1
CONNECTION G1 O1

input.txt

10
11
00

Output

0
1
0

Code Structure

1. Gate and Node Structures

Node: Represents a connection between gates.

Gate: Represents a logic gate with properties and logic functions.

2. Logic Functions

Implements the core logic for AND, OR, NOT, and FLIPFLOP gates.

3. Core Functions

create_gate: Creates and initializes a gate.

add_input_gate: Adds an input connection to a gate.

evaluate_gate: Evaluates the output of a gate recursively.

reset_gates: Resets the evaluation state of all gates.

4. Main Function

Handles file reading, circuit creation, input assignment, and output evaluation.

Memory Management

Dynamically allocates memory for gates and connections.

Frees allocated memory after program execution to prevent leaks.

Error Handling

Validates gate definitions and connections.

Ensures gates like AND and OR have at least two inputs.

Checks for missing or incorrect connections in OUTPUT gates.

Limitations

Maximum number of inputs per gate is defined by MAX_INPUTS.

Input and circuit files must strictly follow the expected format.
