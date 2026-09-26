#include "base.h"

// Base ...
u64 FloorPwr2(u64 n) {
	u64 l = n;
	l |= l >> 1;
	l |= l >> 2;
	l |= l >> 4;
	l |= l >> 8;
	l |= l >> 16;
	l |= l >> 32;
	l = l - (l >> 1);
	return l;
}

// @TODO: Learn and Implement Buildins for this ...
u64 CeilPwr2(u64 n) {
	if (n <= 1) { return 1; }

	if (FloorPwr2(n) == n) {
		return n;
	}

	return FloorPwr2(n) * 2;
}

#define MIN(a, b) a < b ? a : b;
#define MAX(a, b) a > b ? a : b;
