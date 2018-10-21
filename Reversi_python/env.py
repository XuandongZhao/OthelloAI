import numpy as np
class Env:
    __directions = [(1, 1), (1, 0), (1, -1), (0, -1), (-1, -1), (-1, 0), (-1, 1), (0, 1)]

    def __init__(self):
        # 1 black   -1 white
        self.state = np.zeros((8, 8))
        self.state[3][4] = 1
        self.state[4][3] = 1
        self.state[3][3] = -1
        self.state[4][4] = -1

    def __getitem__(self, index):
        return self.state[index]

    def setState(self, state):
        self.state = state

    def getState(self):
        return self.state

    def step(self, action, color):
        """ Perform the given move on the board, and flips pieces as necessary.
                color gives the color of the piece to play (1 for white, -1 for black) """
        # Start at the new piece's square and follow it on all 8 directions
        # to look for pieces allowing flipping
        square = (int(action / 8), action % 8)
        #print(square)
        # Add the piece to the empty square
        flips = (flip for direction in self.__directions
                 for flip in self._getFlips(square, direction, color))
        for x, y in flips:
            self.state[x][y] = color

    def getLegalActions(self, state, color):
        """ Return all the legal moves for the given color.
               (1 for black, -1 for white) """
        # Store the legal moves
        if color != 1 and color != -1:
            return []
        moves = set()
        # Get all the squares with pieces of the given color.
        for square in np.argwhere(state == color):
            # Find all moves using these pieces as base squares.
            newmoves = self.getMoves(square)
            # Store these in the moves set.
            moves.update(newmoves)
        moves = list(moves)

        for i , item in enumerate(moves):
            moves[i] = moves[i][0]*8 + moves[i][1]

        return moves

    def count(self, color):
        """ Count the number of pieces of the given color.
        (1 for black, -1 for white, 0 for empty spaces) """
        return np.count_nonzero(self.state == color)

    def getMoves(self, square):
        """ Return all the legal moves that use the given square as a base
        square. That is, if the given square is (3,4) and it contains a black
        piece, and (3,5) and (3,6) contain white pieces, and (3,7) is empty,
        one of the returned moves is (3,7) because everything from there to
        (3,4) can be flipped. """
        (x, y) = square
        # Determine the color of the piece
        color = self.state[x][y]

        # Skip empty source squares
        if color == 0:
            return None

        # Search all possible directions
        moves = []
        for direction in self.__directions:
            move = self._discoverMove(self.state, square, direction)
            if move:
                moves.append(move)
        # Return the generated list of moves
        return moves

    def isTerminate(self):
        return self._isTerminate(self.state)

    def _isTerminate(self, state):
        listwhite = self.getLegalActions(state, -1)
        listblack = self.getLegalActions(state, 1)
        if (len(listwhite) == 0 and len(listblack) == 0):
            return True
        else:
            return False

    def BlackWins(self):
        if not self.isTerminate():
            raise AssertionError("game is not over, can not determined who wins")
        else:
            return self._whowins(self.state)
            # if self._whowins(self.state) == 1:
            #     return 1
            # else:
            #     return -1

    def _whowins(self, state):
        black_count = self.count(1)
        white_count = self.count(-1)
        if black_count > white_count:
            return 1
        elif white_count > black_count:
            return -1
        else:
            return 0

    def _discoverMove(self, state, origin, direction):
        """ Return the endpoint of a legal move, starting at the given origin,
        and moving in the given direction. """
        x, y = origin
        color = state[x][y]
        flips = []

        for x, y in Env._incrementMove(origin, direction):
            if state[x][y] == 0 and flips:
                return x, y
            elif state[x][y] == color or (state[x][y] == 0 and not flips):
                return None
            elif state[x][y] == -color:
                flips.append((x, y))

    def _getFlips(self, origin, direction, color):
        """ Get the list of flips for a vertex and a direction to use within
        the execute_move function. """
        # Initialize variable
        flips = [origin]

        for x, y in Env._incrementMove(origin, direction):
            if self.state[x][y] == -color:
                flips.append((x, y))
            elif self.state[x][y] == 0 or (self.state[x][y] == color and len(flips) == 1):
                break
            elif self.state[x][y] == color and len(flips) > 1:
                return flips
        return []

    @staticmethod
    def _incrementMove(move, direction):
        """ Generator expression for incrementing moves """
        move = list(map(sum, list(zip(move, direction))))
        while all(list(map(lambda x: 0 <= x < 8, move))):
            yield move
            move = list(map(sum, list(zip(move, direction))))

    def display(self, time):
        """" Display the board and the statistics of the ongoing game. """
        print("    0 1 2 3 4 5 6 7")
        print("    ---------------")
        for x in range(8):
            # Print the row number
            print(str(x) + ' |', end=' ')
            for y in range(8):
                # Get the piece to print
                space = self.state[x][y]
                if space == 1:
                    print("B", end=' ')
                elif space == -1:
                    print("W", end=' ')
                else:
                    print(".", end=' ')
            print('| ' + str(x))

        print("    ---------------")
        print("    0 1 2 3 4 5 6 7\n")

        print("STATISTICS (score / remaining time):")
        print("Black: {} / {} min {} sec".format(str(self.count(1)), str(divmod(int(time[1]), 60)[0]), str(divmod(int(time[1]), 60)[1])))
        print("White: {} / {} min {} sec\n".format(str(self.count(-1)), str(divmod(int(time[-1]), 60)[0]), str(divmod(int(time[-1]), 60)[1])))