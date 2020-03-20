//* Za potrebe desktop testiranja ovde metnuti konstante, funkcije... koji se inace nalaze u Arduino.h

#ifndef Arduino_h

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#endif