Overview

This program is designed to process an image represented as a grid of black and white pixels, where connected components of white pixels are labeled and color-coded. The program uses a labeling algorithm to identify these connected components and assign unique labels to each one. Additionally, the program processes the image and applies color to each group based on a predefined color palette.
Features

    Connected Component Labeling: Identifies connected groups of white pixels in a 2D grid.
    Grid-Based Processing: The image is processed as a grid of pixels, with labels assigned to each connected component.
    Color Palette Assignment: Each unique group of connected white pixels is assigned a color from a predefined palette.
    Input/Output in PPM Format: The program reads an image from a text file and generates a color-coded PPM image.

Code Explanation

    Piece Structure: Each grid element is represented by a piece structure, which holds a label (the group identifier) and a value (0 for black or 1 for white).

typedef struct {
    int label;
    int value;
} piece;

    Find Function: This function finds the root label (parent) of a pixel. It is used in the union-find algorithm to determine if two pixels belong to the same group.

int find(int *labels, int x) {
    while (labels[x] != x) {
        x = labels[x];
    }
    return x;
}

    Unite Function: This function unites two different groups by making one group's root point to the other. It uses the find function to check if two pixels belong to the same group.

void unite(int *labels, int x, int y) {
    int root_x = find(labels, x);
    int root_y = find(labels, y);
    if (root_x != root_y) {
        labels[root_y] = root_x;
    }
}

    Vanillia Function: This function processes the grid to identify connected components. It assigns labels to each pixel and unites groups that are connected (either left or up).

void vanillia(piece **grid, int width, int height) {
    // Labeling and union-find operations
}

    Process Image: This function processes an input image, applying the connected component labeling algorithm (vanillia) and then assigning colors to each group.

void process_image(FILE *input, FILE *output, int width, int height, int color_palette[127][3]) {
    // Image processing logic
}

Usage

    Prepare the Input File: The input image should be in a text file (input.txt) where the first two values represent the image dimensions (height and width), followed by the grid of pixel values (1 for white and 0 for black).

    Run the Program: Compile the program and run it. It will read from the input file and output the labeled grid to output.txt. The program also handles image files in PPM format (input.ppm and output.ppm) and generates color-coded images based on the connected components.

    Color Palette: The program uses a predefined color palette with 127 distinct colors. Each connected component is assigned a color from this palette.

Example
Input (input.txt):

5 5
1 0 0 1 0
1 1 0 1 1
0 0 0 1 0
1 1 0 0 0
0 0 1 0 0

Output (output.txt):

1 0 0 2 0
1 1 0 2 2
0 0 0 2 0
3 3 0 0 0
0 0 4 0 0

Each group of connected white pixels is assigned a unique label.
Example of Color Assignment:

The output image in PPM format will have different colors for each connected component, with the color corresponding to the group label.
Bonus: Handling Images in PPM Format

The program also includes bonus functionality for reading and processing images in PPM format (input.ppm). It applies the connected component labeling and assigns colors from the palette, saving the result in output.ppm.
Limitations

    Group Limit: The program supports up to 127 groups. If there are more groups, the program will display a warning, and extra groups will be painted black.
    Grid Size: The maximum grid size supported is 1024x1024.

Memory Management

The program uses dynamic memory allocation to store the grid and label information. It ensures to free all allocated memory before exiting.
Conclusion

This program provides a simple yet effective way to process binary images, identify connected components, and assign color labels to them. It is suitable for image processing tasks involving object segmentation or labeling.
