#include "core/base.h"
#include "core/arena.h"
#include "core/darray.h"

#include <stdio.h>

int main() {
	Arena* arena  = ArenaCreate(4096);
	// @TODO: Remove all these _ from h and c files ...
	Darray* first = DarrayCreate(arena, sizeof(i32), 3);
	for (u64 i = 0; i < 10; i++) {
		first = DarrayPushOne(arena, first, &i);
	}

	Darray* second = DarrayCreate(arena, sizeof(i32), 3);
	for (u64 i = 0; i < 3; i++) {
		second = DarrayPushOne(arena, second, &i);
	}
	for (u64 i = 0; i < 3; i++) {
		first = DarrayPushMany(arena, first, second);
	}

	printf("After DarrayPushMany() -> \n");
	for (u64 i = 0; i < first->size; i++) {
		i32 val;
		DarrayGet(first, i, &val);
		printf("[%02zu]%02d ", i, val);
		if (i && (i + 1) % 8 == 0) printf("\n");
	}
	printf("\n");

	printf("After DarrayClear() -> \n");
	first = DarrayClear(first);
	for (u64 i = 0; i < first->size; i++) {
		i32 val;
		DarrayGet(first, i, &val);
		printf("[%02zu]%02d ", i, val);
		if (i && (i + 1) % 8 == 0) printf("\n");
	}

	ArenaDestroy(arena);
}
