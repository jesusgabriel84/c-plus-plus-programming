#include <vector>
#include <string>
#include <iostream>
#include <ctime>

#include "triple.hpp"

int main() {
    // Seed the random
    srand(time(0));

    std::vector<std::string> strings = {"Templates", "are", "fun", "reb00t", "coffee"};
    // Test constructor, copy, assignment, accessors and IsHomogenous functions
    {
        // Test the constructor
        std::cout << "*** Creating different kind of triples.." << std::endl;
        Triple<int, int, int> t1(rand()%5, rand()%5, rand()%5);
        const Triple<int, int, int>& rt1 = t1;

        Triple<int, int, int> t2(rand()%5, rand()%5, rand()%5);
        const Triple<int, int, int>& rt2 = t2;

        Triple<int, double, char> t3(rand()%5, ((double)((rand()%100)+10))/17.2, (char)((rand()%91)+33));
        const Triple<int, double, char>& rt3 = t3;

        // Test the accessors
        std::cout << "*** Testing the accessors (First, Second, and Third).." << std::endl;
        std::cout << "F: " << rt1.First() << " S: " << rt1.Second() << " T: " << rt1.Third() << std::endl;
        std::cout << "F: " << rt2.First() << " S: " << rt2.Second() << " T: " << rt2.Third() << std::endl;
        std::cout << "F: " << rt3.First() << " S: " << rt3.Second() << " T: " << rt3.Third() << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;

        // Test the copy constructor
        std::cout << "*** Testing the copy constructor.." << std::endl;
        Triple<int, int, int> ct1(rt1);
        Triple<int, int, int> ct2(rt2);
        Triple<int, double, char> ct3(rt3);

        std::cout << "F: " << ct1.First() << " S: " << ct1.Second() << " T: " << ct1.Third() << std::endl;
        std::cout << "F: " << ct2.First() << " S: " << ct2.Second() << " T: " << ct2.Third() << std::endl;
        std::cout << "F: " << ct3.First() << " S: " << ct3.Second() << " T: " << ct3.Third() << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;

        // Test the assignment operator
        std::cout << "*** Testing the assignment, = -operator.." << std::endl;
        Triple<int, int, int> at1 = rt1;
        t2 = t2; // Self assignment
        Triple<int, double, char> at3 = rt3;

        std::cout << "F: " << at1.First() << " S: " << at1.Second() << " T: " << at1.Third() << std::endl;
        std::cout << "F: " << t2.First() << " S: " << t2.Second() << " T: " << t2.Third() << std::endl;
        std::cout << "F: " << at3.First() << " S: " << at3.Second() << " T: " << at3.Third() << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;
        
        // Test the IsHomogenous function
        std::cout << "*** Testing your IsHomogenous function.." << std::endl;
        std::cout << "The IsHomogenous function returned: " << (IsHomogenous(rt1) ? "yes" : "no") << std::endl;
        std::cout << "The IsHomogenous function returned: " << (IsHomogenous(rt2) ? "yes" : "no") << std::endl;
        std::cout << "The IsHomogenous function returned: " << (IsHomogenous(rt3) ? "yes" : "no") << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;
    }
    {
        // Test the ==, !=, and << -operators
        std::cout << "*** Creating different kind of triples.." << std::endl;
        Triple<int, int, int> t1(rand()%5, rand()%5, rand()%5);
        const Triple<int, int, int>& rt1 = t1;

        Triple<int, int, int> t2(rand()%5, rand()%5, rand()%5);
        const Triple<int, int, int>& rt2 = t2;

        Triple<int, double, char> t3(rand()%5, ((double)((rand()%100)+10))/17.2, (char)((rand()%91)+33));
        const Triple<int, double, char>& rt3 = t3;
        Triple<int, double, char> t4(rand()%5, ((double)((rand()%100)+10))/17.2, (char)((rand()%91)+33));
        const Triple<int, double, char>& rt4 = t4;

        // Test the << -operator
        std::cout << "*** Printing the triples, using the << -operator.." << std::endl;
        std::cout << rt1 << std::endl;
        std::cout << rt2 << std::endl;
        std::cout << rt3 << std::endl;
        std::cout << rt4 << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;

        // Test the == -operator
        std::cout << "*** Testing the == -operator, comparing triples.." << std::endl;
        std::cout << "Are the triples equal: " << (rt1==rt2 ? "yes" : "no") << std::endl;
        std::cout << "Are the triples equal: " << (rt3==rt4 ? "yes" : "no") << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;

        // Test the != -operator
        std::cout << "*** Testing the != -operator, comparing triples.." << std::endl;
        std::cout << "Are the triples inequal: " << (rt1!=rt2 ? "yes" : "no") << std::endl;
        std::cout << "Are the triples inequal: " << (rt3!=rt4 ? "yes" : "no") << std::endl;
        std::cout << "*** END OF READ ***" << std::endl;
    }

    std::cout << "*** All done, exiting.." << std::endl;

    return 0;
}
