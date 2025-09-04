#include "lsh.hpp"     // include your header
#include <eigen3/Eigen/Dense>

//to run move to src then use "g++ -std=c++11 lsh_test.cpp -I /usr/include/eigen3 -o test_lsh"
// then "./test_lsh"

int main() {
    // Parameters
    int numTables = 2;
    int numHashes = 4;
    int dimension = 3;

    // Create LSH object
    diskann::LSH lsh(numTables, numHashes, dimension);

    // Example points
    Eigen::VectorXd p1(dimension);
    p1 << 1.0, 2.0, 3.0;

    Eigen::VectorXd p2(dimension);
    p2 << 0.5, -1.0, 2.5;

    // Add points
    lsh.add(p1, 101);
    lsh.add(p2, 102);

    // Query
    Eigen::VectorXd q(dimension);
    q << 1.1, 2.1, 3.1;

    std::vector<int> result = lsh.query(q);

    std::cout << "Query returned IDs: ";
    for (int id : result) std::cout << id << " ";
    std::cout << std::endl;

    return 0;
}
