#include <iostream>
#include "matrix.hpp"

int main(void) {
    Matrix m;
    int n; 
    std::cout << "Give dimension for n x n matrix: " << std::endl;
    std::cin >> n;
    m = ReadMatrix(n);
    std::cout << "Rotating by 90 degrees!" << std::endl;
    m = Rotate90Deg(m);
    Print(m);

    return 0;
}
