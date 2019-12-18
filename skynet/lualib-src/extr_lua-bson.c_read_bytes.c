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
struct bson_reader {void* ptr; int size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  check_reader (int /*<<< orphan*/ *,struct bson_reader*,int) ; 

__attribute__((used)) static inline const void *
read_bytes(lua_State *L, struct bson_reader *br, int sz) {
	const void * r = br->ptr;
	check_reader(L, br, sz);
	br->ptr+=sz;
	br->size-=sz;
	return r;
}