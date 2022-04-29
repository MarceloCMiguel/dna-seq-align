import random
import numpy as np
n_max = 20
txt = 1
for n in np.arange(4,n_max+1,1):
    for m in np.arange(4,n_max+1,1):
        # m = random.randint(n,n*5)
        # m = n # comentar caso tenha m diferente
        seq=[str(n)+'\n',
        str(m)+'\n',
        ''.join(random.choices(['A','T','C','G','-'],k=n))+'\n',
        ''.join(random.choices(['A','T','C','G','-'],k=m))]
        file = f'in{txt}.txt'
        f = open(file,'w')
        f.writelines(seq)
        f.close()
        txt+=1