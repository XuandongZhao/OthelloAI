#include "util.h"
#include "configure.h"

BitBoard::BitBoard()
{
    b.reset();
    w.reset();
    e.reset();
}

BitBoard::BitBoard(const BitBoard &bb)
{
    b = bb.b;
    w = bb.w;
    e = bb.e;
}

BitBoard& BitBoard::operator=(const BitBoard& bb)
{
    b = bb.b;
    w = bb.w;
    e = bb.e;
    return *this;
}

void BitBoard::set(int color, int i, int j)
{
    if (color == BLACK)
        b.set(i * 8 + j);
    else if (color == WHITE)
        w.set(i * 8 + j);
    else
        e.set(i * 8 + j);
}

void BitBoard::reset(int color, int i, int j)
{
    if (color == BLACK)
        b.reset(i * 8 + j);
    else if (color == WHITE)
        w.reset(i * 8 + j);
    else
        e.reset(i * 8 + j);
}

int BitBoard::get(int i, int j)
{
    if (b[i*8 + j])
        return BLACK;
    else if (w[i*8 + j])
        return WHITE;
    else
        return EMPTY;
}

BitBoard BitBoard::rotate()
{
    BitBoard bb;
    int i, j;
    for (i = 0; i<8; i++)
        for (j = 0; j<8; j++)
            bb.set(i,j, get(7-j, i));
}






Basic::Basic()
{
    active[0].reset();
    active[1].reset();
    active[2].reset();
    active[3].reset();
}

Basic::Basic(const Basic& basic)
{
    active[0] = basic.active[0];
    active[1] = basic.active[1];
    active[2] = basic.active[2];
    active[3] = basic.active[3];
    children = basic.children;
}

Feature::Feature(BitBoard bitBoard)
{
    this->bitBoard[0] = bitBoard;
    this->bitBoard[1] = (this->bitBoard[0]).rotate();
    this->bitBoard[2] = (this->bitBoard[1]).rotate();
    this->bitBoard[3] = (this->bitBoard[2]).rotate();
}

Feature::Feature(const Feature& f)
{
    bitBoard[0] = f.bitBoard[0];
    bitBoard[1] = f.bitBoard[1];
    bitBoard[2] = f.bitBoard[2];
    bitBoard[3] = f.bitBoard[3];
}

Feature& Feature::operator=(const Feature& f)
{
    active[0] = f.active[0];
    active[1] = f.active[1];
    active[2] = f.active[2];
    active[3] = f.active[3];
    bitBoard[0] = f.bitBoard[0];
    bitBoard[1] = f.bitBoard[1];
    bitBoard[2] = f.bitBoard[2];
    bitBoard[3] = f.bitBoard[3];
    children = f.children;
    return *this;
}

void Feature::setActive(BitBoard *boards[], int size)
{
    int i, j;
    for (j = 0; j<4; j++)
        for (i = 0; i<size; i++)
        {
            if (
            ((boards[i]->b & bitBoard[j].b) == bitBoard[j].b) && 
            ((boards[i]->w & bitBoard[j].w) == bitBoard[j].w) &&
            ((boards[i]->e & bitBoard[j].e) == bitBoard[j].e)
            )
            active[j].set(i);
        }
}





Configure::Configure()
{
    active[0].reset();
    active[1].reset();
    active[2].reset();
    active[3].reset();
}

void Configure::addBase(Basic *base)
{
    bases.push_back(base);
    base->children.push_back(this);
}

void Configure::setActive()
{
    vector<Basic*>::iterator iter;
    for (iter = bases.begin(); iter != bases.end(); iter++)
    {
        if (iter == bases.begin())
        {
            active[0] = (*iter)->active[0];
            active[1] = (*iter)->active[1];
            active[2] = (*iter)->active[2];
            active[3] = (*iter)->active[3];
        }
        else
        {
            active[0] &= (*iter)->active[0];
            active[1] &= (*iter)->active[1];
            active[2] &= (*iter)->active[2];
            active[3] &= (*iter)->active[3];
        }
    }
}
