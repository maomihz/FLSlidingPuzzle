# Configuration
CC = $(shell fltk-config --cxx)
SRCS = $(wildcard *.cpp)
OBJS = ${SRCS:.cpp=.o}
BASEFLAGS = -g -Wall -Wextra -std=c++11 -Wno-unused-parameter -Wno-unused-variable
TARGET = FLSlidingPuzzle

# Compiler Flags
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)

.PHONY: all clean run
.SUFFIXES:

all: $(TARGET)

# Linking
$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJS)

run: $(TARGET)
	@./$(TARGET)
