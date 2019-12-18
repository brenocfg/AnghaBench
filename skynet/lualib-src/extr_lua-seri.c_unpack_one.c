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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  type ;
struct read_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  invalid_stream (int /*<<< orphan*/ *,struct read_block*) ; 
 int /*<<< orphan*/  push_value (int /*<<< orphan*/ *,struct read_block*,int,int) ; 
 int* rb_read (struct read_block*,int) ; 

__attribute__((used)) static void
unpack_one(lua_State *L, struct read_block *rb) {
	uint8_t type;
	uint8_t *t = rb_read(rb, sizeof(type));
	if (t==NULL) {
		invalid_stream(L, rb);
	}
	type = *t;
	push_value(L, rb, type & 0x7, type>>3);
}