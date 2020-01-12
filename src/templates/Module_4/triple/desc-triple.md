**Objective:** Practice creating a template class from scratch

In this exercise your task is to implement a template class from scratch.
As some might have already noticed templates can be very useful when
writing container-like classes. Implementing the containers with templates
ensures that the container is type independent, i.e. supports different
types of objects.

Your task is to implement a template container class, Triple.
Triple is much like a pair, but with three values instead of two.
A triple can either be homogenous or heterogenous, meaning that it can
either have three values, all of which are the same type, or it can contain
different types.

The Triple class that you have to implement has been declared in more
detail in the *triple.hpp* file.

**Note:** template implementations such as this usually fail in the
compile stage. Test your implementation carefully. Certain things can only 
be initialised in an initialiser list.