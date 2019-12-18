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
typedef  int /*<<< orphan*/  v ;
typedef  int uint8_t ;
struct sproto_arg {int type; int index; int* value; int length; } ;
typedef  int (* sproto_callback ) (struct sproto_arg*) ;

/* Variables and functions */
 int SIZEOF_LENGTH ; 
 int SPROTO_CB_NIL ; 
 int SPROTO_CB_NOARRAY ; 
#define  SPROTO_TBOOLEAN 129 
#define  SPROTO_TINTEGER 128 
 int* encode_integer_array (int (*) (struct sproto_arg*),struct sproto_arg*,int*,int,int*) ; 
 int fill_size (int*,int) ; 

__attribute__((used)) static int
encode_array(sproto_callback cb, struct sproto_arg *args, uint8_t *data, int size) {
	uint8_t * buffer;
	int sz;
	if (size < SIZEOF_LENGTH)
		return -1;
	size -= SIZEOF_LENGTH;
	buffer = data + SIZEOF_LENGTH;
	switch (args->type) {
	case SPROTO_TINTEGER: {
		int noarray;
		buffer = encode_integer_array(cb,args,buffer,size, &noarray);
		if (buffer == NULL)
			return -1;
	
		if (noarray) {
			return 0;
		}
		break;
	}
	case SPROTO_TBOOLEAN:
		args->index = 1;
		for (;;) {
			int v = 0;
			args->value = &v;
			args->length = sizeof(v);
			sz = cb(args);
			if (sz < 0) {
				if (sz == SPROTO_CB_NIL)		// nil object , end of array
					break;
				if (sz == SPROTO_CB_NOARRAY)	// no array, don't encode it
					return 0;
				return -1;	// sz == SPROTO_CB_ERROR
			}
			if (size < 1)
				return -1;
			buffer[0] = v ? 1: 0;
			size -= 1;
			buffer += 1;
			++args->index;
		}
		break;
	default:
		args->index = 1;
		for (;;) {
			if (size < SIZEOF_LENGTH)
				return -1;
			size -= SIZEOF_LENGTH;
			args->value = buffer+SIZEOF_LENGTH;
			args->length = size;
			sz = cb(args);
			if (sz < 0) {
				if (sz == SPROTO_CB_NIL) {
					break;
				}
				if (sz == SPROTO_CB_NOARRAY)	// no array, don't encode it
					return 0;
				return -1;	// sz == SPROTO_CB_ERROR
			}
			fill_size(buffer, sz);
			buffer += SIZEOF_LENGTH+sz;
			size -=sz;
			++args->index;
		}
		break;
	}
	sz = buffer - (data + SIZEOF_LENGTH);
	return fill_size(data, sz);
}