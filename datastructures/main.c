#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
// 		-> Extract this into a base / core lib
// ----------------------------------------------------------------------------

// Base ...
size_t FloorPwr2(size_t n) {
	size_t l = n;
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
size_t CeilPwr2(size_t n) {
	if (n <= 1) { return 1; }

	if (FloorPwr2(n) == n) {
		return n;
	}

	return FloorPwr2(n) * 2;
}

#define MIN(a, b) a < b ? a : b;
#define MAX(a, b) a > b ? a : b;

#include <stdint.h>

#define u64 uint64_t
#define u32 uint32_t
#define i64 int64_t
#define i32 int32_t
#define u8  unsigned char


// Memory ...
void* copy(void* src, void* dst, u64 bytes) {
	const u64 strides8 = bytes / 8;
	const u64 strides4 = bytes % 8 / 4;
	const u64 strides1 = bytes % 4;

	u64 curr = 0;

	for (u64 i = 0; i < strides8; i++) {
		((u64*)dst)[curr] = ((u64*)src)[curr];
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)dst)[curr] = ((u32*)src)[curr];
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
		((u64*)start)[curr] = value;
		curr += 8;
	}
	for (u64 i = 0; i < strides4; i++) {
		((u32*)start)[curr] = value;
		curr += 4;
	}
	for (u64 i = 0; i < strides1; i++) {
		((u8*)start)[curr] = value;
		curr++;
	}

	return start;
}


// ----------------------------------------------------------------------------
// Declarations ...
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// 		-> Types
// ----------------------------------------------------------------------------

typedef struct {
	void* 	start;
	size_t 	size;
	size_t 	pos;
} Arena;

// String8 ...
typedef struct {
	char* start;
	size_t size;
	size_t pos;
} String8;


// ----------------------------------------------------------------------------
// 		-> Functions
// ----------------------------------------------------------------------------

Arena* ArenaCreate(size_t _size);
// Arena* ArenaCreate(Arena* _arena, size_t _size);
void* ArenaPushAssert(Arena* _arena, size_t _blockSize);
Arena* ArenaClear(Arena* _arena);
void ArenaDestroy(Arena* _arena);


// String8 ...
const char* GetCStr(Arena* _arena, String8* _s8);
String8* CreateStr8(Arena* _arena, const char* _cStr);
String8* AppendCStr(Arena* _arena, String8* _s8, const char* _cStr);
u64 CStrnLen(const char* _cStr, const u64 _limit);



// ----------------------------------------------------------------------------
// Main(): Orchestration ...
// ----------------------------------------------------------------------------

int main() {
	printf("==========================\n");
	printf("======Main() { ===========\n");
	printf("==========================\n\n\n");


	Arena* arena = ArenaCreate(4096);

	String8* str8 = CreateStr8(arena, "1234567");
	printf("start: %p; pos: %lu; size: %lu\n", str8->start, str8->pos, str8->size);
	str8 = AppendCStr(arena, str8, "8");
	str8 = AppendCStr(arena, str8, "9");
	printf("start: %p; pos: %lu; size: %lu\n", str8->start, str8->pos, str8->size);
	const char* cStr = GetCStr(arena, str8);
	printf("start: %p; pos: %lu; size: %lu\n", str8->start, str8->pos, str8->size);
	// String8* s8 = CreateStr8(arena, "Hello, World");
	// printf("start: %p; pos: %lu; size: %lu\n", s8->start, s8->pos, s8->size);
	// printf("s8->start - str8->start: %d\n", s8->start - str8->start);
	printf("%s | %s | %s\n", str8->start, cStr, "Hello World");
	for (u64 i = 0; i < str8->size; i++) {
		printf("%d | ", str8->start[i]);
	}

	ArenaDestroy(arena);

	printf("\n\n");
	printf("==========================\n");
	printf("====== } =================\n");
	printf("==========================\n");
}



// ----------------------------------------------------------------------------
// Implementations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// 		-> Functions
// ----------------------------------------------------------------------------

Arena* ArenaCreate(size_t _size) {
	if (_size == 0) { _size = 4096; }

	Arena* arena = (Arena*)calloc(1, sizeof(Arena));
	arena->start = calloc(_size, sizeof(char));
	arena->pos 	 = 0;
	arena->size  = _size;
	return arena;
}

void* ArenaPushAssert(Arena* _arena, size_t _blockSize) {
	assert(_arena->pos + _blockSize < _arena->size);

	void* blockStart = &(((char*)_arena->start)[_arena->pos]);
	_arena->pos = _arena->pos + _blockSize;
	return blockStart;
}


Arena* ArenaClear(Arena* _arena) {
	set(_arena, 0, _arena->size);
	_arena->pos = 0;
	return _arena;
}

void ArenaDestroy(Arena* _arena) {
	free(_arena->start);
	free(_arena);
}




// String8 ...
const char* GetCStr(Arena* _arena, String8* _s8) {
	char* cStr = (char*)ArenaPushAssert(_arena, _s8->pos + 1);
	// memcpy(cStr, _s8->start, _s8->pos);
	copy(_s8->start, cStr, _s8->pos);
	cStr[_s8->pos] = '\0';
	return cStr;
}

String8* CreateStr8(Arena* _arena, const char* _cStr) {
	size_t cStrLen = CStrnLen(_cStr, _arena->size);
	String8* s8    = (String8*)ArenaPushAssert(_arena, sizeof(String8));
	// s8->size 	   = MAX(CeilPwr2(cStrLen), 8);
	s8->size		   = CeilPwr2(cStrLen);
	s8->start 	   = (char*)ArenaPushAssert(_arena, s8->size);
	// memcpy(s8->start, (void*)_cStr, cStrLen);
	copy((void*)_cStr, s8->start, cStrLen);
	s8->pos = cStrLen;
	return s8;
}

String8* AppendCStr(Arena* _arena, String8* _s8, const char* _cStr) {
	size_t cStrLen = CStrnLen((void*)_cStr, _arena->size);
	if (_s8->pos + cStrLen > _s8->size) {
		char* prevStart = _s8->start;
		_s8->size   = CeilPwr2(_s8->size + cStrLen);
		_s8->start = (char*)ArenaPushAssert(_arena, _s8->size);
		// memcpy(_s8->start, prevStart, _s8->pos);
		copy(prevStart, _s8->start, _s8->pos);
	}
	copy((void*)_cStr, _s8->start + _s8->pos, cStrLen);
	// memcpy(_s8->start + _s8->pos, (void*)_cStr, cStrLen);
	_s8->pos += cStrLen;
	return _s8;
}

u64 CStrnLen(const char* _cStr, const u64 _limit) {
	for (u64 i = 0; i < _limit; i++) {
		if (_cStr[i] == '\0') return i;
	}
	return _limit;
}
