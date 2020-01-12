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

### Code
Following the codes I wrote for this repository and a brief description about them:

* [**Containers**](src/containers): Get to know the different kinds of containers for storing and handling data, how they differ between each other and in what situations they might be used. In addition we observe how iterators work to walk through –and if needed, modify– the data stored in containers.

* [**Classes**](src/classes): A more detailed look into **C++** classes and object-oriented programming mechanisms, such as inheritance and polymorphism. In addition, we observe how operator overloading works –and how it can be used– for example, together with input and output streams.

* [**Templates**](src/templates): Understand how to use templates, useful to create generic types and functions where same code can be shared to operate on different data types. In addition, we look into ``smart pointers`` –an applications of templates.

* [**Advanced topics**](src/advanced): In this section we walk through miscellaneous topics that can be useful sometimes such as lambdas –a mechanism for implementing functionality for temporary use inside program code–, and exceptions –a way of handling unexpected situations, such as errors.

### Built with
* **C++**
* Compiler version: ``gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0``