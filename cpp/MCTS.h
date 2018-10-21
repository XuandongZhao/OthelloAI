#ifndef _MCTS_H_
#define _MCTS_H_

#include "board.h"
#include "autoPlay.h"
#include <vector>
#include <memory>
#include <map>
using namespace std;


class UCTNode
{
public:
    UCTNode(Board& state, shared_ptr<UCTNode> father, int color);
    unsigned int getAccessTime() const { return _access_time; }
    int getReward() const { return _reward; }
    shared_ptr<UCTNode> getFather() { return _father; }
    int getColor() const { return _color; }
    void addAccessTime() { _access_time += 1; }
    void addReward(int delta) { _reward += delta; }
    void addChild(Position action, shared_ptr<UCTNode> child) { _children.insert(make_pair(action, child)); }
    //double getQ(Board state, Position action);
    int getN(Board state, Position action);
    double getValue(Position action, int role, double c);
private:
    Board _board;    // TODO: maybe this is not necessary?
    unsigned int _access_time;
    int _reward;
    int _color;
    //vector<shared_ptr<UCTNode>> _children;
    shared_ptr<UCTNode> _father;
    map<Position, shared_ptr<UCTNode>> _children;
    map<pair<Board, Position>, int>N;
};

class MCTS{
public:
    //int play();
    MCTS(int _role, int t = 1);
    Position search(Board& state); // position, color pair
    void simulate(Board& state);
    shared_ptr<UCTNode> simulateTree();
    int simulateDefault();
    //double getValue(Board& state, int action, double c);
    Position getMove(Board& state, int role, double c = 0.1);
    void backup(shared_ptr<UCTNode> v, int reward);
    shared_ptr<UCTNode> newNode(Board state, shared_ptr<UCTNode> father, int role);
    Position DefaultPoicy(Board &state, int role, double T);
private:
    Env env;
    shared_ptr<UCTNode> _root;
    map<Board, shared_ptr<UCTNode>> tree;
    int t;  // time limit in seconds 
    int _role; // 1 for Black, -1 for White
};


#endif
