import numpy as np
import random
from collections import defaultdict
#This code was used as concept for LSH. Unused and redundant rn
class LSH:
    def __init__(self, num_tables, num_hashes, dimension):
        """
        Initialize the LSH model with the required number o tables, hashes and vector
        agruments:
        - num_tables: The number of hash tables.
        - num_hashes: The number of random hyperplanes (hash functions) per table.
        - dimension: Dimension of vector inpusts.
        """

        self.num_tables = num_tables
        self.num_hashes = num_hashes
        self.dimension = dimension

        # Initialize the hash tables
        self.tables = [defaultdict(list) for _ in range(num_tables)]

        # Random hyperplanes for hashing
        self.hyperplanes = [
            np.random.randn(self.num_hashes, self.dimension) for _ in range(self.num_tables)
        ]

        print(f"[INIT] Created LSH with {num_tables} tables, "
              f"{num_hashes} hashes per table, dimension {dimension}")

    def _hash_function(self, point, hyperplane):
        """
        Hash the point based on a single set of random hyperplanes. 
        Each dimension of the hyperplane is multiplied with the vector,
        and the sign is taken (1 if above, 0 if below).
        """

        projection = np.dot(hyperplane, point)
        hash_value = tuple((projection > 0).astype(int)) #Binary hash
        print(f"    [HASH_FUNCTION] point={point} → projection={projection} → hash={hash_value}")
        return hash_value


    def _generate_hash(self, point):
        """
        Generate a hash for a point across all tables.
        """
        
        print(f"[GENERATE_HASH] Generating hash for point {point}")
        hashes = []
        for i in range(self.num_tables):
            hash_value = self._hash_function(point, self.hyperplanes[i])
            print(f"    [TABLE {i}] hash={hash_value}")            
            hashes.append(hash_value)
        return hashes

    def add(self, point, id_):
        """
        Add a pont to the LSH tables with an ID.
        """
        print(f"[ADD] Adding point {id_}: {point}")

        hash_value = self._generate_hash(point)
        for i in range(self.num_tables):
            self.tables[i][hash_value[i]].append(id_)
            print(f"    [TABLE {i}] Inserted {id_} into bucket {hash_value[i]}")


    def query(self, query_point):
        """
        Query the LSH tables to find the nearest neighbors
        """

        print(f"[QUERY] Querying for point {query_point}")

        candidate_ids = set()
        hash_value = self._generate_hash(query_point)

        # Look or similar items in the same hash bucket
        for i in range(self.num_tables):
            bucket_contents = self.tables[i][hash_value[i]]
            print(f"    [TABLE {i}] Bucket {hash_value[i]} contains {bucket_contents}")
            candidate_ids.update(bucket_contents)
        print(f"[QUERY_RESULT] Candidates found: {list(candidate_ids)}")

        return list(candidate_ids)