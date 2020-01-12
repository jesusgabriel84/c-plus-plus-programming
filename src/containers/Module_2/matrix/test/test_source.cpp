#include <string>
#include <cmath>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/matrix.hpp"

gcheck::RandomSizeContainer rnd({ 0, 1, 4, 9, 16, 25 }, 0, 9);
gcheck::SequenceArgument<std::vector<int>> seq(
    { { 0, 1, 2, 
        2, 3, 4, 
        2, 1, 1 },
      { 7, 5, 
        9, 0 },
      { 7, 1, 3, 5, 
        9, 2, 3, 2, 
        0, 2, 3, 8, 
        8, 4, 5, 6 },
    });

bool operator==(const Matrix& m1, const Matrix& m2) {
    if(m1.size() != m2.size())
        return false;
        
    for(auto it1 = m1.begin(), it2 = m2.begin(); it1 != m1.end(); it1++, it2++) {
        for(auto it12 = it1->begin(), it22 = it2->begin(); it12 != it1->end(); it12++, it22++) {
            if(*it12 != *it22)
                return false;
        }
    }
    return true;
}

Matrix TRead(std::pair<std::string, int> input) {
    
    gcheck::StdinInjecter tin(input.first);
    
    return ReadMatrix(input.second);
}

TEST_(test_matrix, test_read, 2.5) {
    seq.Reset();
    {
        std::vector correct_not_reserved = {std::vector<std::vector<int>>{std::vector<int>{0,1,2},std::vector<int>{2,3,4},std::vector<int>{2,1,1}},std::vector<std::vector<int>>{std::vector<int>{7,5},std::vector<int>{9,0}},std::vector<std::vector<int>>{std::vector<int>{7,1,3,5},std::vector<int>{9,2,3,2},std::vector<int>{0,2,3,8},std::vector<int>{8,4,5,6}}};
        gcheck::SequenceArgument inputs_not_reserved0({std::pair<std::string, int>("0 1 2 2 3 4 2 1 1\u000A",3),std::pair<std::string, int>("7 5 9 0\u000A",2),std::pair<std::string, int>("7 1 3 5 9 2 3 2 0 2 3 8 8 4 5 6\u000A",4)});
        TestCase(seq.GetSize(),correct_not_reserved,TRead,inputs_not_reserved0);
    };
}
TEST_(test_matrix, test_read_random, 5) {
    {
        std::vector correct_not_reserved = {std::vector<std::vector<int>>{std::vector<int>{0,6,0,0},std::vector<int>{0,1,3,1},std::vector<int>{3,5,3,3},std::vector<int>{6,9,3,0}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{4,0,9,1,6},std::vector<int>{1,8,6,5,4},std::vector<int>{7,2,1,8,3},std::vector<int>{6,6,9,0,3},std::vector<int>{1,5,2,3,4}},std::vector<std::vector<int>>{std::vector<int>{9,1,0,9,2},std::vector<int>{5,3,4,3,8},std::vector<int>{0,8,0,4,1},std::vector<int>{2,0,9,9,0},std::vector<int>{9,3,2,1,6}},std::vector<std::vector<int>>{std::vector<int>{6}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{2}},std::vector<std::vector<int>>{std::vector<int>{4,9,3},std::vector<int>{4,0,9},std::vector<int>{9,4,3}},std::vector<std::vector<int>>{std::vector<int>{8,2},std::vector<int>{0,0}},std::vector<std::vector<int>>{}};
        gcheck::SequenceArgument inputs_not_reserved0({std::pair<std::string, int>("0 6 0 0 0 1 3 1 3 5 3 3 6 9 3 0\u000A",4),std::pair<std::string, int>("\u000A",0),std::pair<std::string, int>("4 0 9 1 6 1 8 6 5 4 7 2 1 8 3 6 6 9 0 3 1 5 2 3 4\u000A",5),std::pair<std::string, int>("9 1 0 9 2 5 3 4 3 8 0 8 0 4 1 2 0 9 9 0 9 3 2 1 6\u000A",5),std::pair<std::string, int>("6\u000A",1),std::pair<std::string, int>("\u000A",0),std::pair<std::string, int>("2\u000A",1),std::pair<std::string, int>("4 9 3 4 0 9 9 4 3\u000A",3),std::pair<std::string, int>("8 2 0 0\u000A",2),std::pair<std::string, int>("\u000A",0)});
        TestCase(10,correct_not_reserved,TRead,inputs_not_reserved0);
    };
}


Matrix TRotate(Matrix input) {
    return Rotate90Deg(input);
}

