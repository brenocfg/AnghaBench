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
typedef  int int32_t ;
typedef  int /*<<< orphan*/ * document ;

/* Variables and functions */
 int /*<<< orphan*/  OP_UPDATE ; 
 int /*<<< orphan*/  buffer_create (struct buffer*) ; 
 int /*<<< orphan*/  buffer_destroy (struct buffer*) ; 
 int get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int reserve_length (struct buffer*) ; 
 int /*<<< orphan*/  write_int32 (struct buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct buffer*,int,int) ; 
 int /*<<< orphan*/  write_string (struct buffer*,char const*,size_t) ; 

__attribute__((used)) static int
op_update(lua_State *L) {
	document selector  = lua_touserdata(L,3);
	document update = lua_touserdata(L,4);
	if (selector == NULL || update == NULL) {
		luaL_error(L, "Invalid param");
	}
	size_t sz = 0;
	const char * name = luaL_checklstring(L,1,&sz);

	luaL_Buffer b;
	luaL_buffinit(L, &b);

	struct buffer buf;
	buffer_create(&buf);
		// make package header, don't raise L error
		int len = reserve_length(&buf);
		write_int32(&buf, 0);
		write_int32(&buf, 0);
		write_int32(&buf, OP_UPDATE);
		write_int32(&buf, 0);
		write_string(&buf, name, sz);
		write_int32(&buf, lua_tointeger(L,2));

		int32_t selector_len = get_length(selector);
		int32_t update_len = get_length(update);

		int total = buf.size + selector_len + update_len;
		write_length(&buf, total, len);

		luaL_addlstring(&b, (const char *)buf.ptr, buf.size);
	buffer_destroy(&buf);

	luaL_addlstring(&b, (const char *)selector, selector_len);
	luaL_addlstring(&b, (const char *)update, update_len);

	luaL_pushresult(&b);

	return 1;
}