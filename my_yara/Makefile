CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = my_yara
SRC = my_yara.cpp

all: clean $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
