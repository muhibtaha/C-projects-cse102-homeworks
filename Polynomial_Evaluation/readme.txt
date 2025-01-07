# Polynomial Evaluation Program

## Overview
This program reads polynomial expressions from a file (`polynomials.txt`), evaluates them for specific `x` and `y` values provided in another file (`values.txt`), and outputs the results to a third file (`evaluations.txt`). It supports multi-variable polynomials with powers of `x` and `y`.

## Features
- **Polynomial Parsing**: Decomposes polynomials into individual terms and extracts coefficients and exponents.
- **Custom Power Function**: Implements an efficient exponentiation function.
- **ASCII-based Digit Validation**: Ensures accurate parsing of numeric characters.
- **Evaluation**: Computes the result of polynomials for given `x` and `y` values.
- **Output Formatting**: Results are written line-by-line, corresponding to the order of input polynomials.

## Input Files
1. **`polynomials.txt`**
   - Contains polynomial expressions, one per line.
   - Example:
     ```
     3x^2y + 2x - y^3
     -4x^2 + 5y^2 - 1
     ```
2. **`values.txt`**
   - Contains `x` and `y` value pairs, one pair per line.
   - Example:
     ```
     1.0 2.0
     -3.5 4.2
     ```

## Output File
- **`evaluations.txt`**
  - Each line corresponds to the evaluation of a polynomial for the `x, y` pairs in the input.
  - Example output:
    ```
    14.00 -2.50
    -25.00 30.25
    ```

## How It Works
1. **Initialization**: Opens input and output files, ensuring all are accessible.
2. **Polynomial Parsing**:
   - Splits polynomial strings into individual terms.
   - Extracts coefficients, and exponents of `x` and `y`.
3. **Evaluation**:
   - Reads `x` and `y` pairs from `values.txt`.
   - Computes the result of the polynomial for each pair.
4. **Output**: Writes the computed results for each polynomial and value pair to `evaluations.txt`.

## Constants
- `MAX_LINE_LENGTH`: Maximum length of a polynomial line.
- `MAX_TERMS`: Maximum number of terms in a single polynomial.

## Functions
### `double power(double base, int exp)`
- Calculates `base^exp` manually using iteration.

### `int digit_control(char a)`
- Checks if a character is a numeric digit.

### `void parse_term(char *term, int *coef, int *exp_x, int *exp_y)`
- Parses a single term, extracting its coefficient and the exponents of `x` and `y`.

### `double calculate_term(int coef, int exp_x, int exp_y, double x, double y)`
- Calculates the result of a single term for specific `x` and `y` values.

### `double evaluate_polynomial(int coefs[], int exp_x[], int exp_y[], int term_count, double x, double y)`
- Evaluates an entire polynomial for specific `x` and `y` values.

### `int split_polynomial(char *polynomial, char terms[MAX_TERMS][100])`
- Splits a polynomial string into individual terms.

## Error Handling
- Checks for the existence and readability of `polynomials.txt` and `values.txt`.
- Prints error messages if files cannot be opened.

## Usage
1. Prepare the input files:
   - `polynomials.txt` for polynomial expressions.
   - `values.txt` for `x` and `y` values.
2. Compile the program using a C compiler:
   ```
   gcc -o polynomial_evaluator polynomial_evaluator.c -lm
   ```
3. Run the program:
   ```
   ./polynomial_evaluator
   ```
4. Check `evaluations.txt` for results.

## Notes
- Ensure `polynomials.txt` and `values.txt` are in the same directory as the program.
- Each polynomial line in `polynomials.txt` should follow the format: `[coef]x^[exp]y^[exp]`.
- Each value line in `values.txt` should contain two numeric values separated by a space.

## Limitations
- Assumes well-formatted input files.
- Does not handle variables other than `x` and `y`.
- Large polynomials or high exponents may cause performance degradation.

## Example Configuration
Input Files:
- `polynomials.txt`:
  ```
  2x^3y + 3x - 4y^2
  x^2 - y^3 + 5
  ```
- `values.txt`:
  ```
  1.0 1.0
  2.0 -1.0
  ```
Output (`evaluations.txt`):
```
1.00 -2.00
4.00 8.00
```


