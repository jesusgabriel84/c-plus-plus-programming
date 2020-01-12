CXXFLAGS = -g -std=c++17 -Wall -Wextra -pedantic
CPPFLAGS += -c

ifeq ($(OS),Windows_NT)
	RM=del /f /q
	EXECUTABLE:=$(EXECNAME).exe
else
	RM=rm -f
	EXECUTABLE:=$(EXECNAME)
endif

.PHONY: all clean run valgrind-run

all: $(EXECUTABLE)
  
$(EXECUTABLE): $(OBJECTS) $(COBJECTS)
	$(CXX) $(OBJECTS) $(COBJECTS) $(LDFLAGS) -o $@ 

$(OBJECTS): %.o : %.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	
$(COBJECTS): %.o : %.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o $(EXECNAME) $(EXECNAME).exe $(CLEAN_FILES)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
	
valgrind-run: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)
	