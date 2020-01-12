MAIN_DIR = src

.PHONY: main clean run-main valgrind-run 

all: main

main:
	$(MAKE) -C $(MAIN_DIR)

clean:
	$(MAKE) -C $(MAIN_DIR) clean

clean-all:
	$(MAKE) -C $(MAIN_DIR) clean

run-main:
	$(MAKE) -C $(MAIN_DIR) run

valgrind-run:
	$(MAKE) -C $(MAIN_DIR) valgrind-run
	
