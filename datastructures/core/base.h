#ifndef _BASE_H_
#define _BASE_H_

#include <stdint.h>

typedef uint64_t    u64;
typedef uint32_t    u32;
typedef int64_t     i64;
typedef int32_t     i32;
typedef uint8_t      u8;
typedef uint8_t	boolean;

// Base ...
u64 FloorPwr2(u64 n);


u64 CeilPwr2(u64 n);


#define MIN(a, b) a < b ? a : b;
#define MAX(a, b) a > b ? a : b;

#define true  1
#define false 0
#define NULL  0

// ANSI CODES
#define LIGHT_RED 	"\033[31m"
#define RED			"\033[1;31m"
#define RESET		"\033[0m"
#define YELLOW 		"\033[1;32m"
#define ORANGE		"\033[1;33m"

#endif // _BASE_H_
