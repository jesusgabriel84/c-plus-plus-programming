#include "restricted_ptr.hpp"
//#include "restricted_ref_counter.hpp"

/* TODO:
 *
 * MakeRestricted: a template function that takes any type of
 * pointer as a parameter and returns a RestrictedPtr holding
 * that pointer with the use set to "RestrictedPtr instance".
 * 
 * CopyRestricted: a template function that takes a reference to
 * a RestrictedPtr as a parameter and returns a copy of it. If
 * the copying fails, prints the error in the exception to
 * standard output with a newline appended and returns a
 * default constructed RestrictedPtr.
 *
 * operator<<: a template function that takes in a ostream 
 * reference and a RestrictedPtr reference, prints the object
 * pointed to by the pointer to the stream using the << operator 
 * and returns a reference to the stream. If the pointer is null,
 * prints the return value of GetError of the exception thrown by 
 * GetData instead.
*/

template<class T>
WeirdMemoryAllocator::RestrictedPtr<T> MakeRestricted(T* ptr)
{
	WeirdMemoryAllocator::RestrictedPtr<T> new_ptr(ptr,"RestrictedPtr instance");
	return new_ptr;
}

template<class T>
WeirdMemoryAllocator::RestrictedPtr<T> CopyRestricted( WeirdMemoryAllocator::RestrictedPtr<T>& sp)
{
	
	if(sp.GetRefCount() < 3)
    {
	    WeirdMemoryAllocator::RestrictedPtr<T> new_ptr(sp);
	    return new_ptr;
	}
	else
	{
	 	try
	 	{
	   		throw WeirdMemoryAllocator::RestrictedCopyException(sp.GetUse());
	   	}
	   	catch (WeirdMemoryAllocator::RestrictedPtrException &e) {
	    		std::cout << e.GetError() << std::endl;
	    		WeirdMemoryAllocator::RestrictedPtr<T> new_ptr;
	    		return new_ptr;
		}
	}
}


//Remember to set the Get functions as const in order to make the compiler know 
//https://stackoverflow.com/questions/5973427/error-passing-xxx-as-this-argument-of-xxx-discards-qualifiers

template<class T>
std::ostream& operator<<(std::ostream& os, const WeirdMemoryAllocator::RestrictedPtr<T>& sp) 
{
	if(sp.GetPointer() != nullptr)
	{
		os << sp.GetData() << std::endl;
		return os;
	}
	else
	{
		try
        	{
        		throw WeirdMemoryAllocator::RestrictedNullException("nullptr");
        	}
        	catch (WeirdMemoryAllocator::RestrictedPtrException &e) {
	    		os << e.GetError() << std::endl;
	    		return os;
			}
	}
}