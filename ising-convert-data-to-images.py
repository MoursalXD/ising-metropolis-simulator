import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


df = pd.DataFrame(pd.read_csv('ising-output.dat', sep='\t', header=-1, names=['run','x','y']))
df.head()


for run in range(np.max(df['run'])+1):
    plt.scatter(df[df['run']==run]['x'], df[df['run']==run]['y'], c='grey', marker=',')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.rcParams["figure.figsize"] = (8,8)
    plt.xlabel('x')
    plt.ylabel('y')
    filename = 'ising' + str(run) +'.png'
    plt.savefig(filename)
    plt.show()