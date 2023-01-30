CC ?= g++
CFLAGS ?= -Wall -Wextra -Werror -std=c++17
LDLIBS ?= -lstdc++ -pthread

INCLUDE_PATH = ./include

TARGET   = pacman

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Programme compilé !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: all tests clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
	rm -r html

debug: 
	make CFLAGS="-Wall -Wextra -Werror -std=c++17 -DDEBUG"

doc:
	@cp -r ./assets ./html
	@doxygen > /dev/null 2>&1
	@echo "Documentaion générée !"
	@wslview html/index.html 	# Windows Subsystem for Linux
	# @open html/index.html 		# MacOS
	# @xdg-open html/index.html 	# Linux

all:
	make
	make doc
