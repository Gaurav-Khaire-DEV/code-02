#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "base.h"

void* copy(void* src, void* dst, u64 bytes);

void* set(void* start, u64 value, u64 bytes);

#endif // _MEMORY_H_
