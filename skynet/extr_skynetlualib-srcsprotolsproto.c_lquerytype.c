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
struct sproto_type {int dummy; } ;
struct sproto {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct sproto_type*) ; 
 struct sproto* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 struct sproto_type* sproto_type (struct sproto*,char const*) ; 

__attribute__((used)) static int
lquerytype(lua_State *L) {
	const char * type_name;
	struct sproto *sp = lua_touserdata(L,1);
	struct sproto_type *st;
	if (sp == NULL) {
		return luaL_argerror(L, 1, "Need a sproto object");
	}
	type_name = luaL_checkstring(L,2);
	st = sproto_type(sp, type_name);
	if (st) {
		lua_pushlightuserdata(L, st);
		return 1;
	}
	return 0;
}