**Objective:** Operator overloading, resource management, inheritance
and virtual interfaces, exceptions, etc.

**StringPrinter** is an abstract base class for printing strings in different 
styles. There are two different classes that implement the *StringPrinter* 
interface: **DiagonalPrinter**, which outputs text in a diagonal format, and
**StandardPrinter**, which just prints the text normally.

Printing is implemented overloading the *function call operator*
(`operator()`). See [this link] for examples how it is used.

[this link]: http://www.tutorialspoint.com/cplusplus/function_call_operator_overloading.htm

In addition, there is **Printers** container for different kind of printers.


**Compile and run:**
```bash
#In the folder src/advanced/strprinter
make
cd src
./main
```