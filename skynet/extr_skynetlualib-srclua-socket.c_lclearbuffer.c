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
struct socket_buffer {scalar_t__ size; scalar_t__ head; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 struct socket_buffer* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  return_free_node (int /*<<< orphan*/ *,int,struct socket_buffer*) ; 

__attribute__((used)) static int
lclearbuffer(lua_State *L) {
	struct socket_buffer * sb = lua_touserdata(L, 1);
	if (sb == NULL) {
		if (lua_isnil(L, 1)) {
			return 0;
		}
		return luaL_error(L, "Need buffer object at param 1");
	}
	luaL_checktype(L,2,LUA_TTABLE);
	while(sb->head) {
		return_free_node(L,2,sb);
	}
	sb->size = 0;
	return 0;
}