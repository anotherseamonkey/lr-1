import matplotlib.pyplot as plt
from scipy import stats
import numpy as np
import os

def get_matrix(name):
    with open(name, 'r')  as file:
        mat = []
        for j in file.readlines():
            mat.append(j.strip().split())
        return np.array(mat, dtype=float)


n = [10, 20, 50, 100, 250, 500, 700, 1000, 1500, 2000, 2500]

for i in n:
    A_mat = os.path.join('matrices', f'Matrix A if n = {i}')
    B_mat = os.path.join('matrices', f'Matrix B if n = {i}')
    C_mat = os.path.join('matrices', f'Matrix C if n = {i}')

    A = get_matrix(A_mat)
    B = get_matrix(B_mat)
    C = get_matrix(C_mat)

    C_new = np.array(np.dot(A,B), dtype=float)

    if np.allclose(C, C_new, atol=1e-4):
        print(f'True for {i}x{i}')
    else:
        print(f'False for {i}x{i}')

time = []

for i in n:
    time_file = os.path.join('matrices', f'Time for N = {i}')
    with open(time_file, 'r') as file:
        for j in file.readlines():
            if 'time (s)' in j:
                time.append(float(j.strip().replace('time (s): ', '')))

mean = np.mean(time)
ci = stats.t.interval(confidence= .80, loc=np.mean(time), scale=stats.sem(time), df=len(time)-1)


fig, ax = plt.subplots()
ax.plot(n, time)
ax.errorbar(n, time, yerr=[[mean - ci[0]], [ci[1] - mean]], fmt='.', mfc='r', capsize=5, ecolor='r')
ax.set(xlabel='Matrix size N', ylabel='Time (s)', title='Matrix Size vs Execution Time')
ax.grid(True)
plt.show()