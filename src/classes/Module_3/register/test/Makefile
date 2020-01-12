include ../src/vars.make

TESTNAME = test
TEST_SOURCE = test_source.cpp

SOURCES := $(filter-out $(MAIN_FILES), $(SOURCES))
OBJECTS := $(filter-out $(MAIN_FILES), $(OBJECTS))
HEADERS := $(filter-out $(MAIN_FILES), $(HEADERS))

include ../../../scripts/test.make