#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int label;
	int value;

}piece;

//it find the parent label
int find(int *labels, int x) {
    while (labels[x] != x) {
        x = labels[x];
    }
    return x;
}

//it change parent with other one if actually there are same gouprs
void unite(int *labels, int x, int y) {
    int root_x = find(labels, x);
    int root_y = find(labels, y);
    if (root_x != root_y) {
        labels[root_y] = root_x;
    }
}


//vanillia is a function that control and decided which are in which group
void vanillia(piece **grid, int width, int height){
    int *labels = malloc(width * height * sizeof(int)); //parents root array
    int next_label = 1;

//at the begining each items are labeled with themself
    for (int i = 0; i < width * height; i++) {
        labels[i] = i;
    }

//temp lebelling, before groups connections
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].value == 1) {
                int left;
                        if (x > 0) { left= grid[y][x - 1].label; } else left=0; //if left or up < 0, it means it is on border, progrems bheavour is its like 0
                int up; 
                        if(y > 0) { up=grid[y - 1][x].label; } else  up=0;

                if (left == 0 && up == 0) {
                    grid[y][x].label = next_label;
                    next_label++;
                } else if (left != 0 && up == 0) {
                    grid[y][x].label = left;
                } else if (left == 0 && up != 0) {
                    grid[y][x].label = up;
                } else { //it means, left and up have different groups
                    grid[y][x].label = left;
                    unite(labels, left, up); //unite them
                }
            } else {
                grid[y][x].label = 0;
            }
        }
    }

//updates the label of each pixel to the actual label of the group to which that pixel belongs
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].label != 0) {
                grid[y][x].label = find(labels, grid[y][x].label);
            }
        }
    }

    //now each label found and sent to grid.label. bu we have to renumber them
            
             //renumber grups
    int *new_labels = calloc(width * height, sizeof(int)); //for new labels, each is 0
    int current_label = 1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x].label != 0) {
                int old_label = grid[y][x].label;
                if (new_labels[old_label] == 0) { // if a new label has not yet been assigned to this old label, group
                    new_labels[old_label] = current_label++;
                }
                grid[y][x].label = new_labels[grid[y][x].label]; //same with writing old_label
            }
        }
    }

    free(labels);
    free(new_labels);
}



//bonus part functions
void get_group_color(int group, int *r, int *g, int *b, int color_palette[127][3], int *overgroup) {
    if (group > 0 && group <= 127) {
        *r = color_palette[group - 1][0];
        *g = color_palette[group - 1][1];
        *b = color_palette[group - 1][2];
    } else if (group >127) {
        *overgroup=1;
    } else {
                *r = *g = *b = 0; //default black thats have no grups, they was black pixel before

    }
}

void process_image(FILE *input, FILE *output, int width, int height, int color_palette[127][3]) {
    piece **pixels = (piece **)malloc(height * sizeof(piece *));
    for (int i = 0; i < height; i++) {
        pixels[i] = (piece *)malloc(width * sizeof(piece));
    }

    // read the input image and assign each pixel a group
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r;
            if (fscanf(input, "%d", &r) != 1) {
                printf("Error reading pixel values at %d, %d\n", i, j);
                r  = 0;  // Default to black if read fails

            }

            
            // assign values based on RGB
            if (r == 0) {
                pixels[i][j].value = 0;  // Black
            } else if (r == 1) {
                pixels[i][j].value = 1;  // white
            } else {
                pixels[i][j].value = 0;  // default to black if not pure black or white
            }
        }

    }

    // assign colors to groups and write the PPM file
    fprintf(output, "P3\n%d %d\n255\n", width, height);
    int group_number = 1;

    //first make 1 0 and new gruops then we will change them with color
    vanillia(pixels, width, height);


    int over_group=0;
    // write pixel colors to output
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            get_group_color(pixels[i][j].label, &r, &g, &b, color_palette, &over_group);
            fprintf(output, "%d %d %d ", r, g, b);
        }
        fprintf(output, "\n");
    }

    if(over_group==1) printf("Warning, there are more than 127 groups. Groups that stayed longer were painted black\n");
    // free allocated memory
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

    }
    



	    for (int i = 0; i < y_value; i++) {
      						  for (int j = 0; j < x_value; j++) {
            														fscanf(input, "%d", &two_dimensional_array_pointer_list[i][j].value);  // read input
        }
    }




   int group_number = 1; //labels 

    vanillia(two_dimensional_array_pointer_list, x_value, y_value);


    for (int i = 0; i < y_value; i++) {
        for (int j = 0; j < x_value; j++) {
            fprintf(output, "%d ", two_dimensional_array_pointer_list[i][j].label); //write to outputs after each lines
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

    // Process the image
    process_image(bonus_input, bonus_output, bonus_x_value, bonus_y_value, color_palette);

    fclose(bonus_input);
    fclose(bonus_output);

	
	return 1;
	}
	