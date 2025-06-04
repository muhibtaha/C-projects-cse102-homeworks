# README: Cluster Point Inclusion Program

This program clusters a series of points into three predefined clusters based on their distances from the cluster centers. It dynamically adjusts the cluster centers as new points are added, ensuring the closest points are included while maintaining cluster separation.

---

## Features
- **Distance Calculation**: Computes Euclidean distance between a point and cluster centers.
- **Dynamic Center Adjustment**: Updates cluster centers based on the average coordinates of all included points.
- **Cluster Separation Check**: Discards points that fall within a specified proximity ratio between two or more clusters.
- **User Interaction**: Prompts the user to input point coordinates for clustering.

---

## Input Structure
- The first three points provided define the initial centers of the clusters.
- The subsequent points are assigned to the closest cluster unless proximity constraints are violated.

### Example Input
```plaintext
3.0 4.0  # First point for Cluster 1
1.0 2.0  # First point for Cluster 2
5.0 6.0  # First point for Cluster 3
2.5 3.5  # Additional points
4.5 5.5
...
```

---

## Output Structure
The program outputs:
1. Messages indicating which cluster each point was included in or if it was discarded.
2. Final coordinates of cluster centers and the total number of points in each cluster.

### Example Output
```plaintext
Point (2.5, 3.5) included in Cluster 1
Point (4.5, 5.5) included in Cluster 3
...
Final Cluster 1: (x: 2.75, y: 3.75) with 2 points
Final Cluster 2: (x: 1.0, y: 2.0) with 1 points
Final Cluster 3: (x: 4.75, y: 5.75) with 2 points
```

---

## Code Components

1. **`calculate` Function**
   - Computes the Euclidean distance between two points.
   - Formula: \( \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2} \).

2. **`absolute` Function**
   - Computes the absolute value of a number.

3. **`main` Function**
   - Handles input, distance calculations, cluster assignments, and center updates.
   - Contains the loop for processing additional points.

---

## Proximity Constraint
The program uses a proximity ratio \( X \) to prevent points from being ambiguously assigned. If the relative difference between distances to two clusters is less than \( X \), the point is discarded.

### Example
For \( X = 0.001 \):
```plaintext
|distance_1 - distance_2| / ((distance_1 + distance_2) / 2) <= 0.001
```

---

## Constants
- **`N`**: Total number of points to process (including initial cluster centers).
- **`X`**: Proximity ratio for discarding points.
- **`EPSILON`**: Small value to handle numerical precision issues.

---

## Compilation and Execution

### Compilation
Compile the program using a C compiler:
```bash
gcc cluster_program.c -o cluster_program -lm
```

### Execution
Run the executable and follow the prompts to enter point coordinates:
```bash
./cluster_program
```

---

## Limitations
- Assumes valid numeric input for all point coordinates.
- Fixed to three clusters; cannot dynamically change the number of clusters.
- Requires exactly three points for initial cluster definition.
- No error handling for invalid inputs or edge cases.

---

## Future Improvements
- Allow dynamic cluster count based on user input.
- Add file input/output for large datasets.
- Implement visualizations of clusters and their updates.
- Enhance error handling for invalid or malformed inputs.

---

## License
This program is open-source and available under the MIT License.


