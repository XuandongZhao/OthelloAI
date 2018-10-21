#include "util.h"
#include "board.h"
#include "autoPlay.h"
#include <iostream>
#include <fstream>

int main()
{
    Env env;
    ifstream in;
    ofstream out;
    string s;
    int count;
    double value;
    int k =0;

    in.open("../data/tp11.txt");
    out.open("../data/utp11.txt");
    while(!in.eof())
    {
        Board board;
        in>>s>>count>>value;
        
        for (int i = 0; i<s.length(); i++)
        {
            if (s[i] == '0')
                board[i/8][i%8] = WHITE;
            else if (s[i] == '2')
                board[i/8][i%8] = BLACK;
            else
                board[i/8][i%8] = EMPTY;
        }
        env.setState(board);
        value = AB(env, 5, WHITE, MIN, -1e9, 1e9);

        out<<s<<' '<<value<<endl;
        k ++;
        if ((k + 1) % 10000 == 0)
            cout<<k<<endl;
    }
    in.close();
    out.close();
}