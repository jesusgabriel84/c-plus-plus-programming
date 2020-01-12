#include <iosfwd>
#include <map>
#include <iostream>
#include <sstream>
#include <string>

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
    int GetSize() {return values_.size();}

    
private:
    Values values_;
};

int Poly::operator[](int exp) const {
    Values::const_iterator it = values_.find(exp);
    return it == values_.end() ? 0 : it->second;
}


int GetDegree(const Poly& a)
{
	return a.begin()->first;
}

Poly operator+(const Poly& a, const Poly& b)
{
	Poly c;
	int degree_a = GetDegree(a);
	int degree_b = GetDegree(b);

	if(degree_a > degree_b)
	{
		for(int i = 0; i <= degree_a; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] + b[i];
			}
			
		}
	}
	else
	{
		for(int i = 0; i <= degree_b; i++)
		{
			if(a[i] != 0 || b[i] != 0)
			{
				c[i] = a[i] + b[i];
			}
		}
	}
	/*auto it_a = a.begin();
	auto it_b = b.begin();
	
	int degree_a = it_a-> first;
	int degree_b = it_b-> first;*/

	std::cout << "Deg A: " << degree_a << std::endl;
	std::cout << "Deg B: " << degree_b << std::endl;
	std::cout << "a[degree_a]: " << a[degree_a] << std::endl;
	std::cout << "b[degree_b]: " << b[degree_b] << std::endl;

	std::cout << "c[degree_a]: " << c[degree_a] << std::endl;
	std::cout << "Size: " << c.GetSize() << std::endl;

	return c;
}



std::ostream& operator<<(std::ostream& os, const Poly& p)
{
	auto it = p.begin();
    for(; it != p.end(); it++)
    {
    	if(it == p.begin())
    	{
    		os << it->second << "x" << it->first;
    	}
    	else
    	{
    		if(it->second < 0)
    		{
    			os << it->second << "x" << it->first;
    		}
    		else
    		{
    			os << "+" << it->second << "x" << it->first;
    		}
    	}
    	
    }
    return os;
}



int main()
{
	std::map<int, int> Values;
	Values[3] = 1;
	Values[10] = 3;
	Values[2] = 4;
	Values[1] = 2;
	std::cout << Values[10] << std::endl;
	std::cout << "size: " << Values.size() << std::endl;


	
	Poly p1;
	p1[30] = -5;
    p1[0] = -5;
    p1[20] = 20;
    p1[10] = 7;
    p1[3] = 3;
    p1[4] = 4;
    const Poly& pref = p1;
    std::cout << "PRINTING POLYNOMIAL" << std::endl;
    auto it = p1.begin();
    std::cout << "Exp: " << it->first << " | Mul: " << it->second << std::endl;
    /*for(; it != p1.end(); it++)
    {
    	std::cout << "Exp: " << it->first << " | Mul: " << it->second << std::endl;
    }*/


	Poly p2;
	p2[30] = -5;
    p2[0] = -5;
    p2[20] = 20;
    p2[102] = 7;
    p2[3] = 3;
    p2[4] = 4;

    Poly p3 = p1 + p2;

    std::cout << "P3 SIZE: " << p3.GetSize() << std::endl;
    
    
    for(auto it3 = p3.begin(); it3 != p3.end(); it3++)
    {
    	std::cout << "NEW POLY!!!! Exp: " << it3->first << " | Mul: " << it3->second << std::endl;
    }

    std::cout << p3 << std::endl;

    std::cout << "DEGREE: " << GetDegree(p3) << std::endl;

    std::string str = "+123";
    int number = std::stoi(str);
    std::cout << "Number: " << number + 1<< std::endl;
}
