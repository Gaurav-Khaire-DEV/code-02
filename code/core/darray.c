#include "base.h"
#include "memory.h"
#include "darray.h"

Darray* DarrayCreate(Arena* _arena, u64 _block_size, u64 _block_len) {
	Darray* darray 		= (Darray*)ArenaPushAssert(_arena, sizeof(Darray));
	darray->start  		= ArenaPushAssert(_arena, _block_size * _block_len);
	darray->len	   		= 0;
	darray->size   		= _block_len;
	darray->block_size 	= _block_size;

	return darray;
}

Darray* DarrayClear(Darray* _darray) {
	set(_darray->start, 0, _darray->block_size * _darray->size);
	return _darray;
}

Darray* DarrayPushOne(Arena* _arena, Darray* _darray, void* _unit) {
	if (_darray->len + 1 > _darray->size) {
		u64 nextSize = CeilPwr2(_darray->size + 1);
		// @TODO: Currently just wasting the space for old Darray, may need to come up with better ...
		Darray* nextDarray = (Darray*)ArenaPushAssert(_arena, sizeof(Darray));
		nextDarray->block_size = _darray->block_size;
		nextDarray->start = ArenaPushAssert(_arena, nextSize * _darray->block_size);
		copy(_darray->start, nextDarray->start, _darray->size * _darray->block_size);
		nextDarray->len = _darray->len; // So code below this block is same
		nextDarray->size = nextSize;
		_darray = nextDarray;
	}

	copy(_unit, (u8*)_darray->start + _darray->len * _darray->block_size, _darray->block_size);
	_darray->len++;

	return _darray;
}

Darray* DarrayPushMany(Arena* _arena, Darray* _this, Darray* _other) {
	if (_this->block_size != _other->block_size) { return NULL; }

	if (_this->len + _other->len > _this->size) {
		u64 nextSize = CeilPwr2(_this->size + _other->len);
		// @TODO: Currently just wasting the space for old Darray, may need to come up with better ...
		Darray* nextDarray = (Darray*)ArenaPushAssert(_arena, sizeof(Darray));
		nextDarray->block_size = _this->block_size;
		nextDarray->start = ArenaPushAssert(_arena, nextSize * _this->block_size);
		copy(_this->start, nextDarray->start, _this->size * _this->block_size);
		nextDarray->len = _this->len; // So code below this block is same
		nextDarray->size = nextSize;
		_this = nextDarray;
	}

	copy(_other->start, (u8*)_this->start + _this->len * _this->block_size, _this->block_size * _other->len);
	_this->len = _this->len + _other->len;

	return _this;
}

boolean DarrayGet(Darray* _darray, u64 _index, void* _unit) {
	if (_index > _darray->size) { return false; }

	copy((u8*)_darray->start + _index * _darray->block_size, _unit, _darray->block_size);
	return true;
}

Darray* DarrayCopy(Darray* _this, Darray* _other) {
	if (_this->len < _other->len || _this->block_size != _other->block_size) { return NULL; }

	copy(_other->start, _this->start, _other->len * _other->block_size);

	return _this;
}
