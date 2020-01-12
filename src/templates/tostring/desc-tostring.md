**Objective:** Learn basic use of templates.

In this exercise you will need to implement different overloaded
versions of function *ToString* that returns the contents of an
container as a string. Any type of sequential container should be
compatible, i.e. you need to use the container through template.

  * One version of the function gets a container type as a parameter,
    in which case it will return the contents of the whole container
    in a string.        
  * Another version of the function gets beginning and ending
    iterators, in which case the range between iterators is printed.
  * In addition, if given a string, the *ToString* should just return
    the string inside double quotes: `"somestring"`.
* When a string is given as two iterators
(e.g., ToString(str.begin(), str.end()), it will be printed as sequence
of characters: { f, o, o }

Apart from the single string case, the function should return the
container items as comma separated list inside brackets. For example,
in the case of string container elements, it would return something
like the following (spaces are significant):

`{ foo, bar, baz }`

*If this task feels difficult to understand at first, you could start with
a version that uses only e.g. vector container. Then modify it to use
templates in place of specific container type. Note that e.g. begin() and
end() functions are available for all sequential container types.*