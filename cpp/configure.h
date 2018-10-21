#ifndef _CONFIGURE_H_
#define _CONFIGURE_H_

#include <bitset>
#include <vector>
using namespace std;

#define MAX_TRAINPOS 1000000

class BitBoard
{
public:
    bitset<64> b, w, e;
    BitBoard();
    BitBoard(const BitBoard &bb);
    BitBoard& operator=(const BitBoard& bb);
    void set(int color, int i, int j);
    void reset(int color, int i, int j);
    int get(int i, int y);
    BitBoard rotate();
};

class Basic
{
public:
    double w;
    bitset<MAX_TRAINPOS> active[4];
    vector<Basic*> children;
    Basic();
    Basic(const Basic& basic);
};

class Feature:public Basic
{
private:
    BitBoard bitBoard[4];
public:
    Feature(BitBoard bitBoard);
    Feature(const Feature& f);
    Feature& operator=(const Feature& f);
    void setActive(BitBoard *boards[], int size);
};

class Configure:public Basic
{
private:
    vector<Basic*> bases;
public:
    Configure();
    void addBase(Basic *base);
    void setActive();
};

#endif
