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
 int LUA_TNUMBER ; 
 int /*<<< orphan*/  SPROTO_REQUEST ; 
 int /*<<< orphan*/  SPROTO_RESPONSE ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct sproto_type*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 struct sproto* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 char* sproto_protoname (struct sproto*,int) ; 
 struct sproto_type* sproto_protoquery (struct sproto*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sproto_protoresponse (struct sproto*,int) ; 
 int sproto_prototag (struct sproto*,char const*) ; 

__attribute__((used)) static int
lprotocol(lua_State *L) {
	struct sproto * sp = lua_touserdata(L, 1);
	struct sproto_type * request;
	struct sproto_type * response;
	int t;
	int tag;
	if (sp == NULL) {
		return luaL_argerror(L, 1, "Need a sproto_type object");
	}
	t = lua_type(L,2);
	if (t == LUA_TNUMBER) {
		const char * name;
		tag = lua_tointeger(L, 2);
		name = sproto_protoname(sp, tag);
		if (name == NULL)
			return 0;
		lua_pushstring(L, name);
	} else {
		const char * name = lua_tostring(L, 2);
		if (name == NULL) {
			return luaL_argerror(L, 2, "Should be number or string");
		}
		tag = sproto_prototag(sp, name);
		if (tag < 0)
			return 0;
		lua_pushinteger(L, tag);
	}
	request = sproto_protoquery(sp, tag, SPROTO_REQUEST);
	if (request == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, request);
	}
	response = sproto_protoquery(sp, tag, SPROTO_RESPONSE);
	if (response == NULL) {
		if (sproto_protoresponse(sp, tag)) {
			lua_pushlightuserdata(L, NULL);	// response nil
		} else {
			lua_pushnil(L);
		}
	} else {
		lua_pushlightuserdata(L, response);
	}
	return 3;
}