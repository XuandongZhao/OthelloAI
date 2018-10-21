import pickle

with open('tp.pk', 'rb') as f:
    TP = pickle.load(f)

idx = 59
#for tp in TP:
tp = TP[58]
with open('tp' + str(idx) + '.txt', 'w') as f:
    for key in tp.keys():
        f.write(key + ' ')
        f.write(str(tp[key][0]) + ' ')
        f.write(str(tp[key][1]) + '\n')
    f.write('\n')
    print(idx)
    idx += 1
