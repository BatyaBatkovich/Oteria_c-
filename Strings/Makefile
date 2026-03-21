CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = my_strings
SRC = my_strings.cpp

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
