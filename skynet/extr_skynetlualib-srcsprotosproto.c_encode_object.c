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
typedef  int /*<<< orphan*/  uint8_t ;
struct sproto_arg {int length; int /*<<< orphan*/ * value; } ;
typedef  int (* sproto_callback ) (struct sproto_arg*) ;

/* Variables and functions */
 int SIZEOF_LENGTH ; 
 int SPROTO_CB_NIL ; 
 int /*<<< orphan*/  assert (int) ; 
 int fill_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
encode_object(sproto_callback cb, struct sproto_arg *args, uint8_t *data, int size) {
	int sz;
	if (size < SIZEOF_LENGTH)
		return -1;
	args->value = data+SIZEOF_LENGTH;
	args->length = size-SIZEOF_LENGTH;
	sz = cb(args);
	if (sz < 0) {
		if (sz == SPROTO_CB_NIL)
			return 0;
		return -1;	// sz == SPROTO_CB_ERROR
	}
	assert(sz <= size-SIZEOF_LENGTH);	// verify buffer overflow
	return fill_size(data, sz);
}