#include <stdio.h>
#include <string.h>

typedef struct {
    char main_module_name[31];       
    char sub_module_names[100][31]; 
    char temp_string_array[1000];    // input mathematical expression
} built;

// to check if a character is a digit
int isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}


int stringToInt(char *str) {
    int result = 0;
    while (*str) {
        if (isDigit(*str)) {
            result = result * 10 + (*str - '0');
        } else {
            return -1; // if not a valid integer, return -1
        }
        str++;
    }
    return result; 
}



int my_function(built *module1) {
    char *ptr = module1->temp_string_array; 
    int result = 0; // result for the current module

    printf("Define %s: ", module1->main_module_name);
    getchar(); // clear newline character
    scanf("%[^\n]", module1->temp_string_array); // read full line


    while (*ptr != '\0') {
        while (*ptr == ' ') ptr++; // skip spaces

        int coef = 1; // Default coefficient : 1
        char submodule_name[31] = {0}; // Temporary buffer for submodule name

        // parse coefficient if it not non
        if (isDigit(*ptr)) {
            coef = 0;
            while (isDigit(*ptr)) {
                coef = coef * 10 + (*ptr - '0');
                ptr++;
            }
        }
        if (*ptr == '*') ptr++; // skip '*'

        while (*ptr == ' ') ptr++; // skip space before submodule name

        // parse submodule name
        int len = 0;
        while (*ptr != '+' && *ptr != '\0' && *ptr != ' ') {
            if (len < 30) {
                submodule_name[len++] = *ptr; //we know that max len is 30
            }
            ptr++;
        }
        submodule_name[len] = '\0'; //add null

        while (*ptr == ' ') ptr++; // skip spaces
        if (*ptr == '+') ptr++; // skip '+'

        // if no submodule name, treat coefficient as a direct integer result
        // if user enter just integer, integers become ceoefficient and moddule name become ' '
        if (strlen(submodule_name) == 0) {
            result += coef;
            continue;
        }

        // check if submodule name is a direct integer
        int potentialInt = stringToInt(submodule_name);
        if (potentialInt == -1) {
            // if not an integer, recursively process the submodule
            built submodule = {0};
            strcpy(submodule.main_module_name, submodule_name);
            int submodule_result = my_function(&submodule); // Recursive call
            result += coef * submodule_result; // Add submodule result to the total
        } 
    }

    return result; // return the calculated result for the module
}

int main(void) {
    built module1 = {0}; 
    printf("Module name? ");
    scanf("%s", module1.main_module_name); 
    int final_result = my_function(&module1); // calculate
    printf("Final result for %s: %d\n", module1.main_module_name, final_result); // the final result
    return 0;
}
