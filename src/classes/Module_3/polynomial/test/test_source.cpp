#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

#include <gcheck.h>
#include <argument.h>
#include "../src/poly.hpp"

// variables for tests

gcheck::SequenceArgument<std::vector<int>> seq({ {}, {1}, {1, 2}, {5, 3, 3, -2}, {0, 5, -10, 15, 20}, 
    });
gcheck::SequenceArgument<std::vector<int>> seq2({ {1, -4}, {0, 5, -2}, {1, 2}, {1, -3, 3, -2}, {4, 5, -1, 5}, 
    });

class Wrapper {
public:
    std::vector<int> vector_;

    Wrapper(const Poly& p) {
        for(auto it = p.begin(); it != p.end(); it++) {
            if(vector_.size() < (unsigned)it->first+1)
                vector_.resize(it->first+1, 0);
            vector_[it->first] = it->second;
        }
    }
    Wrapper(const std::vector<int>& v) : vector_(v) {}
    
    bool operator==(const Poly& p) const {
        
        int non_zeros = 0;
        for(auto& i : vector_) {
            if(i != 0) non_zeros++;
        }
        
        int non_zeros_p = 0;
        for(auto& i : p) {
            size_t index = i.first;
            if(i.second != 0) {
                non_zeros_p++;
                if(index >= vector_.size() || vector_[index] != i.second)
                    return false;
            }
        }
        return non_zeros == non_zeros_p;
    }
};


bool operator==(const Poly& p, const Wrapper& w) {
    return w == p;
}
std::string to_string(const Wrapper& w) {
    std::string out;
    
    const std::vector<int>& v = w.vector_;
    
    for(int i = v.size()-1; i >= 0; i--) {
        if(i != 0) {
            out += v[i] > 0 ? " +" : " ";
        }
        out += std::to_string(v[i]);
        out += "x^";
        out += std::to_string(i);
    }
    
    return out;
}

Poly MakePoly(const std::vector<int>& v, int mult = 1) {
    Poly p;
    for(unsigned i = 0; i < v.size(); i++)
        p[i] = v[i] * mult;
    return p;
}


Poly TNegate(const std::vector<int>& v) {
    return -MakePoly(v, -1);
}

TEST(Poly, negate) {
    seq.Reset();
    {
        std::vector correct_not_reserved = {Wrapper(std::vector<int>({})),Wrapper(std::vector<int>({1})),Wrapper(std::vector<int>({1,2})),Wrapper(std::vector<int>({5,3,3,-2})),Wrapper(std::vector<int>({0,5,-10,15,20}))};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        TestCase(seq.GetSize(),correct_not_reserved,TNegate,inputs_not_reserved0);
    };
}

Poly TAdd(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) + MakePoly(v2);
}   

TEST(Poly, add) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {Wrapper(std::vector<int>({1,-4})),Wrapper(std::vector<int>({1,5,-2})),Wrapper(std::vector<int>({2,4})),Wrapper(std::vector<int>({6,0,6,-4})),Wrapper(std::vector<int>({4,10,-11,20,20}))};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TAdd,inputs_not_reserved0,inputs_not_reserved1);
    };
}

Poly TSubstract(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) - MakePoly(v2);
}   

TEST(Poly, substract) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {Wrapper(std::vector<int>({-1,4})),Wrapper(std::vector<int>({1,-5,2})),Wrapper(std::vector<int>({0,0})),Wrapper(std::vector<int>({4,6,0,0})),Wrapper(std::vector<int>({-4,0,-9,10,20}))};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TSubstract,inputs_not_reserved0,inputs_not_reserved1);
    };
}

bool TEqual(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) == MakePoly(v2);
}   

TEST(Poly, equal) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {false,false,true,true,false};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TEqual,inputs_not_reserved0,inputs_not_reserved1);
    };
}

bool TNEqual(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) != MakePoly(v2);
}   

TEST(Poly, not_equal) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {true,true,false,false,true};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TNEqual,inputs_not_reserved0,inputs_not_reserved1);
    };
}

bool TSmaller(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) < MakePoly(v2);
}   

TEST(Poly, lesser_than) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {true,true,false,false,false};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TSmaller,inputs_not_reserved0,inputs_not_reserved1);
    };
}

bool TBigger(const std::vector<int>& v1, const std::vector<int>& v2) {
    return MakePoly(v1) > MakePoly(v2);
}   

TEST(Poly, greater_than) {
    seq.Reset();
    seq2.Reset();
    {
        std::vector correct_not_reserved = {false,false,false,false,true};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        gcheck::SequenceArgument inputs_not_reserved1({std::vector<int>({1, -4}),std::vector<int>({0, 5, -2}),std::vector<int>({1, 2}),std::vector<int>({1, -3, 3, -2}),std::vector<int>({4, 5, -1, 5})});
        TestCase(seq.GetSize(),correct_not_reserved,TBigger,inputs_not_reserved0,inputs_not_reserved1);
    };
}

std::string TWrite(const std::vector<int>& v) {
    std::stringstream ss;
    ss << MakePoly(v);
    return ss.str();
}

TEST(Poly, write_operator) {
    seq.Reset();
    {
        std::vector correct_not_reserved = {"","1x0","2x1+1x0","-2x3+3x2+3x1+5x0","20x4+15x3-10x2+5x1"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<int>({}),std::vector<int>({1}),std::vector<int>({1, 2}),std::vector<int>({5, 3, 3, -2}),std::vector<int>({0, 5, -10, 15, 20})});
        TestCase(seq.GetSize(),correct_not_reserved,TWrite,inputs_not_reserved0);
    };
}
Poly TRead(const std::string& str) {
    std::stringstream ss(str);
    Poly out;
    ss >> out;
    return out;
}


TEST(Poly, read_operator) {
    seq2.Reset();
    {
        std::vector correct_not_reserved = {Wrapper(std::vector<int>({1,-4})),Wrapper(std::vector<int>({0,5,-2})),Wrapper(std::vector<int>({1,2})),Wrapper(std::vector<int>({1,-3,3,-2})),Wrapper(std::vector<int>({4,5,-1,5}))};
        gcheck::SequenceArgument inputs_not_reserved0({std::string("-4x1+1x0"),std::string("-2x2+5x1"),std::string("2x1+1x0"),std::string("-2x3+3x2-3x1+1x0"),std::string("5x3-1x2+5x1+4x0")});
        TestCase(seq2.GetSize(),correct_not_reserved,TRead,inputs_not_reserved0);
    };
}
