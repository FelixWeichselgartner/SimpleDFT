/* File: dft.i */
%module dft

%{
    #define SWIG_FILE_WITH_INIT
    #include "dft.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

%apply (int * IN_ARRAY1, int DIM1) {(int *x, int N)}
%apply (float complex * ARGOUT_ARRAY1, int DIM1) {(float complex *X, int N)}

%include "dft.h"