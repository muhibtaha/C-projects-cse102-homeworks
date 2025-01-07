# README: Language Dissimilarity Calculator

This program calculates the **dissimilarity** between a base language file (`language_x.txt`) and several other language files (`language_1.txt`, `language_2.txt`, ..., `language_5.txt`). The dissimilarity metric is computed using bigram frequency differences across the files.

---

## Features
- **Bigram Counting**: Counts the occurrences of each two-character combination (bigram) in the input files.
- **Space Handling**: Treats spaces as valid characters in bigrams.
- **Dissimilarity Calculation**: Measures the difference in bigram frequency distributions using absolute differences.
- **Multiple Files**: Processes up to `N` additional language files to compare with the base language.

---

## How It Works

### Bigram Counting
Each bigram (two consecutive characters) in a file is recorded. Both letters (`a` to `z`) and spaces are valid characters, resulting in 27 possible characters and a total of 729 unique bigrams.

### Dissimilarity Metric
For each bigram, the program calculates:
```text
dissimilarity += |frequency_in_language_x - frequency_in_language_i|
```
The result is a numerical value representing the difference in character distribution between the base language and the other languages.

---

## Input Files
- `language_x.txt`: Base language file.
- `language_1.txt` to `language_5.txt`: Comparison language files.
- All files should contain plain text consisting of lowercase letters and spaces. No special characters are allowed.

---

## Output
The program outputs the dissimilarity between the base language file and each comparison file. Example:

```plaintext
Dissimilarity between language_x.txt and language_1.txt: 0.123456
Dissimilarity between language_x.txt and language_2.txt: 0.234567
...
```

---

## Code Components

1. **`positive_maker` Function**:
   - Converts a negative number to its positive value (absolute value).

2. **`search_and_count` Function**:
   - Reads a file and counts the frequency of each bigram.
   - Updates the count array and the total bigram count for the file.

3. **`calculate_dissimilarity` Function**:
   - Computes the dissimilarity metric between two frequency distributions.

4. **Main Function**:
   - Initializes bigram combinations.
   - Reads and processes all files.
   - Outputs dissimilarity results for all comparisons.

---

## Compilation and Execution

### Compilation
Compile the program using a C compiler:
```bash
gcc language_dissimilarity.c -o language_dissimilarity
```

### Execution
Run the executable:
```bash
./language_dissimilarity
```

---

## Limitations
- Assumes the input files contain only valid lowercase letters and spaces.
- Hardcoded to compare up to 5 files (adjustable via the `N` macro).
- Ignores newline and tab characters.

---

## Future Improvements
- Extend support for files with larger character sets (e.g., uppercase, punctuation).
- Implement dynamic file handling to process an arbitrary number of input files.
- Add error handling for malformed or missing input files.
- Provide visualization of bigram distributions and dissimilarity scores.

---

## License
This program is open-source and available under the MIT License.


