#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include <gcheck.h>
#include "../src/restricted_ptr.hpp"
#include "car.hpp"

PREREQ_TEST(RestrictedPtr, constructors_getters, 2, 0) {
    
    RestrictedPtr<double> restr_ptr;
    EXPECT_EQ(nullptr, restr_ptr.GetPointer()) << "default constructor";
    EXPECT_EQ(1, restr_ptr.GetRefCount()) << "default constructor";
    
    int* raw_pointer = new int;
    RestrictedPtr restr_ptr2(raw_pointer);
    EXPECT_EQ(raw_pointer, restr_ptr2.GetPointer()) << "raw pointer constructor";
    EXPECT_EQ(1, restr_ptr2.GetRefCount()) << "raw pointer constructor";
}

PREREQ_TEST(RestrictedPtr, copy_assignment_constructor, 4, 1) {
    GradingMethod(gcheck::AllOrNothing);
    int* raw_pointer = new int;
    RestrictedPtr ptr(raw_pointer);
    
    RestrictedPtr ptr_first_copy(ptr);
    EXPECT_EQ(raw_pointer, ptr_first_copy.GetPointer()) << "copy constructor; after one copy";
    EXPECT_EQ(2, ptr.GetRefCount()) << "default constructor; after one copy";
    EXPECT_EQ(2, ptr_first_copy.GetRefCount()) << "copy constructor; after one copy";
    
    RestrictedPtr<int> ptr_second_copy(nullptr);
    ptr_second_copy = ptr_first_copy;
    EXPECT_EQ(raw_pointer, ptr_second_copy.GetPointer()) << "copy assignment; after two copies";
    EXPECT_EQ(raw_pointer, ptr_first_copy.GetPointer()) << "copy constructor; after two copies";
    EXPECT_EQ(3, ptr.GetRefCount()) << "default constructor; after two copies";
    EXPECT_EQ(3, ptr_first_copy.GetRefCount()) << "copy constructor; after two copies";
    EXPECT_EQ(3, ptr_second_copy.GetRefCount()) << "copy assignment; after two copies";
    
    RestrictedPtr ptr_third_copy(ptr_second_copy);
    EXPECT_EQ(nullptr, ptr_third_copy.GetPointer()) << "copy constructor; after three copies";
    EXPECT_EQ(1, ptr_third_copy.GetRefCount()) << "copy constructor; after three copies";
    EXPECT_EQ(raw_pointer, ptr_second_copy.GetPointer()) << "copy assignment; after three copies";
    EXPECT_EQ(3, ptr_second_copy.GetRefCount()) << "copy assignment; after three copies";
}

class DeleteTester {
public:
	DeleteTester() {}
	void operator delete(void* p, size_t) { if(p != nullptr) static_cast<DeleteTester*>(p)->was_deleted_ = true; }
	void ActualDelete() { ::delete this; }
    bool WasDeleted() { return was_deleted_; }


private:
	bool was_deleted_ = false;
};
TEST_(RestrictedPtr, destruct, 1) {
    GradingMethod(gcheck::AllOrNothing);
    DeleteTester* p = new DeleteTester;
    {
        RestrictedPtr ptr(p);
        EXPECT_EQ(1, ptr.GetRefCount()) << "construct";
        {
            RestrictedPtr ptr2(ptr);
            EXPECT_EQ(2, ptr.GetRefCount()) << "construct -> copy";
        }
        EXPECT_EQ(1, ptr.GetRefCount()) << "construct -> copy -> destruct";
        {
            RestrictedPtr ptr3(ptr);
            RestrictedPtr ptr4(ptr);
            RestrictedPtr ptr5(ptr);
            EXPECT_EQ(3, ptr.GetRefCount()) << "construct -> copy -> destruct -> 3x copy";
        }
        EXPECT_EQ(1, ptr.GetRefCount()) << "construct -> copy -> destruct -> 3x copy -> 2x destruct";
        ExpectFalse(p->WasDeleted(), "Memory has been released") << "Reference count isn't 0: pointer's memory shouldn't be released yet";
    }
    ExpectTrue(p->WasDeleted(), "Memory has been released") << "Reference count is 0: pointer's memory should be released";
    p->ActualDelete();
}
