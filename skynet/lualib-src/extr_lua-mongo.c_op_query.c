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
 int OP_QUERY ; 
 int /*<<< orphan*/  buffer_create (struct buffer*) ; 
 int /*<<< orphan*/  buffer_destroy (struct buffer*) ; 
 int get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int reserve_length (struct buffer*) ; 
 int /*<<< orphan*/  write_int32 (struct buffer*,int) ; 
 int /*<<< orphan*/  write_length (struct buffer*,int,int) ; 
 int /*<<< orphan*/  write_string (struct buffer*,char const*,size_t) ; 

__attribute__((used)) static int
op_query(lua_State *L) {
	int id = luaL_checkinteger(L,1);
	document query = lua_touserdata(L,6);
	if (query == NULL) {
		return luaL_error(L, "require query document");
	}
	document selector = lua_touserdata(L,7);
	int flags = luaL_checkinteger(L, 2);
	size_t nsz = 0;
	const char *name = luaL_checklstring(L,3,&nsz);
	int skip = luaL_checkinteger(L, 4);
	int number = luaL_checkinteger(L, 5);

	luaL_Buffer b;
	luaL_buffinit(L,&b);

	struct buffer buf;
	buffer_create(&buf);
		int len = reserve_length(&buf);
		write_int32(&buf, id);
		write_int32(&buf, 0);
		write_int32(&buf, OP_QUERY);
		write_int32(&buf, flags);
		write_string(&buf, name, nsz);
		write_int32(&buf, skip);
		write_int32(&buf, number);

		int32_t query_len = get_length(query);
		int total = buf.size + query_len;
		int32_t selector_len = 0;
		if (selector) {
			selector_len = get_length(selector);
			total += selector_len;
		}

		write_length(&buf, total, len);
		luaL_addlstring(&b, (const char *)buf.ptr, buf.size);
	buffer_destroy(&buf);

	luaL_addlstring(&b, (const char *)query, query_len);

	if (selector) {
		luaL_addlstring(&b, (const char *)selector, selector_len);
	}

	luaL_pushresult(&b);

	return 1;
}