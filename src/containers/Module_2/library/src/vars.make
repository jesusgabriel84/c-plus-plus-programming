MAIN_FILES = main.cpp main.o
SOURCES=main.cpp book.cpp customer.cpp library.cpp
HEADERS=book.hpp customer.hpp library.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main