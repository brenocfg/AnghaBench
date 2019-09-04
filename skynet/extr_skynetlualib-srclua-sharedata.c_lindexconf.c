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
typedef  scalar_t__ uint32_t ;
struct table {int sizearray; int /*<<< orphan*/  L; int /*<<< orphan*/ * array; int /*<<< orphan*/ * arraytype; } ;
struct node {int /*<<< orphan*/  v; int /*<<< orphan*/  valuetype; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int KEYTYPE_INTEGER ; 
 int KEYTYPE_STRING ; 
 int LUA_TNUMBER ; 
 scalar_t__ calchash (char const*,size_t) ; 
 struct table* get_table (int /*<<< orphan*/ *,int) ; 
 struct node* lookup_key (struct table*,scalar_t__,int,int,char const*,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lindexconf(lua_State *L) {
	struct table *tbl = get_table(L,1);
	int kt = lua_type(L,2);
	uint32_t keyhash;
	int key = 0;
	int keytype;
	size_t sz = 0;
	const char * str = NULL;
	if (kt == LUA_TNUMBER) {
		if (!lua_isinteger(L, 2)) {
			return luaL_error(L, "Invalid key %f", lua_tonumber(L, 2));
		}
		key = (int)lua_tointeger(L, 2);
		if (key > 0 && key <= tbl->sizearray) {
			--key;
			pushvalue(L, tbl->L, tbl->arraytype[key], &tbl->array[key]);
			return 1;
		}
		keytype = KEYTYPE_INTEGER;
		keyhash = (uint32_t)key;
	} else {
		str = luaL_checklstring(L, 2, &sz);
		keyhash = calchash(str, sz);
		keytype = KEYTYPE_STRING;
	}

	struct node *n = lookup_key(tbl, keyhash, key, keytype, str, sz);
	if (n) {
		pushvalue(L, tbl->L, n->valuetype, &n->v);
		return 1;
	} else {
		return 0;
	}
}