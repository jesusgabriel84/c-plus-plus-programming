#include "restricted_ptr.hpp"
#include "car.hpp"
#include <iostream>

int main(void) {
	RestrictedPtr<Car> new_car(new Car(0, "Ferrari"));

	// should print "Ferrari"
	std::cout << new_car.GetPointer()->GetName() << std::endl;

	// should also print "Ferrari"
	std::cout << new_car.GetData().GetName() << std::endl;
	
	new_car.GetData().score_ = 50;
	
	// should printf "50", as it was just assigned before
	std::cout << new_car.GetPointer()->score_ << std::endl;

	// make some copies
	RestrictedPtr<Car> copy_of_new_car = new_car;
	RestrictedPtr<Car> copy_of_new_car2 = new_car;

	// this copy should fail
	RestrictedPtr<Car> copy_of_new_car3 = new_car;

	// should be nullptr
	std::cout << copy_of_new_car3.GetPointer() << std::endl;

	// should be something other than 0 and equal
	std::cout << "copy2 pointer: " << copy_of_new_car2.GetPointer() << " copy1 pointer: " << copy_of_new_car.GetPointer() << std::endl;
	copy_of_new_car2.GetData().score_ = 40;
	
	// should be 40 now	
	std::cout << new_car.GetPointer()->score_ << std::endl;
	RestrictedPtr<Car> copy_of_new_car4(new_car);
	
	// should be nullptr
	std::cout << copy_of_new_car4.GetPointer() << std::endl;
}
