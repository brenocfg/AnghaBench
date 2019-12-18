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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int reserve_length (struct bson*) ; 
 int /*<<< orphan*/  write_byte (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct bson*,scalar_t__,int) ; 

__attribute__((used)) static void
pack_ordered_dict(lua_State *L, struct bson *b, int n, int depth) {
	int length = reserve_length(b);
	int i;
	size_t sz;
	// the first key is at index n
	const char * key = lua_tolstring(L, n, &sz);
	for (i=0;i<n;i+=2) {
		if (key == NULL) {
			luaL_error(L, "Argument %d need a string", i+1);
		}
		lua_pushvalue(L, i+1);
		append_one(b, L, key, sz, depth);
		lua_pop(L,1);
		key = lua_tolstring(L, i+2, &sz);	// next key
	}
	write_byte(b,0);
	write_length(b, b->size - length, length);
}