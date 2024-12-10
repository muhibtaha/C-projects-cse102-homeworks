#include <stdio.h>
#define N 3

typedef struct {

		int  id;
		char names[51];
		char surnames[51];
		float gpa;



}student;


int
	main(void){	

		    student s[100];
		    char choice;
		    int count_student=0;
		    
		for(int i=0; i<100; i++){    
		    printf("Student ID: \n");
		    scanf(" %d", &s[i].id);

		    
		    printf("Name: ");
		    scanf(" %[^\n]", s[i].names);
		    
	            
		    printf("Sur name: \n");
		    scanf(" %[^\n]", s[i].surnames);
		    
		    
		    printf("Student GPA: \n");
		    scanf(" %f", &s[i].gpa);
		    
		    printf("do you want to add new student?(y or n)\n");
		    scanf(" %c", &choice);
		    
		    count_student++;
		    //printf("%c\n", choice);
		    if(choice!='y') break;
		    }
		    
		   	            printf("ID----Name----Surname---GPA\n");		  
		  for(int i=0; i< count_student; i++){
		  

		    printf("%d ",s[i].id);
		    printf("%s ", s[i].names);
		    printf("%s ", s[i].surnames);
		    printf("%f ", s[i].gpa);
		    printf("\n");
		    }
		    
		    
	
	
	
	
	
	
	
	
	
	
	
	
	}

