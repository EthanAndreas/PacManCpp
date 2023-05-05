CC ?= g++
CFLAGS ?= -Wall -Wextra -Werror -std=c++17 -g -Og
LDLIBS ?= -lSDL2 -lstdc++

INCLUDE_PATH = ./include

TARGET   = pacman

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mCompiled\033[0m"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: all tests clean cov 
clean:
	@echo "\033[93mCleaning...\033[0m"
	rm -rf obj/*.o
	rm -rf tests/obj/*.o
	rm -f $(BINDIR)/$(TARGET)
	rm -rf html
	@echo "\033[92mCleaned\033[0m" 

debug: 
	@make clean -s 1>/dev/null 
	@echo "\033[93mCompilation...\033[0m"
	@make CFLAGS="-Wall -Wextra -Werror -std=c++17 -DDEBUG" -s 2>/dev/null || (echo "\033[91mError on compilation, re-run with \"make\" to see the errors\033[0m" && exit 1)
	@echo "\033[93mRun Application in debug mode...\033[0m"
	./$(BINDIR)/$(TARGET)
	@echo "\033[92mExit properly\033[0m"

doc:
	@echo "\033[93mBuilding documentation...\033[0m"
	@cp -r ./assets ./html
	@doxygen > /dev/null 2>&1
	@echo "\033[92mDocumentation built\033[0m"
	@wslview html/index.html 		
	# @wslview html/index.html 		# Windows Subsystem for Linux
	# @open html/index.html 		# MacOS
	# @xdg-open html/index.html 		# Linux

run:
	@make clean -s 1>/dev/null 
	@echo "\033[93mCompilation...\033[0m"
	@make -s 2>/dev/null || (echo "\033[91mError on compilation, re-run with \"make\" to see the errors\033[0m" && exit 1)
	@echo "\033[93mRun Application...\033[0m"
	./$(BINDIR)/$(TARGET)
	@echo "\033[92mExit properly\033[0m"

valgrind:
	@make clean -s 1>/dev/null 
	@echo "\033[93mCompilation...\033[0m"
	@make -s 2>/dev/null || (echo "\033[91mError on compilation, re-run with \"make\" to see the errors\033[0m" && exit 1)
	@echo "\033[93mRun Application with valgrind...\033[0m"
	valgrind --leak-check=full --show-leak-kinds=all ./$(BINDIR)/$(TARGET)
	@echo "\033[92mExit properly\033[0m"

valgrind-segfault:
	@make clean -s 1>/dev/null 
	@echo "\033[93mCompilation...\033[0m"
	@make -s 2>/dev/null || (echo "\033[91mError on compilation, re-run with \"make\" to see the errors\033[0m" && exit 1)
	@echo "\033[93mRun Application with valgrind...\033[0m"
	valgrind --show-possibly-lost=yes --show-reachable=yes ./$(BINDIR)/$(TARGET)
	@echo "\033[92mExit properly\033[0m"

all:
	make
	make doc
