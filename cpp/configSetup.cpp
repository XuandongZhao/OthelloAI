#include "configure.h"
#include "board.h"
#include "util.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//c = 0 white 1 empty 2 black
#define FCSLOC(x, y, c) ((((x) * 4 + (y)) * 3) + c)
const int FCS_NUM = 200000;

int fcs_num = 0;
Basic* fcs[200000];

BitBoard *boards[800000];
double values[800000];
int boards_num =0;

void addFeature(int x, int y)
{
    BitBoard bb1, bb2, bb3;
    bb1.set(WHITE, x, y);
    bb2.set(EMPTY, x, y);
    bb3.set(BLACK, x, y);

    fcs[fcs_num] = new Feature(bb1);
    fcs[fcs_num + 1] = new Feature(bb2);
    fcs[fcs_num + 2] = new Feature(bb3);
    fcs_num += 3;
}

void addPattern1()
{
    int a, b, c, d;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                {
                    Configure *config = new Configure();
                    config->addBase(fcs[FCSLOC(0, 3, a)]);
                    config->addBase(fcs[FCSLOC(1, 2, b)]);
                    config->addBase(fcs[FCSLOC(2, 1, c)]);
                    config->addBase(fcs[FCSLOC(3, 0, d)]);
                    fcs[fcs_num++] = config;
                }
}

void addPattern2()
{
    int a, b, c, d, e;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                    {
                        Configure *config = new Configure();
                        config->addBase(fcs[FCSLOC(0, 4, a)]);
                        config->addBase(fcs[FCSLOC(1, 3, b)]);
                        config->addBase(fcs[FCSLOC(2, 2, c)]);
                        config->addBase(fcs[FCSLOC(3, 1, d)]);
                        config->addBase(fcs[FCSLOC(4, 0, e)]);
                        fcs[fcs_num++] = config;
                    }
}

void addPattern3()
{
    int a, b, c, d, e, f;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                        {
                            Configure *config = new Configure();
                            config->addBase(fcs[FCSLOC(0, 5, a)]);
                            config->addBase(fcs[FCSLOC(1, 4, b)]);
                            config->addBase(fcs[FCSLOC(2, 3, c)]);
                            config->addBase(fcs[FCSLOC(3, 2, d)]);
                            config->addBase(fcs[FCSLOC(4, 1, e)]);
                            config->addBase(fcs[FCSLOC(5, 0, f)]);
                            fcs[fcs_num++] = config;
                        }
}

void addPattern4()
{
    int a, b, c, d, e, f, g;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                            {
                                Configure *config = new Configure();
                                config->addBase(fcs[FCSLOC(0, 6, a)]);
                                config->addBase(fcs[FCSLOC(1, 5, b)]);
                                config->addBase(fcs[FCSLOC(2, 4, c)]);
                                config->addBase(fcs[FCSLOC(3, 3, d)]);
                                config->addBase(fcs[FCSLOC(4, 2, e)]);
                                config->addBase(fcs[FCSLOC(5, 1, f)]);
                                config->addBase(fcs[FCSLOC(6, 0, g)]);
                                fcs[fcs_num++] = config;
                            }
}

void addPattern5()
{
    int a, b, c, d, e, f, g, h;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                {
                                    Configure *config = new Configure();
                                    config->addBase(fcs[FCSLOC(0, 7, a)]);
                                    config->addBase(fcs[FCSLOC(1, 6, b)]);
                                    config->addBase(fcs[FCSLOC(2, 5, c)]);
                                    config->addBase(fcs[FCSLOC(3, 4, d)]);
                                    config->addBase(fcs[FCSLOC(4, 3, e)]);
                                    config->addBase(fcs[FCSLOC(5, 2, f)]);
                                    config->addBase(fcs[FCSLOC(6, 1, g)]);
                                    config->addBase(fcs[FCSLOC(7, 0, h)]);
                                    fcs[fcs_num++] = config;
                                }
}

void addPattern6()
{
    int a, b, c, d, e, f, g, h;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                {
                                    Configure *config = new Configure();
                                    config->addBase(fcs[FCSLOC(1, 7, a)]);
                                    config->addBase(fcs[FCSLOC(1, 6, b)]);
                                    config->addBase(fcs[FCSLOC(1, 5, c)]);
                                    config->addBase(fcs[FCSLOC(1, 4, d)]);
                                    config->addBase(fcs[FCSLOC(1, 3, e)]);
                                    config->addBase(fcs[FCSLOC(1, 2, f)]);
                                    config->addBase(fcs[FCSLOC(1, 1, g)]);
                                    config->addBase(fcs[FCSLOC(1, 0, h)]);
                                    fcs[fcs_num++] = config;
                                }
}

void addPattern7()
{
    int a, b, c, d, e, f, g, h;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                {
                                    Configure *config = new Configure();
                                    config->addBase(fcs[FCSLOC(2, 7, a)]);
                                    config->addBase(fcs[FCSLOC(2, 6, b)]);
                                    config->addBase(fcs[FCSLOC(2, 5, c)]);
                                    config->addBase(fcs[FCSLOC(2, 4, d)]);
                                    config->addBase(fcs[FCSLOC(2, 3, e)]);
                                    config->addBase(fcs[FCSLOC(2, 2, f)]);
                                    config->addBase(fcs[FCSLOC(2, 1, g)]);
                                    config->addBase(fcs[FCSLOC(2, 0, h)]);
                                    fcs[fcs_num++] = config;
                                }
}

