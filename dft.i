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

%numpy_typemaps(unsigned long long, NPY_ULONGLONG, int)
%numpy_typemaps(float             , NPY_FLOAT    , int)
%numpy_typemaps(double            , NPY_DOUBLE   , int)
%numpy_typemaps(signed char       , NPY_BYTE     , size_t)
%numpy_typemaps(unsigned char     , NPY_UBYTE    , size_t)
%numpy_typemaps(short             , NPY_SHORT    , size_t)
%numpy_typemaps(unsigned short    , NPY_USHORT   , size_t)
%numpy_typemaps(int               , NPY_INT      , size_t)
%numpy_typemaps(unsigned int      , NPY_UINT     , size_t)
%numpy_typemaps(long              , NPY_LONG     , size_t)
%numpy_typemaps(unsigned long     , NPY_ULONG    , size_t)
%numpy_typemaps(long long         , NPY_LONGLONG , size_t)
%numpy_typemaps(unsigned long long, NPY_ULONGLONG, size_t)
%numpy_typemaps(float             , NPY_FLOAT    , size_t)
%numpy_typemaps(double            , NPY_DOUBLE   , size_t)

%apply (int * IN_ARRAY1, int DIM1) {(int *x, int in_n)}
%apply (float complex ** ARGOUTVIEWM_ARRAY1, int *DIM1) {(float complex **X, int *out_n)}

%include "dft.h"