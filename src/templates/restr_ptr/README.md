**Objective:** Learn to implement your own kind of smart pointers.
Templates become more familiar again.

In this exercise you should implement a generic smart pointer of your own.
Your  smart pointer class should be called *RestrictedPtr*, and it should
be able to  contain a pointer to any any type of data (use a template!).
There is a little  twist in this restricted pointer compared to the
traditional shared pointer, as  **its reference count can be only 3 or
less**. This means there may be at most 3 copies of a RestrictedPtr
pointing to the same memory address.

**The RestrictedPtr should have:**

 - Constructor for a case when no parameters are given, and 
 - Constructor for a case when a raw pointer is given as a parameter. In
this  case the constructor should obviously store the given pointer into
this instance.
 - Copy constructor. This should make a copy of another *RestrictedPtr* and
its raw pointer should point to the same memory location as the instance
it was copied from. If there are already 3 or more copies of that
instance, this copied instance's raw pointer will point to *nullptr* and
the reference count of this  instance will be set to 1.
 - Destructor. If the reference count of this instance drops to 0, the
destructor should release the memory allocated to the raw pointer.
 - Copy assignment. This is basically the same as with the copy
constructor, but for copy assignment there might also be a situation when an already
initialized  RestrictedPtr is assigned to another RestrictedPtr, and the
assigned instance's  reference count is 1 (it is the only copy of
RestrictedPtr pointing to that address). Because of this the copy
assignment should also release the memory allocated to the raw pointer in
that situation.

**The RestrictedPtr should also have the methods**

 - *GetData()* should return the data where the instance's raw pointer 
 points to. This returned data/type should be modifiable.
 - *GetPointer()* should return the raw pointer of this instance.
 - *GetRefCount()* should return the number of RestrictedPtrs that contain the
 same raw pointer.


**Compile and run:**
```bash
#In the folder src/classes/register
make
cd src
./main
```