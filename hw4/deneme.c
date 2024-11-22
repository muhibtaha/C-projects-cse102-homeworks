#include <stdio.h>
#include <string.h>

// Structure definition
typedef struct {
    char main_module_name[31];
    int coef_submodules[100];
    char sub_module_names[100][31];
    int integers[100];
    char temp_string_array[1000];
} built;

// Helper functions
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int stringToInt(char *str) {
    int result = 0;
    while (*str) {
        if (isDigit(*str)) {
            result = result * 10 + (*str - '0');
        } else {
            return -1;
        }
        str++;
    }
    return result;
}

// Calculation function
int calculate(built module1, int submodule_count) {
    int result = 0;
    for (int i = 0; i < submodule_count; i++) {
        result += module1.coef_submodules[i] * module1.integers[i];
    }
    return result;
}

// Recursive processing function
built my_function(built module1) {
    char *ptr = module1.temp_string_array;
    int submodule_count = 0;

    printf("Define %s: ", module1.main_module_name);
    getchar(); // Clear newline character
    scanf("%[^\n]", module1.temp_string_array);

    while (*ptr != '\0') {
        // Default coefficient to 1
        module1.coef_submodules[submodule_count] = 1;
        if (isDigit(*ptr)) {
            module1.coef_submodules[submodule_count] = 0;
            while (isDigit(*ptr)) {
                module1.coef_submodules[submodule_count] = 
                    module1.coef_submodules[submodule_count] * 10 + (*ptr - '0');
                ptr++;
            }
        }
        if (*ptr == '*') ptr++;

        // Extract submodule name
        int len = 0;
        while (*ptr != '+' && *ptr != '\0') {
            module1.sub_module_names[submodule_count][len++] = *ptr;
            ptr++;
        }
        module1.sub_module_names[submodule_count][len] = '\0';
        if (*ptr == '+') ptr++;

        // Process submodule
        int potentialInt = stringToInt(module1.sub_module_names[submodule_count]);
        if (potentialInt == -1) {
            // Submodule is not an integer
            built submodule;
            strcpy(submodule.main_module_name, module1.sub_module_names[submodule_count]);
            submodule = my_function(submodule);
            module1.integers[submodule_count] = submodule.integers[0];
        } else {
            // Submodule is an integer
            module1.integers[submodule_count] = potentialInt;
        }
        submodule_count++;
    }

    // Calculate final result for the main module
    module1.integers[0] = calculate(module1, submodule_count);
    return module1;
}

int main(void) {
    built module1 = {0};
    printf("Module name? ");
    scanf("%s", module1.main_module_name);
    module1 = my_function(module1);
    
    printf("Final result for %s: %d\n", module1.main_module_name, module1.integers[0]);
    return 0;
}
