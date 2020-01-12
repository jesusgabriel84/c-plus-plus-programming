MAIN_FILES = main.cpp main.o
SOURCES=main.cpp vector_it.cpp
HEADERS=vector_it.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt in.txt