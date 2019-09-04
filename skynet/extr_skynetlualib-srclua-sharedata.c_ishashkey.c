#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct context {TYPE_1__* tbl; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int sizearray; } ;

/* Variables and functions */
 int KEYTYPE_INTEGER ; 
 int KEYTYPE_STRING ; 
 int LUA_TNUMBER ; 
 scalar_t__ calchash (char const*,size_t) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int stringindex (struct context*,char const*,size_t) ; 

__attribute__((used)) static int
ishashkey(struct context * ctx, lua_State *L, int index, int *key, uint32_t *keyhash, int *keytype) {
	int sizearray = ctx->tbl->sizearray;
	int kt = lua_type(L, index);
	if (kt == LUA_TNUMBER) {
		*key = lua_tointeger(L, index);
		if (*key > 0 && *key <= sizearray) {
			return 0;
		}
		*keyhash = (uint32_t)*key;
		*keytype = KEYTYPE_INTEGER;
	} else {
		size_t sz = 0;
		const char * s = lua_tolstring(L, index, &sz);
		*keyhash = calchash(s, sz);
		*key = stringindex(ctx, s, sz);
		*keytype = KEYTYPE_STRING;
	}
	return 1;
}