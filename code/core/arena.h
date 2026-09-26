#ifndef _ARENA_H_
#define _ARENA_H_

#include "base.h"

typedef struct {
	void* 	start;
	u64 	size;
	u64 	pos;
} Arena;

Arena* ArenaCreate(u64 _size);
// Arena* ArenaCreate(Arena* _arena, u64 _size);
void* ArenaPushAssert(Arena* _arena, u64 _blockSize);
Arena* ArenaClear(Arena* _arena);
void ArenaDestroy(Arena* _arena);

#endif // _ARENA_H_
