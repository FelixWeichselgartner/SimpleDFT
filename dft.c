#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dft.h"

#define pi 3.14159265358979323846

/**
 * @brief       absolute value of a complex number (c * conj(c) = sqrt(real(c)^2 + imag(c)^2))
 * @note   
 * @param  x:   the real component
 * @param  y:   the imaginary component
 * @retval      the absolute value
 */
float absoluteComplex(float x, float y) {
    return sqrt(x * x + y * y);
}

/**
 * @brief       implementation of the arctan2
 * @note        
 * @param  x:   the x component (or real)
 * @param  y:   the y component (or imag)
 * @retval      the angle in radian
 */
float arctan2(float x, float y) {
    //values = ]-pi;pi]
    if (x > 0) {
        return atan(y / x);
    } else if (x < 0) {
        if (y > 0) {
            return atan(y / x) + pi;
        } else if (y == 0) {
            return pi;
        } else if (y < 0) {
            return atan(y / x) - pi;
        }
    } else if (x ==0 ) {
        if (y == 0) {
            return 0; //or None actually it has no phase here but 0 is fine
        } else if (y > 0) {
            return pi / 2;
        } else if (y < 0) {
            return -pi / 2;
        }
    }
}

/**
 * @brief       calculates the angle of a complex number
 * @note   
 * @param  X:   a complex number to calculate the angle for
 * @retval      the angle in radian
 */
float angle(float complex X){
    return arctan2(creal(X), cimag(X));
}

/**
 * @brief       implementation of discrete fourier transformation
 * @note   
 * @param  *x:  the function to be transformed
 * @param  N:   the amount of values in the function
 * @retval      pointer to the fourier transformation
 */
void dft(int *x, float complex *X, int N) {
    X = malloc(N * sizeof(float complex));
    float complex wExponent = -2 * I * pi / N;
    float complex temp;
    for (int l = 0; l < N; l++) {
        temp = 0 + 0 * I;
        for (int k = 0; k < N; k++) {
            temp = x[k] * cexp(wExponent * k * l) + temp;
        }
        X[l] = temp/N;
    }
}

/**
 * @brief       implementation of fast fourier transformation
 * @note   
 * @param  *x:  the function to be transformed
 * @param  N:   the amount of values in the function
 * @retval      pointer to the fourier transformation
 */
void fft(int *x, float complex *X, int N) {
    int max = N / 2;

    //decimation in time
    int *xs = malloc(max * sizeof(int));
    int *xss = malloc(max * sizeof(int));

    for (int k = 0; k < max; k++) {
        xs[k] = x[2 * k];
        xss[k] = x[2 * k + 1];
    }

    //fourier transform those both parts
    float complex *XS, *XSS;
    dft(xs, XS, max);
    dft(xss, XSS, max);

    //add both together to actual fourier transformation
    X = malloc(N * sizeof(float complex));
    complex float wExponent = -2 * I * pi / N;

    for (int l = 0; l < max; l++) {
        X[l] = (XS[l] + cexp(wExponent * l) * XSS[l]) / 2;
    }

    for (int l = 0; l < max; l++) {
        X[l + max] = (XS[l] - cexp(wExponent * l) * XSS[l]) / 2;
    }

    free(xs);
    free(xss);
    free(XS);
    free(XSS);
}

void PyDFT(int *x, int in_n, float complex **X, int *out_n) {
    float complex *arr;
    dft(x, arr, in_n);

    *out_n = in_n;
    *X = arr;
}

void PyFFT(int *x, int in_n, float complex **X, int *out_n) {
    float complex *arr;
    fft(x, arr, in_n);

    *out_n = in_n;
    *X = arr;
}

/**
 * @brief               adds zeros to the function to get a better resolution
 * @note   
 * @param  *function:   the function to add the zeros to
 * @param  N:           the current length of the function
 * @param  n:           the new length of the function
 * @retval None
 */
void zeroPadding(float *function, int N, int n) {
    function = (float *)realloc(function, n * sizeof(float));
    for (int x = n - N; x < n; x++) {
        function[x] = 0; 
    }
}

/**
 * @brief               adds zeros so the length of the function is pow(2, n) with n being a positive integer
 * @note   
 * @param  *function:   the function to add zeros to
 * @param  N:           the current length
 * @retval None
 */
void zeroPaddingToNextPOW2N(float *function, int N) {
    int n = 1;
    while (N > pow(2, n)) {
        n++;
    }
    int add = pow(2, n) - N;
    zeroPadding(function, add, N);
}

/**
 * @brief           implementation of the vonHann window
 * @note   
 * @param  alpha:   the alpha value
 * @param  beta:    the beta value
 * @param  N:       the length of the window function
 * @retval          pointer to the generated window function
 */
float * vonHann(float alpha, float beta, int N) {
    float *vonHann = malloc(N * sizeof(float));
    for (int n = 0; n < N; n++) {
        vonHann[n] = alpha - beta * cos(2 * pi * n / (N - 1));
    }
    return vonHann;
}

/**
 * @brief       implementation of the hamming window
 * @note   
 * @param  N:   the lenght of the windows function
 * @retval      pointer to the generated window function
 */
float * hamming(int N) {
    float alpha = 25.0 / 46;
    float beta = 1 - alpha;
    return vonHann(alpha, beta , N);
}
