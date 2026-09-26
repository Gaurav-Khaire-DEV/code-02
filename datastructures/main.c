#include <stdio.h>
#include "core/base.h"
#include "core/arena.h"
#include "core/string8.h"


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

