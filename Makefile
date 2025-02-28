# Makefile for TermiKnight

# Compiler and Flags
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# List of source files (add or remove as needed)
SRCS = main.cpp \
       Game.cpp \
       Player.cpp \
       Enemy.cpp \
       CombatManager.cpp \
       Item.cpp \
       Inventory.cpp \
       Structure.cpp \
       World.cpp \
       SaveManager.cpp \
       Utilities.cpp

# Derive object files by replacing .cpp with .o
OBJS = $(SRCS:.cpp=.o)

# The final executable name
TARGET = TermiKnight

# Default rule: build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp into a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule: remove object files and the binary
clean:
	rm -f $(OBJS) $(TARGET)
