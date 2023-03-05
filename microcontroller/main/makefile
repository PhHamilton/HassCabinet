# Use the C++ compiler to compile all .cpp files in the src folder
# and place the resulting object files and dependency files in the obj folder
# Use the C++ compiler to compile all .cpp files in the tests folder
# and place the resulting object files and dependency files in the obj folder

# Set the C++ compiler and flags
CXX = g++
CFLAGS = -Wall -Iheader -I. -g -std=c++17

# Set the target and dependencies
TARGET = testfile
SRCS = $(wildcard src/*.cpp)
OBJS = $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))
DEPS = $(addprefix obj/,$(notdir $(SRCS:.cpp=.d)))
TEST_SRCS = $(wildcard tests/*.cpp)
TEST_OBJS = $(addprefix obj/,$(notdir $(TEST_SRCS:.cpp=.o)))
TEST_DEPS = $(addprefix obj/,$(notdir $(TEST_SRCS:.cpp=.d)))

# Set the rules for building the target
$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $^

# Set the rule for building the object files
obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# Set the rule for building the dependency files
obj/%.d: src/%.cpp
	$(CXX) $(CFLAGS) -MM -MF $@ $<

# Include the dependency files
-include $(DEPS)

# Set the rules for building the test target
test: $(TEST_OBJS)
	$(CXX) $(CFLAGS) -o testfile $^

# Set the rule for building the test object files
obj/%.o: tests/%.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

# Set the rule for building the test dependency files
obj/%.d: tests/%.cpp
	$(CXX) $(CFLAGS) -MM -MF $@ $<

# Include the test dependency files
-include $(TEST_DEPS)

# Set the clean rule
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) testfile $(TEST_OBJS) $(TEST_DEPS)
