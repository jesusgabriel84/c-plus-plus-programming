#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

#include <gcheck.h>
#include <redirectors.h>
#include "../src/restricted_ptr_ex.hpp"
#include "../src/restricted_interface.hpp"
#include "../src/restricted_ptr.hpp"

gcheck::Random rnd_int(4, 20);

std::string random_string(std::string::size_type length) {
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::default_random_engine rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while(length--)
        s += chrs[pick(rg)];

    return s;
}



PREREQ_TEST(RestrictedPtr, GetData_exception, 1, 0) {
    bool GetData_threw_with_non_nullptr = false;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> test_int(new int, "not null");
        test_int.GetData();
        WeirdMemoryAllocator::RestrictedPtr<double> test_double(new double, "not null");
        test_double.GetData();
    }
    catch(WeirdMemoryAllocator::RestrictedNullException& ex) {
        GetData_threw_with_non_nullptr = true;
    }
    EXPECT_FALSE(GetData_threw_with_non_nullptr) << "GetData shouldn't throw when the pointer is not null";
    
    bool GetData_threw_with_nullptr = false;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> test_int(nullptr, "null");
        test_int.GetData();
    }
    catch(WeirdMemoryAllocator::RestrictedNullException& ex) {
        GetData_threw_with_nullptr = true;
    }
    EXPECT_TRUE(GetData_threw_with_nullptr) << "GetData() should throw an exception when the raw pointer is nullptr.";
}


PREREQ_TEST(RestrictedPtr, copy_exception, 1, 0) {   
    bool copy_constructor_or_assignment_threw = false;
    WeirdMemoryAllocator::RestrictedPtr<int> test_int(new int, "Just testing storage of integer.");
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> i2(test_int);

        WeirdMemoryAllocator::RestrictedPtr<int> i3;

        i3 = i2;
    }
    catch(WeirdMemoryAllocator::RestrictedPtrException& ex) {
        copy_constructor_or_assignment_threw = true;
    }
    EXPECT_FALSE(copy_constructor_or_assignment_threw) << "Copy constructor or assignment operator threw an exception where it should have not";

    WeirdMemoryAllocator::RestrictedPtr<int> i2(test_int);
    WeirdMemoryAllocator::RestrictedPtr<int> i3;
    i3 = i2;

    bool copy_constructor_threw = false;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> i4(i2);
    }
    catch(WeirdMemoryAllocator::RestrictedCopyException& ex) {
        copy_constructor_threw = true;
    }
    EXPECT_TRUE(copy_constructor_threw) << "Copy constructor should throw at the 4th copy";
    
    bool copy_assignment_threw = false;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> i4;
        i4 = i3;
    }
    catch(WeirdMemoryAllocator::RestrictedCopyException& ex) {
        copy_assignment_threw = true;
    }
    EXPECT_TRUE(copy_assignment_threw) << "Copy assignment operator should throw at the 4th copy";
}

TEST(RestrictedCopyException, GetError) {
    GradingMethod(gcheck::AllOrNothing);

    std::string expect = random_string(6);

    std::string correct = expect + ": Too many copies of RestrictedPtr!";

    WeirdMemoryAllocator::RestrictedPtr<int> test_int(new int, expect);

    WeirdMemoryAllocator::RestrictedPtr<int> i2(test_int);

    WeirdMemoryAllocator::RestrictedPtr<int> i3;

    i3 = i2;

    std::string GetError_after_copy_construct;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> i4(i3);
    }
    catch(WeirdMemoryAllocator::RestrictedCopyException& ex) {
        GetError_after_copy_construct = ex.GetError();
    }
    EXPECT_EQ(correct, GetError_after_copy_construct) << "Testing GetError of RestrictedCopyException after copy constructor";
    
    std::string GetError_after_copy_assignment;
    try {
        WeirdMemoryAllocator::RestrictedPtr<int> i4 = i3;
    }
    catch(WeirdMemoryAllocator::RestrictedCopyException& ex) {
        GetError_after_copy_assignment = ex.GetError();
    }
    EXPECT_EQ(correct, GetError_after_copy_assignment) << "Testing GetError of RestrictedCopyException after copy assignment";
}

TEST(RestrictedPtrInterface, MakeRestricted) {
    GradingMethod(gcheck::AllOrNothing);
    int* tester = new int;

    *tester = rnd_int.Next();
    int correct_int = rnd_int();

    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr = MakeRestricted(tester);
    
    EXPECT_EQ(tester, test_ptr.GetPointer()) << "After MakeRestricted with the pointer 'tester'";
    EXPECT_EQ(correct_int, test_ptr.GetData()) << "After MakeRestricted with a pointer containing " << correct_int;

    std::string* another = new std::string;
    std::string correct = "test string" + random_string(3);
    *another = correct;

    std::string expectString = *another;

    WeirdMemoryAllocator::RestrictedPtr<std::string> test_ptr2 = MakeRestricted(another);

    EXPECT_EQ(another, test_ptr2.GetPointer()) << "After MakeRestricted with the pointer 'another'";
    EXPECT_EQ(correct, test_ptr2.GetData()) << "After MakeRestricted with a pointer containing the string: " << correct;
}


/*******/
TEST(RestrictedPtrInterface, CopyRestricted) {
    int* tester = new int;

    *tester = 6;

    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr(tester, "tester");

    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr2 = CopyRestricted(test_ptr);
    EXPECT_EQ(tester, test_ptr.GetPointer()) << "After CopyRestricted(test_ptr) with test_ptr containing the pointer 'tester'";
    EXPECT_EQ(tester, test_ptr2.GetPointer()) << "After CopyRestricted(test_ptr) with test_ptr containing the pointer 'tester'";

    // test that the 4th copy fails
    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr3(test_ptr);


    gcheck::StdoutCapturer tout;
    
    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr4 = CopyRestricted(test_ptr);

    std::string CopyRestricted_out = tout.str();

    std::string correct = "tester: Too many copies of RestrictedPtr!\n";

    EXPECT_EQ(correct, CopyRestricted_out) << "On the 4th copy";

}



/********/

TEST(RestrictedPtrInterface, write_operator) {
    int* tester = new int;
    int correct_int = rnd_int.Next();
    *tester = correct_int;

    WeirdMemoryAllocator::RestrictedPtr<int> test_ptr = MakeRestricted(tester);
    WeirdMemoryAllocator::RestrictedPtr<int> null_ptr;

    gcheck::StdoutCapturer tout;

    std::cout << test_ptr;
    std::cout << null_ptr;

    //read output from function
    std::string write_operator_out = tout.str();

    std::string correct = std::to_string(correct_int) + "\n"
        "nullptr: nullptr exception!\n";

    EXPECT_EQ(correct, write_operator_out) << "Output of writing two pointers; one not null and the other null";
}



