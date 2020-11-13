import numpy as np
import matplotlib.pyplot as plt

file = open("lattice.txt", "r");
a = np.str(file.read()).split('\n')
N = len(a) - 1
for i in range(N):
    a[i] = list(a[i])
x = np.array(a[0:N], dtype=int)

plt.title(r"2D Ising Model (100$\times$100 lattice): T = 4.0")
plt.imshow(x)
plt.show()

#print(np.sum(1 - 2*x))
