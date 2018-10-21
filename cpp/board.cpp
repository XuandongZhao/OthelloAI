#include "board.h"
#include "configure.h"
#include <vector>
#include <iostream>

using namespace std;

const int BLACK = 1;
const int EMPTY = 0;
const int WHITE = -1;

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
    this->value = 0;
}

Position::Position(const Position &pos) {
    x = pos.x;
    y = pos.y;
    value = pos.value;
}

Position &Position::operator=(const Position &pos) {
    x = pos.x;
    y = pos.y;
    value = pos.value;
    return *this;
}

bool Position::operator<(const Position &pos) const {
    return (x < pos.x) || (x == pos.x && y < pos.y);
}

Board::Board() {
    int i;
    for (i = 0; i < 64; i++)
        state[i] = EMPTY;
}

Board::Board(const Board &board) {
    int i;
    for (i = 0; i < 64; i++)
        state[i] = board.state[i];
}

char *Board::operator[](int k) {
    return &state[k * 8];
}

Board &Board::operator=(const Board &board) {
    int i;
    for (i = 0; i < 64; i++)
        state[i] = board.state[i];
    return *this;
}

BitBoard Board::toBit() {
    int i, j;
    BitBoard bb;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (state[i * 8 + j] == BLACK)
                bb.b.set(i * 8 + j);
            else if (state[i * 8 + j] == WHITE)
                bb.w.set(i * 8 + j);
            else
                bb.e.set(i * 8 + j);
    return bb;
}

string Board::toString() {
    int i, j;
    char s[65];
    s[64] = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (state[i * 8 + j] == BLACK)
                s[i * 8 + j] = 2;
            else if (state[i * 8 + j] == WHITE)
                s[i * 8 + j] = 0;
            else
                s[i * 8 + j] = 1;
    return string(s);
}

bool Board::operator<(const Board &board) const {
    int i;
    for (i = 0; i < 64; i++) {
        if (state[i] < board.state[i]) return true;
        if (state[i] > board.state[i]) return false;
    }
    return false;
}

Env::Env() {
    board[3][3] = board[4][4] = WHITE;
    board[3][4] = board[4][3] = BLACK;
}

void Env::setState(Board &board) {
    this->board = board;
}

Board Env::getState() {
    return board;
}

static bool _test(Board &board, Position &pos, int color, int dx, int dy) {
    int x, y;
    int state = 0;
    x = pos.x + dx;
    y = pos.y + dy;
    while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
        if (state == 0) {
            if (color == BLACK && board[x][y] != WHITE) return false;
            if (color == WHITE && board[x][y] != BLACK) return false;
            state = 1;
        } else {
            if (board[x][y] == EMPTY) return false;
            if (color == board[x][y]) return true;
        }
        x += dx;
        y += dy;
    }
    return false;
}

static void _update(Board &board, Position &pos, int color, int dx, int dy) {
    int x, y;
    x = pos.x;
    y = pos.y;
    while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
        if (color == board[x][y] && (x != pos.x || y != pos.y)) break;
        board[x][y] = color;
        x += dx;
        y += dy;
    }
}

void Env::step(Position pos, int color) {
    if (board[pos.x][pos.y] != EMPTY) return;
    if (_test(board, pos, color, -1, -1))
        _update(board, pos, color, -1, -1);
    if (_test(board, pos, color, -1, 0))
        _update(board, pos, color, -1, 0);
    if (_test(board, pos, color, -1, 1))
        _update(board, pos, color, -1, 1);
    if (_test(board, pos, color, 0, -1))
        _update(board, pos, color, 0, -1);
    if (_test(board, pos, color, 0, 1))
        _update(board, pos, color, 0, 1);
    if (_test(board, pos, color, 1, -1))
        _update(board, pos, color, 1, -1);
    if (_test(board, pos, color, 1, 0))
        _update(board, pos, color, 1, 0);
    if (_test(board, pos, color, 1, 1))
        _update(board, pos, color, 1, 1);
}

void addLegal(vector<Position> &list, Board &board, Position &pos, int color, int dx, int dy) {
    int x, y;
    int state = 0;
    x = pos.x + dx;
    y = pos.y + dy;
    while (x >= 0 && x <= 7 && y >= 0 && y <= 7) {
        if (state == 0) {
            if (color == BLACK && board[x][y] != WHITE) return;
            if (color == WHITE && board[x][y] != BLACK) return;
            state = 1;
        } else {
            if (board[x][y] == EMPTY) {
                list.push_back(Position(x, y));
                return;
            }
            if (color == board[x][y]) return;
        }
        x += dx;
        y += dy;
    }
}

vector<Position> Env::getLegalActions(int color) {
    int i, j;
    vector<Position> list = vector<Position>();
    if (count(EMPTY) < 30) {
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++) {
                if (board[i][j] != color) continue;
                Position pos = Position(i, j);
                addLegal(list, board, pos, color, -1, -1);
                addLegal(list, board, pos, color, -1, 0);
                addLegal(list, board, pos, color, -1, 1);
                addLegal(list, board, pos, color, 0, -1);
                addLegal(list, board, pos, color, 0, 1);
                addLegal(list, board, pos, color, 1, -1);
                addLegal(list, board, pos, color, 1, 0);
                addLegal(list, board, pos, color, 1, 1);
            }
    } else {
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++) {
                if (board[i][j] != EMPTY) continue;
                Position pos = Position(i, j);
                if (_test(board, pos, color, -1, -1)
                    || _test(board, pos, color, -1, 0)
                    || _test(board, pos, color, -1, 1)
                    || _test(board, pos, color, 0, -1)
                    || _test(board, pos, color, 0, 1)
                    || _test(board, pos, color, 1, -1)
                    || _test(board, pos, color, 1, 0)
                    || _test(board, pos, color, 1, 1))
                    list.push_back(pos);
            }
    }
    return list;
}

int Env::count(int color) {
    int i, j, res = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            res += board[i][j] == color;
    return res;
}

bool Env::isTerminate() {
    vector<Position> temp1, temp2;
    temp1 = getLegalActions(BLACK);
    temp2 = getLegalActions(WHITE);
    return temp1.empty() && temp2.empty();
}

int Env::winner() {
    int temp1 = count(BLACK);
    int temp2 = count(WHITE);
    if (temp1 > temp2)
        return 1;
    else if (temp2 > temp1)
        return -1;
    return 0;
}

void Env::display() {
    int i, j;
    cout << "   0 1 2 3 4 5 6 7" << endl;
    cout << "   ---------------" << endl;
    for (i = 0; i < 8; i++) {
        cout << i << "| ";
        for (j = 0; j < 8; j++)
            if (board[i][j] == BLACK)
                cout << "# ";
            else if (board[i][j] == WHITE)
                cout << "O ";
            else
                cout << ". ";
        cout << "| " << i << endl;
    }
    cout << "   ---------------" << endl;
    cout << "   0 1 2 3 4 5 6 7" << endl;
    cout << "Black: " << count(BLACK) << endl;
    cout << "White: " << count(WHITE) << endl;
}
