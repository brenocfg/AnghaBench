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
struct skynet_context {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 struct skynet_context* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 char* skynet_command (struct skynet_context*,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 double strtod (char const*,char**) ; 
 int /*<<< orphan*/  strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lintcommand(lua_State *L) {
	struct skynet_context * context = lua_touserdata(L, lua_upvalueindex(1));
	const char * cmd = luaL_checkstring(L,1);
	const char * result;
	const char * parm = NULL;
	char tmp[64];	// for integer parm
	if (lua_gettop(L) == 2) {
		if (lua_isnumber(L, 2)) {
			int32_t n = (int32_t)luaL_checkinteger(L,2);
			sprintf(tmp, "%d", n);
			parm = tmp;
		} else {
			parm = luaL_checkstring(L,2);
		}
	}

	result = skynet_command(context, cmd, parm);
	if (result) {
		char *endptr = NULL; 
		lua_Integer r = strtoll(result, &endptr, 0);
		if (endptr == NULL || *endptr != '\0') {
			// may be real number
			double n = strtod(result, &endptr);
			if (endptr == NULL || *endptr != '\0') {
				return luaL_error(L, "Invalid result %s", result);
			} else {
				lua_pushnumber(L, n);
			}
		} else {
			lua_pushinteger(L, r);
		}
		return 1;
	}
	return 0;
}