#include "board.h"
#include "autoPlay.h"
#include "MCTS.h"
#include <iostream>
using namespace std;
/*
int main()
{
    Position pos(-1,-1);
    Board board;
    MCTS mcts(1, 10);
    Env env;
    int x, y;
    env.display();
    while(!env.isTerminate())
    {
        cout<<"start"<<endl;
        board = env.getState();
        pos = mcts.search(board);
        //cin>>x>>y;
        cout<<pos.x<<' '<<pos.y<<endl;
        env.step(pos, BLACK);
        env.display();

        cin>>x>>y;
        env.step(Position(x, y), WHITE);
        env.display();
    }
    
    return 0;
}
*/

int main()
{
    vector<Position> list;
    vector<Position>::iterator iter;
    double value, bestValue;
    Position bestPos(-1,-1);
    Env env;
    Board board;
    int x, y;
    env.display();
    while(!env.isTerminate())
    {
        list = env.getLegalActions(BLACK);
        board = env.getState();
        bestValue = -1e9;
        if (list.size() != 0) 
        {
            for (iter = list.begin(); iter != list.end(); iter++)
            {
                env.setState(board);
                env.step(*iter, BLACK);
                value = AB(env, 8, WHITE, MIN, -1e9, 1e9);
                if (value>bestValue)
                {
                    bestValue = value;
                    bestPos = *iter;
                }
            }
            env.setState(board);
            env.step(bestPos, BLACK);
        }
        env.display();

        cin>>x>>y;
        env.step(Position(x, y), WHITE);
        env.display();
    }
}
