#ifndef _DARRAY_H_
#define _DARRAY_H_


#include "base.h"
#include "memory.h"
#include "arena.h"

/*
 * 1. need unit size and type should be derefed automatically ... (macro ??)
 * 2. Create()
 * 3. Functions ... (pushMany[], pushOne(), concat([], []), substr??([])->[], copy([])->[], swap([], [])->bool) 
*/

typedef struct {
	void* start;
	u64   block_size;
	u64   len;
	u64	  size;
} Darray;

Darray* DarrayCreate(Arena* _arena, u64 _block_size, u64 _block_len);
Darray* DarrayClear(Darray* _darray);
Darray* DarrayPushMany(Arena* _arena, Darray* _darray, Darray* _other);
Darray* DarrayPushOne(Arena* _arena, Darray* _darray, void* _unit);
boolean DarrayGet(Darray* _darray, u64 _index, void* _unit);
Darray* DarrayCopy(Darray* _this, Darray* _other);

#endif // _DARRAY_H_
