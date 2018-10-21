from env import *
import random
import pickle
from MCTS import MSTC

with open('tp.pk', 'rb') as f:
    TP = pickle.load(f)
    print('load successfully')

def hash(board):
    return ''.join([str(int(board[i][j])+1) for i in range(8) for j in range(8)])

env = Env()
env.display((60,60))
while not env.isTerminate():
    # mstc = MSTC(env, env.getState(), TP)
    # policy = mstc.search(env.getState())
    # print(policy)
    # env.step(policy, 1)
    # env.display((60, 60))
    # x, y = map(int, input().split())
    # env.step(x*8+y, -1)
    # env.display((60,60))
    
    
    origin_state = env.getState().copy()
    policy = (-1, -2)#location is -1, value is -2
    potential = env.getLegalActions(env.getState(), 1)
    if (potential == []): 
        print('no move')
        continue
    for step in potential:
        env.setState(origin_state.copy())
        env.step(step, 1)
        key = hash(env.getState())
        if key in TP[59 - env.count(0)]:
            if TP[59 - env.count(0)][key][1] > policy[1]:
                policy = (step, TP[59 - env.count(0)][key][1])
                count = TP[59 - env.count(0)][key][0]
    if policy[0] == -1:
        print('no match')
        policy = (random.sample(potential, 1)[0], 0)
    env.setState(origin_state)
    env.step(policy[0], 1)
    env.display((60,60))
    print(count, policy[1])

    x, y = map(int, input().split())
    env.step(x*8+y, -1)
    env.display((60,60))
