CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.

TARGET = indice

SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Limpando arquivos compilados..."
	rm -f $(OBJS) $(TARGET)
	@echo "Limpeza concluída!"

run: $(TARGET)
	./$(TARGET)