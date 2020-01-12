#include "poly.hpp"
#include <iostream>
#include <sstream>

int main() {
    std::cout << "TEST 1:" << std::endl; {
        Poly p1;
        std::cout << "Default-constructed polynomial: " << p1 << "(should be empty)" << std::endl;
        p1[0] = -5;
        p1[2] = 20;
        p1[1] += 10;
        const Poly& pref = p1;
        std::cout << "After modifications: " << pref << ", should be\n                     20x2+10x1-5x0" << std::endl;
        Poly p2 = -pref;
        std::cout << "After negation: " << p2 << ", should be\n                -20x2-10x1+5x0" << std::endl;
    }
    /*std::cout << "TEST 2:" << std::endl; {
        Poly p1, p2;
        std::istringstream iss("20x2+10x1+5x0  -1x2+3x4+2x-34+5x2");
        if (iss >> p1 >> p2) {
            std::cout << "p1: " << p1 << ", should be\n    20x2+10x1+5x0" << std::endl;
            std::cout << "p2: " << p2 << ", should be\n    3x4+4x2+2x-34" << std::endl;
        } else std::cout << "Reading from stream failed (shouldn't have failed)" << std::endl;
        const Poly& p1ref = p1;
        const Poly& p2ref = p2;
        std::cout << "p1 + p2: " << p1ref + p2ref << ", should be\n         3x4+24x2+10x1+5x0+2x-34" << std::endl;
        std::cout << "p1 - p2: " << p1ref - p2ref << ", should be\n         -3x4+16x2+10x1+5x0-2x-34" << std::endl;
    }*/
    std::cout << "TEST 3:" << std::endl; {
        Poly p1;
        p1[2] = 20;
        p1[7] = 30;
        p1[-3] = 10;
        for (Poly::iterator it = p1.begin(); it != p1.end(); ++it) {
            if (it->second == 0) continue;
            ++it->second;
        }
        const Poly& p1ref = p1;
        for (Poly::const_iterator it = p1ref.begin(); it != p1ref.end(); ++it) {
            if (it->second == 0) continue;
            std::cout << "(" << it->first << "," << it->second << ")";
        }
        std::cout << ", should be\n(7,31)(2,21)(-3,11)" << std::endl;
    }
}

