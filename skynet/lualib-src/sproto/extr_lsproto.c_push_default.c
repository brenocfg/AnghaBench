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
struct sproto_arg {int type; int /*<<< orphan*/  subtype; int /*<<< orphan*/  extra; int /*<<< orphan*/ * ud; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  SPROTO_TBOOLEAN 131 
#define  SPROTO_TINTEGER 130 
#define  SPROTO_TSTRING 129 
#define  SPROTO_TSTRUCT 128 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  sproto_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
push_default(const struct sproto_arg *args, int array) {
	lua_State *L = args->ud;
	switch(args->type) {
	case SPROTO_TINTEGER:
		if (args->extra)
			lua_pushnumber(L, 0.0);
		else
			lua_pushinteger(L, 0);
		break;
	case SPROTO_TBOOLEAN:
		lua_pushboolean(L, 0);
		break;
	case SPROTO_TSTRING:
		lua_pushliteral(L, "");
		break;
	case SPROTO_TSTRUCT:
		if (array) {
			lua_pushstring(L, sproto_name(args->subtype));
		} else {
			lua_createtable(L, 0, 1);
			lua_pushstring(L, sproto_name(args->subtype));
			lua_setfield(L, -2, "__type");
		}
		break;
	default:
		luaL_error(L, "Invalid type %d", args->type);
		break;
	}
}