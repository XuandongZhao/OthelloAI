#include "board.h"
#include "evaluation.h"
#include <algorithm>
using namespace std;

const int MAX = 1;
const int MIN = 0;

static bool comp1(const Position &pos1, const Position &pos2)
{
    return pos1.value < pos2.value;
}

static bool comp2(const Position &pos1, const Position &pos2)
{
    return pos1.value > pos2.value;
}

//a -max  b +max
double AB(Env& env, int depth, int color, int role, double a, double b)
{
    vector<Position> list;
    vector<Position>::iterator iter;
    Board board;
    double v, temp;

    if (env.isTerminate() || depth == 0)
        return (dynamic_heuristic_evaluation_function(env, color, -color));

    board = env.getState();
    list = env.getLegalActions(color);
    /*
    if (!list.empty())
    {
        for (iter = list.begin(); iter != list.end(); iter++)
        {
            env.setState(board);
            env.step(*iter, color);
            iter->value = dynamic_heuristic_evaluation_function(env, color, -color);
        }
    }
    */
    if (role == MIN)
    {
        v = 1e9;
        if (list.empty())
        {
            if (color == BLACK)
                temp = AB(env, depth-1, WHITE, MAX, a, b);
            else
                temp = AB(env, depth-1, BLACK, MAX, a, b);
            v = v<temp? v : temp;
            return v;
        }
        //sort(list.begin(), list.end(), comp1);
        for (iter = list.begin(); iter != list.end(); iter++)
        {
            env.setState(board);
            env.step(*iter, color);
            if (color == BLACK)
                temp = AB(env, depth-1, WHITE, MAX, a, b);
            else
                temp = AB(env, depth-1, BLACK, MAX, a, b);
            v = v<temp? v : temp;
            b = b<v? b : v;
            if (b <= a)
                break;
        }
        return v;
    }
    else
    {
        v = -1e9;
        if (list.empty())
        {
            if (color == BLACK)
                temp = AB(env, depth-1, WHITE, MIN, a, b);
            else
                temp = AB(env, depth-1, BLACK, MIN, a, b);
            v = v>temp? v : temp;
            return v;
        }
        //sort(list.begin(), list.end(), comp2);
        for (iter = list.begin(); iter != list.end(); iter++)
        {
            env.setState(board);
            env.step(*iter, color);
            if (color == BLACK)
                temp = AB(env, depth-1, WHITE, MIN, a, b);
            else
                temp = AB(env, depth-1, BLACK, MIN, a, b);
            v = v>temp? v : temp;
            a = a>v? a : v;
            if (a >= b)
                break;
        }
        return v;
    }
}

