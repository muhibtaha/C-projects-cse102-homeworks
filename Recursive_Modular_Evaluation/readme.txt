Recursive Modular Evaluation Program

This program implements a recursive system to calculate the result of modular mathematical expressions. Each module can have submodules or direct integer values, which are processed recursively. It is designed to handle hierarchical relationships between modules dynamically.

Features

Recursive Processing: Supports nested module definitions.

Dynamic Submodule Parsing: Identifies coefficients and submodule names dynamically.

Integer Detection: Recognizes direct integer inputs and processes them accordingly.

Error Handling: Handles invalid inputs gracefully, such as malformed expressions.

Input Structure

Main Module

The program starts by asking for a main module name.

The user is prompted to define the main module by entering an expression.

Module Expressions

Expressions consist of terms in the format: <coefficient>*<submodule> + <coefficient>*<submodule> + ...

Example: 3*A + 2*B + 10

Coefficients are optional (default is 1).

Submodules can themselves be defined recursively.

Special Cases

If a term contains only an integer, it is treated as a direct contribution to the result.

Submodules that are undefined are processed recursively.

Example Run

Input

Module name? Main
Define Main: 3*A + 5*B + 10
Define A: 2*X + 4
Define B: 1*X + 3
Define X: 7

Output

Final result for Main: 82

Explanation

Main = 3 * A + 5 * B + 10

A = 2 * X + 4

B = 1 * X + 3

X = 7

Calculate X: 7

Calculate A: 2 * 7 + 4 = 18

Calculate B: 1 * 7 + 3 = 10

Calculate Main: 3 * 18 + 5 * 10 + 10 = 82

File Structure

Code Components

built Struct: Stores the module name, submodule names, and temporary expressions.

isDigit Function: Checks if a character is a numeric digit.

stringToInt Function: Converts a numeric string to an integer.

my_function Function: Recursively calculates the result of a module.

Main Function: Initiates the program and outputs the final result.

Compilation and Execution

Compilation

Use any C compiler to compile the code. For example:

gcc recursive_module_eval.c -o recursive_module_eval

Execution

Run the executable and follow the prompts:

./recursive_module_eval

Limitations

The program assumes a valid input structure; malformed inputs may lead to undefined behavior.

Submodule names are case-sensitive and must not exceed 30 characters.

The maximum number of submodules per module is set to 100.

Future Improvements

Add validation for malformed expressions.

Improve error messages and debugging options.

Expand functionality to support floating-point coefficients.

Allow saving and loading module definitions from files.

License

This program is open-source and available under the MIT License.


