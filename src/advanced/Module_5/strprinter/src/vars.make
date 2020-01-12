MAIN_FILES = main.cpp main.o
SOURCES=main.cpp printers.cpp diagonal_printer.cpp standard_printer.cpp 
HEADERS=diagonal_printer.hpp printers.hpp standard_printer.hpp string_printer.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt