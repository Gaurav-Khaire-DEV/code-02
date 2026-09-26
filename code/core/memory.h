#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "base.h"

void* copy(void* _src, void* _dst, u64 _bytes);

void* set(void* _start, u64 _value, u64 _bytes);

#endif // _MEMORY_H_
