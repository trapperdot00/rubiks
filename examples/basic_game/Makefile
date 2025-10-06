CXX := g++
CXXFLAGS := -I../../src/cube -I../../src/game -I../../src/tile
SRCS := $(shell find -name '*.cpp')
BUILD_DIR := ../../build/examples/basic_game
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
EXEC := ./basic_game.out

all: library $(OBJS) basic_game.out

library:
	cd ../.. && $(MAKE) 

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

basic_game.out:
	$(CXX) $(CXXFLAGS) $(shell find ../../build/src -name '*.o') $(OBJS) -o $@

.PHONY: clean
clean:
	rm -f $(EXEC)
	rm -f $(OBJS)
	rmdir $(BUILD_DIR)
