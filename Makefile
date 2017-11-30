# Configuration
CC = $(shell fltk-config --cxx)
SRCS = $(wildcard src/*.cpp)
TESTSRCS = $(wildcard tests/*.cpp)
OBJS = $(notdir ${SRCS:.cpp=.o})
TESTOBJS = $(notdir ${TESTSRCS:.cpp=.o})

BASEFLAGS = -g -Wall -Wextra -std=c++11 -Wno-unused-parameter -Wno-unused-variable
# BASEFLAGS += -pedantic -fsanitize=address,undefined
TARGET = FLSlidingPuzzle
TESTS = test

# Compiler Flags
CFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --cxxflags)
LDFLAGS = $(BASEFLAGS) $(shell fltk-config --use-images --ldflags)

.PHONY: all clean run
.SUFFIXES:

all: $(TARGET) $(TESTS)

board.o: src/board.cpp src/board.h
game.o: src/game.cpp src/game.h
point.o: src/point.cpp src/point.h
FLSlidingPuzzle.o: src/FLSlidingPuzzle.cpp src/FLSlidingPuzzle.h src/GameBoard.h
GameBoard.o: src/GameBoard.cpp src/GameBoard.h
InfoBoard.o: src/InfoBoard.cpp src/GameBoard.h
HelpPanel.o: src/HelpPanel.cpp src/HelpPanel.h
util.o: src/util.cpp src/util.h
configparser.o: src/configparser.cpp src/configparser.h
test.o: tests/test.cpp src/configparser.h

src/GameBoard.h: src/game.h
src/board.h: src/point.h
src/game.h: src/board.h
src/point.h:

test: test.o configparser.o

# Linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Compiling
%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: tests/%.cpp
	$(CC) $(CFLAGS) -Isrc -c -o $@ $<

clean:
	$(RM) $(TARGET) $(TESTS) $(OBJS) $(TESTOBJS)

run: $(TARGET)
	@./$(TARGET)

wc:
	@sed -e 's|//.*$$||g' -e '/^[	 ]*$$/d' src/*.cpp src/*.h | wc -l
wcall:
	@wc -l src/*.cpp src/*.h | sort
