"""
Eric P. Nichols
Feb 8, 2008

This is a human move engine. It simply reads and validates user input
to get the move to make.
"""

from board import print_moves
from engines import Engine


class HumanEngine(Engine):
    """ Game engine that reads user input to get the move to make. """

    def get_move(self, board, color, move_num=None,
                 time_remaining=None, time_opponent=None):
        """ Provide an interactive console for the human player to make moves.
        Use parse_input to process the data. """
        # Generate the legal moves
        legal_moves = board.get_legal_moves(color)
        player = {-1: "(B)", 1: "(W)"}

        # Request the move
        user_input = raw_input("Enter your move " + player[color] + ": ")
        move = HumanEngine.parse_input(legal_moves, user_input)
        while move is None:
            print "This move is invalid. The legal moves are: "
            print_moves(sorted(legal_moves))
            user_input = raw_input("\nEnter your move " + player[color] + ": ")
            move = HumanEngine.parse_input(legal_moves, user_input)

        return move

    @staticmethod
    def parse_input(legal_moves, user_input):
        """ Verify that the move is in the list of legal moves. Return either a
        valid move or None if the move is invalid. """
        # Verify length
        if len(user_input) == 2:
            xc = user_input[0].lower()
            yc = user_input[1].lower()

            # Validate range
            if 'a' <= xc <= 'h' and '1' <= yc <= '8':
                x = ord(xc) - ord('a')  # Convert letter to number from 0 to 7
                y = int(yc) - 1  # Convert numeral to number from 0 to 7

                # Create move
                move = (x, y)

                # Validate move
                if move in legal_moves:
                    return move
                else:
                    return None


engine = HumanEngine
