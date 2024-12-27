#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int visited;
	int value;

}piece;



//vanillia is a function that control right,left, up and down and decided which are in which group
void vanillia(piece **two_dimensional_array_pointer_list, int x, int y, int max_x, int max_y, int group_number){

//border controls
    if (x < 0 || x >= max_x || y < 0 || y >= max_y)
        return;
	//ensure that it is 1 and in not visited status
    if (two_dimensional_array_pointer_list[y][x].value == 0 || two_dimensional_array_pointer_list[y][x].visited == 1)
        return;

	//label with group number
    two_dimensional_array_pointer_list[y][x].visited = 1;
    two_dimensional_array_pointer_list[y][x].value = group_number;

// these are connected if (|y1-y2| == 1 and x1==x2) or (|x1-x2| == 1 and y1==y2)
    vanillia(two_dimensional_array_pointer_list,  x + 1, y, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list,  x - 1, y, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list,  x, y + 1, max_x, max_y, group_number); 
    vanillia(two_dimensional_array_pointer_list,  x, y - 1, max_x, max_y, group_number); 


}


//bonus 

void get_group_color(int group, int *r, int *g, int *b, int color_palette[127][3]) {
    if (group > 0 && group <= 127) {
        *r = color_palette[group - 1][0];
        *g = color_palette[group - 1][1];
        *b = color_palette[group - 1][2];
    } else {
        *r = *g = *b = 0; // Default to black if group is out of range
    }
}

void process_image(FILE *input, FILE *output, int width, int height, int color_palette[127][3]) {
    piece **pixels = (piece **)malloc(height * sizeof(piece *));
    for (int i = 0; i < height; i++) {
        pixels[i] = (piece *)malloc(width * sizeof(piece));
    }

    // Read the input image and assign each pixel a group
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            if (fscanf(input, "%d %d %d", &r, &g, &b) != 3) {
                printf("Error reading pixel values at %d, %d\n", i, j);
                r = g = b = 0;  // Default to black if read fails

            }

            

            // Assign values based on RGB
            if (r == 0 && g == 0 && b == 0) {
                pixels[i][j].value = 0;  // Black
            } else if (r == 255 && g == 255 && b == 255) {
                pixels[i][j].value = 1;  // White
            } else {
                pixels[i][j].value = 0;  // Default to black if not pure black or white
            }
            pixels[i][j].visited = 0;  // Mark as not visited
        }

    }

    // Assign colors to groups and write the PPM file
    fprintf(output, "P3\n%d %d\n255\n", width, height);
    int group_number = 1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (pixels[i][j].value == 1 && pixels[i][j].visited == 0) {
                vanillia(pixels, j, i, width, height, group_number);
                group_number++;
            }
        }
    }

    // Write pixel colors to output
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            get_group_color(pixels[i][j].value, &r, &g, &b, color_palette);
            fprintf(output, "%d %d %d ", r, g, b);
        }
        fprintf(output, "\n");
    }

    // Free allocated memory
    for (int i = 0; i < height; i++) {
        free(pixels[i]);
    }
    free(pixels);
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
    piece **two_dimensional_array_pointer_list = (piece **)malloc(y_value * sizeof(piece *));
    
//each of them keep another lists, so it become 2d SSS
    for (int i = 0; i < y_value; i++) {
        two_dimensional_array_pointer_list[i] = (piece *)malloc(x_value * sizeof(piece));
        for (int j = 0; j < x_value; j++) {
            two_dimensional_array_pointer_list[i][j].visited = 0;  
        }		
    }
    



	    for (int i = 0; i < y_value; i++) {
      						  for (int j = 0; j < x_value; j++) {
            														fscanf(input, "%d", &two_dimensional_array_pointer_list[i][j].value);  // read input
        }
    }




   int group_number = 1; //labels 
    for (int i = 0; i < y_value; i++) {
        for (int j = 0; j < x_value; j++) {
            if (two_dimensional_array_pointer_list[i][j].value == 1 && two_dimensional_array_pointer_list[i][j].visited == 0) {
                vanillia(two_dimensional_array_pointer_list, j, i, x_value, y_value, group_number);
                group_number++;
            }
        }
	}	


    for (int i = 0; i < y_value; i++) {
        for (int j = 0; j < x_value; j++) {
            fprintf(output, "%d ", two_dimensional_array_pointer_list[i][j].value); //write to outputs after each lines
        }
        fprintf(output, "\n"); //newline 
    }

    fclose(input);
    fclose(output);
	//free dynamic memory
    for (int i = 0; i < y_value; i++) { //
        free(two_dimensional_array_pointer_list[i]); //free what show pointer array list
    }
    free(two_dimensional_array_pointer_list);// free itself of pointer array list
    		



 //bonus

