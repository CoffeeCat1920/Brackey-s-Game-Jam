# Define the compiler
CXX = g++

# Define the directories
SRCDIR = src
INCDIR = include
BINDIR = bin
LIBDIR = lib

# Define the target executable
TARGET = $(BINDIR)/app

# Define the source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Define the object files
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%.o, $(SOURCES)) main.cpp

# Define the compiler flags
CXXFLAGS = -I$(INCDIR)

# Define the linker flags
LDFLAGS = -L$(LIBDIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default rule to build the target
all: $(TARGET)

# Rule to link the object files into the target executable
$(TARGET): $(OBJECTS)
	@echo "Linking: $(OBJECTS)"
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Rule to compile source files into object files
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<"
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(BINDIR)/*.o $(TARGET)

# Debug variables
debug:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"

# Run the program
run: all
	./$(TARGET)

# Clean, then build and run
run-clean: clean all
	./$(TARGET)

# Phony targets
.PHONY: all clean debug run run-clean
