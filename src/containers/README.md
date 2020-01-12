## Containers
In this section we will see how the containers work in practice, how to implement them, how to use iterators and some algorithms useful to work with containers:

* Sequential containers:
	* Vector
	* List
	* String
	* Array

* Iterators

* Associative containers:
	* Map
	* Set
	* Multimap
	* Multiset

* Algotihms applied on containers:
	* read-only algorithms
	* Writing algorithms
	* Re-ordering algorithms

For a more detailed information please refer to the official **C++** documentation on [**containers**](https://en.cppreference.com/w/cpp/container).

### Code
Following the programs I wrote for this repository, a brief description about them and how to compile/run:

* [**Vector iterators**](src/containers/vector_iterators/src): 

	**Objective:** Learn to use iterators with vectors.

	Implement three functions that operate on integer vectors in the
	following manner:

		**ReadVector** that will read numbers from user and stores them as
		integer vector that is returned by the function. The function stops
		reading when a non-numeric value is given by the user.

		**PrintSum1** that calculates sums of pair of numbers in the vector
		and prints them on the screen. The function will print the sum of
		two consecutive numbers in vector, seprated by space. For example,
		if the user gives the following input: `1 2 3 4 !`, the output
		should be `3 5 7`, followed by a newline character. As can be seen,
		the output will have one number less than the input.

		**PrintSum2** that calculates sum of the first and last item in the
		vector, then the sum of second and second-last item in the vector,
		and so on, until all integers in the vector have been
		processed. With input `1 2 3 4 !` the output will be `5 5`, followed
		by newline.

		Compile and run:

		```bash
		#In the folder src/containers/vector_iterators
		make
		cd src
		./main
		```


* [**Classes**](src/classes): A more detailed look into **C++** classes and object-oriented programming mechanisms, such as inheritance and polymorphism. In addition, we observe how operator overloading works –and how it can be used– for example, together with input and output streams.

* [**Templates**](src/templates): Understand how to use templates, useful to create generic types and functions where same code can be shared to operate on different data types. In addition, we look into ``smart pointers`` –an applications of templates.

* [**Advanced topics**](src/advanced): In this section we walk through miscellaneous topics that can be useful sometimes such as lambdas –a mechanism for implementing functionality for temporary use inside program code–, and exceptions –a way of handling unexpected situations, such as errors.

### Built with
* **C++**
* Compiler version: ``gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0``