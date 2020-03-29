//* Za potrebe desktop testiranja ovde metnuti konstante, funkcije... koji se inace nalaze u Arduino.h

#pragma once

template <class T>
static inline T _abs(T val) { return val < 0 ? -val : val; }

template <typename T>
int _sgn(T val) { return (T(0) < val) - (val < T(0)); }

#ifndef TESTV2
#include <Arduino.h>
#else

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define _max(a, b) ({ decltype(a) _a = (a); decltype(b) _b = (b); _a > _b? _a : _b; })

#endif