#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <tuple>
#include <functional>
#include <set>
#include <Eigen/Dense>

//Hash key type is vector<int> representing a binary hash
using HashKey = std::vector<int>;

namespace diskann
{
    struct HashKeyHash {
        std::size_t operator()(const HashKey& key) const {
            std::size_t h = 0;
            for (int bit : key) {
                h = (h << 1) ^ std::hash<int>()(bit);
            }
            return h;
        }
    };

    struct HashKeyEq {
        bool operator()(const HashKey& a, const HashKey& b) const {
            return a == b;
        }
    };

    class LSH {
    private:
        int numTables;
        int numHashes;
        int dimension;

        //For each table create a map from the hash key to a list of ids
        std::vector<std::unordered_map<HashKey, std::vector<int>, HashKeyHash, HashKeyEq>> tables;
        
        //Hyperplanes: One matix per table (numHashes * dimension)
        std::vector<Eigen::MatrixXd> hyperplanes;

    };
}