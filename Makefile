# Configuration
CC = $(shell fltk-config --cxx)
SRCS = $(wildcard src/*.cpp)
OBJS = $(notdir ${SRCS:.cpp=.o})
BASEFLAGS = -g -Wall -Wextra -std=c++11 -Wno-unused-parameter -Wno-unused-variable
TARGET = FLSlidingPuzzle

# Compiler Flags
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)

.PHONY: all clean run
.SUFFIXES:

all: $(TARGET)

board.o: src/board.cpp src/board.h
game.o: src/game.cpp src/game.h
point.o: src/point.cpp src/point.h
FLSlidingPuzzle.o: src/GameBoard.h

src/GameBoard.h: src/game.h
src/board.h: src/point.h
src/game.h: src/board.h
src/point.h:

# Linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling
%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJS)

run: $(TARGET)
	@./$(TARGET)
