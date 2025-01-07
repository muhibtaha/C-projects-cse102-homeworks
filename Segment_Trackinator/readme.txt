# Segment Tracking Program

## Overview
This program implements a segment-based tracking system that reads integers from an input file (`input.txt`) and processes them into fixed-size segments. It identifies repeated segments, tracks their occurrence counts, and writes the processed data to an output file (`output.txt`).

## Features
- **Segment Management**: Groups input integers into segments of size `X`.
- **Memory Limitation**: Remembers only the most recent `Y` segments.
- **Duplicate Detection**: Tracks the occurrence count of identical segments.
- **Output Formatting**: Outputs each remembered segment along with its occurrence count.

## Constants
The program uses the following constants for configuration:
- `X`: Size of each segment.
- `Y`: Number of recent segments to remember.
- `c`: Small constant multiplier used in `MAX_SIZE` calculation.
- `MAX_SIZE`: Maximum size of the array, calculated as `c * X * Y`.
- `control`: A unique control value used to initialize arrays, ensuring no random data is present.

## Input Format
The program expects an input file named `input.txt` containing a list of integers separated by whitespace. Example:
```
3 5 7 9 3 5 7 9 10 11 12 13 14
```

## Output Format
The program writes the results to an output file named `output.txt`. Each line in the output contains:
- A remembered segment.
- Its occurrence count.

Example output:
```
3 5 : 2
7 9 : 1
10 11 : 1
```

## How It Works
1. **Initialization**: Arrays for storing segments and their counts are initialized with the `control` value.
2. **Reading Input**: Integers are read from `input.txt` and grouped into segments of size `X`.
3. **Duplicate Check**: Each new segment is checked against the remembered segments.
   - If a match is found, the occurrence count of the segment is incremented.
   - If no match is found, the oldest segment is replaced with the new one.
4. **Output**: The remembered segments and their occurrence counts are written to `output.txt`.

## Error Handling
- The program checks if `input.txt` and `output.txt` can be opened. If either fails, it prints an error message and exits.

## Usage
1. Place the `input.txt` file in the program's working directory.
2. Compile the program using a C compiler:
   ```
   gcc -o segment_tracker segment_tracker.c
   ```
3. Run the program:
   ```
   ./segment_tracker
   ```
4. View the results in `output.txt`.

## Notes
- The segment size (`X`) and memory limit (`Y`) can be adjusted by modifying the corresponding `#define` values.
- Ensure that the input file adheres to the expected format to avoid unexpected behavior.

## Limitations
- The program assumes `input.txt` contains sufficient integers to form at least one segment of size `X`.
- If the input contains fewer integers than `X`, no segments will be processed or output.

## Example Configuration
With the default constants:
```c
#define X 2  // Segment size
#define Y 13 // Number of recent segments
#define c 1  // Multiplier constant
```
The program processes integers in pairs, remembers up to 13 recent pairs, and tracks their occurrence counts.