int color_palette[127][3] = {
    {255, 0, 0}, {255, 128, 0}, {255, 255, 0}, {128, 255, 0}, {0, 255, 0}, {0, 255, 128}, {0, 255, 255}, {0, 128, 255}, {0, 0, 255}, {128, 0, 255}, // Group 1-10
    {255, 0, 255}, {255, 0, 128}, {192, 0, 0}, {192, 96, 0}, {192, 192, 0}, {96, 192, 0}, {0, 192, 0}, {0, 192, 96}, {0, 192, 192}, {0, 96, 192}, // Group 11-20
    {0, 0, 192}, {96, 0, 192}, {192, 0, 192}, {192, 0, 96}, {160, 32, 32}, {160, 80, 32}, {160, 160, 32}, {80, 160, 32}, {32, 160, 32}, {32, 160, 80}, // Group 21-30
    {32, 160, 160}, {32, 80, 160}, {32, 32, 160}, {80, 32, 160}, {160, 32, 160}, {160, 32, 80}, {128, 64, 64}, {128, 96, 64}, {128, 128, 64}, {96, 128, 64}, // Group 31-40
    {64, 128, 64}, {64, 128, 96}, {64, 128, 128}, {64, 96, 128}, {64, 64, 128}, {96, 64, 128}, {128, 64, 128}, {128, 64, 96}, {255, 64, 64}, {255, 96, 64}, // Group 41-50
    {255, 255, 64}, {96, 255, 64}, {64, 255, 64}, {64, 255, 96}, {64, 255, 255}, {64, 96, 255}, {64, 64, 255}, {96, 64, 255}, {255, 64, 255}, {255, 64, 96}, // Group 51-60
    {192, 128, 64}, {192, 192, 128}, {128, 192, 192}, {96, 192, 192}, {128, 96, 192}, {192, 96, 192}, {192, 128, 128}, {160, 64, 64}, {160, 96, 64}, {160, 160, 64}, // Group 61-70
    {96, 160, 64}, {64, 160, 64}, {64, 160, 96}, {64, 160, 160}, {64, 96, 160}, {64, 64, 160}, {96, 64, 160}, {160, 64, 160}, {160, 64, 96}, {255, 96, 96}, // Group 71-80
    {255, 160, 96}, {255, 255, 160}, {160, 255, 160}, {96, 255, 160}, {160, 160, 255}, {96, 96, 255}, {96, 96, 192}, {96, 96, 128}, {192, 96, 128}, {255, 96, 128}, // Group 81-90
    {128, 128, 255}, {192, 128, 255}, {255, 192, 255}, {192, 255, 255}, {255, 255, 255}, {0, 0, 0}, {64, 64, 64}, {128, 128, 128}, {192, 192, 192}, {255, 255, 255}  // Group 91-127
};

	
    int bonus_x_value, bonus_y_value;
    FILE *bonus_input = fopen("input.ppm", "r");
	if (!bonus_input) {
    printf("Error opening input.ppm\n");
    return 1;
}
    FILE *bonus_output = fopen("output.ppm", "w");

    // Read PPM header
    char bonus_header[3];
    fscanf(bonus_input, "%s", bonus_header);
    fscanf(bonus_input, "%d %d", &bonus_x_value, &bonus_y_value);
    int bonus_max_value;
    fscanf(bonus_input, "%d", &bonus_max_value);
 

    

    // Process the image
    process_image(bonus_input, bonus_output, bonus_x_value, bonus_y_value, color_palette);

    fclose(bonus_input);
    fclose(bonus_output);

	
	return 1;
	}
	