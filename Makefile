CXX := g++
SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:%.cpp=build/%.o)

all: $(OBJS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< -o $@

.PHONY: clean
clean:
	rm -rf build
