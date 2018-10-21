#ifndef _BOARD_H_
#define _BOARD_H_

#include "util.h"
#include "configure.h"
#include <vector>
using namespace std;

class Position
{
public:
    int x, y;
    double value;
    Position(int x, int y);
    Position(const Position& pos);
    Position& operator=(const Position& pos);
    bool operator < (const Position &pos) const;
};

class Board
{
private:
    char state[64];
public:
    Board();
    Board(const Board& board);
    char * operator[](int k);
    Board& operator=(const Board& board);
    BitBoard toBit();
    string toString();
    bool operator < (const Board &board) const;
};

class Env
{
private:
    Board board;
public:
    Env();
    void setState(Board& board);
    Board getState();
    void step(Position p, int color);
    vector<Position> getLegalActions(int color);
    int count(int color);
    bool isTerminate();
    int winner();
    void display();
};

#endif
