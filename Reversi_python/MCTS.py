import numpy as np
from util import getBestAction, makeHashable
import pickle

def hash(board):
    return ''.join([str(int(board[i][j])+1) for i in range(8) for j in range(8)])

class Table:
    def __init__(self):
        self.t = {}

    def increment(self, key, value):
        key = makeHashable(key)
        if key not in self.t:
            self.t[key] = value
        else:
            self.t[key] += value
    
    def QUpdate(self, key, new_value, alpha):
        key = makeHashable(key)
        if key not in self.t:
            self.t[key] = alpha * new_value
        else:
            self.t[key] = (1 - alpha) * self.t[key] + alpha * new_value

    def __getitem__(self, key):
        key = makeHashable(key)
        if key not in self.t:
            return 1
        else:
            return self.t[key]

"""
MSTC is a collection of tree nodes with hierarchy. It querys tree node for useful information. During the trainig phase, it chooses one path to explore and then backs up information and updates values from leaf node up to root node. During the test phase, it gives an action given a state.  
"""
class MSTC:
    def __init__(self, env, start_state, TP, role="black"):
        self.root_state = start_state
        self.env = env
        self.reward = 0
        self.tree =  []  # node has been visited
        self.N = Table()
        self.Q = Table()
        self.Value = Table()
        self.state_count = Table()
        self.role = role
        self.TP = TP


    def play(self):
        policy = []
        while not self.env.isTerminate():
            a = self.search(self.env.getState())
            policy.append(a)
            self.env.step(a)
        return self.env.BlackWins(), policy

    def search(self, state, time=10):
        while time > 0:
            self.simulate(state.copy())
            time -= 1
        self.env.setState(state)
        if self.role == 'black':
            return self.getMove(state, 1)
        else:
            return self.getMove(state, -1)

    def simulate(self, state):
        self.env.setState(state)
        epoch_history, role = self.simulateTree()
        reward = self.simulateDefault(state, role)
        self.backup(epoch_history, reward)

    #history is  s0, a0, s1, a1, ... sn, an, s_stop
    def simulateTree(self):
        if self.role == 'black': role = 1
        else: role = -1
        epoch_history = []
        while not self.env.isTerminate():
            state = self.env.getState()
            if str(state) not in self.tree:
                self.new_node(state)  # add to the tree
                epoch_history.append((state.copy(), "roll_out")) #
                return epoch_history, role
            else:
                action = self.getMove(state, role)
                if action != -1:
                    epoch_history.append((state.copy(), action))
                    self.env.step(action, role)
            role = -role
        return epoch_history, role   # S_T is not included 

    '''
    def simulateDefault(self, state):
        while not self.env.isTerminate():
            action = self.DEFAULT_POLICY(state)
            self.env.step(action)
        return self.env.BlackWins()
    '''
    def simulateDefault(self, state, role):
        while not self.env.isTerminate():
            key = hash(state)
            step = 59 - np.count_nonzero(state == 0)
            if key in self.TP[step]:
                return self.TP[step][key][1]
            else:
                action = self.DEFAULT_POLICY(state, role)
                if action != -1:
                    self.env.step(action, role)
            role = -role
        return self.env.BlackWins()
            
    def getValue(self, state, action, c):
        return self.Q[(str(state), action)] + c * np.sqrt(np.log(self.state_count[state] / self.N[(str(state), action)]))

    def getMove(self, state, role, c=0.1):
        actions = self.env.getLegalActions(state, role)
        if len(actions) == 0: return -1
        if self.role == 1:
            values = [self.getValue(state, a, c) for a in actions]
            action = getBestAction(values, "max")
        else:
            values = [self.getValue(state, a, c) for a in actions]
            action = getBestAction(values, "min")
        return actions[action]

    def backup(self, epoch_history, reward, alpha=0.5):
        for state, action in epoch_history:
            self.state_count.increment(state, 1)
            if action == "roll_out": # new node
                #self.Value[state] = (1-alpha) * self.Value[state] + alpha * reward # what to backup for new node?
                self.Value.QUpdate(state, reward, alpha)
            else:
                self.N.increment((str(state), action), 1)
                #self.Q[(state, action)] = (1-alpha) * self.Q[(state, action)] + alpha * reward
                self.Q.QUpdate((str(state), action), reward, alpha)

    def new_node(self, state):
        self.tree.append(str(state))

    def DEFAULT_POLICY(self, state, role):   # a random default policy
        actions = self.env.getLegalActions(state, role)
        if actions:
            return np.random.choice(actions)
        else:
            return -1