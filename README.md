# FL Sliding Puzzle

热烈庆祝学期结束，猫猫的 Sliding Puzzle 已开源！！

As celebration of the end of semester, the FLTK Sliding Puzzle is now open source!

-----

Howdy fellow programmers, welcome to the world of Computer Science!

Here we present to you an addictive game, the sliding puzzle! It is actually our final project for CSCE121, but let's still have some fun from the project. I hope that everyone can learn something by doing the project.

## What is it?

It is a game written in C++, and uses [FLTK](http://www.fltk.org) graphics library. The interface is not too fancy, but the game is still fun. The source code is also open so everyone can compile the program themselves. Here is the wiki page for [15 Puzzle](https://en.wikipedia.org/wiki/15_puzzle), if you want to read more.

## Building

Checklist:
- FLTK 1.3.2
- C++ 11
- GNU Make (Or any alternative)

### 1. Clone this repository

```
git clone https://github.com/maomihz/FL-Sliding-Puzzle.git
cd FL-Sliding-Puzzle
```

### 2. Compile

A Makefile is given to compile and run the program. To compile all files, use the following command:

```
make
```

To compile and run:

```
make run
```

Make sure that FLTK is installed and put in PATH. Please refer to official documentation of FLTK on how to set it up on your machine.


## To Do List
- [x] Fancy Splash Button
- [x] Fancy Game Background
- [x] Help screen
- [ ] Interactive help screen
- [x] About screen
- [x] Pause game
- [x] Configuration & Leaderboard
- [ ] 2048
- [x] Animation on moving tiles
