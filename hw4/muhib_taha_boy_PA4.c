#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MODULES 100
#define MAX_IDENTIFIER_LEN 30
#define MAX_DESC_LEN 256

typedef struct {
    char identifier[MAX_IDENTIFIER_LEN + 1];
    char description[MAX_DESC_LEN + 1];
    int value;
    int defined; // To check if the module's value is already calculated
} Module;

Module modules[MAX_MODULES];
int module_count = 0;

int find_module_index(char *id) {
    for (int i = 0; i < module_count; i++) {
        if (strcmp(modules[i].identifier, id) == 0) {
            return i;
        }
    }
    return -1;
}

int get_module_value(char *id);

int calculate_module_value(char *description) {
    int result = 0;
    char temp_desc[MAX_DESC_LEN + 1];
    strcpy(temp_desc, description);
    
    char *token = strtok(temp_desc, "+");
    
    while (token != NULL) {
        // Trim leading spaces
        while (isspace(*token)) token++;
        
        int scalar = 1;
        char module_id[MAX_IDENTIFIER_LEN + 1];
        
        if (sscanf(token, "%d*%s", &scalar, module_id) == 2 || sscanf(token, "%*c%s", module_id) == 1) {
            result += scalar * get_module_value(module_id);
        } else if (sscanf(token, "%d", &scalar) == 1) {
            result += scalar;
        }
        
        token = strtok(NULL, "+");
    }
    
    return result;
}

int get_module_value(char *id) {
    int index = find_module_index(id);
    if (index == -1) {
        // Ask user to define the module if not found
        printf("Define %s: ", id);
        char description[MAX_DESC_LEN + 1];
        scanf(" %[^\n]", description);
        
        // Add the module
        strcpy(modules[module_count].identifier, id);
        strcpy(modules[module_count].description, description);
        modules[module_count].defined = 0;
        index = module_count++;
    }
    
    if (!modules[index].defined) {
        // Calculate the module value only if it is not already calculated
        modules[index].value = calculate_module_value(modules[index].description);
        modules[index].defined = 1;
    }
    
    return modules[index].value;
}

int main() {
    char initial_module[MAX_IDENTIFIER_LEN + 1];
    printf("Module name?: ");
    scanf("%s", initial_module);
    
    int final_result = get_module_value(initial_module);
    printf("%d\n", final_result);

    return 0;
}
