import json
import numpy as np
import pickle
from env import Env

def hash(board):
    return ''.join([str(int(board[i][j])+1) for i in range(8) for j in range(8)])

def save(training_position):
    with open('tp.pk', 'wb') as f:
        pickle.dump(training_position, f)

def load(file_name):
    with open(file_name, 'rb') as f:
        return pickle.load(f)

def updateTP(TP, board, result):
    key = hash(board)
    if key in TP.keys():
        count, last_value = TP[key]
        TP[key] = (count + 1, (count * last_value + result)*1.0 / (count+1))
    else:
        TP[key] = (1, result)

if __name__ == '__main__':
    total = 0
    training_position = load('tp.pk')
    #training_position = list()
    #for i in range(90):
    #    training_position.append(dict())

    for start in range(0, 1362):
    #for start in range(0,1359): 
        with open('Reversi-2018-3/%s-%s.matches'%(str(start*100+1), str(start*100+100)),'r', encoding='utf-8') as f:
            file_total = 0
            for line in f.readlines():
                #0 is black
                log = json.loads(line)['log'][1:]
                if 'err' in log[len(log)-1]['output']['display']: continue          
                file_total += 1      
                
                history = list()
                board = Env()
                i = 0
                while i<len(log):
                    if i%4 :#white -1
                        if log[i]['1']['response']['x'] != -1:
                            board.step(log[i]['1']['response']['x'] * 8 + log[i]['1']['response']['y'], -1)
                        history.append((board.getState().copy(), int(i/2)))
                    else:#black 1
                        if log[i]['0']['response']['x'] != -1:
                            board.step(log[i]['0']['response']['x'] * 8 + log[i]['0']['response']['y'], 1)
                        history.append((board.getState().copy(), int(i/2)))
                    i += 2

                if board.isTerminate():
                    result = board.BlackWins()
                    for state in history:
                        updateTP(training_position[state[1]], state[0], result)
                    file_total += 1
                
            print('%s-%s has been handled, %d valid'%(str(start*100 + 1), str(start*100+100), file_total))
            if (start+1) % 100 == 0:
                save(training_position)
                print('%s has been saved'%str(start*100+100))
            total += file_total
            
    save(training_position)
    print("saved")
    print("%d valid"%(total))
