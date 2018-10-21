#include "cpp/board.h"
#include "cpp/MCTS.h"
#include "cpp/network.h"
#include "cpp/autoPlay.h"
#include <vector>
#include <iostream>

using namespace std;

void mainServer(bool first, int ai_seconds, int id) {
    Env env;
    int x, y;
    int SESSION_ID = id;
    Network net;

    env.display();
    bool turn(first);

    while (!env.isTerminate()) {
        if (turn) { //AI turn
            cout << "machine turn" << endl;
            string player = "W";
            Board board;
            env.setState(board);
            env.display();
            turn = !turn;
        } else { //you turn
            string player = "B";
            cout << "Please enter your move:" << endl;
            cin >> x >> y;
            if (x > 7 || y > 7) {
                cout << "invalid input" << endl;
                continue;
            }
            env.step(Position(x, y), BLACK);
            env.display();
            turn = !turn;
        }
    }
}

//    Env env;
//    Network net;
//    int x, y;
//    int SESSION_ID = id;
//    string player = "W";
//    if (first)
//        player = "B";
//
//    while (!env.isTerminate()) {
//        if (net.get_trun(id) == player) { //my move
//            x = 0;
//            y = 0; //use AI to get
//            while (true) {
//                try {
//                    if (net.get_move(x, y, SESSION_ID, player) == "SUCCESS") {
//                        env.step(Position(x, y), BLACK);
//                        env.display();
//                        break;
//                    } else {
//                        cout << "invalid move" << endl;
//                    }
//                } catch (...) {
//                    cout << "unexcept error" << endl;
//                }
//            }
//        } else {
//            sleep(ai_seconds);
//        }
//    }

void aivsai(bool first, int ai_seconds, int id) {
    vector<Position> list;
    vector<Position>::iterator iter;
    double value, bestValue;
    Position bestPos(-1, -1);
    Env env;
    Board board;
    Network net;
    int SESSION_ID = id;
    string player = net.create_session(id);
    cout << "Game begin " << player << endl;
    env.display();
    if (player == "B") {
        cout << "I am black" << endl;
        while (!env.isTerminate()) {
            if (net.get_trun(SESSION_ID) == player) {
                board = net.board_string(SESSION_ID);
                env.setState(board);
                env.display();
                cout << "Oppoent choose " << net.board_last(SESSION_ID) << endl;

                list = env.getLegalActions(BLACK);
                board = env.getState();
                bestValue = -1e9;
                if (list.size() != 0) {
                    for (iter = list.begin(); iter != list.end(); iter++) {
                        env.setState(board);
                        env.step(*iter, BLACK);
                        value = AB(env, 7, WHITE, MIN, -1e9, 1e9);
                        if (value > bestValue) {
                            bestValue = value;
                            bestPos = *iter;
                        }
                    }
                    env.setState(board);
                    env.step(bestPos, BLACK);
                }
                cout << "My AI choose: (" << bestPos.x << " " << bestPos.y << ")" << endl;
                net.get_move(bestPos.x, bestPos.y, SESSION_ID, player);
                env.display();
            } else {
                Sleep(2);
            }
        }
    } else if (player == "W") {
        cout << "I am white" << endl;
        while (!env.isTerminate()) {
            if (net.get_trun(SESSION_ID) == player) {
                board = net.board_string(SESSION_ID);
                env.setState(board);
                env.display();
                cout << "Oppoent choose " << net.board_last(SESSION_ID) << endl;

                list = env.getLegalActions(WHITE);
                board = env.getState();
                bestValue = -1e9;
                if (list.size() != 0) {
                    for (iter = list.begin(); iter != list.end(); iter++) {
                        env.setState(board);
                        env.step(*iter, WHITE);
                        value = AB(env, 7, BLACK, MIN, -1e9, 1e9);
                        if (value > bestValue) {
                            bestValue = value;
                            bestPos = *iter;
                        }
                    }
                    env.setState(board);
                    env.step(bestPos, WHITE);
                }
                cout << "My AI choose: (" << bestPos.x << " " << bestPos.y << ")" << endl;
                net.get_move(bestPos.x, bestPos.y, SESSION_ID, player);
                env.display();
            } else {
                Sleep(2);
            }
        }
    }
}

void humanVShuman() {
    Env env;
    int x, y;
    env.display();
    while (!env.isTerminate()) {
        cin >> x >> y;
        env.step(Position(x, y), BLACK);
        env.display();
        cin >> x >> y;
        env.step(Position(x, y), WHITE);
        env.display();
    }
}

int main() {
//    int choice, ai_seconds, id;
//    cout << "Please choose player and set time limits" << endl;
//    cout << "1 : human vs AI (first move)" << endl;
//    cout << "2 : AI vs human (second move)" << endl;
//    cout << "3 : AI vs AI (my first)" << endl;
//    cout << "4 : AI vs AI (my second)" << endl;
//    cout << "5 : human vs human" << endl;
//    cin >> choice >> ai_seconds >> id;
//    if (choice == 1) {
//        mainServer(false, ai_seconds, id);
//    } else if (choice == 2) {
//        mainServer(true, ai_seconds, id);
//    } else if (choice == 3) {
//        aivsai(true, ai_seconds, id);
//    } else if (choice == 4) {
//        aivsai(false, ai_seconds, id);
//    } else {
//        humanVShuman();
//    }
//    aivsai(false, 3, 8);
    humanVShuman();
    return 0;
}
