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
struct bson {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  append_one (struct bson*,int /*<<< orphan*/ *,char const*,size_t,int) ; 
 size_t bson_numstr (char*,size_t) ; 
 int /*<<< orphan*/  lua_geti (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int reserve_length (struct bson*) ; 
 int /*<<< orphan*/  write_byte (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct bson*,scalar_t__,int) ; 

__attribute__((used)) static void
pack_array(lua_State *L, struct bson *b, int depth, size_t len) {
	int length = reserve_length(b);
	size_t i;
	for (i=1;i<=len;i++) {
		char numberkey[32];
		size_t sz = bson_numstr(numberkey, i - 1);
		const char * key = numberkey;
		lua_geti(L, -1, i);
		append_one(b, L, key, sz, depth);
		lua_pop(L, 1);
	}
	write_byte(b,0);
	write_length(b, b->size - length, length);
}