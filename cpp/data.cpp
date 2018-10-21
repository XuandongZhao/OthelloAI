#include "board.h"
#include "autoPlay.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ifstream in;
    string s;
    int count;
    double value;
    Env env;
    
    in.open("../data/tp59.txt");
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
        cout<<s<<endl;
        env.display();
        cout<<count<<' '<<value<<endl;
        int temp = (int)AB(env, 3, WHITE, MIN, -1e9, 1e9);
        cout<<temp<<endl;
        /*
        if (temp != value)
        {
            env.display();
            cout<<count<<' '<<value<<endl;
        }
        */
       cin>>count;
    }
}
