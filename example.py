from dft import dft
import numpy as np
from math import sin, pi

x = np.empty(16, dtype=np.int32)

print(x)

for i in range(16):
    x[i] = sin(i * pi / 2)

X = dft(x)

print(X)