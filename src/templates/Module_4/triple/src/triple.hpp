/* Add include guards here */
#pragma once
#include <sstream>
#include <iostream>
#include <string>

/* Class: Triple
 * -------------
 * The template class Triple is a container class, which holds three values.
 * All of the values can be of different type. All of the values should be
 * private.
 *
 * The constructor of the class takes three const references to values as a
 * parameter. The parameters are in order, in other words, after construction
 * the first parameter should be accessible through the public member function
 * First, the second parameter through the public member function Second, and
 * the third through the public member function Third. 
 *
 * The default empty constructor should also work.
 *
 * The Triple class should also support the copy constructor, and assignment
 * operations.
 */


template <typename F, typename S, typename T>
class Triple
   {
      public:
               
               Triple() = default;
               Triple(const F&, const S&, const T&);
               Triple(const Triple &other);
               ~Triple();

               const Triple &operator=(const Triple &other);

               F First() const;
               S Second() const;
               T Third() const;

      private:
               F f;
               S s;
               T t;
   };

// 0-parameter constructor
/*template <typename F, typename S, typename T>
Triple<F,S,T>::Triple() { }*/


// 3-param constructor
template <typename F, typename S, typename T>
Triple<F,S,T>::Triple(const F& ff, const S& ss, const T& tt)
  : f(ff), s(ss), t(tt) { }


//copy constructor
template <typename F, typename S, typename T>
Triple<F,S,T>::Triple(const Triple &other)
  : f(other.First()), s(other.Second()), t(other.Third()) { }


//Copy operator
template <typename F, typename S, typename T>
const Triple<F,S,T>& Triple<F,S,T>::operator=(const Triple<F,S,T> &other)
{
    f = other.First();
    s = other.Second();
    t = other.Third();

    return *this;
}

//destructor
template <typename F, typename S, typename T>
Triple<F,S,T>::~Triple()
{

}

/* Public member functions:
 * ------------------------
 * The Triple class has three public member functions, which are used to
 * access the stored elements. All three should work with const instances
 * of Triple.
 *
 * Function: First
 * The function takes no parameters.
 * The function returns a const reference to the first value of the triple.
 *
 * Function: Second
 * The function takes no parameters.
 * The function returns a const reference to the second value of the triple.
 *
 * Function: Third
 * The function takes no parameters.
 * The function returns a const reference to the third value of the triple.
 */

// get first element in pointer
template <typename F, typename S, typename T>
F Triple<F,S,T>::First() const
   {
      return f;
   }


// get second element in pointer
template <typename F, typename S, typename T>
S Triple<F,S,T>::Second() const
   {
      return s;
   }


// get third element in pointer
template <typename F, typename S, typename T>
T Triple<F,S,T>::Third() const
   {
      return t;
   }

/* Non-member functions:
 * ---------------------
 * Function: IsHomogenous
 * The function is a non-member function that takes a Triple as a parameter.
 * The function returns a boolean value indicating whether the triple is
 * homogenous or not. A triple is homogenous if all of its three values are of
 * the same type.
 * Hint: specialisation can help you here.
 */
template <typename F, typename S, typename T>
bool IsHomogenous(const Triple<F,S,T> a)
{
	a.First();
	return false;
}

template <typename T>
bool IsHomogenous(const Triple<T,T,T> a)
{
	a.First();
	return true;
}

/* Operator overloads:
 * -------------------
 * The triple class should support the following operators:
 *
 * Assignment operator, =
 * The default functionality should do here.
 *
 * Equality operator, ==
 * You can assume that all the values in the triple can be compared by the
 * == -operator. Two triples are equal if the corresponding values in both
 * of the triples are equal.
 *
 * Inequality operator, !=
 * You can assume that all the values in the triple can be compared by the
 * != -operator. Two triples are inequal if even one corresponding value in
 * the triples is different.
 *
 * The output stream operator, <<
 * You can assume that all the values in the triple support the << -operator.
 * The triple should be printed to the output stream in the following format: 
[<first value>, <second value>, <third value>]
 * Note that there is NO new line at the end of the output.
 */

template <typename F, typename S, typename T>
bool operator==(const Triple<F,S,T>& a, const Triple<F,S,T>& b)
{
	if(a.First() == b.First())
		if(a.Second() == b.Second())
			if(a.Third() == b.Third())
				return true;

	return false;
}

template <typename F, typename S, typename T>
bool operator!=(const Triple<F,S,T>& a, const Triple<F,S,T>& b)
{
	if(a.First() != b.First())
		return true;

	if(a.Second() != b.Second())
		return true;

	if(a.Third() != b.Third())
		return true;

	return false;
}

template <typename F, typename S, typename T>
std::ostream& operator<<(std::ostream& os, const Triple<F,S,T>& a)
{
	os << "[" << a.First() << ", " << a.Second() << ", " << a.Third() << "]";
	return os;
}

/* Remember the endif here to close the header guards */

