import numpy as np
import matplotlib.pyplot as plt
import csv

file = open("quantities.csv", "r");
a = np.array(list(csv.reader(file, delimiter=' ')), dtype=float)

plt.title("Magnetization")
plt.xlabel("T")
plt.ylabel("M")
plt.plot(a[:, 0], a[:, 1],'.')
plt.axvline(2.69, c='r', ls='--')
plt.show()

plt.title("Energy")
plt.xlabel("T")
plt.ylabel("E")
plt.plot(a[:, 0], a[:, 2],'.')
plt.axvline(2.69, c='r', ls='--')
plt.show()

plt.title("Susceptibility")
plt.xlabel("T")
plt.ylabel("X")
plt.plot(a[:, 0], a[:, 3],'.')
plt.axvline(2.69, c='r', ls='--')
plt.show()

plt.title("Specific Heat")
plt.xlabel("T")
plt.ylabel("C")
plt.plot(a[:, 0], a[:, 4],'.')
plt.axvline(2.69, c='r', ls='--')
plt.show()

t = (2.69-a[:,0]) / 2.69
plt.title("Log-log Plot of Magnetization versus Reduced Temperature")
plt.xlabel("(Tc-T)/Tc")
plt.ylabel("M")
plt.loglog(t, a[:, 1], ".")
plt.show()

t = np.abs(2.69-a[:,0]) / 2.69
plt.title("Log-log Plot of Susceptibility versus Reduced Temperature")
plt.xlabel("|T-Tc|/Tc")
plt.ylabel("X")
plt.loglog(t, a[:, 3], ".")
plt.show()
