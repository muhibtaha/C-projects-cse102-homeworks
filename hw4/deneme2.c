#include <stdio.h>
#include <string.h>

// Structure definition for modules
typedef struct {
    char main_module_name[31];       // Name of the main module (e.g., 'x', 'a')
    char sub_module_names[100][31];  // Names of submodules (e.g., 'a', 'b')
    char temp_string_array[1000];    // User input mathematical expression (e.g., '2*a+b+3')
} built;

// Helper function to check if a character is a digit
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

// Helper function to convert a string to an integer
int stringToInt(char *str) {
    int result = 0;
    while (*str) {
        if (isDigit(*str)) {
            result = result * 10 + (*str - '0');
        } else {
            return -1; // If not a valid integer, return -1
        }
        str++;
    }
    return result; // Return the integer value
}

// Recursive function to process a module and calculate its result
int my_function(built *module1) {
    char *ptr = module1->temp_string_array; // Pointer to the user input expression
    int result = 0; // Accumulated result for the current module

    // Prompt user to define the module's expression
    printf("Define %s: ", module1->main_module_name);
    getchar(); // Clear newline character
    scanf("%[^\n]", module1->temp_string_array); // Read the full input line

    // Loop through the input expression to parse and calculate
    while (*ptr != '\0') {
        while (*ptr == ' ') ptr++; // Skip whitespace

        int coef = 1; // Default coefficient is 1
        char submodule_name[31] = {0}; // Temporary buffer for submodule name

        // Parse coefficient if present
        if (isDigit(*ptr)) {
            coef = 0;
            while (isDigit(*ptr)) {
                coef = coef * 10 + (*ptr - '0');
                ptr++;
            }
        }
        if (*ptr == '*') ptr++; // Skip '*'

        while (*ptr == ' ') ptr++; // Skip whitespace before submodule name

        // Parse submodule name
        int len = 0;
        while (*ptr != '+' && *ptr != '\0' && *ptr != ' ') {
            if (len < 30) {
                submodule_name[len++] = *ptr;
            }
            ptr++;
        }
        submodule_name[len] = '\0'; // Null-terminate the submodule name

        while (*ptr == ' ') ptr++; // Skip whitespace after submodule name
        if (*ptr == '+') ptr++; // Skip '+'

        // If no submodule name is provided, treat coefficient as a direct integer result
        if (strlen(submodule_name) == 0) {
            result += coef;
            continue;
        }

        // Check if submodule name is a direct integer
        int potentialInt = stringToInt(submodule_name);
        if (potentialInt == -1) {
            // If not an integer, recursively process the submodule
            built submodule = {0};
            strcpy(submodule.main_module_name, submodule_name);
            int submodule_result = my_function(&submodule); // Recursive call
            result += coef * submodule_result; // Add submodule result to the total
        } else {
            // If it is an integer, add its value to the total
            result += coef * potentialInt;
        }
    }

    return result; // Return the calculated result for the module
}

int main(void) {
    built module1 = {0}; // Initialize the main module structure
    printf("Module name? ");
    scanf("%s", module1.main_module_name); // Read the name of the main module
    int final_result = my_function(&module1); // Calculate the result for the main module
    printf("Final result for %s: %d\n", module1.main_module_name, final_result); // Print the final result
    return 0;
}
