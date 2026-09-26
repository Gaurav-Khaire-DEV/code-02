#include "memory.h"

// Memory ...
void* copy(void* _src, void* _dst, u64 _bytes) {
	const u64 strides8 = _bytes / 8;
	const u64 strides4 = _bytes % 8 / 4;
	const u64 strides1 = _bytes % 4;

	u64 curr = 0;

	for (u64 i = 0; i < strides8; i++) {
		((u64*)_dst)[curr / 8] = ((u64*)_src)[curr / 8];
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)_dst)[curr / 4] = ((u32*)_src)[curr / 4];
		curr += 4;
	}
	for (u64 i = 0; i < strides1; i++) {
		((u8*)_dst)[curr] = ((u8*)_src)[curr];
		curr++;
	}

	return _dst;
}

// @TODO: Add support for other types as well ...
void* set(void* _start, u64 _value, u64 _bytes) {
	const u64 strides8 = _bytes / 8;
	const u64 strides4 = _bytes % 8 / 4;
	const u64 strides1 = _bytes % 4;

	u64 curr = 0;
	for (u64 i = 0; i < strides8; i++) {
		((u64*)_start)[curr / 8] = _value;
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)_start)[curr / 4] = _value;
		curr += 4;
	}
	for (u64 i = 0; i < strides1; i++) {
		((u8*)_start)[curr] = _value;
		curr++;
	}

	return _start;
}
