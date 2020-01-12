#include <iostream>
 
template<class T>
struct C
{
  void print() { std::cout << "I am generic\n"; }
};
 
// Specialization for T=int
template<>
struct C<int>
{
  void print() { std::cout << "I am specialized for int\n"; }
};
 
template<class T> 
void func();
 
// Specialization for T=double
template<>
void func<double>() { std::cout << "I am func<double>\n"; }
 
int main()
{
  C<double>  c1;
  C<int>     c2;
 
  c1.print();
  c2.print();
 
  func<double>();
  //  func<int>(); // Compile time error
                   // No definition for T=int
} // main