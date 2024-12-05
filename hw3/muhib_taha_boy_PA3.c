#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024  
#define MAX_TERMS 1024  /*max size of polyomal*/

/* exponent calculator */
double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

/* a manual digit controller that controls char and determines if it is a number by using ASCII */
int digit_control(char a) {
    return (a >= '0' && a <= '9');
}



/* parses a single term to determine coefficient and exponents of x and y */
void parse_term(char *term, int *coef, int *exp_x, int *exp_y) {
    *coef = 1;  
    *exp_x = 0;  /*defaults*/
    *exp_y = 0;  

    char *ptr = term;

    while (*ptr==' ') ptr++; /*to skip spaces between two terms or terms between sign*/

    

    if (*ptr == '-') {
        *coef = -1;
        ptr++;
    while (*ptr==' ') ptr++; /*to skip spaces*/

    

    } else if (*ptr == '+') {
        ptr++;
        while (*ptr==' ') ptr++; /*to skip spaces*/

    }

    int num = 0;
    while (digit_control(*ptr)) { /*control*/
        num = num * 10 + (*ptr - '0');  /* change char numbers to integer by using ASCII values */
        ptr++;
    }
    if (num != 0) {
        *coef *= num;
    }


/*x*/
    if (*ptr == 'x') {
        *exp_x = 1;  /*if there has no coefficient its 1 as a default*/
        ptr++;
        if (*ptr == '^') {
            ptr++;
            num = 0;
            while (digit_control(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            *exp_x = num;
        }
    }

/*y*/
    if (*ptr == 'y') {  /*if there has no coefficient its 1 as a default*/
        *exp_y = 1;  
        ptr++;
        if (*ptr == '^') {
            ptr++;
            num = 0;
            while (digit_control(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            *exp_y = num;
        }
    }
}



/* function to calculate the result of a one term*/
double calculate_term(int coef, int exp_x, int exp_y, double x, double y) {
    return coef * power(x, exp_x) * power(y, exp_y);
}


/* calculate all line*/
double evaluate_polynomial(int coefs[], int exp_x[], int exp_y[], int term_count, double x, double y) {
    double total_result = 0.0;
    for (int i = 0; i < term_count; i++) {
        total_result += calculate_term(coefs[i], exp_x[i], exp_y[i], x, y);  /*adds each other the results of terms*/
    }
    return total_result;
}

/* Divides polynomial into terms and returns the number of terms found */
int split_polynomial(char *polynomial, char terms[MAX_TERMS][100]) {
    int index = 0;
    int term_count = 0;

    for (int i = 0; i <= strlen(polynomial); i++) {
        if (polynomial[i] == '+' || polynomial[i] == '-' || polynomial[i] == '\0') {
            if (index > 0) {
                terms[term_count][index] = '\0';  /* save terms for analyise then calculate (next function)*/
                term_count++;
                index = 0;
            }
            if (polynomial[i] != '\0') {
                terms[term_count][index++] = polynomial[i];  /*start new term*/
            }
        } else {
            terms[term_count][index++] = polynomial[i];  
        }
    }
    return term_count;  /*founded terms number*/
}



int main() {
    FILE *polinom = fopen("polynomials.txt", "r");
    if (!polinom) {
        perror("File cannot be opened: polynomials.txt\n");
        return 1;
    }

    FILE *evaluations = fopen("evaluations.txt", "w");
    if (!evaluations) {
        perror("File cannot be opened: evaluations.txt\n");
        fclose(polinom);
        return 1;
    }

    char polynomial[MAX_LINE_LENGTH];
    char terms[MAX_TERMS][100];
    int coefs[MAX_TERMS], exp_x[MAX_TERMS], exp_y[MAX_TERMS]; 

    while (fgets(polynomial, sizeof(polynomial), polinom)) { /*get polinom and save polynomial array*/
        int term_count = split_polynomial(polynomial, terms); /*split polinom and parse to terms then save it to use later*/


        /*parse, analyise and save as like a variable */
        for (int i = 0; i < term_count; i++) {
            parse_term(terms[i], &coefs[i], &exp_x[i], &exp_y[i]);
        }

        FILE *values = fopen("values.txt", "r");
        if (!values) {
            perror("File cannot be opened: values.txt\n");
            fclose(polinom);
            fclose(evaluations);
            return 1;
        }

        double x, y;
        while (fscanf(values, "%lf %lf", &x, &y) == 2) { /*control x and values readed true ?*/
            double result = evaluate_polynomial(coefs, exp_x, exp_y, term_count, x, y);  /*calculate*/
            fprintf(evaluations, "%.2lf ", result);  
        }
        fprintf(evaluations, "\n");

        fclose(values); 
    }

    fclose(polinom);
    fclose(evaluations);

    return 0;
}
