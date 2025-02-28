# Makefile for TermiKnight (producing 'MyRPG' executable)

# Compiler and Flags
CXX      = g++
CXXFLAGS = -std=c++17

# Sources (Adjust if you omit or rename files)
SRCS = main.cpp \
       Game.cpp \
       Player.cpp \
       Enemy.cpp \
       Item.cpp \
       Inventory.cpp \
       World.cpp \
       Structure.cpp \
       CombatManager.cpp \
       SaveManager.cpp \
       Utilities.cpp

# Executable name
TARGET = MyRPG

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
