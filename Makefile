CC ?= g++
CFLAGS ?= -Wall -Wextra -Werror -std=c++17
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
	rm -rf obj/*.o
	rm -rf tests/obj/*.o
	rm -f $(BINDIR)/$(TARGET)
	rm -rf html
	@echo "\033[92mCleaned\033[0m"

debug: 
	make CFLAGS="-Wall -Wextra -Werror -std=c++17 -DDEBUG"

doc:
	@echo "\033[95mBuilding documentation...\033[0m"
	@cp -r ./assets ./html
	@doxygen > /dev/null 2>&1
	@echo "\033[92mDocumentation built!\033[0m"
	@wslview html/index.html 		
	# @wslview html/index.html 		# Windows Subsystem for Linux
	# @open html/index.html 		# MacOS
	# @xdg-open html/index.html 		# Linux

all:
	make
	make doc
