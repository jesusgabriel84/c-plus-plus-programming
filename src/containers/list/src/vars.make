MAIN_FILES = main.cpp main.o
SOURCES=main.cpp list.cpp
HEADERS=list.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt