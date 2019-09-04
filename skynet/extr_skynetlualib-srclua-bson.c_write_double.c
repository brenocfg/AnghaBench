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
typedef  int uint64_t ;
struct bson {int* ptr; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  bson_reserve (struct bson*,int) ; 

__attribute__((used)) static inline void
write_double(struct bson *b, lua_Number d) {
	union {
		double d;
		uint64_t i;
	} v;
	v.d = d;
	int i;
	bson_reserve(b,8);
	for (i=0;i<64;i+=8) {
		b->ptr[b->size++] = (v.i>>i) & 0xff;
	}
}