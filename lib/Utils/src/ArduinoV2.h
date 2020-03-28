//* Za potrebe desktop testiranja ovde metnuti konstante, funkcije... koji se inace nalaze u Arduino.h

template <class T>
static inline T abs(T _a) { return _a < 0 ? -_a : _a; }

#ifndef TESTV2
#include <Arduino.h>
#else

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define _max(a, b) ({ decltype(a) _a = (a); decltype(b) _b = (b); _a > _b? _a : _b; })
//B static inline float fabs(float _a) { return _a < 0 ? -_a : _a; }

#endif