import subprocess
import time
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import random

import pickle




def create_inputs(n_max,dimension,step):
    list_inputs = []
    for n in np.arange(4,n_max+1,step):
        if dimension == '2d':
            m = n
            seq=str(n)+' '+str(m)+" "+''.join(random.choices(['A','T','C','G','-'],k=n))+' '+\
            ''.join(random.choices(['A','T','C','G','-'],k=m))
            list_inputs.append(seq)
        else:
            for m in np.arange(4,n_max+1,step):
                # m = random.randint(n,n*5)
                # m = n # comentar caso tenha m diferente
                seq=str(n)+' '+str(m)+" "+''.join(random.choices(['A','T','C','G','-'],k=n))+' '+\
                ''.join(random.choices(['A','T','C','G','-'],k=m))
                list_inputs.append(seq)
    return list_inputs


def get_list_program(list_alg,list_inputs):
    list_execute=[]
    for i in list_alg:
        for input_ in list_inputs:
            n = input_.split()[0]
            m = input_.split()[1]
            start = time.perf_counter()
            proc = subprocess.run([i], input=input_, text=True, capture_output=True)
            end = time.perf_counter()
            algoritmo = list_alg[i]
            dic = {
                'Tempo':float(end-start),
                'Saida':int(proc.stdout.split()[-1]),
                'n': int(n),
                'm': int(m),
                'Algoritmo': algoritmo
            }
            list_execute.append(dic)
            with open('outfile', 'wb') as fp:
                pickle.dump(list_execute, fp)
    return list_execute

list_alg = {'./exaustive_search/main' : 'Exaustive Search',
            './gpu_parallel/main' : 'GPU Exaustive Search'}

list_inputs = create_inputs(2000,'2d',250)
list_execute = get_list_program(list_alg,list_inputs)

df = pd.DataFrame(list_execute)
df= df.apply(pd.to_numeric,errors="ignore")
df.to_csv("my_data.csv", index=False)


# df.pivot(index='n',columns='Algoritmo',values='Tempo').plot();
