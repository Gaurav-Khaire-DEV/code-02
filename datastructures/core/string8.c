#include "base.h"
#include "memory.h"
#include "arena.h"
#include "string8.h"

// String8 ...
const char* GetCStr(Arena* _arena, String8* _s8) {
	char* cStr = (char*)ArenaPushAssert(_arena, _s8->pos + 1);
	// memcpy(cStr, _s8->start, _s8->pos);
	copy(_s8->start, cStr, _s8->pos);
	cStr[_s8->pos] = '\0';
	return cStr;
}

String8* CreateStr8(Arena* _arena, const char* _cStr) {
	u64 cStrLen = CStrnLen(_cStr, _arena->size);
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
	u64 cStrLen = CStrnLen((void*)_cStr, _arena->size);
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
