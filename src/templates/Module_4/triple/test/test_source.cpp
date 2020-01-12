#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdexcept>

#include <gcheck.h>
#include "../src/triple.hpp"

gcheck::Random rnd_str({"Templates", "are", "fun", "reb00t", "coffee"});
gcheck::Random rnd_int(-100, 100);
gcheck::Random rnd_double(-100.0, 100.0);
gcheck::Random rnd_char('a', 'z');

PREREQ_TEST(Triple, construct_copy_assignment_access, 1, 0) {
    // Test the constructor
    std::vector<int> ints_(10);
    for(auto& i : ints_)
        i = rnd_int.Next();
    
    const auto& ints = ints_;
    
    double d1 = rnd_double.Next();
    char c1 = rnd_char.Next();
    
    Triple t1(ints[0], ints[1], ints[2]);
    const auto& rt1 = t1;

    Triple t2(ints[3], ints[4], ints[5]);
    const auto& rt2 = t2;

    Triple t3(ints[6], d1, c1);
    const auto& rt3 = t3;

    // Test the accessors
    EXPECT_EQ(ints[0], rt1.First());
    EXPECT_EQ(ints[1], rt1.Second());
    EXPECT_EQ(ints[2], rt1.Third());
    EXPECT_EQ(ints[3], rt2.First());
    EXPECT_EQ(ints[4], rt2.Second());
    EXPECT_EQ(ints[5], rt2.Third());
    EXPECT_EQ(ints[6], rt3.First());
    EXPECT_EQ(d1, rt3.Second());
    EXPECT_EQ(c1, rt3.Third());
    // Test the copy constructor
    Triple<int, int, int> ct1(rt1);
    Triple<int, int, int> ct2(rt2);
    Triple<int, double, char> ct3(rt3);
    EXPECT_EQ(ints[0], ct1.First());
    EXPECT_EQ(ints[1], ct1.Second());
    EXPECT_EQ(ints[2], ct1.Third());
    EXPECT_EQ(ints[3], ct2.First());
    EXPECT_EQ(ints[4], ct2.Second());
    EXPECT_EQ(ints[5], ct2.Third());
    EXPECT_EQ(ints[6], ct3.First());
    EXPECT_EQ(d1, ct3.Second());
    EXPECT_EQ(c1, ct3.Third());
    // Test the assignment operator
    Triple at1 = rt1;
    t2 = t2; // Self assignment
    Triple at3 = rt3;
    EXPECT_EQ(ints[0], at1.First());
    EXPECT_EQ(ints[1], at1.Second());
    EXPECT_EQ(ints[2], at1.Third());
    EXPECT_EQ(ints[6], at3.First());
    EXPECT_EQ(d1, at3.Second());
    EXPECT_EQ(c1, at3.Third());
    }

TEST(Triple, IsHomogenous) {
    std::vector<int> ints_(10);
    for(auto& i : ints_)
        i = rnd_int.Next();
    
    const auto& ints = ints_;
    
    double d1 = rnd_double.Next();
    char c1 = rnd_char.Next();
    
    Triple t1(ints[0], ints[1], ints[2]);
    const auto& rt1 = t1;

    Triple t2(ints[3], ints[4], ints[5]);
    const auto& rt2 = t2;

    Triple t3(ints[6], d1, c1);
    const auto& rt3 = t3;

    // Test the IsHomogenous function
    EXPECT_TRUE(IsHomogenous(rt1));
    EXPECT_TRUE(IsHomogenous(rt2));
    EXPECT_FALSE(IsHomogenous(rt3));
    }

TEST(Triple, test_eq_neq_print) {
    std::vector<int> ints_(11);
    for(auto& i : ints_)
        i = rnd_int.Next();
    
    const auto& ints = ints_;
    
    double d1 = rnd_double.Next();
    double d2 = rnd_double.Next();
    char c1 = rnd_char.Next();
    char c2 = rnd_char.Next();
    
    Triple t1(ints[0], ints[1], ints[2]);
    const auto& rt1 = t1;

    Triple t2(ints[3], ints[4], ints[5]);
    const auto& rt2 = t2;

    Triple t3(ints[6], d1, c1);
    const auto& rt3 = t3;

    Triple t4(ints[10], d2, c2);
    const auto& rt4 = t4;

    // Test the << -operator
    // use stringstream as output
    std::stringstream out;
    std::ostringstream c;
    std::string write_operator_out, correct;
    
    
    out << rt1 << std::endl;
    write_operator_out = out.str();

    c << "[" << ints[0] << "," << ints[1] << "," << ints[2] << "]" << std::endl;
    correct = c.str();
    EXPECT_EQ(correct, write_operator_out);
    
    c.str("");
    c.clear();
    out.str("");
    out.clear();
    
    
    out << rt2 << std::endl;
    write_operator_out = out.str();

    c << "[" << ints[3] << "," << ints[4] << "," << ints[5] << "]" << std::endl;
    correct = c.str();
    EXPECT_EQ(correct, write_operator_out);

    c.str("");
    c.clear();
    out.str("");
    out.clear();
    
    
    out << rt3 << std::endl;
    out << rt4 << std::endl;
    write_operator_out = out.str();

    c << "[" << ints[6] << "," << d1 << "," << c1 << "]" << std::endl;
    c << "[" << ints[10] << "," << d2 << "," << c2 << "]" << std::endl;
    correct = c.str();
    EXPECT_EQ(correct, write_operator_out);

    // Test the == -operator
    EXPECT_FALSE(rt1 == rt2);
    EXPECT_FALSE(rt3 == rt4);
    // Test the != -operator
    EXPECT_TRUE(rt1 != rt2);
    EXPECT_TRUE(rt3 != rt4);
    }

