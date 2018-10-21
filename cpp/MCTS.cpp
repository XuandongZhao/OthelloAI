#include "MCTS.h"
#include <ctime>
#include <chrono>
#include "evaluation.h"
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

class Timer {
public:
    void start() {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop() {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds() {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning) {
            endTime = std::chrono::system_clock::now();
        } else {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsed_seconds() {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
};


UCTNode::UCTNode(Board &state, shared_ptr<UCTNode> father, int color) :
        _father(father), _access_time(0), _board(state), _color(color) {
    if (!_father) {
        _access_time = 1; // root init
    }

}

// double UCTNode::getQ(Board state, Position action){
//     if (Q.find(pair<Board, Position>(state, action)) == Q.end()){
//         Q[pair<Board, Position>(state, action)] = 0;
//         return 0;
//     }
//     else{
//         return Q[pair<Board, Position>(state, action)];
//     }
// }
int UCTNode::getN(Board state, Position action) {
    if (N.find(pair<Board, Position>(state, action)) == N.end()) {
        N[pair<Board, Position>(state, action)] = 0;
        return 0;
    } else {
        return N[pair<Board, Position>(state, action)];
    }
}

double UCTNode::getValue(Position action, int role, double c) {
    double Q;
    double uncertain;
    if (_children.find(action) == _children.end()) {
        Q = 0;
        uncertain = 0;
    } else {
        Q = (_children.find(action)->second->getReward()) * 1.0 / _children.find(action)->second->getAccessTime();
        uncertain = c * std::sqrt(std::log(_access_time) / _children.find(action)->second->getAccessTime());
    }

    if (role == 1)
        return Q + uncertain;
    else
        return Q - uncertain;

}

MCTS::MCTS(int _role, int t) {
    Board state;
    this->_role = _role;
    this->t = t;
    tree.insert({state, NULL});
}

Position MCTS::search(Board &state) {
    Timer T;
    int k = 0;
    T.start();
    while (T.elapsed_seconds() < t) {
        simulate(state);
        k += 1;
    }
    T.stop();
    cout << k << endl;
    return getMove(state, _role);
}

void MCTS::simulate(Board &state) {
    env.setState(state);
    shared_ptr<UCTNode> end = simulateTree();
    // the tree is expanded until end, and env is changed to this point as well
    int reward = simulateDefault();
    backup(end, reward);
}

shared_ptr<UCTNode> MCTS::simulateTree() {
    int role_cur = _role;
    Board state_cur, last_state;
    while (!env.isTerminate()) {
        last_state = state_cur;
        state_cur = Board(env.getState());
        if (tree.find(state_cur) == tree.end()) { // new node
            shared_ptr<UCTNode> expand_child =
                    newNode(state_cur, tree.find(last_state)->second, -role_cur);
            return expand_child;
        }
        Position action = getMove(state_cur, role_cur);
        env.step(action, role_cur);
        role_cur = -role_cur;
    }
    return tree.find(state_cur)->second;
}

int MCTS::simulateDefault() {
    int role_cur = _role;

    while (!env.isTerminate()) {
        Board state = env.getState();
        Position action = DefaultPoicy(state, role_cur, 1);  // Can we avoid this construct every time
        if (action.x != -1)
            env.step(action, role_cur);
        role_cur = -role_cur;
        //T *= decay_rate;
    }
    return env.winner();
}

// assert state should be in tree
// double MCTS::getValue(Board &state, Position &action, double c){
//     shared_ptr<UCTNode> node = shared_ptr<UCTNode>(&(tree[state]));



// }
// assert state should be in tree
Position MCTS::getMove(Board &state, int role, double c) {
    env.setState(state);
    vector<Position> actions = env.getLegalActions(role);
    shared_ptr<UCTNode> node = tree.find(state)->second;
    if (actions.size() == 0)
        return Position(-1, -1);
    Position best_action = *actions.begin();
    double best_value = node->getValue(best_action, role, c);
    double value;
    for (auto action: actions) {
        value = node->getValue(action, role, c);
        if (role == 1 && value >= best_value) {
            best_value = value;
            best_action = action;
        } else if (role == -1 && value <= best_value) {
            best_value = value;
            best_action = action;
        }

    }
    return best_action;
}

void MCTS::backup(shared_ptr<UCTNode> v, int reward) {
    shared_ptr<UCTNode> tmp = v;
    while (tmp) {
        tmp->addAccessTime();
        tmp->addReward(reward);
        tmp = tmp->getFather();
    }
}

shared_ptr<UCTNode> MCTS::newNode(Board state, shared_ptr<UCTNode> father, int role) {
    shared_ptr<UCTNode> expand_child =
            std::make_shared<UCTNode>(state, father, role);
    tree.insert({state, expand_child});
    return expand_child;
}

int randomSelect(double potent[], int size) {
    int i;
    double k;
    /*srand( (unsigned)time( NULL ));  
    k = rand()*1.0/RAND_MAX;*/
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    k = dis(gen);
    for (i = 0; i < size; i++) {
        k -= potent[i];
        if (k <= 0) return i;
    }
    return size - 1;
}

// TODO:
//Position MCTS::DefaultPoicy(Board &state, int role, double T)
//{
//    Env env;
//    vector<Position> poses;
//    vector<Position>::iterator iter;
//    double *potent;
//    double sum = 0;
//    int i, k;
//    int idx = 0;
//    //int T = 1;
//
//    env.setState(state);
//    poses = env.getLegalActions(role);
//    if (poses.size() == 0)
//        return Position(-1, -1);
//    potent = new double[poses.size()];
//  
//    for (iter = poses.begin(); iter != poses.end(); iter++)
//    {
//        env.setState(state);
//        env.step(*iter, role);
//        potent[idx] = dynamic_heuristic_evaluation_function(env, role, -role) / T;
//        sum += exp(potent[idx]);
//        idx++;
//    }
//
//    for (i = 0; i < idx; i++)
//        potent[i] = exp(potent[i])/sum;
//
//    k = randomSelect(potent, idx);
//
//    delete[] potent;
//
//    for (iter = poses.begin(); iter != poses.end(); iter++)
//    {
//        if (k == 0) return *iter;
//        k--;
//    }
//
//    return *poses.begin();
//    
//}
Position MCTS::DefaultPoicy(Board &state, int role, double T) {
    Env new_env;
    vector<Position> poses;
    vector<Position>::iterator iter;
    //double sum = 0;
    double value, bestValue;
    Position bestPos(-1, -1);
    //int T = 1;
    bestValue = -1e9;
    new_env.setState(state);
    poses = new_env.getLegalActions(role);
    if (poses.size() == 0)
        return Position(-1, -1);

    for (iter = poses.begin(); iter != poses.end(); iter++) {
        new_env.setState(state);
        new_env.step(*iter, role);
        //potent[idx] = dynamic_heuristic_evaluation_function(new_env, role, -role) / T;
        //            depth, oppo_role,
        value = AB(new_env, 7, -role, MIN, -1e9, 1e9);
        if (value > bestValue) {
            bestValue = value;
            bestPos = *iter;
        }
    }
    return bestPos;
}

