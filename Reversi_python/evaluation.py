from util import sigmoid
import numpy as np
"""
taking a state and give a estimated value of current state
"""
class EvalFun():
    def __init__(self, *arg):
        self.patterns = []
        for pattern in arg:
            self.patterns.append(pattern)
        self.debug = True

    def evaluate(self, state):
        weighted_sum = 0
        for pattern in self.patterns:
            weighted_sum += pattern.getSum(state)
        return sigmoid(weighted_sum)

    def train(self, train_seq):
        error = 0
        N = len(train_seq)
        for state, reward in train_seq:
            p = self.evaluate(state)
            factor = abs(reward - p) * p * (1 - p) / N
            pattern.bp(state, factor)
            if self.debug:
                error += (reward - p) ** 2 / N

class Pattern:
    def __init__(self, max_val):
        self.max_val = max_val
        self.weight = np.zeros(max_val)

    def recognize(self, state):
        # return the id for this state of this pattern, should be a number in [0, max_val)
        pass

    def getSum(self, state):
        #sum(self.weight * self.recognize(state))
        return self.weight[self.recognize(state)]

    def bp(self, state, factor, lr=1e-2):
        id = self.recognize(state)
        self.weight[id] -= lr * factor

