#include "restricted_ptr_ex.hpp"
#include "restricted_interface.hpp"
#include <iostream>


int main(void) {
	int* tester = new int;

	*tester = 6;

	WeirdMemoryAllocator::RestrictedPtr<int> testi_ptr = MakeRestricted(tester);

	WeirdMemoryAllocator::RestrictedPtr<int> testi_ptr2 = CopyRestricted(testi_ptr);

	std::cout << "Next should print 6" << std::endl;
	std::cout << testi_ptr2.GetData() << std::endl;

	WeirdMemoryAllocator::RestrictedPtr<int> testi_ptr3 = CopyRestricted(testi_ptr);

	std::cout << "next should fail and print out: RestrictedPtr instance: Too many copies of RestrictedPtr!" << std::endl;

	WeirdMemoryAllocator::RestrictedPtr<int> testi_ptr4 = CopyRestricted(testi_ptr);

	// calling GetData with this null_ptr instance should throw a
	// RestrictedNullException
	WeirdMemoryAllocator::RestrictedPtr<int> null_ptr(nullptr, "nullptr instance");

	std::cout << "This should print out: nullptr instance: nullptr exception!" << std::endl;

	std::cout << null_ptr;

	return 0;
}