#include "memory.h"

// Memory ...
void* copy(void* src, void* dst, u64 bytes) {
	const u64 strides8 = bytes / 8;
	const u64 strides4 = bytes % 8 / 4;
	const u64 strides1 = bytes % 4;

	u64 curr = 0;

	for (u64 i = 0; i < strides8; i++) {
		((u64*)dst)[curr / 8] = ((u64*)src)[curr / 8];
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)dst)[curr / 4] = ((u32*)src)[curr / 4];
		curr += 4;
	}
	for (u64 i = 0; i < strides1; i++) {
		((u8*)dst)[curr] = ((u8*)src)[curr];
		curr++;
	}

	return dst;
}

// @TODO: Add support for other types as well ...
void* set(void* start, u64 value, u64 bytes) {
	const u64 strides8 = bytes / 8;
	const u64 strides4 = bytes % 8 / 4;
	const u64 strides1 = bytes % 4;

	u64 curr = 0;
	for (u64 i = 0; i < strides8; i++) {
		((u64*)start)[curr / 8] = value;
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)start)[curr / 4] = value;
		curr += 4;
	}
	for (u64 i = 0; i < strides1; i++) {
		((u8*)start)[curr] = value;
		curr++;
	}

	return start;
}
