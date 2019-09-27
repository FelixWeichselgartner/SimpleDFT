#ifndef DFT_H_
#define DFT_H_

#include <complex.h>

float absoluteComplex(float, float);
float arctan2(float, float);
float angle(float complex);

void dft(int *x, float *X, int N);
void fft(int *x, float *X, int N);

void zeroPadding(float *, int, int);
void zeroPaddingToNextPOW2N(float *, int);

float * vonHann(float, float, int);
float * hamming(int);

#endif
