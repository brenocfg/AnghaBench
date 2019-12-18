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
struct bson {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int lua_gettop (int /*<<< orphan*/ *) ; 
 void* lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 struct bson* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_ordered_dict (int /*<<< orphan*/ *,struct bson*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
encode_bson_byorder(lua_State *L) {
	int n = lua_gettop(L);
	struct bson *b = lua_touserdata(L, n);
	lua_settop(L, --n);
	pack_ordered_dict(L, b, n, 0);
	lua_settop(L,0);
	void * ud = lua_newuserdata(L, b->size);
	memcpy(ud, b->ptr, b->size);
	return 1;
}