void addPattern8()
{
    int a, b, c, d, e, f, g, h;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                {
                                    Configure *config = new Configure();
                                    config->addBase(fcs[FCSLOC(3, 7, a)]);
                                    config->addBase(fcs[FCSLOC(3, 6, b)]);
                                    config->addBase(fcs[FCSLOC(3, 5, c)]);
                                    config->addBase(fcs[FCSLOC(3, 4, d)]);
                                    config->addBase(fcs[FCSLOC(3, 3, e)]);
                                    config->addBase(fcs[FCSLOC(3, 2, e)]);
                                    config->addBase(fcs[FCSLOC(3, 1, e)]);
                                    config->addBase(fcs[FCSLOC(3, 0, e)]);
                                    fcs[fcs_num++] = config;
                                }
}

void addPattern9()
{
    int a, b, c, d, e, f, g, h, i;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                    for (i = 0; i<3; i++)
                                    {
                                        Configure *config = new Configure();
                                        config->addBase(fcs[FCSLOC(0, 0, a)]);
                                        config->addBase(fcs[FCSLOC(0, 1, b)]);
                                        config->addBase(fcs[FCSLOC(0, 2, c)]);
                                        config->addBase(fcs[FCSLOC(1, 0, d)]);
                                        config->addBase(fcs[FCSLOC(1, 1, e)]);
                                        config->addBase(fcs[FCSLOC(1, 2, f)]);
                                        config->addBase(fcs[FCSLOC(2, 0, g)]);
                                        config->addBase(fcs[FCSLOC(2, 1, h)]);
                                        config->addBase(fcs[FCSLOC(2, 2, i)]);
                                        fcs[fcs_num++] = config;
                                    }
}

void addPattern10()
{
    int a, b, c, d, e, f, g, h, i, j;
    for (a = 0; a<3; a++)
        for(b = 0; b<3; b++)
            for (c = 0; c<3; c++)
                for (d = 0; d<3; d++)
                    for (e = 0; e<3; e++)
                        for (f = 0; f<3; f++)
                            for (g = 0; g<3; g++)
                                for (h = 0; h<3; h++)
                                    for (i = 0; i<3; i++)
                                        for (j = 0; j<3; j++)
                                        {
                                            Configure *config = new Configure();
                                            config->addBase(fcs[FCSLOC(0, 0, a)]);
                                            config->addBase(fcs[FCSLOC(0, 1, b)]);
                                            config->addBase(fcs[FCSLOC(0, 2, c)]);
                                            config->addBase(fcs[FCSLOC(0, 3, d)]);
                                            config->addBase(fcs[FCSLOC(0, 4, e)]);
                                            config->addBase(fcs[FCSLOC(0, 5, f)]);
                                            config->addBase(fcs[FCSLOC(0, 6, g)]);
                                            config->addBase(fcs[FCSLOC(0, 7, h)]);
                                            config->addBase(fcs[FCSLOC(1, 1, i)]);
                                            config->addBase(fcs[FCSLOC(1, 7, j)]);
                                            fcs[fcs_num++] = config;
                                        }
}

int main()
{
    int i, j;
    ifstream in;
    ofstream out;
    string s;
    double value;
    
    in.open("../data/utp11.txt");
    out.open("../data/cs11.txt");
    while(!in.eof())
    {
        Board board;
        in>>s>>value;
        
        for (int i = 0; i<s.length(); i++)
        {
            if (s[i] == '0')
                board[i/8][i%8] = WHITE;
            else if (s[i] == '2')
                board[i/8][i%8] = BLACK;
            else
                board[i/8][i%8] = EMPTY;
        }

        BitBoard *bb =new BitBoard(board.toBit());
        boards[boards_num] = bb;
        values[boards_num++]= value;
    }
    in.close();
    cout<<boards_num<<endl;

    for (i = 0; i<4; i++)
        for (j = 0; j<4; j++)
            addFeature(i, j);
    addPattern1();
    addPattern2();
    addPattern3();
    addPattern4();
    addPattern5();
    addPattern6();
    addPattern7();
    addPattern8();
    addPattern9();
    addPattern10();
    cout<<fcs_num<<endl;

    for (i =0; i<16; i++)
    {
        ((Feature*)fcs[i])->setActive(boards, boards_num);
    }
    for (i = 16; i<fcs_num; i++)
    {
        ((Configure*)fcs[i])->setActive();
    }

    out<<fcs_num<<endl;
    for (i = 0; i<fcs_num; i++)
    {
        for (j = 0; j<4; j++)
            out<<fcs[i]->active[j].to_string()<<endl;
    }

    out<<boards_num<<endl;
    for (i = 0; i<boards_num; i++)
    {
        out<<values[i]<<endl;
    }
    out.close();

    
}