TEST_(test_matrix, test_rotate, 2.5) {
    seq.Reset();
    {
        std::vector correct_not_reserved = {std::vector<std::vector<int>>{std::vector<int>{2,2,0},std::vector<int>{1,3,1},std::vector<int>{1,4,2}},std::vector<std::vector<int>>{std::vector<int>{9,7},std::vector<int>{0,5}},std::vector<std::vector<int>>{std::vector<int>{8,0,9,7},std::vector<int>{4,2,2,1},std::vector<int>{5,3,3,3},std::vector<int>{6,8,2,5}}};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<std::vector<int>>{std::vector<int>{0,1,2},std::vector<int>{2,3,4},std::vector<int>{2,1,1}},std::vector<std::vector<int>>{std::vector<int>{7,5},std::vector<int>{9,0}},std::vector<std::vector<int>>{std::vector<int>{7,1,3,5},std::vector<int>{9,2,3,2},std::vector<int>{0,2,3,8},std::vector<int>{8,4,5,6}}});
        TestCase(seq.GetSize(),correct_not_reserved,TRotate,inputs_not_reserved0);
    };
}
TEST_(test_matrix, test_rotate_random, 5) {
    {
        std::vector correct_not_reserved = {std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{5,4,0},std::vector<int>{0,1,2},std::vector<int>{2,8,9}},std::vector<std::vector<int>>{std::vector<int>{6,7,6,3,2},std::vector<int>{8,9,9,9,0},std::vector<int>{0,7,8,5,7},std::vector<int>{8,6,8,1,0},std::vector<int>{7,2,5,9,6}},std::vector<std::vector<int>>{std::vector<int>{4,2,3,3,7},std::vector<int>{1,8,4,5,7},std::vector<int>{0,8,0,0,0},std::vector<int>{1,9,1,2,3},std::vector<int>{9,3,7,5,4}},std::vector<std::vector<int>>{std::vector<int>{8,2,8,3,8},std::vector<int>{9,0,7,4,3},std::vector<int>{5,5,5,2,1},std::vector<int>{0,2,8,9,9},std::vector<int>{3,4,3,1,5}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{9,4,2,7,6},std::vector<int>{8,3,3,2,9},std::vector<int>{0,7,2,6,2},std::vector<int>{9,1,5,5,7},std::vector<int>{5,5,3,2,3}},std::vector<std::vector<int>>{}};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{0,2,9},std::vector<int>{4,1,8},std::vector<int>{5,0,2}},std::vector<std::vector<int>>{std::vector<int>{2,0,7,0,6},std::vector<int>{3,9,5,1,9},std::vector<int>{6,9,8,8,5},std::vector<int>{7,9,7,6,2},std::vector<int>{6,8,0,8,7}},std::vector<std::vector<int>>{std::vector<int>{7,7,0,3,4},std::vector<int>{3,5,0,2,5},std::vector<int>{3,4,0,1,7},std::vector<int>{2,8,8,9,3},std::vector<int>{4,1,0,1,9}},std::vector<std::vector<int>>{std::vector<int>{8,3,1,9,5},std::vector<int>{3,4,2,9,1},std::vector<int>{8,7,5,8,3},std::vector<int>{2,0,5,2,4},std::vector<int>{8,9,5,0,3}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{6,9,2,7,3},std::vector<int>{7,2,6,5,2},std::vector<int>{2,3,2,5,3},std::vector<int>{4,3,7,1,5},std::vector<int>{9,8,0,9,5}},std::vector<std::vector<int>>{}});
        TestCase(10,correct_not_reserved,TRotate,inputs_not_reserved0);
    };
}



gcheck::Result<std::string> TPrint(Matrix input) {
    gcheck::StdoutCapturer tout;
    
    Print(input);
    
    return tout.str();
}

TEST_(test_matrix, test_print, 2) {
    seq.Reset();
    {
        std::vector correct_not_reserved = {"Printing out a 3 x 3 matrix:\n0 1 2 \n2 3 4 \n2 1 1 \n","Printing out a 2 x 2 matrix:\n7 5 \n9 0 \n","Printing out a 4 x 4 matrix:\n7 1 3 5 \n9 2 3 2 \n0 2 3 8 \n8 4 5 6 \n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<std::vector<int>>{std::vector<int>{0,1,2},std::vector<int>{2,3,4},std::vector<int>{2,1,1}},std::vector<std::vector<int>>{std::vector<int>{7,5},std::vector<int>{9,0}},std::vector<std::vector<int>>{std::vector<int>{7,1,3,5},std::vector<int>{9,2,3,2},std::vector<int>{0,2,3,8},std::vector<int>{8,4,5,6}}});
        TestCase(seq.GetSize(),correct_not_reserved,TPrint,inputs_not_reserved0);
    };
}
TEST_(test_matrix, test_print_random, 3) {
    {
        std::vector correct_not_reserved = {"Printing out a 3 x 3 matrix:\n4 0 1 \n7 7 9 \n7 6 4 \n","Printing out a 2 x 2 matrix:\n5 9 \n5 6 \n","Printing out a 1 x 1 matrix:\n0 \n","Printing out a 0 x 0 matrix:\n","Printing out a 3 x 3 matrix:\n0 2 9 \n6 0 0 \n0 0 3 \n","Printing out a 0 x 0 matrix:\n","Printing out a 5 x 5 matrix:\n7 4 2 7 4 \n2 9 9 2 7 \n5 6 4 7 7 \n5 0 7 1 0 \n4 5 7 7 9 \n","Printing out a 1 x 1 matrix:\n4 \n","Printing out a 0 x 0 matrix:\n","Printing out a 0 x 0 matrix:\n"};
        gcheck::SequenceArgument inputs_not_reserved0({std::vector<std::vector<int>>{std::vector<int>{4,0,1},std::vector<int>{7,7,9},std::vector<int>{7,6,4}},std::vector<std::vector<int>>{std::vector<int>{5,9},std::vector<int>{5,6}},std::vector<std::vector<int>>{std::vector<int>{0}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{0,2,9},std::vector<int>{6,0,0},std::vector<int>{0,0,3}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{std::vector<int>{7,4,2,7,4},std::vector<int>{2,9,9,2,7},std::vector<int>{5,6,4,7,7},std::vector<int>{5,0,7,1,0},std::vector<int>{4,5,7,7,9}},std::vector<std::vector<int>>{std::vector<int>{4}},std::vector<std::vector<int>>{},std::vector<std::vector<int>>{}});
        TestCase(10,correct_not_reserved,TPrint,inputs_not_reserved0);
    };
}