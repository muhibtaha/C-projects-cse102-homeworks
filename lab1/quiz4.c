#include <stdio.h>

int char_to_int(char a){

return a-'0';
}



int
	main(void){
	
		/*student nunber =3*/
	char my_array[3][5]= {{'m', 'b', '1', '1', '9'}, 
				{'e', 'e', '2', '1', '8'},
				{'f', 'u', '3', '2', '7'}};
	
	
	while(1){
	
	printf("\n\n A:List all of the rows. \n B:Find to row by student id. \n C:Find the row with highest grade by course ID \n D: find the number of student who take the course bu course ID \n E: exit \n --------------\n ");
	
	char c;
	scanf(" %c", &c);
	//while (getchar() != '\n');

	switch (c) {
	

	case ('A'):	for(int i=0; i<3; i++){
	
			for(int j=0; j<5;j++){
			
			printf("%c ", my_array[i][j]);	
			
			}
			printf("\n");
	}
	
		break;
	
	
	case ('B'): printf("student id ? :\n");
		char k;
		scanf(" %c", &k);
		//while (getchar() != '\n');

		if(k== '1') for(int i=0; i<5; i++) { printf("%c ", my_array[0][i]);  }
		if(k== '2') for(int i=0; i<5; i++) { printf("%c ", my_array[1][i]);  }
		if(k== '3') for(int i=0; i<5; i++) { printf("%c ", my_array[2][i]);  }	
		break;	
											
											
	case ('D'): printf("Give course id:\n");
	        int course_id;
	        scanf("%d", &course_id);
	        
	        int count=0;
	        int i;
	      for(i=0; i<5;i++){  
	        if(char_to_int(my_array[i][3])==course_id) { count++;
	        					    }}
	        					   printf("%d", count);  
	
		break;
	
	
	case ('C'): printf("Give course id:\n");
	        course_id=-1;
	        scanf("%d", &course_id);
	        
	        	        	       int max_student=-1;
	        	        	       	       int max=0; 
	        for(int i=0; i<3; i++){

	        if(char_to_int(my_array[i][3])==course_id) {


	       if(max<my_array[i][4]) {max=my_array[i][4];
	       				max_student=i;}
	        
	       } 
	        }
	        printf("Highest graded student: \n");
	              for(int i=0; i<5; i++){
	               printf("%c", my_array[max_student][i]);
	           
	              }
	              
	        break;      
	        

	        
	       
	        
	 case ('E'): return(1);         										
					
					
	}				
	
	
	
	
	
	
	
	
	
	
	
	
	}
	
	
	}
