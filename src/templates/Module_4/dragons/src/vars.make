MAIN_FILES = main.cpp main.o
SOURCES=main.cpp dragon.cpp fantasy_dragon.cpp magic_dragon.cpp chinese_dragon.cpp dragon_cave.cpp
HEADERS=dragon.hpp dragon.hpp fantasy_dragon.hpp magic_dragon.hpp chinese_dragon.hpp dragon_cave.hpp
OBJECTS=$(SOURCES:cpp=o)
EXECNAME=main
CLEAN_FILES=out.txt tmp.txt treasures.txt