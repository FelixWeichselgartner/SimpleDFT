from SimpleDFT import PyDFT, PyFFT
import numpy as np
from math import sin, pi

x = np.empty(16, dtype=np.int32)
print(x)

for i in range(16):
    x[i] = sin(i * pi / 2)

X_SimpleDFT = np.around(PyDFT(x), decimals=2)
X_SimpleFFT = np.around(PyFFT(x), decimals=2)
X_Numpy = np.fft.fft(x)

for i in range(16):
    print(f'{X_SimpleDFT[i]}\t\t {X_SimpleFFT[i]}\t\t {X_Numpy[i]}')