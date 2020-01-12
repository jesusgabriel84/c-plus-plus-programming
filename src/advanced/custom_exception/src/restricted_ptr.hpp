//When a header is going to be forwarded or used several times, it is needed to 
//declare the guardians to avoid multiple definitions
//https://stackoverflow.com/questions/7919600/c-previous-definition-error

#ifndef AALTO_RESTRICTED_PTR
#define AALTO_RESTRICTED_PTR


#include "restricted_ref_counter.hpp"
//#include "restricted_ptr_ex.hpp"

/* TODO: the following
 *
 * Copy your implementation from the last round here (or wait for
 * the example answer to come out and copy that) and wrap it inside a 
 * WeirdMemoryAllocator namespace.
 * 
 * Changes to the class:
 * 
 * Add a new member string to store the use of the RestrictedPtr 
 * and add a new string parameter, which is the use of the pointer, to the 
 * constructor that originally only takes a pointer. Remember to modify
 * copying to also copy the use. If the pointer is automatically set to 
 * a nullptr (i.e. not given in the constructor), the use is "nullptr".
 * 
 * The copy constructor and assigment operators should throw a 
 * RestrictedCopyException with the use of the RestrictedPtr given to it. 
 * 
 * The GetData function should throw a RestrictedNullException with the use
 * of the RestrictedPtr given to it if the pointer is null.
 * 
 * The class shouldn't leak any memory.
*/


namespace WeirdMemoryAllocator
{		
// Class representing a shared pointer 
template <typename T> 
  
class RestrictedPtr { 
public: 
    
	RestrictedPtr(const std::string& use = "nullptr")
	
	{
		
        m_ptr = nullptr;
        m_counter = new RestrictedRefCounter();
        m_counter->Increment();
		use_ = use;
	}

    // Constructor 
    RestrictedPtr(T* ptr, const std::string& use) 
    { 
        m_ptr = ptr; 
        m_counter = new RestrictedRefCounter(); 
        //if (ptr) { 
            m_counter->Increment();
        //} 
        use_ = use;
    } 
  
    // Copy constructor 
    RestrictedPtr(RestrictedPtr<T>& sp) 
    { 
        if(sp.m_counter->GetCount() < 3)
    	{
	        
            m_ptr = sp.m_ptr; 
	        m_counter = sp.m_counter; 
	        m_counter->Increment();
	        use_ = sp.use_;
	    }
	    else
	    {
            /*m_ptr = nullptr;
			m_counter = new RestrictedRefCounter();
	    	m_counter->Increment();
	    	use_ = sp.use_;*/
	    	throw WeirdMemoryAllocator::RestrictedCopyException(sp.use_);
	    }

    } 
  
    //Copy assignment operator
    RestrictedPtr<T> &operator=(RestrictedPtr<T> &sp)
    {
    	

        if(m_counter->GetCount() == 1 && sp.m_counter->GetCount() < 3)
    	{
    		//In this case we need to call the destructor to release the memory already allocated for the raw pointer
    		//(because the count was already 1) and then we can copy the '&sp' pointer
    		this->~RestrictedPtr();
    		m_ptr = sp.m_ptr; 
            sp.m_counter->Increment();
    	    m_counter = sp.m_counter; 
    	    
    	    use_ = sp.use_;
    	    return *this;
    	}

    	if(sp.m_counter->GetCount() < 3)
    	{

            m_ptr = sp.m_ptr; 
            m_counter->Decrement();
    	    sp.m_counter->Increment();
            m_counter = sp.m_counter; 
    	    use_ = sp.use_;
    	    return *this;
    	}
    	else
	    {
			
            throw WeirdMemoryAllocator::RestrictedCopyException(use_);
	    }
    }

    // Reference count 
    unsigned int GetRefCount() 
    { 
        return m_counter->GetCount(); 
    } 

    //Get use
    std::string GetUse()
    {
        return use_;
    }
  
    // Get the pointer 
    T* GetPointer() const
    { 
        return m_ptr; 
    } 

    // Get the pointer data
    T& GetData() const
    { 
        if(m_ptr != nullptr)
        	return *m_ptr;
        else
        {
        	/*try
        	{
        		throw WeirdMemoryAllocator::RestrictedNullException(use_);
        	}
        	catch (WeirdMemoryAllocator::RestrictedPtrException &e) {
	    		std::cout << e.GetError() << std::endl;
	    		return *m_ptr;
			}*/
			throw WeirdMemoryAllocator::RestrictedNullException(use_);
        }
    }
  
    // Destructor 
    ~RestrictedPtr() 
    { 
        m_counter->Decrement(); 
        if (m_counter->GetCount() == 0) { 
            delete m_counter; 
            delete m_ptr; 
        }
    } 
  
private: 
    // Reference counter 
    RestrictedRefCounter* m_counter; 
  
    // Shared pointer 
    T* m_ptr; 

    //Variable containing use of the pointer
    std::string use_;
}; 

}

#endif