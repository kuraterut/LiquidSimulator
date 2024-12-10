#-----------------------
# Compiler/linker flags
#-----------------------

CC = g++

# Compiler flags:
CFLAGS = \
	-std=c++20 \
	-O2
	

# Linker flags:
# NOTE: it is sometimes required to link to math library.
# LDFLAGS =

# Select build mode:
# NOTE: invoke with "DEBUG=1 make" or "make DEBUG=1".
ifeq ($(DEBUG),1)
	# Add default symbols:
	CFLAGS += -g
else
	# Enable link-time optimization:
	CFLAGS  += -flto
	LDFLAGS += -flto
endif

#--------
# Colors
#--------

# Use ANSI color codes:
BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

#-------
# Files
#-------

INCLUDES = $(wildcard include/*.hpp)

# Add "include" folder to header search path:
CFLAGS += -I $(abspath include)

# List of sources:
SOURCES = $(wildcard src/*.cpp)


OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

EXECUTABLE = build/test

#---------------
# Build process
#---------------

# By default, build executable:
# NOTE: first target in the file is the default.
default: $(EXECUTABLE)

# Link all object files together to obtain a binary:
# NOTE: all object files will be built first.
$(EXECUTABLE): $(OBJECTS) Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# Compile an object file:
# NOTE: all include files are passed as dependencies (this may be redundant)
build/%.o: src/%.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c $< $(CFLAGS) -o $@

run: build/main
	./build/main

build/main: build/main.o Makefile
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CC) $(LDFLAGS) build/main.o -o $@

build/main.o: src/main.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CC) -c src/main.cpp $(CFLAGS) -o $@




#--------------
# Test scripts
#--------------

# Run program:
test: $(EXECUTABLE)
	./$(EXECUTABLE)

#---------------
# Miscellaneous
#---------------

clean:
	@printf "$(BYELLOW)Cleaning build directory $(RESET)\n"
	rm -rf build

# List of non-file targets:
.PHONY: run clean default pi