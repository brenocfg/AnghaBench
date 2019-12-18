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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,size_t) ; 
 char* luaL_buffinitsize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lxor_str(lua_State *L) {
	size_t len1,len2;
	const char *s1 = luaL_checklstring(L,1,&len1);
	const char *s2 = luaL_checklstring(L,2,&len2);
	if (len2 == 0) {
		return luaL_error(L, "Can't xor empty string");
	}
	luaL_Buffer b;
	char * buffer = luaL_buffinitsize(L, &b, len1);
	int i;
	for (i=0;i<len1;i++) {
		buffer[i] = s1[i] ^ s2[i % len2];
	}
	luaL_addsize(&b, len1);
	luaL_pushresult(&b);
	return 1;
}