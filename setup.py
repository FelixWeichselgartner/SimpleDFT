import os
import numpy as np
from distutils.core import setup, Extension

ext_module = Extension('_SimpleDFT',
                       sources=['SimpleDFT_wrap.c', 'SimpleDFT.c'],
                       depends=['SimpleDFT.h'],
                       include_dirs=[np.get_include()],
                       )

setup( name = 'SimpleDFT',
       version = '0.1',
       description = "A simple Discrete Fourier Transformation and Fast Fourier Transformation implementation with SWIG generated python interface.",
       author='Felix Weichselgartner',
       ext_modules = [ext_module],
       py_modules = ["SimpleDFT"],
       )