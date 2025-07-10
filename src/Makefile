CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

SRCS = main.cpp rubiks/color.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = main.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(OBJS) $(TARGET)
