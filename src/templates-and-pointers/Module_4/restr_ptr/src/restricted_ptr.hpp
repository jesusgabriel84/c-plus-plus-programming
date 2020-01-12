#include "restricted_ref_counter.hpp"

/*
	Implement a class RestrictedPtr that holds a pointer of any type with at least the following members:
		- default constructor (takes no parameters)
		- constructor with a raw pointer parameter
		- copy constructor
		- destructor
		- copy assignment operator
		- function GetData that takes no parameters and returns the data the raw pointer refers to.
			The data returned should be such that modifying it modifies the data the pointer refers to.
		- function GetPointer that takes no parameters and returns the raw pointer
		- function GetRefCount that takes no parameters and returns an int with the reference count
	
	At any time the objects should keep track of how many references there are to a pointer
	and not allow more than 3 references. If the reference count drops to 0, the referenced
	pointer's memory should be released. If the reference count is already 3 when copying,
	the copier should set it's pointer to nullptr and reference count to 1.
	NOTE: GetPointer, GetData and GetRefCount are needed for the tests to run
*/

		
// Class representing a shared pointer 
template <typename T> 
  
class RestrictedPtr { 
public: 
    
	RestrictedPtr()
	{
		m_ptr = nullptr;
		m_counter = new RestrictedRefCounter();
		m_counter->Increment();
	}
    

    // Constructor 
    RestrictedPtr(T* ptr) 
    { 
        m_ptr = ptr; 
        m_counter = new RestrictedRefCounter(); 
        //if (ptr) { 
            m_counter->Increment();
        //} 
    } 
  
    // Copy constructor 
    RestrictedPtr(RestrictedPtr<T>& sp) 
    { 
        if(sp.m_counter->GetCount() < 3)
    	{
	        m_ptr = sp.m_ptr; 
	        m_counter = sp.m_counter; 
	        m_counter->Increment();
	    }
	    else
	    {
	    	m_ptr = nullptr;
			m_counter = new RestrictedRefCounter();
			m_counter->Increment();
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
    	    m_counter = sp.m_counter; 
    	    m_counter->Increment();
    	    return *this;
    	}

    	if(sp.m_counter->GetCount() < 3)
    	{
    		m_ptr = sp.m_ptr; 
    	    m_counter = sp.m_counter; 
    	    m_counter->Increment();
    	    return *this;
    	}
    	else
	    {
	    	m_ptr = nullptr;
			m_counter = new RestrictedRefCounter();
			m_counter->Increment();
			return *this;

	    }
    }

    // Reference count 
    unsigned int GetRefCount() 
    { 
        return m_counter->GetCount(); 
    } 
  
    // Get the pointer 
    T* GetPointer() 
    { 
        return m_ptr; 
    } 

    // Get the pointer data
    T& GetData() 
    { 
        return *m_ptr; 
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
}; 
