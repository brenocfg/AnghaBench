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
struct buffer {int size; scalar_t__ ptr; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  scalar_t__ document ;

/* Variables and functions */
 int /*<<< orphan*/  OP_INSERT ; 
 int /*<<< orphan*/  buffer_create (struct buffer*) ; 
 int /*<<< orphan*/  buffer_destroy (struct buffer*) ; 
 int document_length (int /*<<< orphan*/ *) ; 
 int get_length (scalar_t__) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int reserve_length (struct buffer*) ; 
 int /*<<< orphan*/  write_int32 (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct buffer*,int,int) ; 
 int /*<<< orphan*/  write_string (struct buffer*,char const*,size_t) ; 

__attribute__((used)) static int
op_insert(lua_State *L) {
	size_t sz = 0;
	const char * name = luaL_checklstring(L,2,&sz);
	int dsz = document_length(L);

	luaL_Buffer b;
	luaL_buffinit(L, &b);

	struct buffer buf;
	buffer_create(&buf);
		// make package header, don't raise L error
		int len = reserve_length(&buf);
		write_int32(&buf, 0);
		write_int32(&buf, 0);
		write_int32(&buf, OP_INSERT);
		write_int32(&buf, lua_tointeger(L,1));
		write_string(&buf, name, sz);

		int total = buf.size + dsz;
		write_length(&buf, total, len);

		luaL_addlstring(&b, (const char *)buf.ptr, buf.size);
	buffer_destroy(&buf);
	
	if (lua_isuserdata(L,3)) {
		document doc = lua_touserdata(L,3);
		luaL_addlstring(&b, (const char *)doc, get_length(doc));
	} else {
		int s = lua_rawlen(L, 3);
		int i;
		for (i=1;i<=s;i++) {
			lua_rawgeti(L,3,i);
			document doc = lua_touserdata(L,-1);
			lua_pop(L,1);	// must call lua_pop before luaL_addlstring, because addlstring may change stack top
			luaL_addlstring(&b, (const char *)doc, get_length(doc));
		}
	}

	luaL_pushresult(&b);

	return 1;
}