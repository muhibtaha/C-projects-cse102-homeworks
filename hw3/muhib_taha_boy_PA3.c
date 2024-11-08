#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 1024  // Satır boyutu (buffer boyutu)

/* exponent calculator*/
double power(double base, int exp) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}


/* a manuel digit controller that control char and determine is it number by using ASCII*/
 int digit_control( char a){
   return (a >= '0' && a <= '9');
 }




double evaluate_term(char *term, double x, double y) {
    double result = 0.0;
    int coef = 1; /* to make coefficent 1 if there has no coefficient*/
    int exp_x = 0, exp_y = 0; /* exponent of x and y*/
    
    char *ptr = term;
    
      /*to make coefficent -1 or +1 if there are -or + before that*/
       if (*ptr == '-') {
        coef = -1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;  /* continue*/
    }
    
   /*detect coefficient */
    int num = 0;
    while (digit_control(*ptr)) {  
        num = num * 10 + (*ptr - '0'); /*change char numbers to integer by using ASCII values. For example: Difference ascıı values between '0' and '2' = 2*/
        ptr++;
    }
    
    if (num != 0) {
        coef = num;  
    } else if (*ptr != 'x' && *ptr != 'y') {
        coef = coef;  /*if there is no coefficient, it is 1 or -1 that we select before*/
    }

/*x*/
    if (*ptr == 'x') {
        exp_x = 1;  /*when we find x exponenet default 1*/
        ptr++;  
        if (*ptr == '^') {  
            ptr++;  
            num = 0;
            while (digit_control(*ptr)) { /*read exponent*/
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            exp_x = num;  // x'in üssü
        }
    }

   /*y*/
    if (*ptr == 'y') {
        exp_y = 1; 
        ptr++;  
        if (*ptr == '^') {
            ptr++; 
            num = 0;
            while (digit_control(*ptr)) {  
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            exp_y = num; 
        }
    }
    
   /*calculations*/
    result = coef * power(x, exp_x) * power(y, exp_y);
    
    return result;
}




/*divides polynoms to terms*/
void process_polynomial(char *polynomial, double x, double y) {
    double total_result = 0.0;
    int sign = 1;  // İşaret (pozitif veya negatif)
    char term[100];  // Her terim için geçici bir buffer
    int index = 0;   // `term` buffer’ı için index

    for (int i = 0; i <= strlen(polynomial); i++) {
        if (polynomial[i] == '+' || polynomial[i] == '-' || polynomial[i] == '\0') {
            if (index > 0) { // Geçerli bir terim varsa işleyin
                term[index] = '\0';  // Term'i sonlandır

                // İşarete göre terimi değerlendirin
                total_result += evaluate_term(term, x, y) * sign;

                index = 0; // Term buffer’ı sıfırlayın
            }

            // Yeni işareti ayarla
            sign = (polynomial[i] == '-') ? -1 : 1;
        } else {
            term[index++] = polynomial[i];  // Terimi buffer’a ekle
        }
    }

    printf("Polinomun toplam sonucu: %lf\n", total_result);
}


int main() {
    FILE *file = fopen("polinom.txt", "r");
    if (!file) {
        perror("Dosya açılamadı");
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    
    double x, y;
    printf("x değeri: ");
    scanf("%lf", &x);
    printf("y değeri: ");
    scanf("%lf", &y);

    // Dosyadaki her satırı oku
    while (fgets(line, sizeof(line), file)) {
        // Satır sonundaki '\n' karakterini temizlemiyoruz
        // Artık satırdaki '\n' karakteri dikkate alınacak
        
        // Polinomu işle ve toplam sonucu hesapla
        process_polynomial(line, x, y);
    }
    
    fclose(file);
    
    return 0;
}
