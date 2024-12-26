#include <stdio.h>
#include <stdlib.h>


void vanillia(int **two_dimensional_array_pointer_list, int **visited, int x, int y, int max_x, int max_y, int group_number){
//border controls
    if (x < 0 || x >= max_x || y < 0 || y >= max_y)
        return;
	//ensure that it is 1 and in not visited status
    if (two_dimensional_array_pointer_list[y][x] == 0 || visited[y][x] == 1)
        return;

	//label with group number
    visited[y][x] = 1;
    two_dimensional_array_pointer_list[y][x] = group_number;

// these are connected if (|y1-y2| == 1 and x1==x2) or (|x1-x2| == 1 and y1==y2)
    vanillia(two_dimensional_array_pointer_list, visited, x + 1, y, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list, visited, x - 1, y, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list, visited, x, y + 1, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list, visited, x, y - 1, max_x, max_y, group_number); 


}


int
	main(void){
	int x_value, y_value;
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");

	fscanf(input, "%d",&y_value);
	fscanf(input, "%d",&x_value);	
	

//control grip if is it in the borders
	if (x_value > 1024 || y_value > 1024|| x_value<1 || y_value<1)
	{
		printf("M x N must be between 1 - 1024\n");
		return 1;
	}
	
	
	
//dynamically pointer array list
    int **two_dimensional_array_pointer_list = (int **)malloc(x_value * sizeof(int *));
    int **visited = (int **)malloc(y_value * sizeof(int *));



    
//each of them keep another lists, so it become 2d SSS
    for (int i = 0; i < y_value; i++) {
        two_dimensional_array_pointer_list[i] = (int *)malloc(x_value * sizeof(int));
        visited[i] = (int *)malloc(x_value * sizeof(int));  //for each line
        for (int j = 0; j < x_value; j++) {
            visited[i][j] = 0;  
        }		
    }


	    for (int i = 0; i < y_value; i++) {
      						  for (int j = 0; j < x_value; j++) {
            														fscanf(input, "%d", &two_dimensional_array_pointer_list[i][j]);  // Dosyadan her hücreye 0 veya 1 değerini ata
        }
    }




   int group_number = 1; //labels 
    for (int i = 0; i < y_value; i++) {
        for (int j = 0; j < x_value; j++) {
            if (two_dimensional_array_pointer_list[i][j] == 1 && visited[i][j] == 0) {
                vanillia(two_dimensional_array_pointer_list, visited, j, i, x_value, y_value, group_number);
                group_number++;
            }
        }
	}	


    for (int i = 0; i < y_value; i++) {
        for (int j = 0; j < x_value; j++) {
            fprintf(output, "%d ", two_dimensional_array_pointer_list[i][j]); //write to outputs after each lines
        }
        fprintf(output, "\n"); //newline 
    }

    fclose(input);
    fclose(output);
	//free dynamic memory
    for (int i = 0; i < y_value; i++) { //free what show pointer array list
        free(two_dimensional_array_pointer_list[i]); // free itself of pointer array list
        free(visited[i]);
    }
    free(two_dimensional_array_pointer_list);
    free(visited);		
    		
	
	
	return 1;
	}
	