#ifndef _BASE_H_
#define _BASE_H_

#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t  i64;
typedef int32_t  i32;
typedef uint8_t   u8;

// Base ...
u64 FloorPwr2(u64 n);


u64 CeilPwr2(u64 n);


#define MIN(a, b) a < b ? a : b;
#define MAX(a, b) a > b ? a : b;

#endif // _BASE_H_
