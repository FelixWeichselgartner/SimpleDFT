#ifndef SIMPLE_DFT_H_
#define SIMPLE_DFT_H

#include <complex.h>

float absoluteComplex(float, float);
float arctan2(float, float);
float angle(float complex);

float complex * dft(int *x, int N);
float complex * fft(int *x, int N);

void PyDFT(int *x, int in_n, float complex **X, int *out_n);
void PyFFT(int *x, int in_n, float complex **X, int *out_n);

void zeroPadding(float *, int, int);
void zeroPaddingToNextPOW2N(float *, int);

float * vonHann(float, float, int);
float * hamming(int);

#endif
