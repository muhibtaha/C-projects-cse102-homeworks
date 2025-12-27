# Connected Component Labeling Program

## Overview
This program processes an image represented as a grid of black and white pixels, labeling connected components of white pixels and assigning unique colors to each group. It supports reading images from text files and generating color-coded PPM images.

## Features
- **Connected Component Labeling:** Identifies connected groups of white pixels in a 2D grid.  
- **Grid-Based Processing:** Assigns labels to each connected component in a pixel grid.  
- **Color Palette Assignment:** Assigns a unique color to each connected component from a predefined palette.  
- **Input/Output in PPM Format:** Reads from text input and outputs color-coded PPM images.

## Code Explanation

- **Piece Structure:** Each pixel is represented by a structure with a label and a value (0 for black, 1 for white).  
```c
typedef struct { int label; int value; } piece;
```

- **Find Function:** Finds the root label of a pixel for the union-find algorithm.  
```c
int find(int *labels, int x) { while (labels[x] != x) { x = labels[x]; } return x; }
```

- **Unite Function:** Unites two groups by linking roots.  
```c
void unite(int *labels, int x, int y) { int root_x = find(labels, x); int root_y = find(labels, y); if (root_x != root_y) { labels[root_y] = root_x; } }
```

- **Vanillia Function:** Processes the grid to label connected components and unite groups.  
```c
void vanillia(piece **grid, int width, int height) { /* Labeling and union-find */ }
```

- **Process Image:** Applies labeling and assigns colors from the palette.  
```c
void process_image(FILE *input, FILE *output, int width, int height, int color_palette[127][3]) { /* Image processing */ }
```

## Usage
1. **Prepare the Input File:**  
   - `input.txt` contains the image: first two numbers are height and width, followed by pixel values (1 for white, 0 for black).

2. **Compile the Program:**  
```bash
gcc -o image_processor image_processor.c
```

3. **Run the Program:**  
```bash
./image_processor
```
- The program reads `input.txt` and outputs `output.txt` with labeled grid values.  
- Optionally handles `input.ppm` and outputs a color-coded `output.ppm` image.

## Example
**input.txt:**
```
5 5
1 0 0 1 0
1 1 0 1 1
0 0 0 1 0
1 1 0 0 0
0 0 1 0 0
```

**output.txt:**
```
1 0 0 2 0
1 1 0 2 2
0 0 0 2 0
3 3 0 0 0
0 0 4 0 0
```

- Each connected group of white pixels is assigned a unique label and color.

## Limitations
- **Group Limit:** Supports up to 127 groups. Extra groups are painted black.  
- **Grid Size:** Maximum supported grid size is 1024x1024.

## Memory Management
- Uses dynamic memory allocation for grid and labels.  
- Frees all allocated memory before exiting.

## Conclusion
This program efficiently labels connected components in binary images and assigns colors for visualization. It is suitable for image processing tasks such as object segmentation or labeling.
