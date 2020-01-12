**Objective:** Practice abstract classes, inheritance and little bit of
operator overloading.

You will need to implement different kinds of birds that all can fly
(except *const* birds). Birds also speak, but in different languages
specific to the bird type. **Bird** (in *bird.hpp*) is the abstract
base class for birds. You will need to implement **Duck** and **Owl** 
(and define them in *bird.hpp*). To save some
effort, you implement the needed functions inline in the bird-specific
header files together with the the class definitions.

The bird language is simple: duck says `QUACK` and owl says
`WHUU`. The speak function should output the name of the bird, colon,
space, followed by one of the above and ended with a newline, e.g.:

`Donald: QUACK\n`
 
In addition, you will need to implement class **Aviary**, which stores the birds, 
in the *aviary.hpp* file and its member functions in the *aviary.cpp* file.


**Compile and run:**
```bash
#In the folder src/classes/bird
make
cd src
./main
```