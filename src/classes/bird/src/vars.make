MAIN_FILES = main.cpp main.o
SOURCES=main.cpp aviary.cpp
HEADERS=bird.hpp aviary.hpp duck.hpp owl.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt