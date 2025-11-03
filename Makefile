CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = pathfinder
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    @echo "Cleaning up..."
    del /F /Q $(TARGET).exe *.o
    @echo "Clean complete!"

run: $(TARGET)
    .\$(TARGET)