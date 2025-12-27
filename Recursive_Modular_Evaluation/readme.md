# Recursive Modular Evaluation Program

## Overview
This program implements a recursive system to calculate the result of modular mathematical expressions. Each module can have submodules or direct integer values, processed recursively. It handles hierarchical relationships between modules dynamically.

## Features
- **Recursive Processing:** Supports nested module definitions.  
- **Dynamic Submodule Parsing:** Identifies coefficients and submodule names dynamically.  
- **Integer Detection:** Recognizes direct integer inputs.  
- **Error Handling:** Handles invalid inputs gracefully.

## Input Structure
- **Main Module:** The program prompts for a main module name and its defining expression.  
- **Module Expressions:** Expressions are in the format `+ <coefficient><submodule> ... + <integer>`.  
  - Coefficients are optional (default is 1).  
  - Submodules can themselves be defined recursively.  
- **Special Cases:** Integer-only terms contribute directly; undefined submodules are processed recursively.

### Example Run
**Input:**
```
Module name? Main
Define Main: 3A + 5B + 10
Define A: 2X + 4
Define B: 1X + 3
Define X: 7
```

**Output:**
```
Final result for Main: 82
```
**Explanation:**
```
Main = 3 * A + 5 * B + 10
A = 2 * X + 4
B = 1 * X + 3
X = 7
Calculate X: 7
Calculate A: 2 * 7 + 4 = 18
Calculate B: 1 * 7 + 3 = 10
Calculate Main: 3 * 18 + 5 * 10 + 10 = 82
```

## Code Structure
- **Struct `built`:** Stores module name, submodule names, and temporary expressions.  
- **`isDigit` Function:** Checks if a character is numeric.  
- **`stringToInt` Function:** Converts a numeric string to integer.  
- **`my_function` Function:** Recursively calculates module results.  
- **Main Function:** Initiates the program and prints the final result.

## Compilation and Execution
### Compilation
```bash
gcc recursive_module_eval.c -o recursive_module_eval
```

### Execution
```bash
./recursive_module_eval
```
Follow the prompts to define modules and calculate the result.

## Limitations
- Assumes a valid input structure; malformed inputs may cause undefined behavior.  
- Submodule names are case-sensitive and must not exceed 30 characters.  
- Maximum 100 submodules per module.

## Future Improvements
- Add validation for malformed expressions.  
- Improve error messages and debugging options.  
- Support floating-point coefficients.  
- Allow saving and loading module definitions from files.

## License
This program is open-source under the MIT License.
