MAIN_FILES=main.cpp main.o
SOURCES=main.cpp
HEADERS=restricted_interface.hpp restricted_ptr_ex.hpp restricted_ptr.hpp restricted_ref_counter.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt