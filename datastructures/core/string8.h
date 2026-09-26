#ifndef _STRING8_H_
#define _STRING8_H_

#include "memory.h"
#include "arena.h"
#include "base.h"

// String8 ...
typedef struct {
	char* start;
	u64 size;
	u64 pos;
} String8;


// String8 ...
const char* GetCStr(Arena* _arena, String8* _s8);
String8* CreateStr8(Arena* _arena, const char* _cStr);
String8* AppendCStr(Arena* _arena, String8* _s8, const char* _cStr);
u64 CStrnLen(const char* _cStr, const u64 _limit);

#endif // _STRING8_H_
