import numpy as np
from lsh import LSH  # assumes lsh.py is in the same folder

def main():
    # Step 1: Create an LSH instance
    lsh = LSH(num_tables=3, num_hashes=4, dimension=3)

    # Step 2: Define some 2D points
    points = {
        "A": np.array([1, 2, 0]),
        "B": np.array([2, 1, -6]),
        "C": np.array([-1, -2, -1]),
        "D": np.array([-2, -1, 4]),
    }

    # Step 3: Add points to LSH
    for label, point in points.items():
        print(f"Adding point {label}: {point}")
        lsh.add(point, label)

    # Step 4: Query
    query_point = np.array([1.5, 2, -1.4])
    print(f"\nQuerying with {query_point}")
    results = lsh.query(query_point)

    print(f"Candidate neighbors: {results}")

if __name__ == "__main__":
    main()
