#include <stdio.h>
#include <string.h>

/*a function which make calculati
 call another function and*/
 
 typedef struct {   char main_module_name[31];
 		    int coef_submodules[100]; //we have to change char to int
  		    char temp_string_array[1000];		   	 
 		    char sub_module_names[100][31];//+1 for null
 		    int integers[100]; //we have to change char to int 
 		    } built;		    
 		    
 
 
 
 
 /*burası yanlış integeri toplaması lazım*/
 int calculate(built module1, int submodule_count){
 			int result = 0;
   			for (int i = 0; i < submodule_count; i++) {
        			printf("Calculating: %d * %s\n", module1.coef_submodules[i], module1.sub_module_names[i]);
       				 result = module1.coef_submodules[i] * result + module1.integers[i];
    				}
    		return result;
}
 
 
 
 
int digitCount(int number) {
    int count = 0;



    // 0 özel bir durumdur, tek basamaklıdır
    if (number == 0) {
        return 1;
    }

    // Sayıyı 10'a böle böle basamakları say
    while (number != 0) {
        number /= 10;
        count++;
    }

    return count;
}
 
 
 
 
 int isDigit(char blabla){ /*controls chars is it integer*/
 
 return ('0' <= blabla <='9');
 		
 };
 
 
 
 
 
 built my_function(built module1) {  /*it ask models then asko submodels then ask submodels submodels until all submodel become integer. then it ask last menu other submodels.. it going like that while using recoursive function,  make calculations*/
 

 			char *ptr = module1.temp_string_array;
 			char part[100]; 
 

			int submodule_count=0;
 			printf("Define %s\n", module1.main_module_name);
     			getchar(); //to delete \n that comes from scanf 
 			scanf("%[^\n]", module1.temp_string_array);


 			int i=0;
     
     				while (*ptr != '\0') {
        				if (sscanf(ptr, "%[^+]", module1.sub_module_names[submodule_count]) == 1) {

   					 
   				submodule_count++;
   				char *ptr_part=  module1.sub_module_names[submodule_count-1]; /*not next, current*/
   					while(*ptr_part != '\0'){ 
   								while (isDigit(*ptr_part)){	
   											        module1.coef_submodules[0]= 10*module1.coef_submodules[0]+ (*ptr_part-'0');
   												*ptr_part++;}
   												 
   					
   					}	 
   					 


    						ptr += strlen(part) + digitCount(module1.coef_submodules[0]) + 1; /* +1 for '*' sign */			
        			// Eğer + varsa, bir sonraki kısma geç
        			if (*ptr == '+') {
            			i++;
            			ptr++;  // + karakterini atla
        			}
    			}
    			
    			/*buradan sonrasında baya yanlış olabilir*/
    					     // Eğer sadece integer değer girilmişse
      					  else if (sscanf(ptr, "%d", &module1.integers[submodule_count]) == 1) {
            					printf("Final value for %s: %d\n", module1.main_module_name, module1.integers[submodule_count]);
           			 		return module1;  // Geri dönüş
        }
 
 
 /* bunu yapıyor gibi gözükmedi*/
         // Eğer submodül varsa, recursive çağrı yap
        built submodule;
        strcpy(submodule.main_module_name, module1.sub_module_names[submodule_count]);
        submodule = my_function(submodule);  // Submodül işleme
        module1.integers[submodule_count] = calculate(submodule, submodule_count);  // Hesaplama yap
        
        submodule_count++;

        // Eğer + varsa, bir sonraki kısma geç
        if (*ptr == '+') {
            ptr++;
        }
    
}
 
 return module1;
 }
 
 
 
 
 
 
 int main
 	(void) {

 		built module1;
 		printf("Module name?");
 		scanf("%s", module1.main_module_name);
 		module1 =my_function(module1);
 		    int result = calculate(module1, 100);  // Tüm modüllerin sonucunu hesapla
    printf("Final result for %s: %d\n", module1.main_module_name, result);
 	

 	
 	return(0);
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	
 	} 
