#ifndef SGL_H
#define SGL_H

// define continuous (real) numbers in a single location rather than forcing template spaghetti like CGAL
#if !defined(SGL_HIGH_PRECISION)
    typedef float Real;
#else
    typedef double Real;
#endif

#endif // SGL_H
