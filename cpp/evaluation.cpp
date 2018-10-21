#include "board.h"

int num_valid_moves(Env env, int color) {
    vector<Position> temp = env.getLegalActions(color);
    return temp.size();
}

/*
 * Assuming my_color stores your color and opp_color stores opponent's color
 * '-' indicates an empty square on the board
 * 'b' indicates a black tile and 'w' indicates a white tile on the board
 */
double dynamic_heuristic_evaluation_function(Env env, int my_color, int opp_color) {
    Board grid = env.getState();
    int my_tiles = 0, opp_tiles = 0, i, j, k, my_front_tiles = 0, opp_front_tiles = 0, x, y;
    double p = 0, c = 0, l = 0, m = 0, f = 0, d = 0;

    int X1[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int Y1[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int V[8][8] =
            {{20, -3, 11, 8,  8,  11, -3, 20},
             {-3, -7, -4, 1,  1,  -4, -7, -3},
             {11, -4, 2,  2,  2,  2,  -4, 11},
             {8,  1,  2,  -3, -3, 2,  1,  8},
             {8,  1,  2,  -3, -3, 2,  1,  8},
             {11, -4, 2,  2,  2,  2,  -4, 11},
             {-3, -7, -4, 1,  1,  -4, -7, -3},
             {20, -3, 11, 8,  8,  11, -3, 20}};

// Piece difference, frontier disks and disk squares
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            if (grid[i][j] == my_color) {
                d += V[i][j];
                my_tiles++;
            } else if (grid[i][j] == opp_color) {
                d -= V[i][j];
                opp_tiles++;
            }
            if (grid[i][j] != EMPTY) {
                for (k = 0; k < 8; k++) {
                    x = i + X1[k];
                    y = j + Y1[k];
                    if (x >= 0 && x < 8 && y >= 0 && y < 8 && grid[x][y] == EMPTY) {
                        if (grid[i][j] == my_color) my_front_tiles++;
                        else opp_front_tiles++;
                        break;
                    }
                }
            }
        }
    if (my_tiles > opp_tiles)
        p = (100.0 * my_tiles) / (my_tiles + opp_tiles);
    else if (my_tiles < opp_tiles)
        p = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);
    else p = 0;

    if (my_front_tiles > opp_front_tiles)
        f = -(100.0 * my_front_tiles) / (my_front_tiles + opp_front_tiles);
    else if (my_front_tiles < opp_front_tiles)
        f = (100.0 * opp_front_tiles) / (my_front_tiles + opp_front_tiles);
    else f = 0;

// Corner occupancy
    my_tiles = opp_tiles = 0;
    if (grid[0][0] == my_color) my_tiles++;
    else if (grid[0][0] == opp_color) opp_tiles++;
    if (grid[0][7] == my_color) my_tiles++;
    else if (grid[0][7] == opp_color) opp_tiles++;
    if (grid[7][0] == my_color) my_tiles++;
    else if (grid[7][0] == opp_color) opp_tiles++;
    if (grid[7][7] == my_color) my_tiles++;
    else if (grid[7][7] == opp_color) opp_tiles++;
    c = 25 * (my_tiles - opp_tiles);

// Corner closeness
    my_tiles = opp_tiles = 0;
    if (grid[0][0] == EMPTY) {
        if (grid[0][1] == my_color) my_tiles++;
        else if (grid[0][1] == opp_color) opp_tiles++;
        if (grid[1][1] == my_color) my_tiles++;
        else if (grid[1][1] == opp_color) opp_tiles++;
        if (grid[1][0] == my_color) my_tiles++;
        else if (grid[1][0] == opp_color) opp_tiles++;
    }
    if (grid[0][7] == EMPTY) {
        if (grid[0][6] == my_color) my_tiles++;
        else if (grid[0][6] == opp_color) opp_tiles++;
        if (grid[1][6] == my_color) my_tiles++;
        else if (grid[1][6] == opp_color) opp_tiles++;
        if (grid[1][7] == my_color) my_tiles++;
        else if (grid[1][7] == opp_color) opp_tiles++;
    }
    if (grid[7][0] == EMPTY) {
        if (grid[7][1] == my_color) my_tiles++;
        else if (grid[7][1] == opp_color) opp_tiles++;
        if (grid[6][1] == my_color) my_tiles++;
        else if (grid[6][1] == opp_color) opp_tiles++;
        if (grid[6][0] == my_color) my_tiles++;
        else if (grid[6][0] == opp_color) opp_tiles++;
    }
    if (grid[7][7] == EMPTY) {
        if (grid[6][7] == my_color) my_tiles++;
        else if (grid[6][7] == opp_color) opp_tiles++;
        if (grid[6][6] == my_color) my_tiles++;
        else if (grid[6][6] == opp_color) opp_tiles++;
        if (grid[7][6] == my_color) my_tiles++;
        else if (grid[7][6] == opp_color) opp_tiles++;
    }
    l = -12.5 * (my_tiles - opp_tiles);

// Mobility
    my_tiles = num_valid_moves(env, my_color);
    opp_tiles = num_valid_moves(env, opp_color);
    if (my_tiles > opp_tiles)
        m = (100.0 * my_tiles) / (my_tiles + opp_tiles);
    else if (my_tiles < opp_tiles)
        m = -(100.0 * opp_tiles) / (my_tiles + opp_tiles);
    else m = 0;

// final weighted score
    double score = (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d);
    return score;
}