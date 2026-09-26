#include "arena.h"
#include "memory.h"

#include <stdlib.h>
#include <assert.h>

// This is based on lib-c for now ...

Arena* ArenaCreate(u64 _size) {
	if (_size == 0) { _size = 4096; }

	Arena* arena = (Arena*)calloc(1, sizeof(Arena));
	// if getting a NULL try 3 times and throw shit ...
	for (int i = 0; i < 3 && arena == NULL; i++) {
		arena = (Arena*)calloc(1, sizeof(Arena));
	}
	assert(arena != NULL);

	arena->start = calloc(_size, sizeof(char));
	arena->pos 	 = 0;
	arena->size  = _size;

	return arena;
}

void* ArenaPushAssert(Arena* _arena, u64 _blockSize) {
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
