import numpy as np
import json
# a better vestion of argmax(min), break tie by choosing random best action
def getBestAction(lst, option):
    if option == "min":
        v = min(lst)
    elif option == "max":
        v = max(lst)
    else:
        raise AssertionError("option is not valid")
    candidate_idx = [i for i, e in enumerate(lst) if e == v]
    return np.random.choice(candidate_idx)


def makeHashable(key):
    if key.__hash__:
        return key
    else:
        return str(key)

def sigmoid(a):
    return np.exp(a) / (np.exp(a) + 1)