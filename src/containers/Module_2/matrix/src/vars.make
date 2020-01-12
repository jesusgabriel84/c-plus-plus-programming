MAIN_FILES = main.cpp main.o
SOURCES=main.cpp matrix.cpp
HEADERS=matrix.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt in.txt