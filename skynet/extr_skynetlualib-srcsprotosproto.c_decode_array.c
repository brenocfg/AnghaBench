#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct sproto_arg {int type; int index; int* value; int length; } ;
typedef  int /*<<< orphan*/  (* sproto_callback ) (struct sproto_arg*) ;

/* Variables and functions */
 int SIZEOF_INT32 ; 
 int SIZEOF_INT64 ; 
 int /*<<< orphan*/  SIZEOF_LENGTH ; 
#define  SPROTO_TBOOLEAN 131 
#define  SPROTO_TINTEGER 130 
#define  SPROTO_TSTRING 129 
#define  SPROTO_TSTRUCT 128 
 int decode_array_object (int /*<<< orphan*/  (*) (struct sproto_arg*),struct sproto_arg*,int*,scalar_t__) ; 
 int expand64 (void*) ; 
 void* todword (int*) ; 

__attribute__((used)) static int
decode_array(sproto_callback cb, struct sproto_arg *args, uint8_t * stream) {
	uint32_t sz = todword(stream);
	int type = args->type;
	int i;
	if (sz == 0) {
		// It's empty array, call cb with index == -1 to create the empty array.
		args->index = -1;
		args->value = NULL;
		args->length = 0;
		cb(args);
		return 0;
	}	
	stream += SIZEOF_LENGTH;
	switch (type) {
	case SPROTO_TINTEGER: {
		int len = *stream;
		++stream;
		--sz;
		if (len == SIZEOF_INT32) {
			if (sz % SIZEOF_INT32 != 0)
				return -1;
			for (i=0;i<sz/SIZEOF_INT32;i++) {
				uint64_t value = expand64(todword(stream + i*SIZEOF_INT32));
				args->index = i+1;
				args->value = &value;
				args->length = sizeof(value);
				cb(args);
			}
		} else if (len == SIZEOF_INT64) {
			if (sz % SIZEOF_INT64 != 0)
				return -1;
			for (i=0;i<sz/SIZEOF_INT64;i++) {
				uint64_t low = todword(stream + i*SIZEOF_INT64);
				uint64_t hi = todword(stream + i*SIZEOF_INT64 + SIZEOF_INT32);
				uint64_t value = low | hi << 32;
				args->index = i+1;
				args->value = &value;
				args->length = sizeof(value);
				cb(args);
			}
		} else {
			return -1;
		}
		break;
	}
	case SPROTO_TBOOLEAN:
		for (i=0;i<sz;i++) {
			uint64_t value = stream[i];
			args->index = i+1;
			args->value = &value;
			args->length = sizeof(value);
			cb(args);
		}
		break;
	case SPROTO_TSTRING:
	case SPROTO_TSTRUCT:
		return decode_array_object(cb, args, stream, sz);
	default:
		return -1;
	}
	return 0;
}