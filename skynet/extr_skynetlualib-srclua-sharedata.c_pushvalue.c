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
union value {int /*<<< orphan*/  tbl; int /*<<< orphan*/  boolean; int /*<<< orphan*/  string; int /*<<< orphan*/  d; int /*<<< orphan*/  n; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  VALUETYPE_BOOLEAN 132 
#define  VALUETYPE_INTEGER 131 
#define  VALUETYPE_REAL 130 
#define  VALUETYPE_STRING 129 
#define  VALUETYPE_TABLE 128 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void
pushvalue(lua_State *L, lua_State *sL, uint8_t vt, union value *v) {
	switch(vt) {
	case VALUETYPE_REAL:
		lua_pushnumber(L, v->n);
		break;
	case VALUETYPE_INTEGER:
		lua_pushinteger(L, v->d);
		break;
	case VALUETYPE_STRING: {
		size_t sz = 0;
		const char *str = lua_tolstring(sL, v->string, &sz);
		lua_pushlstring(L, str, sz);
		break;
	}
	case VALUETYPE_BOOLEAN:
		lua_pushboolean(L, v->boolean);
		break;
	case VALUETYPE_TABLE:
		lua_pushlightuserdata(L, v->tbl);
		break;
	default:
		lua_pushnil(L);
		break;
	}
}