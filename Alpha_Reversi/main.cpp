#include "core/uct.h"
#include "core/network.h"
#include <iostream>


#define MACHINE_TIME 3

void mainServer(bool first, int ai_seconds)
{

    MatrixXd board;
    reversiInit(board);

    bool turn(first);

    while (!reversiIsTerminal(board))
    {
        if (turn)
        {
            UCTTree uctt(board, first, Position(-1, -1));
            Position best_AI_pos;
            std::printf("Now it is machine move\n");
            if (uctt.UCTSearch(ai_seconds, best_AI_pos))
            {
                std::printf("machien choose to do ");
                std::printf("AI (%d, %d)\n", best_AI_pos.x(), best_AI_pos.y());
                reversiStepOnPos(board, best_AI_pos, first);
            }
            else
            {
                std::cout << "PASS!" << std::endl;
            }
            turn = !turn;
        }
        else
        {
            std::cout << '\n' << board << std::endl;
            int x, y;
            // std::cin >> "your move:please enter x-pos and then y pos like \' 4 5 \'" >> std::endl;
            // std::cin >> "x-pos ranges from 0 to 7. So is y-pos" >> std::endl;
            std::printf("your move. Please enter your decision\n");
            std::cin >> x >> y;
            reversiStepOnPos(board, Position(x, y), !first);
            std::cout << '\n' << board << std::endl;
            turn = !turn;
        }
    }
}

int main()
{
    bool machine_first=false;
    printf("-1 -> machine\n1 -> you\n the chess board is a 8*8 matrix ranging from 0 to 7\n");
    printf("for example,\'2 3\' means the 3rd row and 4th column\n");
    // std::string a = get_trun(8);
    // std::cout << a << std::endl;
    mainServer(machine_first, MACHINE_TIME);
}
