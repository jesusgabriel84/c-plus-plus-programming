#ifndef ELEC_AS_CPP_POLY
#define ELEC_AS_CPP_POLY

#include <iosfwd>
#include <map>

/* Polynomial is a mathematical expression consisting of terms summed to each-other. 
 * In this exercise you will implement class Poly, holding a single polynomial 
 * where each term is of form <mul>x<exp>. 
 * For example, the parabola 4x²+2x+7 would be stored in the Poly object as 
 * std::map<int, int> of pairs of exponent and multiplier: (2, 4), (1, 2), (0, 7).
 * 
 * Before starting, make yourself familiar with operator overloading. 
 * Then implement for your class the following accessors and operators, 
 * and test your implementation with the given main.
 *
 * 
 * Implement:
 *
 * Negation operator (unary operator-) that changes the sign of the multiplier of each term.
 *
 * Binary (two-operand) operators +, -, += and -= that do the corresponding mathematical operations 
 * (adding/subtracting the multipliers termwise)
 *
 * operator<<, using the format described below.
 *
 * A few operators have been implemented for you in poly.hpp and poly.cpp. 
 * Add the missing operators but do not modify the existing ones. 
 *
 *
 * Stream I/O format
 *
 * A simplified format where each term is of format <mul>x<exp> is used. 
 * Between each term there must be a plus or a minus sign depending on the sign of the multiplier of the next term. 
 * For example, 4x²+2x+7 would be written 4x2+2x1+7x0 and -7x^-2 would be written as -7x-2.
 *
 * The output operator must normalize the output by printing the terms with descending order (highest exponent first) 
 * and by omitting all terms where the multiplier is zero. 
 * Nothing is printed if there are no non-zero terms in the polynomial.
 *
 * Ordering
 *
 * In this exercise the degree (the exponent of the first non-zero term) of the polynomial alone determines the order for the comparison operators. 
 * Multipliers or other terms have no effect. E.g. 3x² is considered equal to 1000x²+123x and x³ is considered greater than any of the two others. 
 * An empty polynomial is less than any non-empty polynomial.
 */

/* recommended order for implementing:
 * 1. Unary operator-
 * 2. Binary operators: operator+= & operator+
 * 3. operator-= & operator-
 * 4. Operators for comparisons.
 */


class Poly {
public:
    typedef std::map<int, int> Values;
    typedef Values::const_reverse_iterator const_iterator;
    typedef Values::reverse_iterator iterator;
    
    const_iterator begin() const { return values_.rbegin(); }
    const_iterator end() const { return values_.rend(); }
    iterator begin() { return values_.rbegin(); }
    iterator end() { return values_.rend(); }
    
    int operator[](int exp) const;
    int& operator[](int exp) { return values_[exp]; }
    
    // TODO: implement the following operators
    Poly& operator+=(const Poly& b);
    Poly& operator-=(const Poly& b);
private:
    Values values_;
};

// TODO: implement all of the following
std::istream& operator>>(std::istream& is, Poly& p);
std::ostream& operator<<(std::ostream& os, const Poly& p);

Poly operator+(const Poly& a, const Poly& b);
Poly operator-(const Poly& a, const Poly& b);
Poly operator-(const Poly& p); //Unary operator

bool operator<(const Poly& a, const Poly& b);
bool operator==(const Poly& a, const Poly& b);
bool operator>(const Poly& a, const Poly& b);
bool operator!=(const Poly& a, const Poly& b);

#endif

