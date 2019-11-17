swig -python SimpleDFT.i
gcc -O2 -fPIC -c SimpleDFT.c -lm
gcc -O2 -fPIC -c SimpleDFT_wrap.c -I/usr/include/python3.7 -I/usr/local/lib/python3.7/dist-packages/numpy/core/include
gcc -shared SimpleDFT.o SimpleDFT_wrap.o -o _SimpleDFT.so -lm